#include <buildx/cmake/package.hpp>

#include <fstream>
#include <print>

#include <nlohmann/json.hpp>

#include <buildx/this_build.hpp>
#include <buildx/tool/c_family.hpp>
#include <buildx/tool/ld.hpp>

namespace bx::cmake {
bool package::has_artifact() const { return false; }

std::filesystem::path package::artifact() const { return {}; }

package& package::cmake_minimum_required(const std::string& version) {
  m_cmake_version = version;
  return *this;
}

package& package::find_package(const std::string& name) {
  m_name = name;
  return *this;
}

package& package::version(const std::string& version) {
  m_version = version;
  return *this;
}

package& package::component(const std::string& name) {
  m_components.push_back(name);
  return *this;
}

package& package::components(const std::vector<std::string>& names) {
  m_components.append_range(names);
  return *this;
}

package& package::optional_component(const std::string& name) {
  m_optional.push_back(name);
  return *this;
}

package& package::optional_components(const std::vector<std::string>& names) {
  m_optional.append_range(names);
  return *this;
}

package& package::target(const std::string& name) {
  m_targets.push_back(name);
  return *this;
}

package& package::targets(const std::vector<std::string>& names) {
  m_targets.append_range(names);
  return *this;
}

void package::build_steps(step& first, step& last) {
  auto project = this_build::context.scratch_path(*this) / "cmake";
  auto build = this_build::context.scratch_path(*this) / "build";

  auto CMakeLists_txt = project / "CMakeLists.txt";
  auto main_cpp = project / "main.cpp";
  auto reply = build / ".cmake" / "api" / "v1" / "reply";

  auto write_fn = [=, this] {
    std::ofstream cmake{CMakeLists_txt};

    std::println(cmake, "cmake_minimum_required(VERSION {})", m_cmake_version);
    std::println(cmake, "project(bx_cmake_package)");
    std::println(cmake);

    std::println(cmake, "cmake_file_api(QUERY API_VERSION 1 CODEMODEL 2)");
    std::println(cmake);

    std::print(cmake, "find_package({}", m_name);
    if (m_version.size()) std::print(cmake, " {}", m_version);

    if (m_required) {
      std::print(cmake, " REQUIRED");
    } else {
      std::print(cmake, " OPTIONAL");
    }

    if (m_components.size()) {
      std::print(cmake, " COMPONENTS");
      for (const auto& name : m_components) {
        std::print(cmake, " {}", name);
      }
    }

    if (m_optional.size()) {
      std::print(cmake, " OPTIONAL_COMPONENTS");
      for (const auto& name : m_optional) {
        std::print(cmake, " {}", name);
      }
    }

    std::print(cmake, ")");

    std::println(cmake);
    std::println(cmake, "add_executable(bx main.cpp)");
    std::println(cmake);

    for (const auto& name : m_targets) {
      std::println(cmake, "target_link_libraries(bx PUBLIC {})", name);
    }

    std::ofstream main{main_cpp};
    std::println(main);
  };

  auto read_fn = [=, this] {
    using json = nlohmann::json;
    for (auto file : std::filesystem::directory_iterator(reply)) {
      auto path = file.path();
      if (path.filename().string().starts_with("target-bx-")) {
        std::ifstream fd{path};
        auto j = json::parse(fd);

        if (j.contains("compileGroups")) {
          const auto& options = j["compileGroups"];
          auto& tc = tools().as<tool::c_family>();

          for (const auto& opt : options) {
            if (opt.contains("compileCommandFragments")) {
              for (const auto& opt : opt["compileCommandFragments"]) {
                if (opt.contains("fragment")) {
                  auto flag = opt["fragment"].get<std::string>();
                  compile_flag(flag);
                }
              }
            }

            if (opt.contains("defines")) {
              for (const auto& opt : opt["defines"]) {
                if (opt.contains("define")) {
                  auto define = opt["define"].get<std::string>();
                  compile_flag(tc.to_string(tool::c_family::define(define)));
                }
              }
            }

            if (opt.contains("includes")) {
              for (const auto& opt : opt["includes"]) {
                if (opt.contains("path")) {
                  auto define = opt["path"].get<std::string>();
                  compile_flag(tc.to_string(tool::c_family::include(define)));
                }
              }
            }
          }
        }

        if (j.contains("link")) {
          const auto& options = j["link"];
          auto& tc = tools().as<tool::ld>();
          if (options.contains("commandFragments")) {
            const auto& frags = options["commandFragments"];
            for (const auto& opt : frags) {
              if (opt.contains("fragment")) {
                auto library = opt["fragment"].get<std::string>();
                link_flag(tc.to_string(tool::ld::link(library)));
              }
            }
          }
        }
      }
    }
  };

  auto& write_project = this_build::executor.make_step(write_fn)
                            .out_files({CMakeLists_txt, main_cpp})
                            .depends_on(first)
                            .message("cmake write {} project", name());

  auto& configure = this_build::executor.make_step("cmake")
                        .flag("-S")
                        .in_flag(project)
                        .flag("-B")
                        .out_flag(build)
                        .depends_on(write_project)
                        .message("cmake configure {}", name());

  auto& read =
      this_build::executor.make_step(read_fn).depends_on(configure).message(
          "cmake read {} reply", name());

  last.depends_on(read);
}
}  // namespace bx::cmake

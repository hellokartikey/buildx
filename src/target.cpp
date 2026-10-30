#include <buildx/target.hpp>

#include <buildx/library.hpp>
#include <buildx/this_build.hpp>

namespace bx {
target::target(const std::string& name) : rule(name) {}

void target::build_steps(step& first, step& last) {
  if (files().empty() and headers().empty()) {
    last.depends_on(first);
  } else {
    compile_steps(first, last);
  }
}

toolchain& target::tools() {
  if (not m_tc) {
    return this_build::context.tools();
  }
  return *m_tc;
}

const std::vector<std::filesystem::path>& target::files() const {
  return m_files;
}

const std::vector<std::filesystem::path>& target::headers() const {
  return m_headers;
}

const view<library>& target::link_libraries() const { return m_link; }

view<library> target::all_link_libraries() const {
  return std::views::concat(
             link_libraries(),
             link_libraries()
                 | std::views::transform(&target::all_link_libraries)
                 | std::views::join)
         | as_view;
}

const std::vector<std::string>& target::compile_flags() const { return m_cc; }

std::vector<std::string> target::all_compile_flags() const {
  return std::views::concat(
             compile_flags(),
             link_libraries()
                 | std::views::transform(&target::all_compile_flags)
                 | std::views::join)
         | std::ranges::to<std::vector>();
}

const std::vector<std::string>& target::link_flags() const { return m_ld; }

std::vector<std::string> target::all_link_flags() const {
  return std::views::concat(link_flags(),
                            link_libraries()
                                | std::views::transform(&target::all_link_flags)
                                | std::views::join)
         | std::ranges::to<std::vector>();
}

const std::vector<std::string>& target::archive_flags() const { return m_ar; }

std::vector<std::string> target::all_archive_flags() const {
  return std::views::concat(
             archive_flags(),
             link_libraries()
                 | std::views::transform(&target::all_archive_flags)
                 | std::views::join)
         | std::ranges::to<std::vector>();
}
}  // namespace bx

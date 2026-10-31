#include <buildx/library.hpp>

#include <buildx/this_build.hpp>
#include <buildx/tool/archiver.hpp>
#include <buildx/tool/compiler.hpp>
#include <buildx/tool/linker.hpp>
#include <buildx/view.hpp>

namespace bx {
std::filesystem::path library::artifact() const {
  auto base = this_build::context.library_path();
  if (m_shared) {
    return base / std::format("lib{}.so", name());
  }
  return base / std::format("lib{}.a", name());
}

bool library::is_shared() const { return m_shared; }

void library::build_steps(step& first, step& last) {
  if (files().empty()) throw no_source(*this);

  if (m_shared)
    compile_shared(first, last);
  else
    compile_archive(first, last);
}

void library::compile_shared(step& first, step& last) {
  auto compile = [&](const std::filesystem::path& file) -> step& {
    return tools()
        .as<tool::compiler>()
        .compile_shared(*this, file, all_compile_flags())
        .depends_on(first);
  };

  auto steps = files() | std::views::transform(compile) | as_view;

  auto objects = steps
                 | std::views::transform([](auto& s) { return s.out_files(); })
                 | std::views::join
                 | std::ranges::to<std::vector>();

  auto& link =
      tools()
          .as<tool::linker>()
          .link_shared(*this, objects, all_link_libraries(), all_link_flags())
          .depends_on(steps);

  last.depends_on(link);
}

void library::compile_archive(step& first, step& last) {
  auto compile = [&](const std::filesystem::path& file) -> step& {
    return tools()
        .as<tool::compiler>()
        .compile(*this, file, all_compile_flags())
        .depends_on(first);
  };

  auto steps = files() | std::views::transform(compile) | as_view;

  auto objects = steps
                 | std::views::transform([](auto& s) { return s.out_files(); })
                 | std::views::join
                 | std::ranges::to<std::vector>();

  auto& link =
      tools()
          .as<tool::archiver>()
          .archive(*this, objects, link_libraries(), all_archive_flags())
          .depends_on(steps);

  last.depends_on(link);
}
}  // namespace bx

#include <buildx/executable.hpp>

#include <ranges>

#include <buildx/static_tool.hpp>
#include <buildx/this_build.hpp>

namespace bx {
executable::executable(const std::string& name) : target(name) {}

std::filesystem::path executable::artifact() const {
  return this_build::context.binary_path() / name();
}

command& executable::run() {
  return this_build::context.add<command>(std::format("run_{}", name()))
      .executable(artifact())
      .message("running executable {}", name())
      .depends_on(*this);
}

void executable::compile_steps(step& first, step& last) {
  auto compile = [&](const std::filesystem::path& file) -> step& {
    return tools()
        .as<static_tool>()
        .compile_static(*this, file)
        .depends_on(first);
  };

  auto steps = files() | std::views::transform(compile) | as_view;

  auto objects = steps
                 | std::views::transform([](auto& s) { return s.out_files(); })
                 | std::views::join
                 | std::ranges::to<std::vector>();

  auto& link = tools()
                   .as<static_tool>()
                   .link_static(*this, objects, all_link_libraries())
                   .depends_on(steps);

  last.depends_on(link);
}
}  // namespace bx

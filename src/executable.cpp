#include <buildx/executable.hpp>

#include <ranges>

#include <buildx/this_build.hpp>

namespace bx {
executable::executable(const std::string& name) : target(name) {}

std::filesystem::path executable::artifact() const {
    return this_build::context.binary_path() / name();
}

void executable::compile_steps(step& first, step& last) const {
    auto compile = [&] (const std::filesystem::path& file) -> step& {
        return toolchain()
            .compile_static(*this, file)
            .depends_on(first);
    };

    auto steps = files()
        | std::views::transform(compile)
        | as_view;

    auto objects = steps
        | std::views::transform([] (auto& s) { return s.out_files(); })
        | std::views::join
        | std::ranges::to<std::vector>();

    auto& link = toolchain()
        .link_static(*this, objects, all_link_libraries())
        .depends_on(steps);

    last.depends_on(link);
}
}

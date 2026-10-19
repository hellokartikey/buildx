#include <buildx/executable.hpp>

#include <ranges>

#include <buildx/this_build.hpp>

namespace bx {
executable::executable(const std::string& name) : target(name) {}

std::filesystem::path executable::artifact() const {
    return this_build::context.binary_path() / name();
}

void executable::compile_steps(step& first, step& last) const {
    auto& ctx = this_build::context;

    auto compile = [&] (const std::filesystem::path& file) {
        return &tc().compile_static(*this, file);
    };

    auto steps = files()
        | std::views::transform(compile)
        | std::ranges::to<std::vector>();

    auto objects = steps
        | std::views::transform([] (auto* s) { return s->out_files(); })
        | std::views::join
        | std::ranges::to<std::vector>();

    auto& link = tc()
        .link_static(*this, objects)
        .depends_on(first);

    for (auto* step : steps) { link.depends_on(*step); }
}
}

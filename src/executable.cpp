#include <buildx/executable.hpp>

#include <ranges>

#include <buildx/this_build.hpp>

namespace bx {
executable::executable(const std::string& name) : target(name) {}

void executable::compile_steps(step& first, step& last) const {
    auto& ctx = this_build::context;

    std::vector<step*> objects;
    for (auto& file : files()) {
        auto output =
            ctx.scratch_path(*this)
            / std::filesystem::relative(file, ctx.root());

        output.replace_extension(".o");

        auto& step = tc()
            .compile_static(file, output)
            .depends_on(first);

        objects.push_back(&step);
    }

    auto& link = tc()
        .link_static(
            objects
            | std::views::transform([] (auto* s) { return s->out_files(); })
            | std::views::join
            | std::ranges::to<std::vector>(),
            ctx.binary_path() / name());

    for (auto* object : objects) { link.depends_on(*object); }
}
}

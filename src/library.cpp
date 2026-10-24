#include <buildx/library.hpp>

#include <buildx/this_build.hpp>
#include <buildx/view.hpp>

namespace bx {
library::library(const std::string& name) : target(name) {}

std::filesystem::path library::artifact() const {
    auto base = this_build::context.library_path();
    if (m_shared) { return base / std::format("lib{}.so", name()); }
    return base / std::format("lib{}.a", name());
}

bool library::is_shared() const { return m_shared; }

void library::compile_steps(step& first, step& last) {
    if (m_shared) compile_shared(first, last);
    else compile_archive(first, last);
}

void library::compile_shared(step& first, step& last) const {
    auto compile = [&] (const std::filesystem::path& file) -> step& {
        return tools()
            .compile_shared(*this, file)
            .depends_on(first);
    };

    auto steps = files()
        | std::views::transform(compile)
        | as_view;

    auto objects = steps
        | std::views::transform([] (auto& s) { return s.out_files(); })
        | std::views::join
        | std::ranges::to<std::vector>();

    auto& link = tools()
        .link_shared(*this, objects, link_libraries())
        .depends_on(steps);

    last.depends_on(link);
}

void library::compile_archive(step& first, step& last) const {
    auto compile = [&] (const std::filesystem::path& file) -> step& {
        return tools()
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

    auto& link = tools()
        .link_archive(*this, objects, link_libraries())
        .depends_on(steps);

    last.depends_on(link);
}
}

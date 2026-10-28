#include <buildx/build.hpp>

void bx::build(context& ctx) {
    auto& foo = ctx
        .add<library>("foo")
        .files_in(ctx.path("src"), { "foo.cpp" })
        .use<clang>(std::in_place, clang::define("FOO"));

    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "bar.cpp", "main.cpp" })
        .link(foo)
        .use<clangxx>(std::in_place, clang::define("FOO"));

    auto& run = main.run();

    ctx.install(run);
}

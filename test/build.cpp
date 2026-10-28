#include <buildx/build.hpp>

void bx::build(context& ctx) {
    ctx.use<clangxx>();

    auto& foo = ctx
        .add<library>("foo")
        .files_in(ctx.path("src"), { "foo.cpp" });

    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "bar.cpp", "main.cpp" })
        .link(foo);

    auto& run = main.run();

    ctx.install(run);
}

#include <buildx/build.hpp>

void bx::build(context& ctx) {
    ctx.use<gxx>();

    auto& fmt = ctx.add<system::library>("fmt");

    auto& foo = ctx
        .add<library>("foo")
        .shared()
        .files_in(ctx.path("src"), { "foo.cpp" });

    auto& bar = ctx
        .add<library>("bar")
        .link(foo)
        .files_in(ctx.path("src"), { "bar.cpp" });

    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "main.cpp" })
        .link(foo, bar, fmt);

    auto& run = main.run();

    ctx.install(run);
}

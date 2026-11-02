#include <buildx/build.hpp>

void bx::build(context& ctx) {
    auto& raylib = ctx
        .add<cmake::package>("raylib")
        .find_package("raylib")
        .target("raylib");

    auto& main = ctx
        .add<executable>("main")
        .file(ctx.path("src") / "main.c")
        .link(raylib);

    auto& run = main.run();

    ctx.use<gcc>();
    ctx.install(run);
}

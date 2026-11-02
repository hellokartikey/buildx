#include <buildx/build.hpp>

void bx::build(context& ctx) {
    auto& main = ctx
        .add<executable>("main")
        .file(ctx.path("src") / "main.cpp");

    auto& run = main.run();

    ctx.use<gxx>(std::in_place, gxx::std(23));
    ctx.install(run);
}

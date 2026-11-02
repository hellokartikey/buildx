#include <buildx/build.hpp>

void bx::build(context& ctx) {
    ctx.use<gxx>();

    auto& fmt = ctx
        .add<cmake::package>("fmt")
        .find_package("fmt")
        .target("fmt::fmt");

    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "main.cpp" , "foo.cpp", "bar.cpp" })
        .link(fmt);

    auto& run = main.run();

    ctx.install(run);
}

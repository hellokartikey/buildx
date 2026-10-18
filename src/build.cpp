#include <buildx/build.hpp>

#include <buildx/this_build.hpp>
#include <buildx/executable.hpp>
#include <buildx/gcc.hpp>

void bx::build() {
    auto& ctx = this_build::context;

    auto& exe = ctx
        .add<executable>("test")
        .file(ctx.path("test") / "main.c")
        .use<tc::gcc>();

    ctx.install(exe);
}

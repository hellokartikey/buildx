#include <buildx/build.hpp>

#include <buildx/this_build.hpp>
#include <buildx/executable.hpp>
#include <buildx/gcc.hpp>

void bx::build() {
    auto& ctx = this_build::context;

    auto& exe = ctx
        .add<executable>("test")
        .file(ctx.path("test") / "main.c")
        .file(ctx.path("test") / "foo.c")
        .use<tc::gcc>(tc::gcc::std(23), tc::gcc::prefix("x86_64-linux-gnu-"));

    ctx.install(exe);
}

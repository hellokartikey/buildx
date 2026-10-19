#include <buildx/build.hpp>

#include <buildx/this_build.hpp>
#include <buildx/executable.hpp>
#include <buildx/gcc.hpp>

void bx::build() {
    auto& ctx = this_build::context;

    auto cc = gcc(gcc::flags, gcc::std(23), gcc::prefix("x86_64-linux-gnu-"));

    auto& exe = ctx
        .add<executable>("test")
        .file(ctx.path("test") / "main.c")
        .file(ctx.path("test") / "foo.c")
        .use(cc);

    ctx.install(exe);
}

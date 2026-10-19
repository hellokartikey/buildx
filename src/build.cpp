#include <buildx/build.hpp>

#include <buildx/executable.hpp>
#include <buildx/gcc.hpp>

void bx::build(context& ctx) {
    auto cc = gcc{
        gcc::flags,
        gcc::std(23),
        gcc::prefix("x86_64-linux-gnu-"),
        gcc::define("FOO")
    };

    auto& exe = ctx
        .add<executable>("test")
        .files_in(ctx.path("test"), { "main.c", "foo.c" })
        .use(cc);

    ctx.install(exe);
}

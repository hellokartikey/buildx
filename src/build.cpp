#include <buildx/build.hpp>

#include <buildx/executable.hpp>
#include <buildx/gcc.hpp>
#include <buildx/library.hpp>

void bx::build(context& ctx) {
    auto cc = gcc{
        gcc::flags,
        gcc::std(23),
        gcc::prefix("x86_64-linux-gnu-"),
        gcc::define("FOO")
    };

    auto& bar = ctx
        .add<library>("bar")
        .shared(true)
        .files_in(ctx.path("test"), { "bar.c" })
        .use(cc);

    auto& foo = ctx
        .add<library>("foo")
        .files_in(ctx.path("test"), { "foo.c" })
        .link(bar)
        .use(cc);

    auto& exe = ctx
        .add<executable>("test")
        .files_in(ctx.path("test"), { "main.c" })
        .link(foo)
        .use(cc);

    ctx.install(exe);
}

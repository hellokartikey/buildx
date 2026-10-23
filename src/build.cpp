#include <buildx/build.hpp>

#include <buildx/executable.hpp>
#include <buildx/gxx.hpp>
#include <buildx/library.hpp>

void bx::build(context& ctx) {
    auto cxx = gxx{
        gxx::flags,
        gxx::std(23),
        gxx::prefix("x86_64-linux-gnu-"),
        gxx::define("FOO")
    };

    auto& bar = ctx
        .add<library>("bar")
        .shared(true)
        .files_in(ctx.path("test"), { "bar.c" })
        .use(cxx);

    auto& foo = ctx
        .add<library>("foo")
        .files_in(ctx.path("test"), { "foo.c" })
        .link(bar)
        .use(cxx);

    auto& exe = ctx
        .add<executable>("test")
        .files_in(ctx.path("test"), { "main.c" })
        .link(foo)
        .use(cxx);

    ctx.install(exe);
}

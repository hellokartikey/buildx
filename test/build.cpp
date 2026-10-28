#include <buildx/build.hpp>

#include <buildx/executable.hpp>
#include <buildx/library.hpp>
#include <buildx/gcc.hpp>

void bx::build(context& ctx) {
    auto cc = gcc{
        gcc::define("FOO")
    };

    auto& foo = ctx
        .add<library>("foo")
        .files_in(ctx.path("src"), { "foo.c" })
        .use(cc);

    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "bar.c", "main.c" })
        .link(foo)
        .use(cc);

    auto& run = main.run();

    ctx.install(run);
}

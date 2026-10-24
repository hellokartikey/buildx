#include <buildx/build.hpp>

#include <buildx/executable.hpp>
#include <buildx/gcc.hpp>

void bx::build(context& ctx) {
    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "foo.c", "bar.c", "main.c" })
        .use<gcc>();

    ctx.install(main);
}

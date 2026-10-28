#include <buildx/build.hpp>

void bx::build(context& ctx) {
    using tc = tool::stack<tool::clang_cxx, tool::gnu_ar>;
    ctx.use<tc>();

    auto& foo = ctx
        .add<library>("foo")
        .files_in(ctx.path("src"), { "foo.cpp" });

    auto& main = ctx
        .add<executable>("main")
        .files_in(ctx.path("src"), { "bar.cpp", "main.cpp" })
        .link(foo);

    auto& run = main.run();

    ctx.install(run);
}

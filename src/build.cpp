#include <buildx/build.hpp>

#include <buildx/this_build.hpp>

void bx::build() {
    auto& ctx = this_build::executor;

    auto& first = ctx
        .make_step("echo")
        .flag("Hello, World!")
        .message("first")
        ;

    auto& sleep = ctx
        .make_step("sleep")
        .message("sleep")
        .flag("5")
        ;

    auto& second = ctx
        .make_step("echo")
        .message("echo")
        .flag("Bye, World!")
        .depends_on(sleep, first)
        ;
}

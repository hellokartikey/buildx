#include <buildx/build.hpp>

#include <buildx/this_build.hpp>

void bx::build() {
    auto& exec = this_build::executor;
    auto& ctx = this_build::context;

    auto& first = exec
        .make_step("echo")
        .flag("Hello, World!")
        .message("first")
        ;

    auto& sleep = exec
        .make_step("sleep")
        .message("sleep")
        .flag("5")
        ;

    auto& second = exec
        .make_step("echo")
        .message("echo")
        .flag("Bye, World!")
        .depends_on(sleep, first)
        ;
}

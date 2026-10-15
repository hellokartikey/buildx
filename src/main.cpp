#include <print>

#include <boost/cobalt/main.hpp>

#include <buildx/this_build.hpp>

boost::cobalt::main co_main(int argc, char** argv) {
    try {
        auto& first = bx::this_build::executor
            .make_step("echo")
            .flag("Hello, World!");

        auto& sleep = bx::this_build::executor
            .make_step("sleep")
            .flag("5");

        auto& second = bx::this_build::executor
            .make_step("echo")
            .flag("Bye, World!")
            .depends_on(sleep, first);

        co_await bx::this_build::executor.async_exec();
    } catch (bx::error& e) {
        std::println(stderr, "buildx error: {}", e.what());
        co_return 1;
    } catch (std::exception& e) {
        std::println(stderr, "error: {}", e.what());
        co_return 2;
    }

    std::println("done!");
    co_return 0;
}

#include <print>

#include <boost/cobalt/main.hpp>

#include <buildx/step.hpp>

boost::cobalt::main co_main(int argc, char** argv) {
    bx::step step("echo");
    step.flag("Hello, World!");

    bx::step step2("asljdladj");

    co_await step.async_exec();
    co_await step2.async_exec();

    std::println("done!");

    co_return 0;
}

#include <print>

#include <boost/cobalt/main.hpp>

#include <buildx/build.hpp>
#include <buildx/this_build.hpp>

boost::cobalt::main co_main(int argc, char** argv) {
    try {
        bx::build();
        bx::this_build::executor.exec_all();
    } catch (bx::error& e) {
        std::println(stderr, "[-] buildx error: {}", e.what());
        co_return 1;
    } catch (std::exception& e) {
        std::println(stderr, "[-] error: {}", e.what());
        co_return 2;
    }

    std::println("done!");
    co_return 0;
}

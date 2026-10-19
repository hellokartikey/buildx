#include <print>

#include <boost/cobalt/main.hpp>

#include <buildx/build.hpp>
#include <buildx/this_build.hpp>

namespace cobalt = boost::cobalt;

cobalt::main co_main(int argc, char** argv) {
    using namespace bx;

    auto& ctx = this_build::context;
    auto& exec = this_build::executor;

    try {
        build(ctx);
        exec.build_steps(ctx.install());
        exec.exec_all();
    } catch (error& e) {
        std::println(stderr, "[-] buildx error: {}", e.what());
        co_return 1;
    } catch (std::exception& e) {
        std::println(stderr, "[-] error: {}", e.what());
        co_return 2;
    }

    std::println("done!");
    co_return 0;
}

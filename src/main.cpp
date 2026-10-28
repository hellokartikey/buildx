#include <buildx/build.hpp>

#include <print>

#include <buildx/this_build.hpp>

int main(int argc, char** argv) {
  using namespace bx;

  auto& ctx = this_build::context;
  auto& exec = this_build::executor;

  try {
    ctx.parse(argc, argv);
    build(ctx);
    exec.build_steps(ctx.install());
    exec.exec_all();
  } catch (error& e) {
    std::println(stderr, "[-] buildx error: {}", e.what());
    return 1;
  } catch (std::exception& e) {
    std::println(stderr, "[-] error: {}", e.what());
    return 2;
  }

  return 0;
}

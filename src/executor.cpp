#include <buildx/executor.hpp>

#include <algorithm>
#include <print>
#include <ranges>

#include <boost/cobalt/join.hpp>
#include <boost/cobalt/run.hpp>
#include <boost/cobalt/task.hpp>

#define BOOST_PROCESS_USE_STD_FS
#include <boost/process/environment.hpp>
#include <boost/process/process.hpp>

#include <buildx/this_build.hpp>

using boost::process::environment::find_executable;

namespace bx {
executor::executor(std::uint64_t concurrency) : m_concurrency(concurrency) {}

step& executor::make_step() { return m_steps.emplace_back(m_steps.size()); }

step& executor::make_step(const std::string& exe) {
  return m_steps.emplace_back(m_steps.size(), exe);
}

step& executor::operator[](std::uint64_t id) {
  return *std::ranges::find_if(
      m_steps, [=](const auto& step) { return step.m_id == id; });
}

const step& executor::operator[](std::uint64_t id) const {
  return *std::ranges::find_if(
      m_steps, [=](const auto& step) { return step.m_id == id; });
}

std::uint64_t executor::concurrency() const { return m_concurrency; }

executor& executor::concurrency(std::uint64_t concurrency) {
  m_concurrency = concurrency;
  return *this;
}

void executor::exec_all() {
  namespace cobalt = boost::cobalt;
  auto async_exec = [](step& step) -> cobalt::task<int> {
    if (not step.is_ready()) throw step::pending_dependencies(step);
    if (not step.message().empty()) std::println("[+] {}", step.message());
    if (step.is_phony()) co_return step.m_rc = 0;

    for (auto& out : step.out_files()) {
      if (auto dir = out.parent_path(); !std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
      }
    }

    if (this_build::context.verbose()) {
      std::print(stderr, "{} ", step.executable());
      for (auto& flag : step.flags()) std::print(stderr, "{} ", flag);
      std::println(stderr);
    }

    auto executable = find_executable(step.executable());
    if (executable.empty()) throw step::executable_not_found(step.executable());

    auto process = boost::process::process(
        co_await boost::cobalt::this_coro::executor, executable, step.flags());

    step.m_rc = co_await process.async_wait(boost::cobalt::use_task);
    if (step.rc() != 0) throw step::execution_error(step);
    co_return step.rc();
  };

  auto join = [](auto&& tasks) -> cobalt::task<void> {
    co_await cobalt::join(tasks);
  };

  while (not std::ranges::all_of(m_steps, &step::is_done)) {
    cobalt::run(join(m_steps
                     | std::views::filter(std::not_fn(&step::is_done))
                     | std::views::filter(&step::is_ready)
                     | std::views::take(concurrency())
                     | std::views::transform(async_exec)
                     | std::ranges::to<std::vector>()));
  }
}

void executor::build_steps(rule& rule) {
  rule.build_all_steps(make_step(), make_step());
}
}  // namespace bx

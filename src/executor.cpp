#include <buildx/executor.hpp>

#include <algorithm>
#include <ranges>
#include <print>

#include <boost/cobalt/run.hpp>
#include <boost/cobalt/join.hpp>
#include <boost/cobalt/task.hpp>

#define BOOST_PROCESS_USE_STD_FS
#include <boost/process/process.hpp>

namespace bx {
executor::executor(std::uint64_t concurrency) : m_concurrency(concurrency) {}

step& executor::make_step() { return m_steps.emplace_back(m_steps.size()); }

step& executor::make_step(const std::string& exe) {
    return m_steps.emplace_back(m_steps.size(), exe);
}

step& executor::operator[](std::uint64_t id) {
    return *std::ranges::find_if(
        m_steps,
        [=] (const auto& step) { return step.m_id == id; }
    );
}

const step& executor::operator[](std::uint64_t id) const {
    return *std::ranges::find_if(
        m_steps,
        [=] (const auto& step) { return step.m_id == id; }
    );
}

std::uint64_t executor::concurrency() const { return m_concurrency; }

executor& executor::concurrency(std::uint64_t concurrency) {
    m_concurrency = concurrency;
    return *this;
}

void executor::exec_all() {
    namespace cobalt = boost::cobalt;
    auto async_exec = [] (step& step) -> cobalt::task<int> {
        if (not step.is_ready()) throw step::pending_dependencies(step);
        if (not step.m_message.empty()) std::println("[+] {}", step.m_message);
        if (step.is_phony()) co_return step.m_rc = 0;

        auto process = boost::process::process(
            co_await boost::cobalt::this_coro::executor,
            step.m_exe,
            step.m_flags
        );

        step.m_rc = co_await process.async_wait(boost::cobalt::use_task);
        if (step.rc() != 0) throw step::execution_error(step);
        co_return step.rc();
    };

    auto join = [] (auto&& tasks) -> cobalt::task<void> {
        co_await cobalt::join(tasks);
    };

    while (not std::ranges::all_of(m_steps, &step::is_done)) {
        boost::cobalt::run(
            join(
                m_steps
                    | std::views::filter(std::not_fn(&step::is_done))
                    | std::views::filter(&step::is_ready)
                    | std::views::take(concurrency())
                    | std::views::transform(async_exec)
                    | std::ranges::to<std::vector>()
            )
        );
    }
}

void executor::build_steps(const rule& rule) {
    rule.build_all_steps(make_step(), make_step());
}
}

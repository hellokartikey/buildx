#include <buildx/executor.hpp>

#include <algorithm>
#include <ranges>

#include <boost/cobalt/join.hpp>

namespace bx {
executor::executor(std::uint64_t concurrency) : m_concurrency(concurrency) {}

step& executor::make_step() { return m_steps.emplace_back(m_steps.size()); }

step& executor::make_step(const std::string& exe) {
    return m_steps.emplace_back(m_steps.size(), exe);
}

step& executor::operator[](std::uint64_t id) {
    return *std::ranges::find_if(
        m_steps,
        [=] (const auto& step) { return step.id() == id; }
    );
}

const step& executor::operator[](std::uint64_t id) const {
    return *std::ranges::find_if(
        m_steps,
        [=] (const auto& step) { return step.id() == id; }
    );
}

std::uint64_t executor::concurrency() const { return m_concurrency; }

executor& executor::concurrency(std::uint64_t concurrency) {
    m_concurrency = concurrency;
    return *this;
}

executor::task executor::async_exec() {
    while (not std::ranges::all_of(m_steps, &step::is_done)) {
        co_await boost::cobalt::join(
            m_steps
                | std::views::filter(std::not_fn(&step::is_done))
                | std::views::filter(&step::is_ready)
                | std::views::take(concurrency())
                | std::views::transform(&step::async_exec)
                | std::ranges::to<std::vector>()
        );
    }
}
}

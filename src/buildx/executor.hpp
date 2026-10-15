#ifndef BUILDX_EXECUTOR_HPP
#define BUILDX_EXECUTOR_HPP

#include <list>

#include <buildx/step.hpp>

namespace bx {
class executor {
public:
    using task = boost::cobalt::task<void>;

    executor(std::uint64_t concurrency = 1);
    ~executor() = default;

    executor(const executor&) = delete;
    executor& operator=(const executor&) = delete;

    executor(executor&&) = delete;
    executor& operator=(executor&&) = delete;

    step& make_step();
    step& make_step(const std::string& exe);

    step& operator[](std::uint64_t id);
    const step& operator[](std::uint64_t id) const;

    std::uint64_t concurrency() const;
    executor& concurrency(std::uint64_t concurrency);

    task async_exec();

private:
    std::list<step> m_steps;
    std::uint64_t m_concurrency;
};
}

#endif

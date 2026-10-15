#include <buildx/step.hpp>

#include <algorithm>
#include <filesystem>

#define BOOST_PROCESS_USE_STD_FS
#include <boost/process/process.hpp>
#include <boost/process/environment.hpp>

using boost::process::environment::find_executable;

namespace bx {
step::step(std::uint64_t id) : m_id(id), m_phony(true) {}

step::step(std::uint64_t id, const std::string& exe)
    : m_id(id)
    , m_phony(false)
    , m_exe(find_executable(exe)) {
    if (m_exe.empty()) throw executable_not_found(exe);
}

bool step::is_phony() const { return m_phony; }

bool step::is_done() const { return m_rc != -1; }

bool step::is_ready() const {
    auto iter =  std::ranges::find_if_not(m_depends, &step::is_done);
    return iter == m_depends.end();
}

bool step::is_direct_dependency(const step& other) const {
    return std::ranges::find(m_depends, &other) != m_depends.end();
}

bool step::is_dependency(const step& other) const {
    if (is_direct_dependency(other)) return true;
    return std::ranges::any_of(
        m_depends,
        [&] (const auto* step) { return step->is_dependency(other); }
    );
}

std::uint64_t step::id() const { return m_id; }

const std::filesystem::path& step::exe() const { return m_exe; }

const std::vector<std::string>& step::flags() const { return m_flags; }

step& step::flag(const std::string& flag) {
    m_flags.push_back(flag);
    return *this;
}

step& step::flags(const std::vector<std::string>& flags) {
    m_flags.append_range(flags);
    return *this;
}

step& step::depends_on(const step& other) {
    if (other.is_dependency(*this)) throw cycle_detected(*this, other);
    m_depends.push_back(&other);
    return *this;
}

int step::rc() const { return m_rc; }

step::task step::async_exec() {
    if (not is_ready()) throw pending_dependencies(*this);

    if (is_phony()) co_return 0;

    auto process = boost::process::process(
        co_await boost::cobalt::this_coro::executor,
        exe(),
        flags()
    );

    m_rc = co_await process.async_wait(boost::cobalt::use_task);

    if (m_rc != 0) throw execution_error(*this);

    co_return m_rc;
}

step::executable_not_found::executable_not_found(const std::string exe)
    : error("executable {:?} not found.", exe) {}

step::cycle_detected::cycle_detected(const step& parent, const step& child)
    : error(
        "cycle detected from {:?} to {:?}.",
        parent.exe().string(),
        child.exe().string()
    ) {}

step::pending_dependencies::pending_dependencies(const step& step)
    : error("{:?} dependencies are still pending.", step.exe().string()) {}

step::execution_error::execution_error(const step& step)
    : error("{:?} returned code {}.", step.exe().string(), step.rc()) {}
}

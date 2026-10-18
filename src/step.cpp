#include <buildx/step.hpp>

#include <algorithm>
#include <filesystem>

#define BOOST_PROCESS_USE_STD_FS
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

step& step::flag(const std::string& flag) {
    m_flags.push_back(flag);
    return *this;
}

step& step::flags(const std::vector<std::string>& flags) {
    m_flags.append_range(flags);
    return *this;
}

step& step::message(const std::string& message) {
    m_message = message;
    return *this;
}

step& step::depends_on(const step& other) {
    if (other.is_dependency(*this)) throw cycle_detected(*this, other);
    m_depends.push_back(&other);
    return *this;
}

step& step::in_file(const std::filesystem::path& file) {
    m_in.push_back(file);
    return *this;
}

step& step::in_files(const std::vector<std::filesystem::path>& files) {
    m_in.append_range(files);
    return *this;
}

const std::vector<std::filesystem::path>& step::in_files() const {
    return m_in;
}

step& step::out_file(const std::filesystem::path& file) {
    m_out.push_back(file);
    return *this;
}

step& step::out_files(const std::vector<std::filesystem::path>& files) {
    m_out.append_range(files);
    return *this;
}

const std::vector<std::filesystem::path>& step::out_files() const {
    return m_out;
}

int step::rc() const { return m_rc; }

step::executable_not_found::executable_not_found(const std::string exe)
    : error("executable {:?} not found.", exe) {}

step::cycle_detected::cycle_detected(const step& parent, const step& child)
    : error(
        "cycle detected from {:?} to {:?}.",
        parent.m_exe.string(),
        child.m_exe.string()
    ) {}

step::pending_dependencies::pending_dependencies(const step& step)
    : error(
        "{:?} dependencies are still pending.",
        step.m_exe.string()
    ) {}

step::execution_error::execution_error(const step& step)
    : error(
        "{:?} returned code {}.",
        step.m_exe.string(),
        step.rc()
    ) {}
}

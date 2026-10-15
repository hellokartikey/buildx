#ifndef BUILDX_STEP_HPP
#define BUILDX_STEP_HPP

#include <filesystem>
#include <string>
#include <vector>

#include <buildx/exceptions.hpp>

#include <boost/cobalt/task.hpp>

namespace bx {
class step {
public:
    class executable_not_found : public error {
    public:
        executable_not_found(const std::string exe);
    };

    class cycle_detected : public error {
    public:
        cycle_detected(const step& parent, const step& other);
    };

    class pending_dependencies : public error {
    public:
        pending_dependencies(const step& step);
    };

    class execution_error : public error {
    public:
        execution_error(const step& step);
    };

    using task = boost::cobalt::task<int>;

    step(std::uint64_t id);
    step(std::uint64_t id, const std::string& exe);

    ~step() = default;

    step(const step&) = delete;
    step& operator=(const step&) = delete;

    step(step&&) = delete;
    step& operator=(step&&) = delete;

    bool is_phony() const;
    bool is_done() const;
    bool is_ready() const;

    bool is_direct_dependency(const step& other) const;
    bool is_dependency(const step& other) const;

    std::uint64_t get_id() const;
    const std::filesystem::path& get_executable() const;
    const std::vector<std::string>& get_flags() const;
    const std::string& get_message() const;

    step& flag(const std::string& flag);
    step& flags(const std::vector<std::string>& flags);

    step& message(const std::string& message);

    template <typename... T>
    step& depends_on(const T&... others) { return (depends_on(others), ...); }
    step& depends_on(const step& other);

    int rc() const;
    task async_exec();

private:
    std::uint64_t m_id{};
    std::vector<const step*> m_depends;

    std::filesystem::path m_exe;
    std::vector<std::string> m_flags;

    std::string m_message;

    int m_rc = -1;
    bool m_phony{};
};
}

#endif

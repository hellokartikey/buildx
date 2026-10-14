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

    using async_rc = boost::cobalt::task<int>;

    step();
    step(const std::string& exe);

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

    const std::filesystem::path& exe() const;
    const std::vector<std::string>& flags() const;

    step& flag(const std::string& flag);
    step& flags(const std::vector<std::string>& flags);

    step& depends_on(step& other);

    int rc() const;
    async_rc async_exec();

private:
    std::vector<const step*> m_depends;

    std::filesystem::path m_exe;
    std::vector<std::string> m_flags;

    int m_rc = -1;
    bool m_phony;
};
}

#endif

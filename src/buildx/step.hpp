#ifndef BUILDX_STEP_HPP
#define BUILDX_STEP_HPP

#include <filesystem>
#include <string>
#include <vector>

#include <buildx/exceptions.hpp>
#include <buildx/view.hpp>

namespace bx {
class executor;
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

    friend class executor;

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

    const std::filesystem::path& executable() const;

    step& flag(const std::string& flag);
    step& flags(const std::vector<std::string>& flags);
    const std::vector<std::string>& flags() const;

    template <typename... Args>
    step& message(std::format_string<Args...> fmt, Args&&... args) {
        message(std::format(fmt, std::forward<Args>(args)...));
        return *this;
    }

    step& message(const std::string& message);
    const std::string& message() const;

    step& depends_on(const step& other);
    step& depends_on(const view<step>& others);

    step& in_file(const std::filesystem::path& file);
    step& in_files(const std::vector<std::filesystem::path>& files);
    const std::vector<std::filesystem::path>& in_files() const;

    step& in_flag(const std::filesystem::path& file);
    step& in_flags(const std::vector<std::filesystem::path>& files);

    step& out_file(const std::filesystem::path& file);
    step& out_files(const std::vector<std::filesystem::path>& files);
    const std::vector<std::filesystem::path>& out_files() const;

    step& out_flag(const std::filesystem::path& file);
    step& out_flags(const std::vector<std::filesystem::path>& files);

    int rc() const;

private:
    std::uint64_t m_id{};
    std::vector<const step*> m_depends;

    std::filesystem::path m_exe;
    std::vector<std::string> m_flags;

    std::vector<std::filesystem::path> m_in;
    std::vector<std::filesystem::path> m_out;

    std::string m_message;

    int m_rc = -1;
    bool m_phony{};
};
}

#endif

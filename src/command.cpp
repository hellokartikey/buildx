#include <buildx/command.hpp>

#include <buildx/this_build.hpp>

namespace bx {
command::command(const std::string& name) : rule(name) {}

command& command::executable(const std::string& exe) {
    m_exe = exe;
    return *this;
}

const std::string& command::executable() const { return m_exe; }

command& command::flag(const std::string& flag) {
    m_args.push_back(flag);
    return *this;
}

command& command::flags(const std::vector<std::string>& flags) {
    m_args.append_range(flags);
    return *this;
}

const std::vector<std::string>& command::flags() const { return m_args; }

command& command::message(const std::string& message) {
    m_message = message;
    return *this;
}

const std::string& command::message() const { return m_message; }

void command::build_steps(step& first, step& last) {
    auto& step = this_build::executor
        .make_step(m_exe)
        .flags(m_args)
        .message(m_message)
        .depends_on(first);

    last.depends_on(step);
}
}

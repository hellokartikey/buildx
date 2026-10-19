#include <buildx/target.hpp>

namespace bx {
target::target(const std::string& name) : rule(name) {}

void target::build_steps(step& first, step& last) const {
    if (not m_tc) throw no_toolchain(*this);

    if (files().empty() and headers().empty()) {
        last.depends_on(first);
    } else {
        compile_steps(first, last);
    }
}

const toolchain& target::tc() const {
    if (not m_tc) throw no_toolchain(*this);
    return *m_tc;
}

target::no_toolchain::no_toolchain(const target& target)
    : error("no toolchain provided for target {:?}", target.name()) {}
}

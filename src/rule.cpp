#include "buildx/rule.hpp"

#include <algorithm>

#include <buildx/exceptions.hpp>
#include <buildx/this_build.hpp>

namespace bx {
rule::rule(const std::string& name) : m_name(name) {}

const std::string& rule::name() const { return m_name; }

bool rule::is_direct_dependency(const rule& other) const {
    return std::ranges::find(m_depends, &other) != m_depends.end();
}

bool rule::is_dependency(const rule& other) const {
    if (is_direct_dependency(other)) return true;
    return std::ranges::any_of(
            m_depends,
            [&] (const auto* r) { return r->is_dependency(other); });
}

void rule::build_all_steps(step& first, step& last) {
    build_steps(first, last);
    for (auto* dep : m_depends) {
        auto& new_step = this_build::executor.make_step();
        dep->build_all_steps(new_step, first);
    }
}

rule::cyclic_dependency::cyclic_dependency(
    const rule& parent,
    const rule& child
) : error("{} already depends on {}", parent.name(), child.name()) {}
}

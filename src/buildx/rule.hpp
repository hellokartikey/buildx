#ifndef BUILDX_RULE_HPP
#define BUILDX_RULE_HPP

#include <string>
#include <vector>

#include <buildx/exceptions.hpp>
#include <buildx/step.hpp>

namespace bx {
class executor;
class rule {
public:
    struct cyclic_dependency: error {
        cyclic_dependency(const rule& parent, const rule& child);
    };

    rule(const std::string& name);
    virtual ~rule() = default;

    rule(const rule&) = delete;
    rule& operator=(const rule&) = delete;

    rule(rule&&) = delete;
    rule& operator=(rule&&) = delete;

    const std::string& name() const;

    bool is_direct_dependency(const rule& other) const;
    bool is_dependency(const rule& other) const;

    void depends_on(const rule& other);

protected:
    virtual void build_steps(step& first, step& last) const = 0;

private:
    friend class executor;
    void build_all_steps(step& first, step& last) const;

private:
    std::string m_name;
    std::vector<const rule*> m_depends;
};
}

#endif

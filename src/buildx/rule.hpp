#ifndef BX_RULE_HPP
#define BX_RULE_HPP

#include <string>
#include <vector>

namespace bx {
class context;
class executor;
class step;

class rule {
public:
    rule(const std::string& name);
    virtual ~rule() = default;

    rule(const rule&) = delete;
    rule& operator=(const rule&) = delete;

    rule(rule&&) = delete;
    rule& operator=(rule&&) = delete;

    const std::string& name() const;

    bool is_direct_dependency(const rule& other) const;
    bool is_dependency(const rule& other) const;

    void depends_on(rule& other);

protected:
    virtual void build_steps(step& first, step& last) const = 0;
    friend step& build_rule(const rule& rule, executor& exec);

private:
    std::string m_name;
    std::vector<rule*> m_depends;
};
}

#endif

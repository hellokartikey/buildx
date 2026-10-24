#ifndef BUILDX_PHONY_HPP
#define BUILDX_PHONY_HPP

#include <buildx/rule.hpp>

namespace bx {
class phony : public rule {
public:
    phony(const std::string& name);

protected:
    void build_steps(step& first, step& last) override;
};
}

#endif

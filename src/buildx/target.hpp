#ifndef BUILDX_TARGET_HPP
#define BUILDX_TARGET_HPP

#include "rule.hpp"

#include <memory>

namespace bx {
class compiler;
class file_set;

class target : public rule {
public:
    target(const std::string& name);
    ~target() override = default;

    template <typename S>
    S& use(this S& self, const compiler& compiler);

private:
    std::polymorphic<compiler> m_compiler;
    std::polymorphic<file_set> m_file_set;
};
}

#endif

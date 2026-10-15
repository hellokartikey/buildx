#ifndef BUILDX_TARGET_HPP
#define BUILDX_TARGET_HPP

#include <concepts>
#include <memory>

#include <buildx/rule.hpp>
#include <buildx/toolchain.hpp>
#include <buildx/nothing.hpp>

namespace bx {
class target : public rule {
public:
    target(const std::string& name);
    ~target() override = default;

    template <std::derived_from<tc::toolchain> T, typename... Args>
    T& use(Args&&... args) { return *(m_tc = std::make_unique<T>(args...)); }

private:
    std::polymorphic<compiler> m_compiler;
    std::polymorphic<file_set> m_file_set;
};
}

#endif

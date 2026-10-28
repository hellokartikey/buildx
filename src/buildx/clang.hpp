#ifndef BUILDX_CLANG_HPP
#define BUILDX_CLANG_HPP

#include <buildx/tool/clang_cc.hpp>
#include <buildx/tool/llvm_ar.hpp>

namespace bx {
struct clang : tool::clang_cc, tool::llvm_ar {
    template <typename... As>
    clang(As&&... args) { configure(std::forward<As>(args)...); }

    std::string name() const override;

    using clang_cc::apply;
    using llvm_ar::apply;
};
}

#endif

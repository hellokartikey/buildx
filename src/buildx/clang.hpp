#ifndef BUILDX_CLANG_HPP
#define BUILDX_CLANG_HPP

#include <buildx/tool/clang_cc.hpp>
#include <buildx/tool/llvm_ar.hpp>
#include <buildx/tool/stack.hpp>

namespace bx {
struct clang : tool::stack<tool::clang_cc, tool::llvm_ar> {
  using tool::stack<tool::clang_cc, tool::llvm_ar>::stack;
  std::string name() const override;
};
}  // namespace bx

#endif

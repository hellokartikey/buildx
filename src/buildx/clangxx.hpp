#ifndef BUILDX_CLANGXX_HPP
#define BUILDX_CLANGXX_HPP

#include <buildx/tool/clang_cxx.hpp>
#include <buildx/tool/llvm_ar.hpp>
#include <buildx/tool/stack.hpp>

namespace bx {
struct clangxx : tool::stack<tool::clang_cxx, tool::llvm_ar> {
  using tool::stack<tool::clang_cxx, tool::llvm_ar>::stack;
  std::string name() const override;
};
}  // namespace bx

#endif

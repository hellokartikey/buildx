#ifndef BUILDX_CLANGXX_HPP
#define BUILDX_CLANGXX_HPP

#include <buildx/tool/clang_cxx.hpp>
#include <buildx/tool/llvm_ar.hpp>

namespace bx {
struct clangxx : tool::clang_cxx, tool::llvm_ar {
  template <typename... As>
  clangxx(As&&... args) {
    configure(std::forward<As>(args)...);
  }

  std::string name() const override;

  using clang_cxx::apply;
  using llvm_ar::apply;
};
}  // namespace bx

#endif

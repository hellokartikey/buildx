#ifndef BUILDX_GXX_HPP
#define BUILDX_GXX_HPP

#include <buildx/tool/gnu_ar.hpp>
#include <buildx/tool/gnu_cxx.hpp>
#include <buildx/tool/stack.hpp>

namespace bx {
struct gxx : tool::stack<tool::gnu_cxx, tool::gnu_ar> {
  using tool::stack<tool::gnu_cxx, tool::gnu_ar>::stack;
  std::string name() const override;
};
}  // namespace bx

#endif

#ifndef BUILDX_GCC_HPP
#define BUILDX_GCC_HPP

#include <buildx/tool/gnu_ar.hpp>
#include <buildx/tool/gnu_cc.hpp>
#include <buildx/tool/stack.hpp>

namespace bx {
struct gcc : tool::stack<tool::gnu_cc, tool::gnu_ar> {
  using tool::stack<tool::gnu_cc, tool::gnu_ar>::stack;
  std::string name() const override;
};
}  // namespace bx

#endif

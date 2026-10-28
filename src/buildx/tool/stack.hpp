#ifndef BUILDX_TOOL_STACK_HPP
#define BUILDX_TOOL_STACK_HPP

#include <utility>

#include <buildx/toolchain.hpp>

namespace bx::tool {
template <std::derived_from<toolchain>... Ts>
struct stack : Ts... {
  using Ts::apply...;

  std::string name() const { return "unnamed_stack"; }

  template <typename... As>
  stack(As&&... args) {
    this->configure(std::forward<As>(args)...);
  }
};
}  // namespace bx::tool

#endif

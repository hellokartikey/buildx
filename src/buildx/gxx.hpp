#ifndef BUILDX_GXX_HPP
#define BUILDX_GXX_HPP

#include <buildx/tool/gnu_ar.hpp>
#include <buildx/tool/gnu_cxx.hpp>

namespace bx {
struct gxx : tool::gnu_cxx, tool::gnu_ar {
  template <typename... As>
  gxx(As&&... args) {
    configure(std::forward<As>(args)...);
  }

  std::string name() const override;

  using gnu_ar::apply;
  using gnu_cxx::apply;
};
}  // namespace bx

#endif

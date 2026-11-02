#ifndef BUILDX_TOOL_MIXIN_HPP
#define BUILDX_TOOL_MIXIN_HPP

#include <memory>

#include <buildx/toolchain.hpp>

namespace bx {
class tool_mixin {
 public:
  toolchain& tools();

  template <std::derived_from<toolchain> T, typename S>
  S& use(this S& self, const T& tc) {
    self.m_tc = std::make_unique<T>(tc);
    return self;
  }

  template <std::derived_from<toolchain> T, typename S, typename... As>
  S& use(this S& self, std::in_place_t, As&&... args) {
    self.m_tc = std::make_unique<T>(std::forward<As>(args)...);
    return self;
  }

 private:
  std::unique_ptr<toolchain> m_tc;
};
}  // namespace bx

#endif

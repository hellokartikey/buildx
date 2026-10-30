#ifndef BUILDX_TOOL_LINKER_HPP
#define BUILDX_TOOL_LINKER_HPP

#include <buildx/step.hpp>
#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx::tool {
class linker : virtual public toolchain {
 public:
  virtual step& link(const target& target,
                     const std::vector<std::filesystem::path>& objects,
                     const view<library>& libraries = {});

  virtual step& link_shared(const target& target,
                            const std::vector<std::filesystem::path>& objects,
                            const view<library>& libraries = {});
};
}  // namespace bx::tool

#endif

#ifndef BUILDX_SHARED_TOOL_HPP
#define BUILDX_SHARED_TOOL_HPP

#include <buildx/step.hpp>
#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx {
class shared_tool : virtual public toolchain {
 public:
  virtual step& compile_shared(const target& target,
                               const std::filesystem::path& source);

  virtual step& link_shared(const target& target,
                            const std::vector<std::filesystem::path>& objects,
                            const view<library>& libraries = {});
};
}  // namespace bx

#endif

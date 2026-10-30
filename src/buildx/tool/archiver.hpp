#ifndef BUILDX_TOOL_ARCHIVER_HPP
#define BUILDX_TOOL_ARCHIVER_HPP

#include <buildx/step.hpp>
#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx::tool {
class archiver : virtual public toolchain {
 public:
  virtual step& link_archive(const target& target,
                             const std::vector<std::filesystem::path>& objects,
                             const view<library>& libraries = {});
};
}  // namespace bx::tool

#endif

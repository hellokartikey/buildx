#ifndef BUILDX_ARCHIVE_TOOL_HPP
#define BUILDX_ARCHIVE_TOOL_HPP

#include <buildx/step.hpp>
#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx {
class archive_tool : virtual public toolchain {
 public:
  virtual step& link_archive(const target& target,
                             const std::vector<std::filesystem::path>& objects,
                             const view<library>& libraries = {});
};
}  // namespace bx

#endif

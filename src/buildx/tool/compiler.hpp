#ifndef BUILDX_TOOL_COMPILER_HPP
#define BUILDX_TOOL_COMPILER_HPP

#include <buildx/step.hpp>
#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx::tool {
class compiler : virtual public toolchain {
 public:
  virtual step& compile(const target& target,
                        const std::filesystem::path& source);

  virtual step& compile_shared(const target& target,
                               const std::filesystem::path& source);
};
}  // namespace bx::tool

#endif

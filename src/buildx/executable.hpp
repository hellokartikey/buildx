#ifndef BUILDX_EXECUTABLE_HPP
#define BUILDX_EXECUTABLE_HPP

#include <buildx/command.hpp>
#include <buildx/source_mixin.hpp>
#include <buildx/target.hpp>
#include <buildx/tool_mixin.hpp>

namespace bx {
class executable : public target, public source_mixin, public tool_mixin {
 public:
  using target::target;

  std::filesystem::path artifact() const override;

  command& run();

 protected:
  void build_steps(step& first, step& last) override;
};
}  // namespace bx

#endif

#ifndef BUILDX_TOOL_LD_HPP
#define BUILDX_TOOL_LD_HPP

#include <string>

#include <buildx/tool/linker.hpp>

namespace bx::tool {
class ld : public linker {
 public:
  struct ld_f {
    std::string v;
  };

  static ld_f l_flag(const std::string& flag);

  virtual std::string to_string(ld_f flag) const = 0;

  virtual void apply(ld_f flag) = 0;
};
}  // namespace bx::tool

#endif

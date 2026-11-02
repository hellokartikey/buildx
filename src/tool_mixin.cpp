#include <buildx/tool_mixin.hpp>

#include <buildx/this_build.hpp>

namespace bx {
toolchain& tool_mixin::tools() {
  if (not m_tc) {
    return this_build::context.tools();
  }
  return *m_tc;
}

}  // namespace bx

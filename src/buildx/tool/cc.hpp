#ifndef BUILDX_TOOL_CC_HPP
#define BUILDX_TOOL_CC_HPP

#include <buildx/tool/c_family.hpp>
#include <buildx/tool/compiler.hpp>

namespace bx::tool {
class cc : public c_family, public compiler {};
}  // namespace bx::tool

#endif

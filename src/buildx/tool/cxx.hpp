#ifndef BUILDX_TOOL_CXX_HPP
#define BUILDX_TOOL_CXX_HPP

#include <buildx/tool/c_family.hpp>
#include <buildx/tool/compiler.hpp>

namespace bx::tool {
class cxx : public c_family, public compiler {};
}  // namespace bx::tool

#endif

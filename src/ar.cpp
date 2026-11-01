#include <buildx/tool/ar.hpp>

namespace bx::tool {
ar::ar_f ar::a_flag(const std::string& v) { return {v}; }
}  // namespace bx::tool

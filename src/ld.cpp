#include <buildx/tool/ld.hpp>

namespace bx::tool {
ld::ld_f ld::l_flag(const std::string& v) { return {v}; }
}  // namespace bx::tool

#include <buildx/tool/ld.hpp>

namespace bx::tool {
ld::link_f ld::link(const std::filesystem::path& v) { return {v}; }

ld::ld_f ld::l_flag(const std::string& v) { return {v}; }

void ld::apply(link_f flag) { apply(l_flag(to_string(flag))); }
}  // namespace bx::tool

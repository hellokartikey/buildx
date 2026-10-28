#include <buildx/static_tool.hpp>

namespace bx {
step& static_tool::compile_static(const target& target,
                                  const std::filesystem::path& source) {
  throw not_implemented(*this, "compile_static()");
}

step& static_tool::link_static(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries) {
  throw not_implemented(*this, "link_static()");
}
}  // namespace bx

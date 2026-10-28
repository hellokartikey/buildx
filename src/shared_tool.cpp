#include <buildx/shared_tool.hpp>

namespace bx {
step& shared_tool::compile_shared(const target& target,
                                  const std::filesystem::path& source) {
  throw not_implemented(*this, "compile_shared()");
}

step& shared_tool::link_shared(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries) {
  throw not_implemented(*this, "link_shared()");
}
}  // namespace bx

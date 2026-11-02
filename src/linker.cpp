#include <buildx/tool/linker.hpp>

namespace bx::tool {
step& linker::link(const target& target,
                   const std::vector<std::filesystem::path>& objects,
                   const view<linkable>& libraries,
                   const view<const std::vector<std::string>>& flags) {
  throw not_implemented(*this, "link()");
}

step& linker::link_shared(const target& target,
                          const std::vector<std::filesystem::path>& objects,
                          const view<linkable>& libraries,
                          const view<const std::vector<std::string>>& flags) {
  throw not_implemented(*this, "link_shared()");
}
}  // namespace bx::tool

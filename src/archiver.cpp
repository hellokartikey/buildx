#include <buildx/tool/archiver.hpp>

namespace bx::tool {
step& archiver::link_archive(const target& target,
                             const std::vector<std::filesystem::path>& objects,
                             const view<library>& libraries) {
  throw not_implemented(*this, "link_archive()");
}
}  // namespace bx::tool

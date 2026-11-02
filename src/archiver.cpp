#include <buildx/tool/archiver.hpp>

namespace bx::tool {
step& archiver::archive(const target& target,
                        const std::vector<std::filesystem::path>& objects,
                        const view<linkable>& libraries,
                        const view<const std::vector<std::string>>& flags) {
  throw not_implemented(*this, "archive()");
}
}  // namespace bx::tool

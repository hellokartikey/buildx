#include <buildx/archive_tool.hpp>

namespace bx {
step& archive_tool::link_archive(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) {
    throw not_implemented(*this, "link_archive()");
}
}

#ifndef BUILDX_ARCHIVE_TOOL_HPP
#define BUILDX_ARCHIVE_TOOL_HPP

#include <buildx/toolchain.hpp>
#include <buildx/target.hpp>
#include <buildx/step.hpp>

namespace bx {
class archive_tool : virtual public toolchain {
public:
    virtual step& link_archive(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    );
};
}

#endif

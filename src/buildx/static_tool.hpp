#ifndef BUILDX_STATIC_TOOL_HPP
#define BUILDX_STATIC_TOOL_HPP

#include <buildx/toolchain.hpp>
#include <buildx/target.hpp>
#include <buildx/step.hpp>

namespace bx {
class static_tool : virtual public toolchain {
public:
    virtual step& compile_static(
        const target& target,
        const std::filesystem::path& source
    );

    virtual step& link_static(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    );
};
}

#endif

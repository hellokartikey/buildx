#ifndef BUILDX_SHARED_TOOL_HPP
#define BUILDX_SHARED_TOOL_HPP

#include <buildx/toolchain.hpp>
#include <buildx/target.hpp>
#include <buildx/step.hpp>

namespace bx {
class shared_tool : virtual public toolchain {
public:
    virtual step& compile_shared(
        const target& target,
        const std::filesystem::path& source
    );

    virtual step& link_shared(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    );
};
}

#endif

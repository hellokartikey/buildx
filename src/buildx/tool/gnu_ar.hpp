#ifndef BUILDX_TOOL_GNU_AR_HPP
#define BUILDX_TOOL_GNU_AR_HPP

#include <buildx/archive_tool.hpp>
#include <buildx/tool/c_mixins.hpp>

namespace bx::tool {
class gnu_ar : public archive_tool, public ar_mixin {
public:
    void apply(ar_f flag);

    step& link_archive(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    ) override;

private:
    std::string m_exe = "ar";

    std::vector<std::string> m_ar;
};
}

#endif

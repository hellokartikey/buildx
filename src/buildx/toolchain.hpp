#ifndef BUILDX_TOOLCHAIN_HPP
#define BUILDX_TOOLCHAIN_HPP

#include <filesystem>
#include <string>
#include <vector>

#include "exceptions.hpp"

namespace bx {
class step;
}

namespace bx::tc {
class toolchain {
public:
    toolchain() = default;
    virtual ~toolchain() = default;

    virtual std::string name() const = 0;

    virtual step& compile_static(
        const std::filesystem::path& source,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags
    );

    virtual step& compile_shared(
        const std::filesystem::path& source,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags
    );

    virtual step& link_archive(
        const std::vector<std::filesystem::path>& objects,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags
    );

    virtual step& link_module(
        const std::vector<std::filesystem::path>& objects,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags
    );

    virtual step& link_static(
        const std::vector<std::filesystem::path>& objects,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags
    );

    virtual step& link_shared(
        const std::vector<std::filesystem::path>& objects,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags
    );
};

class not_implemented : public error {
public:
    not_implemented(const std::string& name, const std::string& method);
};
}

#endif

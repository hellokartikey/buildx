#ifndef BUILDX_TOOLCHAIN_HPP
#define BUILDX_TOOLCHAIN_HPP

#include <filesystem>
#include <string>
#include <vector>

#include <buildx/exceptions.hpp>
#include <buildx/step.hpp>

namespace bx {
class target;
class toolchain {
public:
    class not_implemented : public error {
    public:
        not_implemented(const std::string& name, const std::string& method);
    };

    toolchain() = default;
    virtual ~toolchain() = default;

    virtual std::string name() const = 0;

    virtual step& compile_static(
        const target& target,
        const std::filesystem::path& source
    ) const;

    virtual step& compile_shared(
        const target& target,
        const std::filesystem::path& source
    ) const;

    virtual step& compile_module(
        const target& target,
        const std::filesystem::path& source
    ) const;

    virtual step& link_static(
        const target& target,
        const std::vector<std::filesystem::path>& objects
    ) const;

    virtual step& link_shared(
        const target& target,
        const std::vector<std::filesystem::path>& objects
    ) const;

    virtual step& link_archive(
        const target& target,
        const std::vector<std::filesystem::path>& objects
    ) const;

    virtual step& link_module(
        const target& target,
        const std::vector<std::filesystem::path>& objects
    ) const;
};
}

#endif

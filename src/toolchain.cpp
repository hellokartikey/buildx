#include <buildx/toolchain.hpp>

#include <buildx/target.hpp>

namespace bx {
bool toolchain::is_same_as(const toolchain& other) const {
    if (typeid(*this) == typeid(other)) {
        return *this == other;
    }
    return false;
}

step& toolchain::compile_static(
    const target& target,
    const std::filesystem::path& source
) const {
    throw not_implemented(name(), "compile_static()");
}

step& toolchain::compile_shared(
    const target& target,
    const std::filesystem::path& source
) const {
    throw not_implemented(name(), "compile_shared()");
}

step& toolchain::compile_module(
    const target& target,
    const std::filesystem::path& source
) const {
    throw not_implemented(name(), "compile_module()");
}

step& toolchain::link_static(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    throw not_implemented(name(), "link_static()");
}

step& toolchain::link_shared(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    throw not_implemented(name(), "link_shared()");
}

step& toolchain::link_archive(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    throw not_implemented(name(), "link_archive()");
}

step& toolchain::link_module(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    throw not_implemented(name(), "link_module()");
}

toolchain::not_implemented::not_implemented(
    const std::string& name,
    const std::string& method
) : error("toolchain {} does not implement {}", name, method) {}
}

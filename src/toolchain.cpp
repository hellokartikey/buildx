#include <buildx/toolchain.hpp>

namespace bx::tc {
step& toolchain::compile_static(
    const std::filesystem::path& source,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "compile_static()");
}

step& toolchain::compile_shared(
    const std::filesystem::path& source,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "compile_shared()");
}

step& toolchain::compile_module(
    const std::filesystem::path& source,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "compile_module()");
}

step& toolchain::link_static(
    const std::vector<std::filesystem::path>& objects,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "link_static()");
}

step& toolchain::link_shared(
    const std::vector<std::filesystem::path>& objects,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "link_shared()");
}

step& toolchain::link_archive(
    const std::vector<std::filesystem::path>& objects,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "link_archive()");
}

step& toolchain::link_module(
    const std::vector<std::filesystem::path>& objects,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) {
    throw not_implemented(name(), "link_module()");
}

not_implemented::not_implemented(
    const std::string& name,
    const std::string& method
) : error("toolchain {} does not implement {}", name, method) {}
}

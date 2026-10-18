#include <buildx/context.hpp>

#include <buildx/rule.hpp>

namespace bx {
const std::filesystem::path& context::root() const { return m_root; }

const std::filesystem::path& context::prefix() const { return m_prefix; }

context& context::prefix(const std::filesystem::path& path) {
    m_prefix = path;
    return *this;
}

const std::filesystem::path& context::binary_path() const { return m_binary; }

context& context::binary_path(const std::filesystem::path& path) {
    m_binary = path;
    return *this;
}

const std::filesystem::path& context::include_path() const { return m_include; }

context& context::include_path(const std::filesystem::path& path) {
    m_include = path;
    return *this;
}

const std::filesystem::path& context::library_path() const { return m_library; }

context& context::library_path(const std::filesystem::path& path) {
    m_library = path;
    return *this;
}

std::filesystem::path context::scratch_path(const rule& rule) const {
    return m_scratch / rule.name();
}

context& context::scratch_path_prefix(const std::filesystem::path& path) {
    m_scratch = path;
    return *this;
}
}

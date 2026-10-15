#ifndef BUILDX_CONTEXT_HPP
#define BUILDX_CONTEXT_HPP

#include <filesystem>

namespace bx {
class rule;

class context {
public:
    context() = default;
    ~context() = default;

    context(const context&) = delete;
    context& operator=(const context&) = delete;

    context(context&&) = delete;
    context& operator=(context&&) = delete;

    const std::filesystem::path& root() const;

    const std::filesystem::path& prefix() const;
    context& set_prefix(const std::filesystem::path& path);

    const std::filesystem::path& binary_path() const;
    context& set_binary_path(const std::filesystem::path& path);

    const std::filesystem::path& include_path() const;
    context& set_include_path(const std::filesystem::path& path);

    const std::filesystem::path& library_path() const;
    context& set_library_path(const std::filesystem::path& path);

    std::filesystem::path scratch_path(const rule& rule) const;
    context& set_scratch_path_prefix(const std::filesystem::path& path);

private:
    std::filesystem::path m_root = std::filesystem::current_path();
    std::filesystem::path m_prefix = m_root / "bx-out";
    std::filesystem::path m_binary = m_prefix / "bin";
    std::filesystem::path m_include = m_prefix / "include";
    std::filesystem::path m_library = m_prefix / "lib";
    std::filesystem::path m_scratch = m_root / ".bx-out";
};
}

#endif

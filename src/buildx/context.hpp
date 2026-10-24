#ifndef BUILDX_CONTEXT_HPP
#define BUILDX_CONTEXT_HPP

#include <filesystem>
#include <list>
#include <unordered_map>

#include <buildx/rule.hpp>
#include <buildx/phony.hpp>
#include <buildx/exceptions.hpp>

int main(int argc, char** argv);

namespace bx {
class context {
public:
    struct parse_error : error {
        template <typename... Args>
        parse_error(std::format_string<Args...> fmt, Args&&... args)
            : error(std::format(fmt, std::forward<Args>(args)...)) {}
    };

    friend int ::main(int argc, char** argv);

    context() = default;
    ~context() = default;

    context(const context&) = delete;
    context& operator=(const context&) = delete;

    context(context&&) = delete;
    context& operator=(context&&) = delete;

    const std::filesystem::path& root() const;
    std::filesystem::path path(const std::string& path) const;

    const std::filesystem::path& prefix() const;
    context& prefix(const std::filesystem::path& path);

    const std::filesystem::path& binary_path() const;
    context& binary_path(const std::filesystem::path& path);

    const std::filesystem::path& include_path() const;
    context& include_path(const std::filesystem::path& path);

    const std::filesystem::path& library_path() const;
    context& library_path(const std::filesystem::path& path);

    std::filesystem::path scratch_path(const rule& rule) const;
    const std::filesystem::path& scratch_path() const;
    context& scratch_path_prefix(const std::filesystem::path& path);

    template <typename T, typename... Args>
    T& add(Args&&... args) {
        auto* ptr = m_rules.emplace_back(
            std::make_unique<T>(std::forward<Args>(args)...)
        ).get();
        return *static_cast<T*>(ptr);
    }

    context& install(rule& rule);
    phony& install();

    bool verbose() const;
    const std::filesystem::path& build_script() const;

    int argc() const;
    char** argv() const;

private:
    void parse(int argc, char** argv);

private:
    std::filesystem::path m_root = std::filesystem::current_path();
    std::filesystem::path m_prefix = m_root / "bx-out";
    std::filesystem::path m_binary = m_prefix / "bin";
    std::filesystem::path m_include = m_prefix / "include";
    std::filesystem::path m_library = m_prefix / "lib";
    std::filesystem::path m_scratch = m_root / "bx-cache";

    std::list<std::unique_ptr<rule>> m_rules;
    phony m_install{"install"};

    int m_argc = 0;
    char** m_argv = nullptr;

    std::filesystem::path m_script;
    std::unordered_map<std::string, std::string> m_options;
    bool m_verbose = false;
};
}

#endif

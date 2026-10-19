#ifndef BUILDX_TARGET_HPP
#define BUILDX_TARGET_HPP

#include <concepts>
#include <memory>

#include <buildx/exceptions.hpp>
#include <buildx/rule.hpp>
#include <buildx/toolchain.hpp>

namespace bx {
class target : public rule {
public:
    class no_toolchain : public error {
    public:
        no_toolchain(const target& target);
    };

    target(const std::string& name);
    ~target() override = default;

    template <typename S>
    S& file(this S& self, const std::filesystem::path& file) {
        self.m_files.push_back(file);
        return self;
    }

    template <typename S>
    S& files(this S& self, const std::vector<std::filesystem::path>& files) {
        self.m_files.append_range(files);
        return self;
    }

    const std::vector<std::filesystem::path>& files() const { return m_files; }

    template <typename S>
    S& header(this S& self, const std::filesystem::path& file) {
        self.m_headers.push_back(file);
        return self;
    }

    template <typename S>
    S& headers(this S& self, const std::vector<std::filesystem::path>& files) {
        self.m_headers.append_range(files);
        return self;
    }

    const std::vector<std::filesystem::path>& headers() const {
        return m_headers;
    }

    template <std::derived_from<toolchain> T, typename S>
    S& use(this S& self, const T& tc) {
        self.m_tc = std::make_unique<T>(tc);
        return self;
    }

    template <std::derived_from<toolchain> T, typename S, typename... Args>
    S& use(this S& self, Args&&... args) {
        self.m_tc = std::make_unique<T>(args...);
        return self;
    }

    const toolchain& tc() const;

protected:
    void build_steps(step& first, step& last) const override;
    virtual void compile_steps(step& first, step& last) const = 0;

private:
    std::unique_ptr<toolchain> m_tc;

    std::vector<std::filesystem::path> m_files;
    std::vector<std::filesystem::path> m_headers;
};
}

#endif

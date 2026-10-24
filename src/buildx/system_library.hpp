#ifndef BUILDX_SYSTEM_LIBRARY_HPP
#define BUILDX_SYSTEM_LIBRARY_HPP

#include <buildx/library.hpp>

namespace bx {
class system_library : public library {
public:
    system_library(const std::string& name);

    std::filesystem::path artifact() const override;

    template <typename S>
    S& path(this S& self, const std::filesystem::path& path) {
        self.m_prefix = path;
        return self;
    }

    template <typename S>
    S& version(this S& self, const std::string& path) {
        self.m_prefix = path;
        return self;
    }

    const std::filesystem::path& path() const;
    const std::string& version() const;

protected:
    void build_steps(step& first, step& last) override;

private:
    std::filesystem::path m_prefix = "/usr/lib/";
    std::string m_version;
};
}

#endif

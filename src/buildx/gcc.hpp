#ifndef BUILDX_GCC_HPP
#define BUILDX_GCC_HPP

#include <buildx/cc.hpp>

namespace bx {
class gcc : public cc {
public:
    gcc() = default;

    template <typename... Args>
    gcc(flags_t, Args&&... args) { (apply(std::forward<Args>(args)), ...); }

    std::string name() const override;

    void apply(std_f flag) override;
    void apply(define_f flag) override;
    void apply(define_kv flag) override;
    void apply(include_f flag) override;
    void apply(prefix_f flag) override;

    void apply(cc_f flag) override;
    void apply(ld_f flag) override;
    void apply(ar_f flag) override;
    void apply(md_f flag) override;

    step& compile_static(
        const target& target,
        const std::filesystem::path& source
    ) const override;

    step& compile_shared(
        const target& target,
        const std::filesystem::path& source
    ) const override;

    step& link_static(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    ) const override;

    step& link_archive(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    ) const override;

    step& link_shared(
        const target& target,
        const std::vector<std::filesystem::path>& objects,
        const view<library>& libraries = {}
    ) const override;

private:
    std::string m_exe = "gcc";
    std::string m_ar_exe = "gcc-ar";

    std::vector<std::string> m_cc;
    std::vector<std::string> m_ar;
};
}

#endif

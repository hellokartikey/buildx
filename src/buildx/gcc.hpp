#ifndef BUILDX_GCC_HPP
#define BUILDX_GCC_HPP

#include <buildx/c_family.hpp>

namespace bx::tc {
class gcc : public c_family {
public:
    template <typename... Args>
    gcc(Args&&... args) { (apply(args),...); }

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
        const std::filesystem::path& source,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags = {}
    ) const override;

    step& link_static(
        const std::vector<std::filesystem::path>& objects,
        const std::filesystem::path& output,
        const std::vector<std::string>& flags = {}
    ) const override;

private:
    std::string m_exe = "gcc";

    std::vector<std::string> m_cc;
    std::vector<std::string> m_ar;
};
}

#endif

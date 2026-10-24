#ifndef BUILDX_C_FAMILY_HPP
#define BUILDX_C_FAMILY_HPP

#include <buildx/toolchain.hpp>
#include <buildx/rule.hpp>

namespace bx {
class c_family : public toolchain {
public:
    static constexpr struct flags_t {} flags;

    struct std_f { int v; };
    struct define_f { std::string v; };
    struct define_kv { std::string k, v; };
    struct include_f { std::filesystem::path v; };
    struct prefix_f { std::string v; };

    struct cc_f { std::string v; };
    struct ld_f { std::string v; };
    struct ar_f { std::string v; };
    struct md_f { std::string v; };

    static std_f std(int v);
    static define_f define(const std::string& v);
    static define_kv define(const std::string& k, const std::string& v);
    static include_f include(const std::filesystem::path& v);
    static prefix_f prefix(const std::string& v);

    static cc_f flag(const std::string& v);
    static ld_f link_flag(const std::string& v);
    static ar_f archive_flag(const std::string& v);
    static md_f module_flag(const std::string& v);

    virtual void apply(std_f flag) = 0;
    virtual void apply(define_f flag) = 0;
    virtual void apply(define_kv flag) = 0;
    virtual void apply(include_f flag) = 0;
    virtual void apply(prefix_f flag) = 0;

    virtual void apply(cc_f flag) = 0;
    virtual void apply(ld_f flag) = 0;
    virtual void apply(ar_f flag) = 0;
    virtual void apply(md_f flag) = 0;
};

std::filesystem::path to_object(
    const target& target,
    const std::filesystem::path& source
);
}

#endif

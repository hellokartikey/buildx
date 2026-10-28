#ifndef BUILDX_C_FAMILY_HPP
#define BUILDX_C_FAMILY_HPP

#include <buildx/toolchain.hpp>
#include <buildx/target.hpp>

namespace bx {
class cc_mixin {
public:
    struct std_f { int v; };
    struct define_f { std::string v; };
    struct define_kv { std::string k, v; };
    struct include_f { std::filesystem::path v; };

    struct cc_f { std::string v; };
    struct ld_f { std::string v; };

    static std_f std(int std);
    static define_f define(const std::string& define);
    static define_kv define(const std::string& key, const std::string& value);
    static include_f include(const std::filesystem::path& path);

    static cc_f c_flag(const std::string& flag);
    static ld_f l_flag(const std::string& flag);
};

class ar_mixin {
public:
    struct ar_f { std::string v; };

    static ar_f a_flag(const std::string& flag);
};

std::filesystem::path to_object(
    const target& target,
    const std::filesystem::path& source
);
}

#endif

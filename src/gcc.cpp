#include <buildx/gcc.hpp>

#include <buildx/this_build.hpp>

namespace bx {
std::string gcc::name() const { return "gcc"; }

void gcc::apply(std_f flag) { m_cc.push_back(std::format("-std=gnu{}", flag.v)); }

void gcc::apply(define_f flag) { m_cc.push_back(std::format("-D{}", flag.v)); }

void gcc::apply(define_kv flag) {
    m_cc.push_back(std::format("-D{}={}", flag.k, flag.v));
}

void gcc::apply(include_f flag) { m_cc.push_back(std::format("-I{}", flag.v)); }

void gcc::apply(prefix_f flag) { m_exe = std::format("{}gcc", flag.v); }

void gcc::apply(cc_f flag) { m_cc.push_back(flag.v); }

void gcc::apply(ld_f flag) { m_cc.push_back(std::format("-Wl,{}", flag.v)); }

void gcc::apply(ar_f flag) { m_ar.push_back(flag.v); }

void gcc::apply(md_f flag) {}

step& gcc::compile_static(
    const std::filesystem::path& source,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) const {
    return this_build::executor
        .make_step(m_exe)
        .message(
            "{} compile static {}",
            name(),
            std::filesystem::relative(output))
        .flag("-c")
        .flags(m_cc)
        .flags(flags)
        .in_flag(source)
        .flag("-o")
        .out_flag(output);
}

step& gcc::link_static(
    const std::vector<std::filesystem::path>& objects,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) const {
    return this_build::executor
        .make_step(m_exe)
        .message(
            "{} link executable {}",
            name(),
            std::filesystem::relative(output))
        .flags(m_cc)
        .flags(flags)
        .in_flags(objects)
        .flag("-o")
        .out_flag(output);
}
}

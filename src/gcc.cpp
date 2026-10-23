#include <buildx/gcc.hpp>

#include <functional>

#include <buildx/this_build.hpp>
#include <buildx/target.hpp>
#include <buildx/library.hpp>

namespace bx {
std::string gcc::name() const { return "gcc"; }

void gcc::apply(std_f flag) { m_cc.push_back(std::format("-std=gnu{}", flag.v)); }

void gcc::apply(define_f flag) { m_cc.push_back(std::format("-D{}", flag.v)); }

void gcc::apply(define_kv flag) {
    m_cc.push_back(std::format("-D{}={}", flag.k, flag.v));
}

void gcc::apply(include_f flag) { m_cc.push_back(std::format("-I{}", flag.v)); }

void gcc::apply(prefix_f flag) {
    m_exe = std::format("{}gcc", flag.v);
    m_ar_exe = std::format("{}gcc-ar", flag.v);
}

void gcc::apply(cc_f flag) { m_cc.push_back(flag.v); }

void gcc::apply(ld_f flag) { m_cc.push_back(std::format("-Wl,{}", flag.v)); }

void gcc::apply(ar_f flag) { m_ar.push_back(flag.v); }

void gcc::apply(md_f flag) {}

step& gcc::compile_static(
    const target& target,
    const std::filesystem::path& source
) const {
    auto output = to_object(target, source);
    return this_build::executor
        .make_step(m_exe)
        .message(
            "{} compile static {}",
            name(),
            std::filesystem::relative(output, this_build::context.root()))
        .flag("-o")
        .out_flag(output)
        .flag("-c")
        .flags(m_cc)
        .in_flag(source);
}

step& gcc::compile_shared(
    const target& target,
    const std::filesystem::path& source
) const {
    auto output = to_object(target, source);
    return this_build::executor
        .make_step(m_exe)
        .message(
            "{} compile shared {}",
            name(),
            std::filesystem::relative(output, this_build::context.root()))
        .flag("-o")
        .out_flag(output)
        .flag("-c")
        .flags(m_cc)
        .in_flag(source);
}

step& gcc::link_static(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    return this_build::executor
        .make_step(m_exe)
        .message(
            "{} link executable {}",
            name(),
            std::filesystem::relative(target.artifact()))
        .flag("-o")
        .out_flag(target.artifact())
        .flags(m_cc)
        .in_flags(objects)
        .in_flags(
            libraries
            | std::views::transform(&library::artifact)
            | std::ranges::to<std::vector>()
        );
}

step& gcc::link_archive(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    return this_build::executor
        .make_step(m_ar_exe)
        .message(
            "{} link archive {}",
            name(),
            std::filesystem::relative(target.artifact()))
        .flag("rcs")
        .flags(m_ar)
        .out_flag(target.artifact())
        .in_flags(objects)
        .in_flags(
            libraries
            | std::views::filter(std::not_fn(&library::is_shared))
            | std::views::transform(&library::artifact)
            | std::ranges::to<std::vector>()
        );
}

step& gcc::link_shared(
    const target& target,
    const std::vector<std::filesystem::path>& objects,
    const view<library>& libraries
) const {
    return this_build::executor
        .make_step(m_exe)
        .message(
            "{} link shared {}",
            name(),
            std::filesystem::relative(target.artifact()))
        .flag("-o")
        .out_flag(target.artifact())
        .flag("-shared")
        .flags(m_cc)
        .in_flags(objects)
        .in_flags(
            libraries
            | std::views::transform(&library::artifact)
            | std::ranges::to<std::vector>()
        );
}

}

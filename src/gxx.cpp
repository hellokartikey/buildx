#include <buildx/gxx.hpp>

#include <functional>

#include <buildx/this_build.hpp>
#include <buildx/target.hpp>
#include <buildx/library.hpp>

namespace bx {
std::string gxx::name() const { return "g++"; }

void gxx::apply(std_f flag) { m_cc.push_back(std::format("-std=c++{}", flag.v)); }

void gxx::apply(define_f flag) { m_cc.push_back(std::format("-D{}", flag.v)); }

void gxx::apply(define_kv flag) {
    m_cc.push_back(std::format("-D{}={}", flag.k, flag.v));
}

void gxx::apply(include_f flag) { m_cc.push_back(std::format("-I{}", flag.v)); }

void gxx::apply(prefix_f flag) {
    m_exe = std::format("{}g++", flag.v);
    m_ar_exe = std::format("{}gcc-ar", flag.v);
}

void gxx::apply(cc_f flag) { m_cc.push_back(flag.v); }

void gxx::apply(ld_f flag) { m_cc.push_back(std::format("-Wl,{}", flag.v)); }

void gxx::apply(ar_f flag) { m_ar.push_back(flag.v); }

void gxx::apply(md_f flag) {}

step& gxx::compile_static(
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

step& gxx::compile_shared(
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

step& gxx::link_static(
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

step& gxx::link_archive(
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

step& gxx::link_shared(
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

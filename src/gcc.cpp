#include <buildx/gcc.hpp>

#include <ranges>

#include <buildx/this_build.hpp>

namespace bx::tc {
std::string gcc::name() const { return "gcc"; }

void gcc::apply(std_f flag) { m_cc.push_back(std::format("-std=c{}", flag.v)); }

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
        .make_step("gcc")
        .message("Compiling C object {} using {}", output.filename(), name())
        .flag("-c")
        .flags(m_cc)
        .flags(flags)
        .in_file(source)
        .flag(source.string())
        .flag("-o")
        .out_file(output)
        .flag(output.string());
}

step& gcc::link_static(
    const std::vector<std::filesystem::path>& objects,
    const std::filesystem::path& output,
    const std::vector<std::string>& flags
) const {
    auto to_string = [] (auto& object) { return object.string(); };
    return this_build::executor
        .make_step("gcc")
        .message("Linking C executable {} using {}", output.filename(), name())
        .flags(m_cc)
        .flags(flags)
        .in_files(objects)
        .flags(
            objects
                | std::views::transform(to_string)
                | std::ranges::to<std::vector>())
        .flag("-o")
        .out_file(output)
        .flag(output.string());
}
}

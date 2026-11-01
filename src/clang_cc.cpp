#include <buildx/tool/clang_cc.hpp>

#include <buildx/linkable.hpp>
#include <buildx/target.hpp>
#include <buildx/this_build.hpp>

namespace bx::tool {
std::string clang_cc::to_string(cc_f flag) const {
    return flag.v;
}

std::string clang_cc::to_string(ld_f flag) const {
    return std::format("-Wl,{}", flag.v);
}

std::string clang_cc::to_string(std_f flag) const {
    return std::format("-std=c{}", flag.v);
}

std::string clang_cc::to_string(define_f flag) const {
    return std::format("-D{}", flag.v);
}

std::string clang_cc::to_string(define_kv flag) const {
    return std::format("-D{}={}", flag.k, flag.v);
}

std::string clang_cc::to_string(include_f flag) const {
    return std::format("-I{}", flag.v);
}

void clang_cc::apply(cc_f flag) { m_cc.push_back(to_string(flag)); }

void clang_cc::apply(ld_f flag) { m_ld.push_back(to_string(flag)); }

step& clang_cc::compile(const target& target,
                        const std::filesystem::path& source,
                        const std::vector<std::string>& flags) {
  auto output = to_object(target, source);
  return this_build::executor.make_step(m_exe)
      .message("{} compile {}",
               name(),
               std::filesystem::relative(output, this_build::context.root()))
      .flag("-o")
      .out_flag(output)
      .flag("-c")
      .flags(m_cc)
      .flags(flags)
      .in_flag(source);
}

step& clang_cc::compile_shared(const target& target,
                               const std::filesystem::path& source,
                               const std::vector<std::string>& flags) {
  auto output = to_object(target, source);
  return this_build::executor.make_step(m_exe)
      .message("{} compile shared {}",
               name(),
               std::filesystem::relative(output, this_build::context.root()))
      .flag("-o")
      .out_flag(output)
      .flag("-c")
      .flags(m_cc)
      .flags(flags)
      .in_flag(source);
}

step& clang_cc::link(const target& target,
                     const std::vector<std::filesystem::path>& objects,
                     const view<linkable>& libraries,
                     const std::vector<std::string>& flags) {
  return this_build::executor.make_step(m_exe)
      .message(
          "{} link {}", name(), std::filesystem::relative(target.artifact()))
      .flag("-o")
      .out_flag(target.artifact())
      .flags(m_ld)
      .flags(flags)
      .in_flags(objects)
      .in_flags(libraries
                | std::views::filter(&linkable::has_artifact)
                | std::views::transform(&linkable::artifact)
                | std::ranges::to<std::vector>());
}

step& clang_cc::link_shared(const target& target,
                            const std::vector<std::filesystem::path>& objects,
                            const view<linkable>& libraries,
                            const std::vector<std::string>& flags) {
  return this_build::executor.make_step(m_exe)
      .message("{} link shared {}",
               name(),
               std::filesystem::relative(target.artifact()))
      .flag("-o")
      .out_flag(target.artifact())
      .flag("-shared")
      .flags(m_ld)
      .flags(flags)
      .in_flags(objects)
      .in_flags(libraries
                | std::views::filter(&linkable::has_artifact)
                | std::views::transform(&linkable::artifact)
                | std::ranges::to<std::vector>());
}
}  // namespace bx::tool

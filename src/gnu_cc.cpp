#include <buildx/tool/gnu_cc.hpp>

#include <buildx/linkable.hpp>
#include <buildx/target.hpp>
#include <buildx/this_build.hpp>

namespace bx::tool {
std::string gnu_cc::to_string(cc_f flag) const { return flag.v; }

std::string gnu_cc::to_string(ld_f flag) const {
  return std::format("-Wl,{}", flag.v);
}

std::string gnu_cc::to_string(link_f flag) const { return flag.v; }

std::string gnu_cc::to_string(std_f flag) const {
  return std::format("-std=gnu{}", flag.v);
}

std::string gnu_cc::to_string(define_f flag) const {
  return std::format("-D{}", flag.v);
}

std::string gnu_cc::to_string(define_kv flag) const {
  return std::format("-D{}={}", flag.k, flag.v);
}

std::string gnu_cc::to_string(include_f flag) const {
  return std::format("-I{}", flag.v);
}

void gnu_cc::apply(cc_f flag) { m_cc.push_back(to_string(flag)); }

void gnu_cc::apply(ld_f flag) { m_ld.push_back(to_string(flag)); }

step& gnu_cc::compile(const target& target,
                      const std::filesystem::path& source,
                      const view<const std::vector<std::string>>& flags) {
  auto output = to_object(target, source);
  return this_build::executor.make_step(m_exe)
      .message("{} compile {}",
               name(),
               std::filesystem::relative(output, this_build::context.root()))
      .flag("-o")
      .out_flag(output)
      .flag("-c")
      .flags(m_cc)
      .dynamic_flags(flags)
      .in_flag(source);
}

step& gnu_cc::compile_shared(
    const target& target,
    const std::filesystem::path& source,
    const view<const std::vector<std::string>>& flags) {
  auto output = to_object(target, source);
  return this_build::executor.make_step(m_exe)
      .message("{} compile shared {}",
               name(),
               std::filesystem::relative(output, this_build::context.root()))
      .flag("-o")
      .out_flag(output)
      .flag("-c")
      .flags(m_cc)
      .dynamic_flags(flags)
      .in_flag(source);
}

step& gnu_cc::link(const target& target,
                   const std::vector<std::filesystem::path>& objects,
                   const view<linkable>& libraries,
                   const view<const std::vector<std::string>>& flags) {
  return this_build::executor.make_step(m_exe)
      .message(
          "{} link {}", name(), std::filesystem::relative(target.artifact()))
      .flag("-o")
      .out_flag(target.artifact())
      .flags(m_ld)
      .dynamic_flags(flags)
      .in_flags(objects)
      .in_flags(libraries
                | std::views::filter(&linkable::has_artifact)
                | std::views::transform(&linkable::artifact)
                | std::ranges::to<std::vector>());
}

step& gnu_cc::link_shared(const target& target,
                          const std::vector<std::filesystem::path>& objects,
                          const view<linkable>& libraries,
                          const view<const std::vector<std::string>>& flags) {
  return this_build::executor.make_step(m_exe)
      .message("{} link shared {}",
               name(),
               std::filesystem::relative(target.artifact()))
      .flag("-o")
      .out_flag(target.artifact())
      .flag("-shared")
      .flags(m_ld)
      .dynamic_flags(flags)
      .in_flags(objects)
      .in_flags(libraries
                | std::views::filter(&linkable::has_artifact)
                | std::views::transform(&linkable::artifact)
                | std::ranges::to<std::vector>());
}
}  // namespace bx::tool

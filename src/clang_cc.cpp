#include <buildx/tool/clang_cc.hpp>

#include <buildx/library.hpp>
#include <buildx/target.hpp>
#include <buildx/this_build.hpp>

namespace bx::tool {
void clang_cc::apply(std_f flag) {
  m_cc.push_back(std::format("-std=gnu{}", flag.v));
}

void clang_cc::apply(define_f flag) {
  m_cc.push_back(std::format("-D{}", flag.v));
}

void clang_cc::apply(define_kv flag) {
  m_cc.push_back(std::format("-D{}={}", flag.k, flag.v));
}

void clang_cc::apply(include_f flag) {
  m_cc.push_back(std::format("-I{}", flag.v));
}

void clang_cc::apply(cc_f flag) { m_cc.push_back(flag.v); }

void clang_cc::apply(ld_f flag) {
  m_ld.push_back(std::format("-Wl,{}", flag.v));
}

step& clang_cc::compile_static(const target& target,
                               const std::filesystem::path& source) {
  auto output = to_object(target, source);
  return this_build::executor.make_step(m_exe)
      .message("{} compile static {}",
               name(),
               std::filesystem::relative(output, this_build::context.root()))
      .flag("-o")
      .out_flag(output)
      .flag("-c")
      .flags(m_cc)
      .in_flag(source);
}

step& clang_cc::compile_shared(const target& target,
                               const std::filesystem::path& source) {
  auto output = to_object(target, source);
  return this_build::executor.make_step(m_exe)
      .message("{} compile shared {}",
               name(),
               std::filesystem::relative(output, this_build::context.root()))
      .flag("-o")
      .out_flag(output)
      .flag("-c")
      .flags(m_cc)
      .in_flag(source);
}

step& clang_cc::link_static(const target& target,
                            const std::vector<std::filesystem::path>& objects,
                            const view<library>& libraries) {
  return this_build::executor.make_step(m_exe)
      .message("{} link executable {}",
               name(),
               std::filesystem::relative(target.artifact()))
      .flag("-o")
      .out_flag(target.artifact())
      .flags(m_ld)
      .in_flags(objects)
      .in_flags(libraries
                | std::views::transform(&library::artifact)
                | std::ranges::to<std::vector>());
}

step& clang_cc::link_shared(const target& target,
                            const std::vector<std::filesystem::path>& objects,
                            const view<library>& libraries) {
  return this_build::executor.make_step(m_exe)
      .message("{} link shared {}",
               name(),
               std::filesystem::relative(target.artifact()))
      .flag("-o")
      .out_flag(target.artifact())
      .flag("-shared")
      .flags(m_ld)
      .in_flags(objects)
      .in_flags(libraries
                | std::views::transform(&library::artifact)
                | std::ranges::to<std::vector>());
}
}  // namespace bx::tool

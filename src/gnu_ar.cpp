#include <buildx/tool/gnu_ar.hpp>

#include <buildx/library.hpp>
#include <buildx/this_build.hpp>

#include <functional>

namespace bx::tool {
void gnu_ar::apply(ar_f flag) { m_ar.push_back(flag.v); }

step& gnu_ar::link_archive(const target& target,
                           const std::vector<std::filesystem::path>& objects,
                           const view<library>& libraries) {
  return this_build::executor.make_step(m_exe)
      .message("{} link archive {}",
               name(),
               std::filesystem::relative(target.artifact()))
      .flag("rcs")
      .flags(m_ar)
      .out_flag(target.artifact())
      .in_flags(objects)
      .in_flags(libraries
                | std::views::filter(std::not_fn(&library::is_shared))
                | std::views::transform(&library::artifact)
                | std::ranges::to<std::vector>());
}
}  // namespace bx::tool

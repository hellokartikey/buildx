#include <buildx/tool/gnu_ar.hpp>

#include <buildx/linkable.hpp>
#include <buildx/this_build.hpp>

namespace bx::tool {
void gnu_ar::apply(ar_f flag) { m_ar.push_back(flag.v); }

step& gnu_ar::archive(const target& target,
                      const std::vector<std::filesystem::path>& objects,
                      const view<linkable>& libraries,
                      const std::vector<std::string>& flags) {
  return this_build::executor.make_step(m_exe)
      .message(
          "{} archive {}", name(), std::filesystem::relative(target.artifact()))
      .flag("rcs")
      .flags(m_ar)
      .flags(flags)
      .out_flag(target.artifact())
      .in_flags(objects)
      .in_flags(libraries
                | std::views::transform(&linkable::artifact)
                | std::ranges::to<std::vector>());
}
}  // namespace bx::tool

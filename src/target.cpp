#include <buildx/target.hpp>

#include <buildx/library.hpp>
#include <buildx/this_build.hpp>

namespace bx {
bool target::has_artifact() const { return true; }

const view<linkable>& target::link_libraries() const { return m_link; }

view<linkable> target::all_link_libraries() const {
  return std::views::concat(
             link_libraries(),
             link_libraries()
                 | std::views::transform(&target::all_link_libraries)
                 | std::views::join)
         | as_view;
}

const std::vector<std::string>& target::compile_flags() const { return m_cc; }

std::vector<std::string> target::all_compile_flags() const {
  return std::views::concat(
             compile_flags(),
             link_libraries()
                 | std::views::transform(&target::all_compile_flags)
                 | std::views::join)
         | std::ranges::to<std::vector>();
}

const std::vector<std::string>& target::link_flags() const { return m_ld; }

std::vector<std::string> target::all_link_flags() const {
  return std::views::concat(link_flags(),
                            link_libraries()
                                | std::views::transform(&target::all_link_flags)
                                | std::views::join)
         | std::ranges::to<std::vector>();
}

const std::vector<std::string>& target::archive_flags() const { return m_ar; }

std::vector<std::string> target::all_archive_flags() const {
  return std::views::concat(
             archive_flags(),
             link_libraries()
                 | std::views::transform(&target::all_archive_flags)
                 | std::views::join)
         | std::ranges::to<std::vector>();
}
}  // namespace bx

#include <buildx/target.hpp>

#include <buildx/library.hpp>
#include <buildx/this_build.hpp>

namespace bx {
target::target(const std::string& name) : rule(name) {}

void target::build_steps(step& first, step& last) {
  if (files().empty() and headers().empty()) {
    last.depends_on(first);
  } else {
    compile_steps(first, last);
  }
}

toolchain& target::tools() {
  if (not m_tc) {
    return this_build::context.tools();
  }
  return *m_tc;
}

const std::vector<std::filesystem::path>& target::files() const {
  return m_files;
}

const std::vector<std::filesystem::path>& target::headers() const {
  return m_headers;
}

const view<library>& target::link_libraries() const { return m_link; }

view<library> target::all_link_libraries() const {
  return std::views::concat(
             link_libraries(),
             link_libraries()
                 | std::views::transform(&target::all_link_libraries)
                 | std::views::join)
         | as_view;
}
}  // namespace bx

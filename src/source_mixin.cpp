#include <buildx/source_mixin.hpp>

#include <buildx/this_build.hpp>

namespace bx {
toolchain& source_mixin::tools() {
  if (not m_tc) {
    return this_build::context.tools();
  }
  return *m_tc;
}

const std::vector<std::filesystem::path>& source_mixin::files() const {
  return m_files;
}

const std::vector<std::filesystem::path>& source_mixin::headers() const {
  return m_headers;
}

source_mixin::no_source::no_source(const target& target)
    : error("no sources provided for target {}", target.name()) {}
}

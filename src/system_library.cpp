#include <buildx/system_library.hpp>

namespace bx {
system_library::system_library(const std::string& name) : library(name) {}

std::filesystem::path system_library::artifact() const {
  auto file = std::format("lib{}.{}", name(), is_shared() ? "so" : "a");
  auto path = m_prefix / file;
  if (not m_version.empty()) {
    path += std::format(".{}", m_version);
  }
  return path;
}

const std::filesystem::path& system_library::path() const { return m_prefix; }

const std::string& system_library::version() const { return m_version; }

void system_library::build_steps(step& first, step& last) {
  last.depends_on(first);
}
}  // namespace bx

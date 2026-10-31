#include <buildx/system/library.hpp>

namespace bx::system {
std::filesystem::path library::artifact() const {
  auto file = std::format("lib{}.{}", name(), is_shared() ? "so" : "a");
  auto path = m_prefix / file;
  if (not m_version.empty()) {
    path += std::format(".{}", m_version);
  }
  return path;
}

const std::filesystem::path& library::path() const { return m_prefix; }

const std::string& library::version() const { return m_version; }

bool library::is_shared() const { return m_shared; }

void library::build_steps(step& first, step& last) { last.depends_on(first); }
}  // namespace bx::system

#ifndef BUILDX_SYSTEM_LIBRARY_HPP
#define BUILDX_SYSTEM_LIBRARY_HPP

#include <buildx/linkable.hpp>

namespace bx::system {
class library : public linkable {
 public:
  using linkable::linkable;

  std::filesystem::path artifact() const override;

  template <typename S>
  S& path(this S& self, const std::filesystem::path& path) {
    self.m_prefix = path;
    return self;
  }

  template <typename S>
  S& version(this S& self, const std::string& path) {
    self.m_prefix = path;
    return self;
  }

  template <typename S>
  S& shared(this S& self, bool value = true) {
      self.m_shared = value;
      return self;
  }

  const std::filesystem::path& path() const;
  const std::string& version() const;
  bool is_shared() const;

 protected:
  void build_steps(step& first, step& last) override;

 private:
  std::filesystem::path m_prefix = "/usr/lib/";
  std::string m_version;
  bool m_shared = true;
};
}  // namespace bx::system

#endif

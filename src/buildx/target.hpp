#ifndef BUILDX_TARGET_HPP
#define BUILDX_TARGET_HPP

#include <concepts>

#include <buildx/exceptions.hpp>
#include <buildx/rule.hpp>

namespace bx {
class linkable;
class target : public rule {
 public:
  target(const std::string& name);
  ~target() override = default;

  virtual std::filesystem::path artifact() const = 0;

  template <typename S>
  S& link(this S& self, linkable& library) {
    self.m_link.push_back(library);
    self.depends_on(library);
    return self;
  }

  template <typename S, typename... L>
    requires(std::derived_from<L, linkable> && ...)
  S& link(this S& self, linkable& library, L&... libraries) {
    self.link(library);
    return (self.link(libraries), ...);
  }

  template <typename S>
  S& link(this S& self, view<linkable> libraries) {
    for (auto& library : libraries) self.link(library);
    return self;
  }

  template <typename S>
  S& compile_flag(this S& self, const std::string& flag) {
    self.m_cc.push_back(flag);
    return self;
  }

  template <typename S>
  S& compile_flags(this S& self, const std::vector<std::string>& flags) {
    self.m_cc.append_range(flags);
    return self;
  }

  template <typename S>
  S& link_flag(this S& self, const std::string& flag) {
    self.m_ld.push_back(flag);
    return self;
  }

  template <typename S>
  S& link_flags(this S& self, const std::vector<std::string>& flags) {
    self.m_ld.append_range(flags);
    return self;
  }

  template <typename S>
  S& archive_flag(this S& self, const std::string& flag) {
    self.m_ar.push_back(flag);
    return self;
  }

  template <typename S>
  S& archive_flags(this S& self, const std::vector<std::string>& flags) {
    self.m_ar.append_range(flags);
    return self;
  }

  const std::vector<std::string>& compile_flags() const;
  std::vector<std::string> all_compile_flags() const;

  const std::vector<std::string>& link_flags() const;
  std::vector<std::string> all_link_flags() const;

  const std::vector<std::string>& archive_flags() const;
  std::vector<std::string> all_archive_flags() const;

  const view<linkable>& link_libraries() const;
  view<linkable> all_link_libraries() const;

 private:
  std::vector<std::string> m_cc;
  std::vector<std::string> m_ld;
  std::vector<std::string> m_ar;

  view<linkable> m_link;
};
}  // namespace bx

#endif

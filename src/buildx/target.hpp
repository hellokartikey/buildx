#ifndef BUILDX_TARGET_HPP
#define BUILDX_TARGET_HPP

#include <concepts>
#include <memory>
#include <ranges>
#include <utility>

#include <buildx/exceptions.hpp>
#include <buildx/rule.hpp>
#include <buildx/toolchain.hpp>

namespace bx {
class library;
class target : public rule {
 public:
  target(const std::string& name);
  ~target() override = default;

  virtual std::filesystem::path artifact() const = 0;

  template <typename S>
  S& file(this S& self, const std::filesystem::path& file) {
    self.m_files.push_back(file);
    return self;
  }

  template <typename S>
  S& files(this S& self, const std::vector<std::filesystem::path>& files) {
    self.m_files.append_range(files);
    return self;
  }

  template <typename S>
  S& files_in(this S& self,
              const std::filesystem::path& path,
              const std::vector<std::string>& files) {
    self.m_files.append_range(
        files | std::views::transform([&](auto& file) { return path / file; }));
    return self;
  }

  template <typename S>
  S& header(this S& self, const std::filesystem::path& file) {
    self.m_headers.push_back(file);
    return self;
  }

  template <typename S>
  S& headers(this S& self, const std::vector<std::filesystem::path>& files) {
    self.m_headers.append_range(files);
    return self;
  }

  template <typename S>
  S& headers_in(this S& self,
                const std::filesystem::path& path,
                const std::vector<std::string>& files) {
    self.m_headers.append_range(
        files | std::views::transform([&](auto& file) { return path / file; }));
    return self;
  }

  template <std::derived_from<toolchain> T, typename S>
  S& use(this S& self, const T& tc) {
    self.m_tc = std::make_unique<T>(tc);
    return self;
  }

  template <std::derived_from<toolchain> T, typename S, typename... As>
  S& use(this S& self, std::in_place_t, As&&... args) {
    self.m_tc = std::make_unique<T>(std::forward<As>(args)...);
    return self;
  }

  template <typename S>
  S& link(this S& self, library& library) {
    self.m_link.push_back(library);
    self.depends_on(library);
    return self;
  }

  template <typename S, typename... L>
    requires(std::derived_from<L, library> && ...)
  S& link(this S& self, library& library, L&... libraries) {
    self.link(library);
    return (self.link(libraries), ...);
  }

  template <typename S>
  S& link(this S& self, view<library> libraries) {
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

  toolchain& tools();
  const std::vector<std::filesystem::path>& files() const;
  const std::vector<std::filesystem::path>& headers() const;

  const std::vector<std::string>& compile_flags() const;
  std::vector<std::string> all_compile_flags() const;

  const std::vector<std::string>& link_flags() const;
  std::vector<std::string> all_link_flags() const;

  const std::vector<std::string>& archive_flags() const;
  std::vector<std::string> all_archive_flags() const;

  const view<library>& link_libraries() const;
  view<library> all_link_libraries() const;

 protected:
  void build_steps(step& first, step& last) override;
  virtual void compile_steps(step& first, step& last) = 0;

 private:
  std::unique_ptr<toolchain> m_tc;

  std::vector<std::filesystem::path> m_files;
  std::vector<std::filesystem::path> m_headers;

  std::vector<std::string> m_cc;
  std::vector<std::string> m_ld;
  std::vector<std::string> m_ar;

  view<library> m_link;
};
}  // namespace bx

#endif

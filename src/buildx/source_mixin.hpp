#ifndef BUILDX_SOURCE_MIXIN_HPP
#define BUILDX_SOURCE_MIXIN_HPP

#include <memory>
#include <filesystem>
#include <ranges>
#include <utility>
#include <vector>

#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx {
class source_mixin {
public:
  struct no_source : public error {
      no_source(const target& target);
  };

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

  toolchain& tools();
  const std::vector<std::filesystem::path>& files() const;
  const std::vector<std::filesystem::path>& headers() const;

private:
  std::unique_ptr<toolchain> m_tc;

  std::vector<std::filesystem::path> m_files;
  std::vector<std::filesystem::path> m_headers;
};
}

#endif

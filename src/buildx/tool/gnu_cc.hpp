#ifndef BUILDX_TOOL_GNU_CC_HPP
#define BUILDX_TOOL_GNU_CC_HPP

#include <buildx/tool/cc.hpp>
#include <buildx/tool/ld.hpp>

namespace bx::tool {
class gnu_cc : public ld, public cc {
 public:
  std::string to_string(cc_f flag) const override;
  std::string to_string(link_f flag) const override;
  std::string to_string(ld_f flag) const override;
  std::string to_string(std_f flag) const override;
  std::string to_string(define_f flag) const override;
  std::string to_string(define_kv flag) const override;
  std::string to_string(include_f flag) const override;

  using cc::apply;
  using ld::apply;
  void apply(cc_f flag) override;
  void apply(ld_f flag) override;

  step& compile(
      const target& target,
      const std::filesystem::path& source,
      const view<const std::vector<std::string>>& flags = {}) override;

  step& compile_shared(
      const target& target,
      const std::filesystem::path& source,
      const view<const std::vector<std::string>>& flags = {}) override;

  step& link(const target& target,
             const std::vector<std::filesystem::path>& objects,
             const view<linkable>& libraries = {},
             const view<const std::vector<std::string>>& flags = {}) override;

  step& link_shared(
      const target& target,
      const std::vector<std::filesystem::path>& objects,
      const view<linkable>& libraries = {},
      const view<const std::vector<std::string>>& flags = {}) override;

 private:
  std::string m_exe = "gcc";

  std::vector<std::string> m_cc;
  std::vector<std::string> m_ld;
};
}  // namespace bx::tool

#endif

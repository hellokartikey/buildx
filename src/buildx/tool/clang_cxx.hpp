#ifndef BUILDX_TOOL_CLANG_CXX_HPP
#define BUILDX_TOOL_CLANG_CXX_HPP

#include <buildx/tool/cxx.hpp>
#include <buildx/tool/ld.hpp>

namespace bx::tool {
class clang_cxx : public cxx, public ld {
 public:
  std::string to_string(ld_f flag) const override;
  std::string to_string(cc_f flag) const override;
  std::string to_string(std_f flag) const override;
  std::string to_string(define_f flag) const override;
  std::string to_string(define_kv flag) const override;
  std::string to_string(include_f flag) const override;

  using cxx::apply;
  using ld::apply;
  void apply(cc_f flag) override;
  void apply(ld_f flag) override;

  step& compile(const target& target,
                const std::filesystem::path& source,
                const std::vector<std::string>& flags = {}) override;

  step& compile_shared(const target& target,
                       const std::filesystem::path& source,
                       const std::vector<std::string>& flags = {}) override;

  step& link(const target& target,
             const std::vector<std::filesystem::path>& objects,
             const view<linkable>& libraries = {},
             const std::vector<std::string>& flags = {}) override;

  step& link_shared(const target& target,
                    const std::vector<std::filesystem::path>& objects,
                    const view<linkable>& libraries = {},
                    const std::vector<std::string>& flags = {}) override;

 private:
  std::string m_exe = "clang++";

  std::vector<std::string> m_cc;
  std::vector<std::string> m_ld;
};
}  // namespace bx::tool

#endif

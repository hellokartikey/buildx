#ifndef BUILDX_TOOL_CLANG_CC_HPP
#define BUILDX_TOOL_CLANG_CC_HPP

#include <buildx/tool/cc.hpp>
#include <buildx/tool/ld.hpp>

namespace bx::tool {
class clang_cc : public cc, public ld {
 public:
  void apply(std_f flag) override;
  void apply(define_f flag) override;
  void apply(define_kv flag) override;
  void apply(include_f flag) override;

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
  std::string m_exe = "clang";

  std::vector<std::string> m_cc;
  std::vector<std::string> m_ld;
};
}  // namespace bx::tool

#endif

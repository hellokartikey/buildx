#ifndef BUILDX_TOOL_CLANG_CC_HPP
#define BUILDX_TOOL_CLANG_CC_HPP

#include <buildx/tool/c_mixins.hpp>
#include <buildx/tool/compiler.hpp>
#include <buildx/tool/linker.hpp>

namespace bx::tool {
class clang_cc : public compiler, public linker, public cc_mixin {
 public:
  void apply(std_f flag);
  void apply(define_f flag);
  void apply(define_kv flag);
  void apply(include_f flag);

  void apply(cc_f flag);
  void apply(ld_f flag);

  step& compile(const target& target,
                const std::filesystem::path& source) override;

  step& compile_shared(const target& target,
                       const std::filesystem::path& source) override;

  step& link(const target& target,
             const std::vector<std::filesystem::path>& objects,
             const view<library>& libraries = {}) override;

  step& link_shared(const target& target,
                    const std::vector<std::filesystem::path>& objects,
                    const view<library>& libraries = {}) override;

 private:
  std::string m_exe = "clang";

  std::vector<std::string> m_cc;
  std::vector<std::string> m_ld;
};
}  // namespace bx::tool

#endif

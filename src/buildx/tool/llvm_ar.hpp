#ifndef BUILDX_TOOL_LLVM_AR_HPP
#define BUILDX_TOOL_LLVM_AR_HPP

#include <buildx/tool/archiver.hpp>
#include <buildx/tool/c_mixins.hpp>

namespace bx::tool {
class llvm_ar : public archiver, public ar_mixin {
 public:
  void apply(ar_f flag);

  step& link_archive(const target& target,
                     const std::vector<std::filesystem::path>& objects,
                     const view<library>& libraries = {}) override;

 private:
  std::string m_exe = "llvm-ar";

  std::vector<std::string> m_ar;
};
}  // namespace bx::tool

#endif

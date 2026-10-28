#include <buildx/target.hpp>
#include <buildx/this_build.hpp>
#include <buildx/tool/c_mixins.hpp>

namespace bx {
cc_mixin::std_f cc_mixin::std(int v) { return {v}; }

cc_mixin::define_f cc_mixin::define(const std::string& v) { return {v}; }

cc_mixin::define_kv cc_mixin::define(const std::string& k,
                                     const std::string& v) {
  return {k, v};
}

cc_mixin::include_f cc_mixin::include(const std::filesystem::path& v) {
  return {v};
}

cc_mixin::cc_f cc_mixin::c_flag(const std::string& v) { return {v}; }

cc_mixin::ld_f cc_mixin::l_flag(const std::string& v) { return {v}; }

ar_mixin::ar_f ar_mixin::a_flag(const std::string& v) { return {v}; }

std::filesystem::path to_object(const target& target,
                                const std::filesystem::path& source) {
  auto& ctx = this_build::context;
  using std::filesystem::relative;
  auto output = ctx.scratch_path(target) / relative(source, ctx.root());
  output += ".o";
  return output;
}
}  // namespace bx

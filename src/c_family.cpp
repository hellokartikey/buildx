#include <buildx/tool/c_family.hpp>

#include <buildx/target.hpp>
#include <buildx/this_build.hpp>

namespace bx::tool {
c_family::std_f c_family::std(int v) { return {v}; }

c_family::define_f c_family::define(const std::string& v) { return {v}; }

c_family::define_kv c_family::define(const std::string& k,
                                     const std::string& v) {
  return {k, v};
}

c_family::include_f c_family::include(const std::filesystem::path& v) {
  return {v};
}

c_family::cc_f c_family::c_flag(const std::string& v) { return {v}; }

void c_family::apply(std_f flag) { apply(c_flag(to_string(flag))); }

void c_family::apply(define_f flag) { apply(c_flag(to_string(flag))); }

void c_family::apply(define_kv flag) { apply(c_flag(to_string(flag))); }

void c_family::apply(include_f flag) { apply(c_flag(to_string(flag))); }

std::filesystem::path to_object(const target& target,
                                const std::filesystem::path& source) {
  auto& ctx = this_build::context;
  using std::filesystem::relative;
  auto output = ctx.scratch_path(target) / relative(source, ctx.root());
  output += ".o";
  return output;
}
}  // namespace bx::tool

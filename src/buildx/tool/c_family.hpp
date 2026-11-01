#ifndef BUILDX_TOOL_C_FAMILY_HPP
#define BUILDX_TOOL_C_FAMILY_HPP

#include <filesystem>
#include <string>

#include <buildx/target.hpp>

namespace bx::tool {
struct c_family {
  struct std_f {
    int v;
  };

  struct define_f {
    std::string v;
  };

  struct define_kv {
    std::string k, v;
  };

  struct include_f {
    std::filesystem::path v;
  };

  struct cc_f {
    std::string v;
  };

  static std_f std(int std);
  static define_f define(const std::string& define);
  static define_kv define(const std::string& key, const std::string& value);
  static include_f include(const std::filesystem::path& path);

  static cc_f c_flag(const std::string& flag);

  virtual void apply(std_f flag) = 0;
  virtual void apply(define_f flag) = 0;
  virtual void apply(define_kv flag) = 0;
  virtual void apply(include_f flag) = 0;
  virtual void apply(cc_f flag) = 0;
};

std::filesystem::path to_object(const target& target,
                                const std::filesystem::path& source);
}  // namespace bx::tool

#endif

#ifndef BUILDX_TOOL_AR_HPP
#define BUILDX_TOOL_AR_HPP

#include <string>

#include <buildx/tool/archiver.hpp>

namespace bx::tool {
class ar : public archiver {
 public:
  struct ar_f {
    std::string v;
  };

  static ar_f a_flag(const std::string& flag);

  virtual void apply(ar_f flag) = 0;
};
}  // namespace bx::tool

#endif

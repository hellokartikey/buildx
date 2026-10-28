#ifndef BUILDX_EXCEPTIONS_HPP
#define BUILDX_EXCEPTIONS_HPP

#include <format>
#include <stdexcept>

namespace bx {
class error : public std::runtime_error {
 public:
  error(const std::string& message);

  template <typename... As>
  error(std::format_string<As...> fmt, As&&... args)
      : error(std::format(fmt, std::forward<As>(args)...)) {}
};
}  // namespace bx

#endif

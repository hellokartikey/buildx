#ifndef BUILDX_EXCEPTIONS_HPP
#define BUILDX_EXCEPTIONS_HPP

#include <format>
#include <stdexcept>

namespace bx {
class error : public std::runtime_error {
public:
    error(const std::string& message);

    template <typename... Args>
    error(std::format_string<Args...> fmt, Args&&... args)
        : error(std::format(fmt, std::forward<Args>(args)...)) {}
};
}

#endif

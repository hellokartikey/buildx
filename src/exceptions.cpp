#include <buildx/exceptions.hpp>

namespace bx {
error::error(const std::string& message) : std::runtime_error(message) {}
}

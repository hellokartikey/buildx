#include "buildx/exceptions.hpp"

#include <format>

#include "buildx/rule.hpp"

namespace bx {
error::error(const std::string& message)
    : std::runtime_error(std::format("buildx error: {}", message)) {}

cyclic_dependency::cyclic_dependency(const rule& parent, const rule& child)
    : error(std::format("{} already depends on {}", parent.name(), child.name())) {}
}

#include <buildx/phony.hpp>

namespace bx {
phony::phony(const std::string& name) : rule(name) {}

void phony::build_steps(step& first, step& last) {
    last.depends_on(first);
}
}

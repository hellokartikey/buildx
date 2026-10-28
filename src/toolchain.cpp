#include <buildx/toolchain.hpp>

#include <buildx/target.hpp>

namespace bx {
toolchain::not_implemented::not_implemented(
    const toolchain& chain,
    const std::string& method
) : error("toolchain {} does not implement {}", chain.name(), method) {}
}

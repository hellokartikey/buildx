#include <buildx/target.hpp>
#include <buildx/toolchain.hpp>

namespace bx {
toolchain::not_implemented::not_implemented(const toolchain& chain,
                                            const std::string& method)
    : error("toolchain {} does not implement {}", chain.name(), method) {}
}  // namespace bx

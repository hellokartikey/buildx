#include <buildx/tool/compiler.hpp>

namespace bx::tool {
step& compiler::compile(const target& target,
                        const std::filesystem::path& source) {
  throw not_implemented(*this, "compile()");
}

step& compiler::compile_shared(const target& target,
                               const std::filesystem::path& source) {
  throw not_implemented(*this, "compile_shared()");
}
}  // namespace bx::tool

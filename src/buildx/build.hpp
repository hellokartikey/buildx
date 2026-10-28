#ifndef BUILDX_BUILD_HPP
#define BUILDX_BUILD_HPP

#include <buildx/archive_tool.hpp>
#include <buildx/toolchain.hpp>
#include <buildx/command.hpp>
#include <buildx/context.hpp>
#include <buildx/exceptions.hpp>
#include <buildx/executable.hpp>
#include <buildx/executor.hpp>
#include <buildx/clang.hpp>
#include <buildx/clangxx.hpp>
#include <buildx/gcc.hpp>
#include <buildx/gxx.hpp>
#include <buildx/library.hpp>
#include <buildx/phony.hpp>
#include <buildx/rule.hpp>
#include <buildx/script.hpp>
#include <buildx/shared_tool.hpp>
#include <buildx/static_tool.hpp>
#include <buildx/step.hpp>
#include <buildx/system_library.hpp>
#include <buildx/target.hpp>
#include <buildx/this_build.hpp>
#include <buildx/tool/c_mixins.hpp>
#include <buildx/tool/clang_cc.hpp>
#include <buildx/tool/clang_cxx.hpp>
#include <buildx/tool/gnu_ar.hpp>
#include <buildx/tool/gnu_cc.hpp>
#include <buildx/tool/gnu_cxx.hpp>
#include <buildx/tool/llvm_ar.hpp>
#include <buildx/view.hpp>

namespace bx {
void build(context& ctx);
}

#endif

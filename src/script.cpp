#include <buildx/script.hpp>

#include <fstream>

#include <buildx/system_library.hpp>
#include <buildx/this_build.hpp>

namespace bx {
script::script(embed_file libbx, embed_file headers)
    : executable("bx")
    , m_lib(libbx)
    , m_head(headers) {}

std::filesystem::path script::artifact() const {
    return this_build::context.scratch_path(*this) / name();
}

void script::compile_steps(step& first, step& last) {
    auto& ctx = this_build::context;
    auto& exec = this_build::executor;

    // extract libbx.a
    std::filesystem::create_directories(ctx.scratch_path());
    std::ofstream libbx_a{ ctx.scratch_path() / m_lib.name, std::ios::binary };
    libbx_a.write(m_lib.data, m_lib.size);

    // extract headers.tar
    std::ofstream head_tar{ ctx.scratch_path() / m_head.name, std::ios::binary };
    head_tar.write(m_head.data, m_head.size);

    auto& tar = exec
        .make_step("tar")
        .flag("-xf")
        .in_flag(ctx.scratch_path() / m_head.name)
        .flag("-C")
        .flag(ctx.scratch_path())
        .depends_on(first);

    // link libbx.a
    link(ctx.add<system_library>("bx").path(ctx.scratch_path()));

    auto& first_exe = exec.make_step().depends_on(tar);
    executable::compile_steps(first_exe, last);
}
}

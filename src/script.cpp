#include <buildx/script.hpp>

#include <fstream>

#include <buildx/system_library.hpp>
#include <buildx/this_build.hpp>

namespace bx {
script::script(embed_file libbx, embed_file headers)
    : executable("bx"), m_lib(libbx), m_head(headers) {}

std::filesystem::path script::artifact() const {
  return this_build::context.scratch_path(*this) / name();
}

void script::compile_steps(step& first, step& last) {
  auto& ctx = this_build::context;
  auto& exec = this_build::executor;

  auto& extract_a =
      exec.make_step([this] {
            std::filesystem::create_directories(ctx.scratch_path());
            std::ofstream libbx_a{ctx.scratch_path() / m_lib.name,
                                  std::ios::binary};
            libbx_a.write(m_lib.data, m_lib.size);
          })
          .message("extracting library {}", m_lib.name)
          .depends_on(first);

  auto& extract_tar =
      exec.make_step([this] {
            std::ofstream head_tar{ctx.scratch_path() / m_head.name,
                                   std::ios::binary};
            head_tar.write(m_head.data, m_head.size);
          })
          .message("extracting headers {}", m_head.name)
          .depends_on(first);

  auto& tar = exec.make_step("tar")
                  .flag("-xf")
                  .in_flag(ctx.scratch_path() / m_head.name)
                  .flag("-C")
                  .flag(ctx.scratch_path())
                  .depends_on(extract_tar);

  link(ctx.add<system_library>("bx").path(ctx.scratch_path()));

  auto& barrier = exec.make_step().depends_on(tar).depends_on(extract_a);

  executable::compile_steps(barrier, last);
}
}  // namespace bx

#include <buildx/script.hpp>

#include <fstream>
#include <print>
#include <string>

#include <archive.h>
#include <archive_entry.h>

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

  auto& libbx = exec.make_step([this] {
                      std::filesystem::create_directories(ctx.scratch_path());
                      std::ofstream libbx_a{ctx.scratch_path() / m_lib.name,
                                            std::ios::binary};
                      libbx_a.write(m_lib.data, m_lib.size);
                    })
                    .depends_on(first);

  auto& headers =
      exec.make_step([&, this] {
            archive* ar = archive_read_new();
            archive_read_support_filter_all(ar);
            archive_read_support_format_all(ar);

            auto r = archive_read_open_memory(ar, m_head.data, m_head.size);
            if (r != ARCHIVE_OK)
              throw archive_error(archive_error_string(ar));

            {
              std::vector<char> buff;
              archive_entry* entry;
              while (archive_read_next_header(ar, &entry) == ARCHIVE_OK) {
                auto size = archive_entry_size(entry);
                buff.reserve(size);

                auto read = archive_read_data(ar, buff.data(), buff.capacity());
                if (read < 0) throw archive_error(archive_error_string(ar));

                auto* name = archive_entry_pathname(entry);
                auto path = ctx.scratch_path() / std::filesystem::path(name);
                std::filesystem::create_directories(path.parent_path());

                std::ofstream out{path};
                out.write(buff.data(), read);
              }
            }

            archive_read_close(ar);
            archive_read_free(ar);
          })
          .depends_on(first);

  link(ctx.add<system_library>("bx").path(ctx.scratch_path()));

  auto& barrier = exec.make_step().depends_on(headers).depends_on(libbx);

  executable::compile_steps(barrier, last);
}

script::archive_error::archive_error(const char* err) : error(err) {}
}  // namespace bx

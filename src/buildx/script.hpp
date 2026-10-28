#ifndef BUILDX_SCRIPT_HPP
#define BUILDX_SCRIPT_HPP

#include <buildx/exceptions.hpp>
#include <buildx/executable.hpp>

namespace bx {
struct embed_file {
  const char* name;
  const char* data;
  std::size_t size;
};

class script : public executable {
 public:
  struct archive_error : error {
    archive_error(const char* err);
  };

  script(embed_file libbx, embed_file headers);

  std::filesystem::path artifact() const override;

 protected:
  void compile_steps(step& first, step& last) override;

 private:
  embed_file m_lib;
  embed_file m_head;
};
}  // namespace bx

#endif

#ifndef BUILDX_LIBRARY_HPP
#define BUILDX_LIBRARY_HPP

#include <buildx/linkable.hpp>
#include <buildx/source_mixin.hpp>
#include <buildx/tool_mixin.hpp>

namespace bx {
class library : public linkable, public source_mixin, public tool_mixin {
 public:
  using linkable::linkable;

  std::filesystem::path artifact() const override;

  template <typename S>
  S& shared(this S& self, bool value = true) {
    self.m_shared = value;
    return self;
  }

  bool is_shared() const;

 protected:
  void build_steps(step& first, step& last) override;

  virtual void compile_shared(step& first, step& last);
  virtual void compile_archive(step& first, step& last);

 private:
  bool m_shared = false;
};
}  // namespace bx

#endif

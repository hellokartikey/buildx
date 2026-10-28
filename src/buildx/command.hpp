#ifndef BUILDX_COMMAND_HPP
#define BUILDX_COMMAND_HPP

#include <buildx/rule.hpp>

namespace bx {
class command final : public rule {
 public:
  command(const std::string& name);

  command& executable(const std::string& exe);
  const std::string& executable() const;

  command& flag(const std::string& flag);
  command& flags(const std::vector<std::string>& flags);
  const std::vector<std::string>& flags() const;

  command& message(const std::string& exe);
  const std::string& message() const;

  template <typename S, typename... As>
  S& message(this S& self, std::format_string<As...> fmt, As&&... args) {
    return self.message(std::format(fmt, std::forward<As>(args)...));
  }

 protected:
  void build_steps(step& first, step& last) override;

 private:
  std::string m_exe;
  std::vector<std::string> m_args;
  std::string m_message;
};
}  // namespace bx

#endif

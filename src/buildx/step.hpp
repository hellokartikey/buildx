#ifndef BUILDX_STEP_HPP
#define BUILDX_STEP_HPP

#include <filesystem>
#include <string>
#include <vector>

#include <buildx/exceptions.hpp>
#include <buildx/view.hpp>

namespace bx {
class executor;
class step {
 public:
  struct executable_not_found : error {
    executable_not_found(const std::string exe);
  };

  struct cycle_detected : error {
    cycle_detected(const step& parent, const step& other);
  };

  struct pending_dependencies : error {
    pending_dependencies(const step& step);
  };

  struct execution_error : error {
    execution_error(const step& step);
  };

  friend class executor;

  step(std::uint64_t id);
  step(std::uint64_t id, const std::string& exe);

  ~step() = default;

  step(const step&) = delete;
  step& operator=(const step&) = delete;

  step(step&&) = delete;
  step& operator=(step&&) = delete;

  bool is_phony() const;
  bool is_done() const;
  bool is_ready() const;

  bool is_direct_dependency(const step& other) const;
  bool is_dependency(const step& other) const;

  const std::string& executable() const;

  step& flag(const std::string& flag);
  step& flags(const std::vector<std::string>& flags);
  const std::vector<std::string>& flags() const;

  template <typename... As>
  step& message(std::format_string<As...> fmt, As&&... args) {
    message(std::format(fmt, std::forward<As>(args)...));
    return *this;
  }

  step& message(const std::string& message);
  const std::string& message() const;

  step& depends_on(const step& other);
  step& depends_on(const view<step>& others);

  step& in_file(const std::filesystem::path& file);
  step& in_files(const std::vector<std::filesystem::path>& files);
  const std::vector<std::filesystem::path>& in_files() const;

  step& in_flag(const std::filesystem::path& file);
  step& in_flags(const std::vector<std::filesystem::path>& files);

  step& out_file(const std::filesystem::path& file);
  step& out_files(const std::vector<std::filesystem::path>& files);
  const std::vector<std::filesystem::path>& out_files() const;

  step& out_flag(const std::filesystem::path& file);
  step& out_flags(const std::vector<std::filesystem::path>& files);

  int rc() const;

 private:
  std::uint64_t m_id{};
  std::vector<const step*> m_depends;

  std::string m_exe;
  std::vector<std::string> m_flags;

  std::vector<std::filesystem::path> m_in;
  std::vector<std::filesystem::path> m_out;

  std::string m_message;

  std::function<void(void)> m_func;

  int m_rc = -1;
  bool m_phony{};
};
}  // namespace bx

#endif

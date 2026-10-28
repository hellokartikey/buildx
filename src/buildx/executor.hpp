#ifndef BUILDX_EXECUTOR_HPP
#define BUILDX_EXECUTOR_HPP

#include <buildx/rule.hpp>
#include <buildx/step.hpp>
#include <list>
#include <thread>

int main(int argc, char** argv);

namespace bx {
class executor {
 public:
  friend int ::main(int argc, char** argv);

  executor(std::uint64_t concurrency = std::thread::hardware_concurrency());
  ~executor() = default;

  executor(const executor&) = delete;
  executor& operator=(const executor&) = delete;

  executor(executor&&) = delete;
  executor& operator=(executor&&) = delete;

  step& make_step();
  step& make_step(const std::string& exe);

  step& operator[](std::uint64_t id);
  const step& operator[](std::uint64_t id) const;

  std::uint64_t concurrency() const;
  executor& concurrency(std::uint64_t concurrency);

  void exec_all();
  void build_steps(rule& rule);

 private:
  std::list<step> m_steps;
  std::uint64_t m_concurrency;
};
}  // namespace bx

#endif

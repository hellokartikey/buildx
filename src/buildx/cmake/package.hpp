#ifndef BUILDX_CMAKE_PACKAGE_HPP
#define BUILDX_CMAKE_PACKAGE_HPP

#include <buildx/linkable.hpp>
#include <buildx/tool_mixin.hpp>

namespace bx::cmake {
class package : public linkable, public tool_mixin {
 public:
  using linkable::linkable;

  bool has_artifact() const override;
  std::filesystem::path artifact() const override;

  package& cmake_minimum_required(const std::string& version);

  package& find_package(const std::string& name);
  package& version(const std::string& version);

  package& component(const std::string& name);
  package& components(const std::vector<std::string>& names);

  package& optional_component(const std::string& name);
  package& optional_components(const std::vector<std::string>& names);

  package& target(const std::string& name);
  package& targets(const std::vector<std::string>& names);

 protected:
  void build_steps(step& first, step& last) override;

 private:
  std::string m_cmake_version = "4.0";
  std::string m_name;
  std::string m_version;

  std::vector<std::string> m_components;
  std::vector<std::string> m_optional;

  std::vector<std::string> m_targets;

  bool m_required = true;
};
}  // namespace bx::cmake

#endif

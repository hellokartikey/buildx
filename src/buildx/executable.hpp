#ifndef BUILDX_EXECUTABLE_HPP
#define BUILDX_EXECUTABLE_HPP

#include <buildx/command.hpp>
#include <buildx/target.hpp>

namespace bx {
class executable : public target {
public:
    executable(const std::string& name);

    std::filesystem::path artifact() const override;

    command& run();

protected:
    void compile_steps(step& first, step& last) override;
};
}

#endif

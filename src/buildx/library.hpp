#ifndef BUILDX_LIBRARY_HPP
#define BUILDX_LIBRARY_HPP

#include <buildx/target.hpp>

namespace bx {
class library : public target {
public:
    library(const std::string& name);

    std::filesystem::path artifact() const override;

    template <typename S>
    S& shared(this S& self, bool value) {
        self.m_shared = value;
        return self;
    }

    bool is_shared() const;

protected:
    void compile_steps(step& first, step& last) const override;

    virtual void compile_shared(step& first, step& last) const;
    virtual void compile_archive(step& first, step& last) const;

private:
    bool m_shared = false;
};
}

#endif

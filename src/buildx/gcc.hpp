#ifndef BUILDX_GCC_HPP
#define BUILDX_GCC_HPP

#include <buildx/tool/gnu_ar.hpp>
#include <buildx/tool/gnu_cc.hpp>

namespace bx {
struct gcc : tool::gnu_cc, tool::gnu_ar {
    template <typename... As>
    gcc(As&&... args) { configure(std::forward<As>(args)...); }

    std::string name() const override;

    using gnu_cc::apply;
    using gnu_ar::apply;
};
}

#endif

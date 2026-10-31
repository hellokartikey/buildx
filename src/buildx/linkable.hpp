#ifndef BUILDX_LINKABLE_HPP
#define BUILDX_LINKABLE_HPP

#include <buildx/target.hpp>

namespace bx {
class linkable : public target {
public:
    using target::target;
};
}

#endif

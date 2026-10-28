#ifndef BUILDX_TOOLCHAIN_HPP
#define BUILDX_TOOLCHAIN_HPP

#include <buildx/exceptions.hpp>

namespace bx {
class toolchain {
public:
    struct not_implemented : error {
        not_implemented(const toolchain& chain, const std::string& method);
    };

    static constexpr struct flags_t {} flags{};

    toolchain() = default;
    virtual ~toolchain() = default;

    virtual std::string name() const = 0;

    template<typename S, typename... Args>
    S& configure(this S& self, Args&&... args) {
        (self.apply(std::forward<Args>(args)), ...);
        return self;
    }

    template<std::derived_from<toolchain> T>
    T& as() { return dynamic_cast<T&>(*this); }
};
}

#endif

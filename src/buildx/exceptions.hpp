#ifndef BUILDX_EXCEPTIONS_HPP
#define BUILDX_EXCEPTIONS_HPP

#include <stdexcept>

namespace bx {
class rule;

class error : public std::runtime_error {
public:
    error(const std::string& message);
    ~error() override = default;
};

class cyclic_dependency: public error {
public:
    cyclic_dependency(const rule& parent, const rule& child);
    ~cyclic_dependency() override = default;
};
}

#endif

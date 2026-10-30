#include <fmt/base.h>

#include "foo.h"
#include "bar.h"

int main() {
    fmt::println("Hello {}, World {}!", foo(), bar());
    return 0;
}

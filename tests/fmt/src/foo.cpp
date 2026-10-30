#include "bar.h"

int foo() {
#ifdef FOO
    return 67;
#else
    return 42;
#endif
}

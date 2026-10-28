#include "bar.h"

int foo() {
#ifdef FOO
    return 42 + bar();
#else
    return 42;
#endif
}

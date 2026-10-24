#include <stdio.h>

#include "foo.h"
#include "bar.h"

int main() {
    printf("Hello %d, World! %d\n", foo(), bar());
    return 0;
}

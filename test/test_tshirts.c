#include <assert.h>

int testTshirtSize() {
    printf("\nTshirt size test\n");
    assert(size(37) == 'S');
    assert(size(40) == 'M');
    assert(size(43) == 'L');
    printf("All is well (maybe!)\n");
    return 0;
}

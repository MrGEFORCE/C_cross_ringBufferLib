#include <stdlib.h>
#include "rbExtApi.h"

void* rbLibMalloc(int size) {
    return malloc(size);
}

void rbLibFree(void* ptr) {
    free(ptr);
}
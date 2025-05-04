#include "mylib.h"

size_t strlen(const char*const s) {
    int len=0;
    while (s[len])
        len++;
    return len;
}

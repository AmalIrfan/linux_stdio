#include "mylib.h"

void* memset(char*const dest, size_t const_, size_t size) {
	size_t i = 0;
	while (i < size) {
		dest[i] = const_;
		i++;
	}
	return dest;
}

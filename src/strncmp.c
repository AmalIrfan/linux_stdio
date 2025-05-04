#include "mylib.h"

ssize_t strncmp(const char*const a, const char*const b, size_t l) {
	size_t i = 0;
	while (i < l) {
		if (a[i] != b[i])
			return a[i] - b[i];
		i++;
	}
	return 0;
}

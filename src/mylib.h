#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>
#include <sys/types.h>

struct string {
	char *p;
	size_t l;
	size_t cap;
};

struct view {
	char *p;
	size_t l;
};

size_t strlen(const char*const s);
size_t strcpy(char* dest, const char* src);
ssize_t strncmp(const char*const a, const char*const b, size_t l);
void* memset(char*const dest, size_t const_, size_t size);

/* if l == -1 then use strlen
     size_t puts(const char*const s, -1); 
   else
     size_t puts(cons tchar*const s, size_t l); */
size_t puts(const char*const s, size_t l);

/* if cap == -1 then use internal buffer
     size_t gets(char**const buf, -1); 
   else
     size_t gets(char*const*const buf, size_t cap); */
size_t gets(char**const buf, size_t cap);

#endif /* MYLIB_H_ */

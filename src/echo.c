#include "mylib.h"

/* NOTE: gets can take
   `char**const` and `char*const*const`
   this is so that if cap == -1 we can return a
   internal buffer pointer.
   if cap != -1 we treat pointer as a pointer to
   external buffer, derefrence it and write to it

   I could just accept `char*const` when cap!=-1
   but that might be confusing, best option is
   probably to provide seperate functions */
int main() {
	char allocation[1024];
	struct string s = {0};
	struct view v = {0};
	/* the data exists here, in 's', by
	   extension 'allocation' */
	s.p = allocation,
	s.l = 0,
	s.cap = 1024;
	/* read into a view, this makes dealing
	   with strings easier */
	v.p = s.p + s.l,  /* for consistency (=s.p) */
	v.l = gets(&v.p, s.cap - s.l),
	s.l = s.l + v.l;  /* this moves the end of 's' */

	v.p = s.p + s.l,
	v.l = gets(&v.p, s.cap - s.l);
	/* add it to s if it is something different */
	if (v.l != s.l || strncmp(s.p, v.p, v.l) != 0) {
		s.l = s.l + v.l;
	}

	puts(s.p, s.l);
	return 0;
}






























/*
int hash(const char* s) {
	int i = 0;
	int h = 0;
	while (s[i]) {
		h = h * 33 + s[i];
		i++;
	}
	return h;
}

int num(const char* s) {
	int i = 0;
	while(s++) {
		i = i * 10 + ((*s) - '0');
	}
	return i;
}

char* str(int x) {
	static char buf[16];
	int i = 14;
	do {
		buf[i] = (x % 10) + '0';
		x = x / 10;
		i--;
	} while (x && i >= 0);
	return buf + i + 1;
}
#define MAPSIZE 1000

int main() {
	struct {
		char s[20];
		int v;
	} map[MAPSIZE] = {0};
	char *inp = 0;
	int h = 0;

	gets(&inp);
	h = hash(inp) % MAPSIZE;
	strcpy(map[h].s, inp);
	map[h].v = 1;

	gets(&inp);
	h = hash(inp) % MAPSIZE;
	if (map[h].v)
		puts(map[h].s, -1);
	return 0;
}
*/

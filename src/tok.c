#include "mylib.h"

enum token {
	TOK_NONE,
	TOK_IDENT,
	TOK_STRING,
	TOK_SPACE
};
size_t lex(char *p, enum token* tokp, size_t l, size_t i);

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
	size_t i = 0;
	size_t j = 0;
	enum token tok = TOK_NONE;
	/* the data exists here, in 's', by
	   extension 'allocation' */
	s.p = allocation,
	s.l = 0,
	s.cap = 1024;
	/* read into a view, this makes dealing
	   with strings easier */
	v.p = s.p + s.l,  /* for consistency (=s.p) */
	v.l = gets(&v.p, s.cap - s.l);
	while (i < v.l) {
		tok = TOK_NONE;
		j = lex(v.p, &tok, v.l, i);
		switch (tok) {
		case TOK_IDENT:
		case TOK_STRING:
			puts(v.p + i, j - i);
			puts("\n", 1);
			break;
		case TOK_NONE:
		default:
			break;
		}
		i = j;
	}
	return 0;
}

size_t lex(char *p, enum token* tokp, size_t l, size_t i) {
	char ch=p[i];
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
		*tokp = TOK_IDENT;
		while (((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) && i < l) {
			i++;
			if (i < l)
				ch = p[i];
		}
	} else if (ch == ' ' || ch == '\n') {
		*tokp = TOK_SPACE;
		while ((ch == ' ' || ch == '\n') && i < l) {
			i++;
			if (i < l)
				ch = p[i];
		}
	} else if (ch == '\'') {
		*tokp = TOK_STRING;
		i++;
		if (i < l)
			ch = p[i];
		while (!(ch == '\'') && i < l) {
			i++;
			if (ch == '\\')
				i++;
			if (i < l)
				ch = p[i];
		}
		if (ch == '\'')
			i++;
	} else if (ch == '"') {
		*tokp = TOK_STRING;
		i++;
		if (i < l)
			ch = p[i];
		while (!(ch == '"') && i < l) {
			i++;
			if (ch == '\\')
				i++;
			if (i < l)
				ch = p[i];
		}
		if (ch == '"')
			i++;
	} else {
		*tokp = TOK_STRING;
		while (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == ' ' || ch == '\n') && i < l) {
			i++;
			if (i < l)
				ch = p[i];
		}
	}
	return i;
}

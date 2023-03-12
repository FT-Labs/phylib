#ifndef STRARRAY_H
#define STRARRAY_H
#include "libphy.h"
#define STRA_MIN_SIZE 4


static inline void
stra_free(char **stra)
{
	free((*stra));
	free(stra);
}

static char **
stra_str_to_arr(const char *str, char delim)
{
	int sz = STRA_MIN_SIZE, end = strlen(str), idx = 0;
	char *s = strdup(str);
	char **stra = malloc(sizeof(char *) * sz);
	stra[0] = s;

	for (int i = 0; i < end; i++) {
		if (s[i] == delim) {
			stra[++idx] = (s + i + 1);
			s[i] = '\0';
		}

		if (idx >= sz - 1) {
			sz <<= 1;
			stra = realloc(stra, sizeof(char *) * sz);
		}
	}
	stra[idx] = NULL;
	return stra;
}

static inline char
*str_tolower(char *s)
{
	char *p = s;
	do {
		*p = tolower(*p);
	} while (*(++p));
	return s;
}

static inline char *
str_toupper(char *s)
{
	char *p = s;
	do {
		*p = toupper(*p);
	} while (*(++p));
	return s;
}
#endif /* STRARRAY_H */

#include "libphy.h"

static char *private_get_line_from_file(FILE *file, int c)
{
#define GROWBY (120)

	int ch;
	int idx = 0;
	char *linebuf = NULL;
	int lbsz = 0;

	while ((ch = getc(file)) != EOF) {
		if (idx > lbsz - 2) {
			linebuf = realloc(linebuf, lbsz + GROWBY);
		}
		linebuf[idx++] = (char)ch;
		if (!ch) return linebuf;
		if (c < 2 && ch == '\n') {
			if (c)	--idx;
			/*  */
			break;
		}
	}

	if (linebuf) {
		if (ferror(file)) {
			free(linebuf);
			return NULL;
		}
		linebuf[idx] = 0;
	}
	return linebuf;
}

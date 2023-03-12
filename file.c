#include "libphy.h"

int dir_iterate(const char *dir_name,
	int (*func) (const char *, struct dirent *, void *), void *private)
{
	struct dirent *de;
	DIR *dir = opendir(dir_name);
	if (!dir)
		return -1;

	while ((de = readdir(dir)))
		func(dir_name, de, private);
	closedir(dir);
	return 0;
}


int dir_check(const char *file_name, int follow_links)
{
	int status;
	struct stat statbuf;

	if (follow_links)
		status = stat(file_name, &statbuf);
	else
		status = lstat(file_name, &statbuf);

	status = (!status && S_ISDIR(statbuf.st_mode));
	return status;
}

static char *file_get_line(FILE *file, int c)
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

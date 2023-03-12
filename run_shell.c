#include "libphy.h"
#include <stdarg.h>
#define MIN_STR_SIZE 16

void shell_run(const char *cmd, ...)
{
	static char buf[1024];
	memset(buf, 0, sizeof(buf));
	va_list argptr;
	va_start(argptr, cmd);
	va_end(argptr);
	vsprintf(buf, cmd, argptr);

	system(cmd);
}

char *shell_run_str(const char *cmd, ...)
{
	static char buf[1024];
	memset(buf, 0, sizeof(buf));
	va_list argptr;
	va_start(argptr, cmd);
	va_end(argptr);
	vsprintf(buf, cmd, argptr);

	FILE *fd = popen(buf, "r");

	if (!fd)
		return NULL;

	char ch, *out = malloc(MIN_STR_SIZE);
	int i = 0, sz = MIN_STR_SIZE;

	while ((ch = getc(fd)) && ch != EOF) {
		out[i++] = ch;
		if (i >= sz - 1) {
			sz <<= 1;
			out = realloc(out, sz);
		}
	}
	out[i] = '\0';
	pclose(fd);
	return out;
}

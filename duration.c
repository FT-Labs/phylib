#include "libphy.h"


static const struct suffix_mult dur_suffixes[] = {
	{ "s", 1 },
	{ "m", 60 },
	{ "h", 60*60 },
	{ "d", 24*60*60 },
	{ "", 0 }
};

duration_t parse_duration_str(char *str)
{
	duration_t dur;

	if (strchr(str, '.')) {
		double d;
		char *pp;
		setlocale(LC_NUMERIC, "C");

		int len = strspn(str, "0123456789.");
		char sv = str[len];
		str[len] = '\0';
		errno = 0;
		d = strtod(str, &pp);
		str += len;
		*str-- = sv;
		sv = *str;
		*str = '1';
		dur = d * xatoull_sfx(str, dur_suffixes);
		*str = sv;
	} else {
		dur = xatoull_sfx(str, dur_suffixes);
	}
	return dur;
}

#include "libphy.h"
#include <fcntl.h>

int device_open(const char *device, int mode)
{
	int m, f, fd = -1;

	m = mode | O_NONBLOCK;

	/* Retry 5 times */
	for (f = 0; f < 5; f++)
		if ((fd = open(device, m, 0600)) >= 0)
			break;

	if (fd < 0)
		return fd;
	/* Reset flags */
	if (m != mode)
		fcntl(fd, F_SETFL, mode);
	return fd;
}

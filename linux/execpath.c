#include <errno.h>
#include <string.h>
#include <unistd.h>

int
getexecpath(char *buf, size_t bufsize)
{
	memset(buf, 0, bufsize);
	if (readlink("/proc/self/exe", buf, bufsize) < 0)
		return errno = ENOENT, -1;
	if (bufsize < 1 || buf[bufsize - 1])
		return errno = ERANGE, -1;
	return 0;
}

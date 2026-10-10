#include <sys/sysctl.h>
#include <sys/types.h>
#include <errno.h>

int
getexecpath(char *buf, size_t bufsize)
{
	const int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
	size_t length = bufsize;

	if (sysctl(mib, 4, buf, &length, NULL, 0) < 0)
		return errno = errno == ENOMEM ? ERANGE : ENOENT, -1;
	if (length < 1 || length > bufsize || buf[length - 1])
		return errno = ERANGE, -1;
	return 0;
}

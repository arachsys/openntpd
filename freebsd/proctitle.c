#include <sys/sysctl.h>
#include <limits.h>
#include <stdlib.h>

void
initproctitle(char **argv, char **envp)
{
	const int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
	static char path[PATH_MAX + 1];
	size_t length = PATH_MAX;

	if (argv[0][0] == '/')
		return;
	if (sysctl(mib, 4, path, &length, NULL, 0) != -1)
		argv[0] = path;
}

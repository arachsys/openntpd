#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *title;
static size_t size;

void
initproctitle(char **argv, char **envp)
{
	char *copy;
	int i;

	if (title || !argv || !argv[0])
		return;
	title = argv[0];

	for (i = 0; argv[i] == title + size; i++) {
		copy = strdup(argv[i]);
		if (!copy)
			break;
		size += strlen(argv[i]) + 1;
		argv[i] = copy;
	}

	for (i = 0; envp[i] == title + size; i++) {
		copy = strdup(envp[i]);
		if (!copy)
			break;
		size += strlen(envp[i]) + 1;
		envp[i] = copy;
	}

	if (argv[0][0] != '/') {
		copy = calloc(PATH_MAX + 1, 1);
		if (!copy)
			return;
		if (readlink("/proc/self/exe", copy, PATH_MAX) > 0) {
			free(argv[0]);
			argv[0] = copy;
		} else {
			free(copy);
		}
	}
}

void
setproctitle(const char *fmt, ...)
{
	extern char *__progname;
	size_t prefix;
	va_list ap;

	if (!title)
		return;
	memset(title, 0, size);

	va_start(ap, fmt);
	prefix = snprintf(title, size, "%s: ", __progname);
	if (prefix < size)
		vsnprintf(title + prefix, size - prefix, fmt, ap);
	va_end(ap);
}

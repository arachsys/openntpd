#include <sys/types.h>
#include <stdint.h>

#define __dead __attribute__((__noreturn__))
#define __packed __attribute__((__packed__))

#define pledge(request, paths) (0)
#define unveil(path, permissions) (0)

int adjfreq(const int64_t *freq, int64_t *oldfreq);
int setsync(int synced);

int getexecpath(char *buf, size_t bufsize);

static inline void initproctitle(char **argv, char **envp)
{
}

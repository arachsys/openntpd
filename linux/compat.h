#include <sys/time.h>
#include <stdint.h>

#define __dead __attribute__((__noreturn__))
#define __packed __attribute__((__packed__))

#define pledge(request, paths) (0)
#define unveil(path, permissions) (0)

int adjfreq(const int64_t *freq, int64_t *oldfreq);
int adjtime(const struct timeval *in, struct timeval *out);
int setsync(int synced);

void initproctitle(char **argv, char **envp);
void setproctitle(const char *fmt, ...);

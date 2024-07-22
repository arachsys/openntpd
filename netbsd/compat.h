#include <sys/types.h>
#include <stdint.h>

#define __dead __attribute__((__noreturn__))
#define __packed __attribute__((__packed__))

#define explicit_bzero(s, len) explicit_memset(s, 0, len)
#define pledge(request, paths) (0)
#define unveil(path, permissions) (0)

int adjfreq(const int64_t *freq, int64_t *oldfreq);
int setsync(int synced);

void initproctitle(char **argv, char **envp);

int setresuid(uid_t ruid, uid_t euid, uid_t suid);
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

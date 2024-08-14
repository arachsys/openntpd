#define __dead __attribute__((__noreturn__))
#define __packed __attribute__((__packed__))

static inline int setsync(int synced)
{
	return 0;
}

static inline void initproctitle(char **argv, char **envp)
{
}

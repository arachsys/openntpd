#define __dead __attribute__((__noreturn__))
#define __packed __attribute__((__packed__))

int setsync(int synced);
void initproctitle(char **argv, char **envp);

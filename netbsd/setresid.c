#include <unistd.h>

int
setresuid(uid_t ruid, uid_t euid, uid_t suid)
{
	if (ruid != euid || euid != suid)
		return -1;
	return setreuid(ruid, euid);
}

int
setresgid(gid_t rgid, gid_t egid, gid_t sgid)
{
	if (rgid != egid || egid != sgid)
		return -1;
	return setregid(rgid, egid);
}

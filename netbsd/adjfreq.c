#include <sys/time.h>
#include <sys/timex.h>
#include <stdint.h>

int
adjfreq(const int64_t *freq, int64_t *oldfreq)
{
	struct timex txc = { 0 };

	if (freq) {
		txc.modes = MOD_FREQUENCY;
		txc.freq = *freq / (1000LL << 16);
		if (ntp_adjtime(&txc) == -1)
			return -1;
	}

	if (oldfreq) {
		txc.modes = 0;
		if (ntp_adjtime(&txc) == -1)
			return -1;
		*oldfreq = txc.freq * (1000LL << 16);
	}

	return 0;
}

int
setsync(int synced)
{
	struct timex txc = { 0 };

	txc.modes = MOD_STATUS;
	if (synced) {
		txc.modes |= MOD_MAXERROR;
		txc.maxerror = 0;
	} else {
		txc.status = STA_UNSYNC;
	}

	return ntp_adjtime(&txc);
}

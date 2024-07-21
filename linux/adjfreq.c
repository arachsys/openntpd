#include <sys/time.h>
#include <sys/timex.h>
#include <stdint.h>

int
adjfreq(const int64_t *freq, int64_t *oldfreq)
{
	struct timex txc = { 0 };

	if (freq) {
		txc.modes = ADJ_FREQUENCY;
		txc.freq = *freq / (1000LL << 16);
		if (adjtimex(&txc) == -1)
			return -1;
	}

	if (oldfreq) {
		txc.modes = 0;
		if (adjtimex(&txc) == -1)
			return -1;
		*oldfreq = txc.freq * (1000LL << 16);
	}

	return 0;
}

int
adjtime(const struct timeval *in, struct timeval *out)
{
	struct timex tx = { 0 };

	if (in) {
		tx.modes = ADJ_OFFSET_SINGLESHOT;
		tx.offset = in->tv_sec * 1000000 + in->tv_usec;
	}

	if (adjtimex(&tx) == -1)
		return -1;

	if (out) {
		out->tv_sec = tx.offset / 1000000;
		out->tv_usec = tx.offset % 1000000;
		if (out->tv_usec < 0) {
			out->tv_sec -= 1;
			out->tv_usec += 1000000;
		}
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

	return adjtimex(&txc);
}

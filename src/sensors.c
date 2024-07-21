#include "ntpd.h"

#ifndef __weak
#define __weak __attribute__((__weak__))
#endif

__weak void
sensor_init(void)
{
	TAILQ_INIT(&conf->ntp_sensors);
}

__weak int
sensor_scan(void)
{
	return 0;
}

__weak void
sensor_query(struct ntp_sensor *s)
{
}

#include <bach/jiffies.h>

volatile unsigned long jiffies = INITIAL_JIFFIES;

/* The following functions are partially lifted from Linux */
unsigned long msecs_to_jiffies(const unsigned int m)
{
#if HZ <= 1000 && !(1000 % HZ)
	/*
	 * HZ is equal to or smaller than 1000, and 1000 is a nice
	 * round multiple of HZ, divide with the factor between them,
	 * but round upwards:
	 */
	return (m + (1000 / HZ) - 1) / (1000 / HZ);
#elif HZ > 1000 && !(HZ % 1000)
	/*
	 * HZ is larger than 1000, and HZ is a nice round multiple of
	 * 1000 - simply multiply with the factor between them.
	 */
	if (m > jiffies_to_msecs(MAX_JIFFY_OFFSET))
		return MAX_JIFFY_OFFSET;

	return m * (HZ / 1000);
#else
	/* If your HZ is strange, you must define the convertions values */
        return (m * MSEC_TO_HZ_NUM + MSEC_TO_HZ_DEN -1) / MSEC_TO_HZ_DEN;
#endif
}

unsigned int jiffies_to_msecs(const unsigned long j)
{
#if HZ <= 1000 && !(1000 % HZ)
	return (1000 / HZ) * j;
#elif HZ > 1000 && !(HZ % 1000)
	return (j + (HZ / 1000) - 1)/(HZ / 1000);
#else
	/* If your HZ is strange, you must define the convertions values */
        return (j * HZ_TO_MSEC_NUM + HZ_TO_MSEC_DEN - 1) / HZ_TO_MSEC_DEN;
#endif
}


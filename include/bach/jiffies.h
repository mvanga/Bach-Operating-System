#ifndef BACH_JIFFIES_H
#define BACH_JIFFIES_H

#define HZ 100

#define INITIAL_JIFFIES ((unsigned long)(unsigned int)(-30 * HZ))

extern volatile unsigned long jiffies;

#define time_after(a,b)		((long)(a) - (long)(b) > 0)
#define time_before(a,b)	time_after(b,a)
#define time_after_eq(a,b)	((long)(a) - (long)(b) >= 0)
#define time_before_eq(a,b)	time_after_eq(b,a)

extern unsigned long msecs_to_jiffies(const unsigned int m);
extern unsigned int jiffies_to_msecs(const unsigned long j);

#endif /* BACH_JIFFIES_H */

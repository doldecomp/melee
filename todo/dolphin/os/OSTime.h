#ifndef __DOLPHIN_OSTIME_H_
#define __DOLPHIN_OSTIME_H_

#include <platform.h>

typedef s64 OSTime;
typedef u32 OSTick;

typedef struct OSCalendarTime {
    int sec;  // seconds after the minute [0, 61]
    int min;  // minutes after the hour [0, 59]
    int hour; // hours since midnight [0, 23]
    int mday; // day of the month [1, 31]
    int mon;  // month since January [0, 11]
    int year; // years in AD [1, ...]
    int wday; // days since Sunday [0, 6]
    int yday; // days since January 1 [0, 365]

    int msec; // milliseconds after the second [0,999]
    int usec; // microseconds after the millisecond [0,999]
} OSCalendarTime;

void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td);
OSTime OSGetTime(void);
OSTick OSGetTick(void);
OSTime __OSTimeToSystemTime(OSTime);
OSTime __OSGetSystemTime(void);

extern u32 __OSBusClock AT_ADDRESS(0x800000F8);

#define OS_BUS_CLOCK __OSBusClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToSeconds(ticks) ((ticks) / (OS_TIMER_CLOCK))
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks)                                          \
    (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))
#define OSSecondsToTicks(sec) ((sec) * (OS_TIMER_CLOCK))
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)
#define OSNanosecondsToTicks(nsec)                                            \
    (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)

#endif

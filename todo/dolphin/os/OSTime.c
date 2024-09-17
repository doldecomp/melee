#include <placeholder.h>

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>

#ifdef MWERKS_GEKKO

asm OSTime OSGetTime(void){ // clang-format off
    mftbu r3
    mftb r4, 0x10c
    mftbu r5
    cmpw r3, r5
    bne OSGetTime
} // clang-format on

#else

OSTime OSGetTime(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm OSTick OSGetTick(void){ // clang-format off
    mftb r3, 0x10c
} // clang-format on

#else

OSTick OSGetTick(void)
{
    NOT_IMPLEMENTED;
}

#endif

extern volatile OSTime OS_SYSTEM_TIME AT_ADDRESS(0x800030D8);

OSTime __OSGetSystemTime(void)
{
    u8 _[4];

    bool intr = OSDisableInterrupts();
    OSTime time = OSGetTime() + OS_SYSTEM_TIME;
    OSRestoreInterrupts(intr);
    return time;
}

OSTime __OSTimeToSystemTime(s64 time)
{
    u8 _[4];

    bool intr = OSDisableInterrupts();
    OSTime sysTime = OS_SYSTEM_TIME + time;
    OSRestoreInterrupts(intr);
    return sysTime;
}

#define OS_TIME_MONTH_MAX 12
#define OS_TIME_WEEK_DAY_MAX 7
#define OS_TIME_YEAR_DAY_MAX 365

static s32 YearDays[12] = { 0,   31,  59,  90,  120, 151,
                            181, 212, 243, 273, 304, 334 };
static s32 LeapYearDays[12] = { 0,   31,  60,  91,  121, 152,
                                182, 213, 244, 274, 305, 335 };

static bool IsLeapYear(s32 year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static s32 GetLeapDays(s32 year)
{
    if (year < 1) {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

static void GetDates(s32 days, OSCalendarTime* cal)
{
    s32 year;
    s32 totalDays;
    s32* p_days;
    s32 month;

    cal->wday = (days + 6) % OS_TIME_WEEK_DAY_MAX;

    for (year = days / OS_TIME_YEAR_DAY_MAX;
         days < (totalDays = year * OS_TIME_YEAR_DAY_MAX + GetLeapDays(year));
         year--)
    {
        ;
    }
    days -= totalDays;
    cal->year = year;
    cal->yday = days;

    p_days = IsLeapYear(year) ? LeapYearDays : YearDays;
    month = OS_TIME_MONTH_MAX;

    while (days < p_days[--month]) {
        continue;
    }

    cal->mon = month;
    cal->mday = days - p_days[month] + 1;
}

#define BIAS                                                                  \
    (2000 * 365 + (2000 + 3) / 4 - (2000 - 1) / 100 + (2000 - 1) / 400)

void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td)
{
    int days;
    int secs;
    OSTime d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0) {
        d += OSSecondsToTicks(1);
    }
    td->usec = (int) (OSTicksToMicroseconds(d) % 1000);
    td->msec = (int) (OSTicksToMilliseconds(d) % 1000);

    ticks -= d;
    days = (int) (OSTicksToSeconds(ticks) / 86400 + BIAS);
    secs = (int) (OSTicksToSeconds(ticks) % 86400);
    if (secs < 0) {
        days -= 1;
        secs += 24 * 60 * 60;
    }

    GetDates(days, td);

    td->hour = secs / 60 / 60;
    td->min = (secs / 60) % 60;
    td->sec = secs % 60;
}

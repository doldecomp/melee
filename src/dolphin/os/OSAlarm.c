#include <dolphin/os/OSAlarm.h>

#include <dolphin/base/PPCArch.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSTime.h>
#include <placeholder.h>

static struct OSAlarmQueue {
    OSAlarm* head;
    OSAlarm* tail;
} AlarmQueue;

void DecrementerExceptionHandler(OSException exception, OSContext* context);

void OSInitAlarm(void)
{
    if (__OSGetExceptionHandler(8) != DecrementerExceptionHandler) {
        AlarmQueue.tail = 0;
        AlarmQueue.head = 0;
        __OSSetExceptionHandler(8, DecrementerExceptionHandler);
    }
}

void OSCreateAlarm(OSAlarm* alarm)
{
    alarm->handler = NULL;
}

static void SetTimer(OSAlarm* alarm)
{
    OSTime delta = alarm->fire - __OSGetSystemTime();
    if (delta < 0) {
        PPCMtdec(0);
    } else if (delta < 0x80000000) {
        PPCMtdec((u32) delta);
    } else {
        PPCMtdec(0x7fffffff);
    }
}

static void InsertAlarm(OSAlarm* alarm, OSTime fire, OSAlarmHandler handler)
{
    OSAlarm* next;
    OSAlarm* prev;

    if (0 < alarm->period) {
        OSTime time = __OSGetSystemTime();

        fire = alarm->start;
        if (alarm->start < time) {
            fire += alarm->period * ((time - alarm->start) / alarm->period + 1);
        }
    }

    alarm->handler = handler;
    alarm->fire = fire;

    for (next = AlarmQueue.head; next; next = next->next) {
        if (next->fire <= fire) {
            continue;
        }

        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;
        if (prev) {
            prev->next = alarm;
        } else {
            AlarmQueue.head = alarm;
            SetTimer(alarm);
        }
        return;
    }
    alarm->next = 0;
    prev = AlarmQueue.tail;
    AlarmQueue.tail = alarm;
    alarm->prev = prev;
    if (prev) {
        prev->next = alarm;
    } else {
        AlarmQueue.head = AlarmQueue.tail = alarm;
        SetTimer(alarm);
    }
}

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler)
{
    u32 oldInt = OSDisableInterrupts();
    alarm->period = 0;
    InsertAlarm(alarm, __OSGetSystemTime() + tick, handler);
    OSRestoreInterrupts(oldInt);
}

void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period,
                        OSAlarmHandler handler)
{
    bool enabled = OSDisableInterrupts();
    alarm->period = period;
    alarm->start = __OSTimeToSystemTime(start);
    InsertAlarm(alarm, 0, handler);
    OSRestoreInterrupts(enabled);
}

void OSCancelAlarm(OSAlarm* alarm)
{
    OSAlarm* next;
    bool enabled;

    enabled = OSDisableInterrupts();

    if (alarm->handler == 0) {
        OSRestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        AlarmQueue.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }
    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        AlarmQueue.head = next;
        if (next) {
            SetTimer(next);
        }
    }
    alarm->handler = 0;

    OSRestoreInterrupts(enabled);
}

static void DecrementerExceptionCallback(register OSException exception,
                                         register OSContext* context)
{
    OSAlarm* alarm;
    OSAlarm* next;
    OSAlarmHandler handler;
    OSTime time;
    OSContext exceptionContext;

    time = __OSGetSystemTime();
    alarm = AlarmQueue.head;
    if (alarm == 0) {
        OSLoadContext(context);
    }

    if (time < alarm->fire) {
        SetTimer(alarm);
        OSLoadContext(context);
    }

    next = alarm->next;
    AlarmQueue.head = next;
    if (next == 0) {
        AlarmQueue.tail = 0;
    } else {
        next->prev = 0;
    }

    handler = alarm->handler;
    alarm->handler = 0;
    if (0 < alarm->period) {
        InsertAlarm(alarm, 0, handler);
    }

    if (AlarmQueue.head) {
        SetTimer(AlarmQueue.head);
    }

    OSDisableScheduler();
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    handler(alarm, context);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
    OSEnableScheduler();
    __OSReschedule();
    OSLoadContext(context);
}

#ifdef MWERKS_GEKKO

#pragma push
asm void DecrementerExceptionHandler(OSException exception, OSContext* context)
{ // clang-format off
    nofralloc
/* 80343DF8 003409D8  90 04 00 00 */	stw r0, 0(r4)
/* 80343DFC 003409DC  90 24 00 04 */	stw r1, 4(r4)
/* 80343E00 003409E0  90 44 00 08 */	stw r2, 8(r4)
/* 80343E04 003409E4  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 80343E08 003409E8  7C 11 E2 A6 */	mfspr r0, 0x391
/* 80343E0C 003409EC  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 80343E10 003409F0  7C 12 E2 A6 */	mfspr r0, 0x392
/* 80343E14 003409F4  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 80343E18 003409F8  7C 13 E2 A6 */	mfspr r0, 0x393
/* 80343E1C 003409FC  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 80343E20 00340A00  7C 14 E2 A6 */	mfspr r0, 0x394
/* 80343E24 00340A04  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 80343E28 00340A08  7C 15 E2 A6 */	mfspr r0, 0x395
/* 80343E2C 00340A0C  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 80343E30 00340A10  7C 16 E2 A6 */	mfspr r0, 0x396
/* 80343E34 00340A14  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 80343E38 00340A18  7C 17 E2 A6 */	mfspr r0, 0x397
/* 80343E3C 00340A1C  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 80343E40 00340A20  4B FF FD 88 */	b DecrementerExceptionCallback
} // clang-format on
#pragma pop

#else

void DecrementerExceptionHandler(OSException exception, OSContext* context)
{
    NOT_IMPLEMENTED;
}

#endif

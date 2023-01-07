#ifndef DOLPHIN_OS_OSALARM_H
#define DOLPHIN_OS_OSALARM_H

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSTime.h>

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
    OSAlarmHandler handler;
    u32 tag;
    OSTime fire;
    OSAlarm* prev;
    OSAlarm* next;
    OSTime period;
    OSTime start;
};

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler);
void OSCancelAlarm(OSAlarm* alarm);
void OSInitAlarm(void);
void OSCreateAlarm(OSAlarm* alarm);

#endif // DOLPHIN_OS_OSALARM_H

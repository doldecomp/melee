#ifndef MELEE_IF_TIME_H
#define MELEE_IF_TIME_H

#include <placeholder.h>

#include <baselib/forward.h>

/* 2F3AE8 */ void ifTime_SetTime(HSD_JObj*, int, int);
/* 2F405C */ void ifTime_HideTimers(void);
/* 2F40B8 */ void ifTime_ShowTimers(void);
/* 2F4144 */ int ifTime_GetCountdownSeconds(void);
/* 2F4194 */ void ifTime_UpdateCountdown(HSD_GObj*);
/* 2F4248 */ void ifTime_FreeCountdown(void);
/* 2F428C */ void ifTime_UpdateTimers(HSD_GObj*);
/* 2F446C */ void ifTime_CreateTimers(void);
/* 2F480C */ void ifTime_Reset(void);
/* 2F483C */ void ifTime_FreeTimers(void);
/* 2F4898 */ bool ifTime_IsTimerHidden(void);

#endif

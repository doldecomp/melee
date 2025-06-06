#ifndef _DOLPHIN_OSREBOOT_H_
#define _DOLPHIN_OSREBOOT_H_

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*RunCallback)(void);

void Run(RunCallback);
void __OSReboot(u32 resetCode, BOOL forceMenu);

#ifdef __cplusplus
}
#endif

#endif

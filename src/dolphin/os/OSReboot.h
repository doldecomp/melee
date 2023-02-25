#ifndef DOLPHIN_OS_OSREBOOT_H
#define DOLPHIN_OS_OSREBOOT_H

#include <Runtime/platform.h>

void __OSReboot(u32 resetCode, bool forceMenu);

void Run(Event);
void __OSReboot(u32 resetCode, bool forceMenu);

#endif

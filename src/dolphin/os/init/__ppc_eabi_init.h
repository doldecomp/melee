#ifndef DOLPHIN_OS_INIT___PPC_EABI_INIT_H
#define DOLPHIN_OS_INIT___PPC_EABI_INIT_H

#include <Runtime/platform.h>

void __init_user(void);
void _ExitProcess(void);

SECTION_INIT void __init_hardware(void);
SECTION_INIT void __flush_cache(void* address, size_t size);

#endif

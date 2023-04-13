#ifndef DOLPHIN_OS_INIT___PPC_EABI_INIT_H
#define DOLPHIN_OS_INIT___PPC_EABI_INIT_H

#include <platform.h>

void __init_user(void);
ATTRIBUTE_NORETURN void _ExitProcess(void);

SECTION_INIT void __init_hardware(void);
SECTION_INIT void __flush_cache(void* address, size_t size);

#endif

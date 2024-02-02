#ifndef DOLPHIN_OS_INIT___START_H
#define DOLPHIN_OS_INIT___START_H

#include <platform.h>

#include "dolphin/os/OSReset.h"

#include <__mem.h>

#define PAD3_BUTTON_ADDR 0x800030E4
#define EXCEPTIONMASK_ADDR 0x80000044
#define BOOTINFO2_ADDR 0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define ARENAHI_ADDR 0x80000034
#define DEBUGFLAG_ADDR 0x800030E8
#define DVD_DEVICECODE_ADDR 0x800030E6

#define MSR_FP 0x2000

extern void InitMetroTRK(void);

u16 Pad3Button AT_ADDRESS(PAD3_BUTTON_ADDR);

extern int main(int argc, char* argv[]);
extern void exit(int);
extern void __init_user(void);
extern void OSInit(void);
extern void DBInit(void);

SECTION_INIT void __check_pad3(void);
SECTION_INIT void __start(void);
SECTION_INIT void __init_data(void);
SECTION_INIT void __init_hardware(void);
SECTION_INIT void __flush_cache(void* address, size_t size);

SECTION_INIT extern u8 _stack_addr[];
SECTION_INIT extern u8 _SDA_BASE_[];
SECTION_INIT extern u8 _SDA2_BASE_[];

typedef struct __rom_copy_info {
    u8* rom;
    void* addr;
    size_t size;
} __rom_copy_info;

SECTION_INIT extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
    void* addr;
    size_t size;
} __bss_init_info;

SECTION_INIT extern __bss_init_info _bss_init_info[];

#endif

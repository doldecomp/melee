#ifndef DOLPHIN_OS_INIT___START_H
#define DOLPHIN_OS_INIT___START_H

#include <dolphin/os/OSReset.h>
#include <dolphin/types.h>
#include <Runtime/__mem.h>

#define PAD3_BUTTON_ADDR 0x800030E4
#define EXCEPTIONMASK_ADDR 0x80000044
#define BOOTINFO2_ADDR 0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define ARENAHI_ADDR 0x80000034
#define DEBUGFLAG_ADDR 0x800030E8
#define DVD_DEVICECODE_ADDR 0x800030E6

#define MSR_FP 0x2000

extern void InitMetroTRK(void);

u16 Pad3Button
#ifndef M2CTX
    : PAD3_BUTTON_ADDR
#endif
      ;

static u8 Debug_BBA = 0;

extern int main(size_t argc, char* argv[]);
extern void exit(int);
extern void __init_user(void);
extern void OSInit(void);
extern void DBInit(void);
extern void __OSCacheInit(void);
extern void __OSPSInit(void);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void __check_pad3(void);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void __start(void);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void __init_registers(void);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void __init_data(void);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void __init_hardware(void);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void __flush_cache(void* address, size_t size);

#ifndef M2CTX
__declspec(section ".init")
#endif
    extern u8 _stack_addr[];

#ifndef M2CTX
__declspec(section ".init")
#endif
    extern u8 _SDA_BASE_[];

#ifndef M2CTX
__declspec(section ".init")
#endif
    extern u8 _SDA2_BASE_[];

typedef struct __rom_copy_info {
    u8* rom;
    void* addr;
    size_t size;
} __rom_copy_info;

#ifndef M2CTX
__declspec(section ".init")
#endif
    extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
    void* addr;
    size_t size;
} __bss_init_info;

#ifndef M2CTX
__declspec(section ".init")
#endif
    extern __bss_init_info _bss_init_info[];

#endif

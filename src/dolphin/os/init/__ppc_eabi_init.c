#include <dolphin/os/init/__ppc_eabi_init.h>

#include <dolphin/base/PPCArch.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSInit.h>

#define MSR_FP 0x2000

typedef void (*voidfunc)(void);
extern voidfunc __ctors[];

static void __init_cpp(void);

SECTION_INIT asm void __init_hardware(void)
{ // clang-format off
    nofralloc
    mfmsr r0
    ori  r0,r0,MSR_FP
    mtmsr r0
    mflr    r31
    bl      __OSPSInit
    bl      __OSCacheInit
    mtlr    r31
    blr
} // clang-format on

SECTION_INIT asm void __flush_cache(void* address, size_t size)
{ // clang-format off
    nofralloc
    lis     r5, 0xffff
    ori     r5, r5, 0xfff1
    and     r5, r5, r3
    subf    r3, r5, r3
    add     r4, r4, r3
rept:
    dcbst   0,r5
    sync
    icbi    0,r5
    addic   r5,r5,0x8
    subic.  r4,r4,0x8
    bge     rept
    isync
    blr
} // clang-format on

void __init_user(void)
{
    __init_cpp();
}

static void __init_cpp(void)
{
    voidfunc* constructor;

    for (constructor = __ctors; *constructor; constructor++) {
        (*constructor)();
    }
}

void _ExitProcess(void)
{
    PPCHalt();
}

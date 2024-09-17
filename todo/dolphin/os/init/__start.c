#include <placeholder.h>

#include <__mem.h>
#include <dolphin/os/init/__start.h>
#include <dolphin/os/OSReset.h>

#define RESET_BUTTON_MASK 0x0EEF

SECTION_INIT static void __init_registers(void);

void __check_pad3(void)
{
    if ((Pad3Button & RESET_BUTTON_MASK) == RESET_BUTTON_MASK) {
        OSResetSystem(OS_RESET_RESTART, 0, false);
    }
}

#ifdef MWERKS_GEKKO
asm void __start(void)
{ // clang-format off
    nofralloc
    bl __init_registers
    bl __init_hardware
    li r0, -1
    stwu r1, -8(r1)
    stw r0, 4(r1)
    stw r0, 0(r1)
    bl __init_data
    li r0, 0
    lis r6, EXCEPTIONMASK_ADDR@ha
    addi r6, r6, EXCEPTIONMASK_ADDR@l
    stw r0, 0(r6)
    lis r6, BOOTINFO2_ADDR@ha
    addi r6, r6, BOOTINFO2_ADDR@l
    lwz r6, 0(r6)
    cmplwi r6, 0
    beq _goto_main
    lwz r7, OS_BI2_DEBUGFLAG_OFFSET(r6)
    li r5, 0
    cmplwi r7, 2
    beq _goto_inittrk
    cmplwi r7, 3
    bne _goto_main
    li r5, 1

_goto_inittrk:
    lis r6, InitMetroTRK@ha
    addi r6, r6, InitMetroTRK@l
    mtlr r6
    blrl

_goto_main:
    lis r6, BOOTINFO2_ADDR@ha
    addi r6, r6, BOOTINFO2_ADDR@l
    lwz r5, 0(r6)
    cmplwi r5, 0
    beq+ _no_args
    lwz r6, 8(r5)
    cmplwi r6, 0
    beq+ _no_args
    add r6, r5, r6
    lwz r14, 0(r6)
    cmplwi r14, 0
    beq _no_args
    addi r15, r6, 4
    mtctr r14

_loop:
    addi r6, r6, 4
    lwz r7, 0(r6)
    add r7, r7, r5
    stw r7, 0(r6)
    bdnz _loop
    lis r5, ARENAHI_ADDR@ha
    addi r5, r5, ARENAHI_ADDR@l
    rlwinm r7, r15, 0, 0, 0x1a
    stw r7, 0(r5)
    b _end_of_parseargs

_no_args:
    li r14, 0
    li r15, 0

_end_of_parseargs:
    bl DBInit
    bl OSInit
    lis r4, DVD_DEVICECODE_ADDR@ha
    addi r4, r4, DVD_DEVICECODE_ADDR@l
    lhz r3, 0(r4)
    andi. r5, r3, 0x8000
    beq _check_pad3
    andi. r3, r3, 0x7fff
    cmplwi r3, 1
    bne _goto_end

_check_pad3:
    bl __check_pad3

_goto_end:
    bl __init_user
    mr r3, r14
    mr r4, r15
    bl main
    b exit
} // clang-format on
#else
void __start(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm static void __init_registers(void)
{ // clang-format off
    nofralloc

    lis r1,  _stack_addr@h
    ori r1, r1,  _stack_addr@l
    lis r2, _SDA2_BASE_@h
    ori r2, r2, _SDA2_BASE_@l
    lis r13, _SDA_BASE_@h
    ori r13, r13, _SDA_BASE_@l
    blr
} // clang-format on
#else
static void __init_registers(void)
{
    NOT_IMPLEMENTED;
}
#endif

inline static void __copy_rom_section(void* dst, void* const src, size_t size)
{
    if (size && (dst != src)) {
        memcpy(dst, src, size);
        __flush_cache(dst, size);
    }
}

inline static void __init_bss_section(void* dst, size_t size)
{
    if (size != 0) {
        memset(dst, 0, size);
    }
}

void __init_data(void)
{
    __rom_copy_info* dci;
    __bss_init_info* bii;

    dci = _rom_copy_info;
    while (true) {
        if (dci->size == 0) {
            break;
        }
        __copy_rom_section(dci->addr, dci->rom, dci->size);
        dci++;
    }

    bii = _bss_init_info;
    while (true) {
        if (bii->size == 0) {
            break;
        }
        __init_bss_section(bii->addr, bii->size);
        bii++;
    }
}

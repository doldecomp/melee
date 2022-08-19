#ifndef DOLPHIN_OS_OSRESETSW_H
#define DOLPHIN_OS_OSRESETSW_H

#include <dolphin/types.h>
#include <dolphin/gx/gxtypes.h>

struct _OSResetSW_Unk1;
typedef BOOL (*OSResetSW_Predicate)(struct _OSResetSW_Unk1 *);
typedef struct _OSResetSW_Unk1
{
    union
    {
        u32 u32;
        u8 bytes[4];
    } x0_maybe_color;
    s32 x4;
    s32 x8;
    u8 *xC_buffer;
    u8 x10_pad[0x14 - 0x10];
    u32 x14;
    u8 x18_pad[0x54 - 0x18];
    u8 *x54_buffer;
    u8 x58_pad[0x5E - 0x58];
    u8 x5E;
    u8 x5F_pad[0x8E - 0x5F];
    u8 x8E;
    u8 x8F_pad[0x9A - 0x8F];
    u8 x9A;
    u8 x9B_pad[0xB4 - 0x9B];
    u8 *xB4_buffer;
    u8 xB8_pad[0xBC - 0xB8];
    u32 xBC;
    u8 xC0_pad[0xC4 - 0xC0];
    BOOL xC4;
    u8 xCC_pad[0xD0 - 0xCC];
    BOOL xD0;
    OSResetSW_Predicate xD4;
} OSResetSW_Unk1;

typedef BOOL (*OSResetSW_MulticastPredicate)(OSResetSW_Predicate *);
s32 OSGetResetSwitchState(OSResetSW_Unk1 *);

#endif
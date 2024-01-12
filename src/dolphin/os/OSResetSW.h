#ifndef DOLPHIN_OS_OSRESETSW_H
#define DOLPHIN_OS_OSRESETSW_H

#include <platform.h>

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

struct _OSResetSW_Unk1;
typedef bool (*OSResetSW_Predicate)(struct _OSResetSW_Unk1*);
typedef union {
    OSResetSW_Predicate predicate;
    struct {
        u8 x0_addr_prefix;
        u8 x1_addr_suffix;
    } bytes;
} OSResetSW_Predicate_Union;

typedef enum {
    OSRESETSW_ENUM1_UNK0,
    OSRESETSW_ENUM1_UNK1,
    OSRESETSW_ENUM1_UNK2,
    OSRESETSW_ENUM1_UNK3,
    OSRESETSW_ENUM1_UNK4,
    OSRESETSW_ENUM1_UNK5,
    OSRESETSW_ENUM1_UNK6,
} OSResetSW_Enum1;

typedef struct _OSResetSW_Unk1 {
    OSResetSW_Predicate_Union x0_predicate_union;
    s32 x4;
    s32 x8;
    u8* xC_buffer;
    u8 x10_pad[0x14 - 0x10];
    OSResetSW_Enum1 x14_enum;
    u8 x18_pad[0x54 - 0x18];
    u8* x54_buffer;
    u8 x58_pad[0x5E - 0x58];
    u8 x5E;
    u8 x5F_pad[0x8E - 0x5F];
    u8 x8E;
    u8 x8F_pad[0x9A - 0x8F];
    u8 x9A;
    u8 x9B_pad[0xB4 - 0x9B];
    u8* xB4_buffer;
    u8 xB8_pad[0xBC - 0xB8];
    u32 xBC_flags;
    u8 xC0_pad[0xC4 - 0xC0];
    bool xC4;
    u8 xCC_pad[0xD0 - 0xCC];
    bool xD0;
    OSResetSW_Predicate xD4_predicate;
} OSResetSW_Unk1;

typedef bool (*OSResetSW_MulticastPredicate)(OSResetSW_Predicate*);
bool OSGetResetSwitchState(void);

void __OSResetSWInterruptHandler(__OSInterrupt interrupt, OSContext* context);
bool OSGetResetButtonState(void);

#endif

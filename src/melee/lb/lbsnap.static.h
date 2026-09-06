#ifndef __GALE01_01D2BC
#define __GALE01_01D2BC

#include <Runtime/platform.h>

#include <melee/it/types.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbsnap.h> // IWYU pragma: export
#include <melee/lb/types.h>

struct Unk80433380_48 {
    int card_result;
    int num;
    int free_blocks;
    int free_files;
    lbCardNew_SnapshotEntry entries[0x7F];
};
ASSERT_SIZE(struct Unk80433380_48, 0x408);

struct Unk80433380_0 {
    s32 x0;
    u16 width;
    u16 height;
    u8 x8;
    s32 xC;
    u16 stkind;
    struct it_8026C47C_arg0_t x14;
    s32 x34;
    char x38[4];
};

typedef union LbMcSnapMemSnapIconData {
    u8* ptr;
    int offset;
    int size;
} LbMcSnapMemSnapIconData;

struct Unk80433380 {
    /* 0x00 */ struct Unk80433380_0* snap;
    /* 0x04 */ char filename[64];
    /* 0x44 */ LbMcSnapMemSnapIconData* icon_data;
    /* 0x48 */ struct Unk80433380_48* slot;
    /* 0x4C */ int card_state[2];
    /* 0x54 */ int state_changed[3];
}; /* size = 0x60 */
ASSERT_SIZE(struct Unk80433380, 0x60);

// snapshot save descriptor
struct Unk803BACC8 {
    /* 0x00 */ u8 icon[0x14];
    /* 0x14 */ struct CardEntry entries[2];
};

static struct Unk80433380 lbSnap_80433380;
static struct Unk803BACC8 lbSnap_803BACC8 = {
    { 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3 },
    {
        { 0, 3, NULL },
        { -1, 0, NULL },
    },
};

#endif

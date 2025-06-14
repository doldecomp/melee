#include <baselib/gobj.h>
#include <melee/sc/types.h>
#include <melee/gm/types.h>

struct gm_80479D58_t {
    /* 0x00 */ u32 unk_0;
    /* 0x04 */ u32 unk_4;
    /* 0x08 */ u32 unk_8;
    /* 0x0C */ int unk_C;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ bool (*unk_14)(void);
    /* 0x18 */ bool (*unk_18)(void);
    /* 0x1C */ char pad_1C[0x4]; /* maybe part of unk_18[0xA]? */
    /* 0x20 */ u64 unk_20;
    /* 0x28 */ u64 unk_28;
    /* 0x30 */ void (*unk_30)(void);
    /* 0x34 */ int unk_34;
    /* 0x38 */ u8 unk_38_0 : 1;
    /* 0x38 */ u8 unk_38_1 : 1;
}; /* size = 0x40 */
STATIC_ASSERT(sizeof(struct gm_80479D58_t) == 0x40);


/* 479D30 */ static struct {
    HSD_GObjLibInitDataType initdata;
    u32 pad;
} gm_80479D48;

/* 479D58 */ static struct gm_80479D58_t gm_80479D58;

/* 4D672C */ HSD_GObj* gm_804D672C;
/* 4D6728 */ int gm_804D6728;
/* 4D6724 */ void (*gm_804D6724)(void);
/* 4D6720 */ struct MinorSceneInfo* gm_804D6720;

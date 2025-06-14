#include <baselib/gobj.h>
#include <melee/sc/types.h>
#include <melee/gm/types.h>

struct gm_80479D58_t {
    /* 0x00 */ struct gm_80479D58_t* unk_0;
    /* 0x04 */ char pad_4[4];
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ s32 unk_C; /* inferred */
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x14 */ UNK_T unk_14;
    /* 0x18 */ UNK_T unk_18;
    /* 0x1C */ char pad_1C[0xC]; /* maybe part of unk_18[0xA]? */
    /* 0x28 */ u64 unk_28;
    /* 0x30 */ UNK_T unk_30;
    /* 0x34 */ UNK_T unk_34;
    /* 0x38 */ char pad2[0x8];
}; /* size = 0x40 */
STATIC_ASSERT(sizeof(struct gm_80479D58_t) == 0x40);


/* 479D30 */ extern GameState gm_80479D30;
/* 479D30 */ static HSD_GObjLibInitDataType gm_80479D48;
/* 479D58 */ static struct gm_80479D58_t gm_80479D58;
/* 4D6720 */ static struct MinorSceneInfo* gm_804D6720;
/* 4D672C */ static HSD_GObj* gm_804D672C;

extern int gm_804D6724;
extern int gm_804D6728;

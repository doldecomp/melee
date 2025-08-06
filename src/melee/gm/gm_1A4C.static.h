#include <baselib/gobj.h>
#include <baselib/cobj.h>
#include <melee/sc/types.h>
#include <melee/gm/types.h>

struct gm_804D67F8_t {
    char pad_0[0x948];
};
STATIC_ASSERT(sizeof(struct gm_804D67F8_t) == 0x948);

struct gm_804D67FC_t {
    char pad_0[0x2E68];
};
STATIC_ASSERT(sizeof(struct gm_804D67FC_t) == 0x2E68);

struct gm_804D6804_t {
    /* +0 */ float x0;
    /* +4 */ float x4;
};

/* 4D67F8 */ static struct {
    struct {
        u8 pad0[0x54];
        HSD_GObj* x54;
        u8 pad58[0x8c - 0x58];
        GXColor x8c;
    }* win[2];
    int x8;
}* gm_804D67F8;

/* 4D67FC */ static struct {
    int index;
    struct {
        u8 pad[0x44];
        Mtx mtx;
    }* x4;
    u8 pad[0x3C - 8];
}* gm_804D67FC;

/* 4D6804 */ static struct gm_804D6804_t gm_804D6804;
/* 4D680C */ static struct {
    u8 pad[0x54];
    HSD_GObj* x54;
}* gm_804D680C;
/* 4D6810 */ static s32 gm_804D6810;
/* 4D6814 */ static s32 gm_804D6814;
/* 4D6818 */ static s32 gm_804D6818;
/* 4D681C */ static s32 gm_804D681C;
/* 4D6820 */ static s32 gm_804D6820;
/* 4D6824 */ static f32 gm_804D6824;
/* 4D6828 */ static f32 gm_804D6828;
/* 4D682C */ static HSD_JObj* gm_804D682C;
/* 4D6830 */ static HSD_CObj* gm_804D6830;
/* 4D6834 */ static HSD_CObj* gm_804D6834;
/* 4D6838 */ static HSD_Fog* gm_804D6838;
/* 4D683C */ static UNK_T gm_804D683C;
/* 4D6840 */ static SceneDesc* gm_804D6840;
/* 4D6844 */ static DynamicModelDesc** gm_804D6844;
/* 4D6848 */ static s32 gm_804D6848;
/* 4D684C */ static s32 gm_804D684C;

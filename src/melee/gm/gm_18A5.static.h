#include <melee/gm/types.h>
#include <melee/sc/types.h>

static s32 lbl_804D4190 = 0xFFFFFFFF;

static HSD_Archive* lbl_804D6638;
static HSD_Archive* lbl_804D6640;
static HSD_Archive* lbl_804D6644;
static HSD_Archive* lbl_804D6648;
static SceneDesc* lbl_804D664C;
static SceneDesc* lbl_804D6650;

static struct {
    u8 x0;
    u8 x1;
    u8 pad2[0x32 - 0x2];
    u8 x32;
    u8 pad33[0x5E - 0x33];
    u8 x5E;
    u8 pad5F[0xDC - 0x5F];
} lbl_80473AB8[0x40];

static TmData gm_804771C4;

struct lbl_803D9D20_t {
    /*  +0 */ char pad_0[0xB0];
    /* +B0 */ HSD_CObj* cobj;
    /* +B4 */ char pad_B4[0xD0 - 0xB4];
    /* +D0 */ float xD0;
    /* +D4 */ float xD4;
    /* +D8 */ Vec3 eye_position;
    /* +E4 */ char pad_E4[0xEC - 0xE4];
    /* +EC */ Vec3 interest;
};

static struct lbl_803D9D20_t lbl_803D9D20 = { 0 };

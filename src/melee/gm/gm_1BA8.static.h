#include <melee/gm/types.h>
#include <melee/mn/types.h>

struct UnkSmallLoadData {
    u8 pad[8];
};

struct gm_804D6900_t {
    int x0;
    struct gm_804D6900_x4_t {
        int x0;
        intptr_t x4;
    }* x4;
    StartMeleeRules* x8;
    struct {
        u8 unk0[0x16];
        u8 x16;
    }* xC;
    void* x10;
    s8* x14;
    s8* x18;
};

/* 4D6900 */ static struct gm_804D6900_t** gm_804D6900[2];
/* 4D6908 */ static struct UnkSmallLoadData gm_804D6908;
/* 4D6910 */ static struct UnkSmallLoadData gm_804D6910;
/* 4D6910 */ static struct UnkSmallLoadData gm_804D6918;
/* 4D6920 */ static struct UnkSmallLoadData gm_804D6920;
/* 4D6928 */ static UNK_T gm_804D6928;
/* 4D692C */ static UNK_T gm_804D692C;
/* 4D6930 */ static struct UnkSmallLoadData gm_804D6930;
/* 4D6938 */ static UNK_T gm_804D6938;
/* 4D693C */ static UNK_T gm_804D693C;

/* 497758 */ static CSSData gm_80497758;
/* 4978A0 */ static StartMeleeData gm_804978A0;
/* 4979D8 */ static MatchExitInfo gm_804979D8[2];
/* 49BEE8 */ static CSSData gm_8049BEE8;
/* 49C030 */ static CSSData gm_8049C030;
/* 49C178 */ static u8 gm_8049C178[16];
/* 49C188 */ static UNK_T gm_8049C188[0x138 / 4];
/* 49C2C0 */ static MatchExitInfo gm_8049C2C0;
/* 49E548 */ static struct gm_8049E548_t gm_8049E548;

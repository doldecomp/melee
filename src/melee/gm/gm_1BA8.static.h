#include <melee/gm/types.h>
#include <melee/mn/types.h>

extern CSSData gm_80497758;
extern StartMeleeData gm_804978A0;
extern MatchExitInfo gm_804979D8;

static struct gm_804D6900_t {
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
    struct {
        u8 pad[0x10];
        UNK_T x10;
    }** x10;
    s8* x14;
    s8* x18;
}** gm_804D6900;

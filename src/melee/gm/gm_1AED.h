#ifndef MELEE_GM_1AED_H
#define MELEE_GM_1AED_H

#include <placeholder.h>
#include <melee/gm/forward.h>

struct gm_80480DA8_0_t {
    int unk0;
    u8 unk4;
    u8 unk5;
    u8 _[2];
};

struct gm_80480DA8_8_t {
    int unk0;
    u8 unk4;
};

struct gm_80480DA8_t {
    struct gm_80480DA8_0_t unk0;
    struct gm_80480DA8_8_t unk8;
    int unk10;
    int unk14;
    int unk18;
    u8 unk1C;
};

/* 1AEE6C */ void gm_801AEE6C(int, int, int);
/* 1AF0D4 */ bool gm_801AF0D4(void);
/* 1AF250 */ void gm_801AF250(void);
/* 1AF568 */ UNK_RET gm_801AF568(UNK_PARAMS);
/* 1B0264 */ void gm_801B0264(struct gm_80480DA8_t*);
/* 1B0304 */ void gm_801B0304(struct gm_80480DA8_8_t*);

#endif

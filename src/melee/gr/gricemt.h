#ifndef GALE01_1F6868
#define GALE01_1F6868

#include <melee/gr/forward.h>

#include <dolphin/mtx.h>
#include <melee/gr/types.h>

/* 1FA6D8 */ void grIceMt_801FA6D8(void);
/* 1FA728 */ void grIceMt_801FA728(Vec3*);
/* 3E4800 */ extern StageData grIm_StageData;

struct grIceMt_YakumonoParam {
    s16 x0;
    s16 x2;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    s16 x34;
    s16 x36;
    s16 x38;
    u16 x3A;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
    float x54;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    float x6C;
    float x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90;
    float x94;
    s16 ft_max_y;
    s16 x9E;
    float x9C;
    float xA0;
    s16 xA4;
    s16 xA6;
    s16 xA8;
    s16* field_ixs;
    s16* xB0;
    s16* xB4;
    s16 xB8;
    s16 pad;
    grZakoGenerator_SpawnDesc xBC;
    float xC0;
    float xC4;
    float xC8;
    float xCC;
};

#endif

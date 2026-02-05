#ifndef MELEE_GM_CLASSIC_H
#define MELEE_GM_CLASSIC_H

#include <placeholder.h>

#include <melee/gm/forward.h>

/* 1B2BA4 */ UNK_RET gm_801B2BA4(UNK_PARAMS);
/* 1B2D54 */ UNK_RET gm_801B2D54(UNK_PARAMS);
/* 1B2F78 */ void gm_801B2F78_OnLoad(void);
/* 1B34B8 */ void gm_801B34B8_OnInit(void);
/* 1B3500 */ void gm_801B3500(MinorScene*);
/* 1B3A34 */ void gm_801B3A34(MinorScene*);
/* 1B3B40 */ void gm_801B3B40(MinorScene*);
/* 1B3D44 */ void gm_801B3D44(MinorScene*);
/* 1B3D84 */ void gm_801B3D84(MinorScene*);
/* 1B3DD8 */ void gm_801B3DD8(MinorScene*);
/* 1B3E44 */ void gmClassic_801B3E44(MinorScene*);
/* 1B3F18 */ void gm_801B3F18(MinorScene*);

typedef struct gm_803DDEC8Struct{
    u8 x0;
    u8 x1_b0 : 1;
    u8 x1_b1 : 1;
    u8 x1_b2 : 1;
    u8 x1_b3 : 1;
    u8 x1_b4 : 1;
    u8 x1_b5 : 1;
    u8 x1_b6 : 1;
    u8 x1_b7 : 1;
    u8 x2[0xC - 0x2];
    void* xC;
} gm_803DDEC8Struct;

gm_803DDEC8Struct gm_803DDEC8;
#endif

#ifndef GALE01_32110C
#define GALE01_32110C

#include <placeholder.h>

#include <baselib/forward.h>

typedef struct vi1202_UnkStruct vi1202_UnkStruct;

typedef struct vi1202_ViData {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ u8 pad18[0x20 - 0x18];
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ s32 x3C;
    /* 0x40 */ f32 x40;
} vi1202_ViData;

/* 4D6500 */ extern vi1202_ViData* Fighter_804D6500;

/* 32110C */ void un_8032110C(HSD_GObj*);
/* 321130 */ void un_80321130(HSD_GObj*);
/* 321154 */ void un_80321154(HSD_GObj*);
/* 321178 */ UNK_RET un_80321178(UNK_PARAMS);
/* 321294 */ void un_80321294(HSD_GObj*);
/* 321300 */ void un_80321300_OnEnter(UNK_T);
/* 3218E0 */ void un_803218E0_OnFrame(void);
/* 321900 */ void un_80321900(void);
/* 321950 */ void un_80321950(vi1202_UnkStruct*);
/* 3219AC */ void fn_803219AC(HSD_GObj*);
/* 321A00 */ void un_80321A00(HSD_GObj*);
/* 321AF4 */ void un_80321AF4(HSD_GObj*);
/* 321BF8 */ void un_80321BF8(int);
/* 321C28 */ void un_80321C28(void);
/* 321C70 */ void un_80321C70(void);
/* 321CA4 */ void un_80321CA4(s32);
/* 321CE8 */ void un_80321CE8(void);
/* 321D30 */ UNK_RET un_80321D30(UNK_PARAMS);
/* 321EBC */ UNK_RET un_80321EBC(UNK_PARAMS);
/* 32201C */ void un_8032201C(int, s32);
/* 322178 */ void un_80322178(int);
/* 322258 */ bool un_80322258(float);
/* 322298 */ s32 un_80322298(float);
/* 3222EC */ float un_803222EC(float mag, float angle);
/* 322314 */ void un_80322314(void);
/* 32233C */ void un_8032233C(int, int);
/* 3224DC */ bool un_803224DC(s32 spawn_id, f32 pos_x, f32 kb_mag);
/* 322598 */ int un_80322598(int, float);

#endif

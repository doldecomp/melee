#ifndef MELEE_GM_1832_H
#define MELEE_GM_1832_H

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/* 1849E0 */ void fn_801849E0(HSD_GObj*);
/* 184A04 */ void fn_80184A04(HSD_GObj*);
/* 184A28 */ void fn_80184A28(HSD_GObj*);
/* 184A4C */ void fn_80184A4C(HSD_GObj*);
/* 184A70 */ void fn_80184A70(HSD_GObj*);
/* 184A94 */ void fn_80184A94(HSD_GObj*);
/* 184AB8 */ void fn_80184AB8(HSD_GObj*);
/* 18504C */ void fn_8018504C(void);
/* 1851C0 */ s32 fn_801851C0(void);
/* 1852FC */ void fn_801852FC(HSD_GObj*);
/* 185408 */ void fn_80185408(int, float, float, float, float);
/* 1855BC */ double fn_801855BC(double);
/* 18564C */ void fn_8018564C(HSD_GObj*);
/* 18569C */ void fn_8018569C(HSD_GObj*);
/* 18575C */ void fn_8018575C(HSD_GObj*);
/* 1857C4 */ void fn_801857C4(HSD_GObj*);
/* 1859C8 */ void fn_801859C8(HSD_GObj*);
/* 185A0C */ s32 fn_80185A0C(void);
/* 185D64 */ void fn_80185D64(void);
/* 185E34 */ s32 fn_80185E34(void);
/* 185F5C */ void fn_80185F5C(s32);
/* 186080 */ void fn_80186080(void);
/* 1861B8 */ void fn_801861B8(void);
/* 186400 */ void fn_80186400(void);
/* 186634 */ void fn_80186634(void*);
/* 186DFC */ void gm_Scene_IntroEasy_OnFrame(void);
/* 186E30 */ void gm_Scene_IntroEasy_OnEnter(void*);

typedef struct {
    /* 0x00 */ f32 vals[3];
} ClassicSlotVals;
ASSERT_SIZE(ClassicSlotVals, 0xC);

typedef struct {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ Vec3 x08;
    /* 0x14 */ u8 pad_14[0x8];
} ClassicCharLayout;
ASSERT_SIZE(ClassicCharLayout, 0x1C);

typedef struct {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ f32 x08;
    /* 0x0C */ u8 pad_0C[0x8];
} ClassicTeamEntry;
ASSERT_SIZE(ClassicTeamEntry, 0x14);

typedef struct {
    /* 0x00 */ f32 x00[3];
    /* 0x0C */ f32 x0C[3];
    /* 0x18 */ f32 x18[3];
    /* 0x24 */ f32 x24[3];
} ClassicSplashRow;
ASSERT_SIZE(ClassicSplashRow, 0x30);

struct lbl_804D6604_t {
    /* 0x000 */ ClassicSlotVals x00[2];
    /* 0x018 */ ClassicSlotVals x18[3];
    /* 0x03C */ ClassicSlotVals x3C[4];
    /* 0x06C */ ClassicCharLayout x6C[28];
    /* 0x37C */ ClassicTeamEntry x37C[25];
    /* 0x570 */ u8 pad_570[0xC];
    /* 0x57C */ ClassicSplashRow x57C[3];
    /* 0x60C */ u8 pad_60C[0x24];
    /* 0x630 */ ClassicSlotVals x630[3];
    /* 0x654 */ ClassicSlotVals x654[3];
    /* 0x678 */ ClassicSlotVals x678[4];
    /* 0x6A8 */ ClassicCharLayout x6A8[28];
};

#endif

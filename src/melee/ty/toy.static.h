#ifndef __GALE01_305058
#define __GALE01_305058

#include "math.h"
#include "types.h"

#include <platform.h>

#include "baselib/fog.h"

#include "if/forward.h"

#include <stddef.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

/* 3053C4 */ static void _Toy_803053C4(s32, s32, s32);
/* 3062EC */ static void _Toy_803062EC(s32 arg0, u32 arg1, f32 farg0);
/* 3064B8 */ static s16 _Toy_803064B8(s16 arg0, s8 arg1);
/* 30663C */ static void _Toy_8030663C(void);
/* 306A0C */ static void _Toy_80306A0C(HSD_GObj* arg0, int);
/* 306C5C */ static void _Toy_80306C5C(HSD_GObj* arg0);
/* 307018 */ static void _Toy_80307018(void);
/* 30715C */ static void _Toy_8030715C(f32, f32);
/* 3075E8 */ static void _Toy_803075E8(s32 arg0);
/* 307828 */ static void _Toy_80307828(int);
/* 3078E4 */ static void _Toy_803078E4(void);
/* 307BA0 */ static HSD_JObj* _Toy_80307BA0(HSD_JObj*, s16);
/* 307F64 */ static void _Toy_80307F64(s32, s32);
/* 3084A0 */ static void _Toy_803084A0(s32 arg0);
/* 308DC8 */ static void _Toy_80308DC8(HSD_CObj*);
/* 308F04 */ static void _Toy_80308F04(HSD_CObj*);
/* 309338 */ static f32 _Toy_80309338(Vec3* arg0, Vec3* arg1);
/* 309404 */ static void _Toy_80309404(HSD_GObj*);
/* 30B530 */ static void _Toy_8030B530(HSD_GObj*);
/* 30E110 */ static void _Toy_8030E110(HSD_GObj*);
/* 30FA50 */ static void _Toy_8030FA50(void);
/* 30FE48 */ static void _Toy_8030FE48(void*, s32);
/* 3102C4 */ static void _Toy_803102C4(s8 arg0);
/* 3109A0 */ static void _Toy_803109A0(s32, s32, s32);
/* 310B48 */ static void _Toy_80310B48(HSD_GObj*);
/* 3114E8 */ static void _Toy_803114E8(void);
/* 311788 */ static void _Toy_80311788(void);
/* 311F5C */ static void _Toy_80311F5C(void);
/* 312050 */ static void _Toy_80312050(HSD_GObj* gobj, int code);
/* 3B8844 */ static HSD_FogDesc const _Toy_803B8844 = {
    GX_FOG_LIN, NULL, 0.0f, 1.0f, { 0xFF, 0xFF, 0xFF, 0xFF },
};
/* 3B8858 */ static Vec3 const _Toy_803B8858 = { 0.0f, 8.0f, 0.0f };
/* 3B8864 */ static PosArrayFull const _Toy_803B8864 = { {
    { 526, 176 },
    { 512, 74 },
    { 0, 74 },
    { 491, 174 },
    { 46, 423 },
    { 66, 37 },
    { 546, 37 },
} };
/* 3B889C */ static PosArrayFull const _Toy_803B889C = { {
    { 526, 172 },
    { 496, 74 },
    { 0, 72 },
    { 491, 174 },
    { 46, 423 },
    { 66, 37 },
    { 546, 37 },
} };
/* 3B88D4 */ static Vec3 const _Toy_803B88D4 = { 0 };
/* 3B88E0 */ static Vec3 const _Toy_803B88E0 = { 0 };
/* 3B88EC */ static Vec3 const _Toy_803B88EC = { 0 };
/* 3B88F8 */ static Vec3 const _Toy_803B88F8 = { 0 };
/* 3B8904 */ static Vec3 const _Toy_803B8904 = { 0 };
/* 3B8910 */ static ToyEntry const _Toy_803B8910[] = {
    { 7, 65 }, { 6, 66 }, { 5, 67 }, { 4, 68 }, { 3, 69 },
    { 2, 70 }, { 0, 73 }, { 1, 88 }, { 8, 83 },
};
/* 4A26B8 */ static struct _Toy_804A26B8_t _Toy_804A26B8;
/* 4A26C4 */ static char _Toy_devtext_buf_804A26C4[0x8C];
/* 4A2750 */ static char _Toy_devtext_buf_804A2750[0xFC];
/* 4A284C */ unsigned short Toy_804A284C[302];
/* 4A2AA8 */ ToyAnimState Toy_804A2AA8;
/* 4D5A40 */ static GXColor _Toy_color_E2E2E2FF = { 0xE2, 0xE2, 0xE2, 0xFF };
/* 4D5A44 */ static GXColor _Toy_color_FF8020FF = { 0xFF, 0x80, 0x20, 0xFF };

/// @warning do not sort. Private members cannot be declared @c static.
/* 4D6EE0 */ TyDisplayData* Toy_sbss_804D6EE0;
/* 4D6EDC */ s16* Toy_sbss_804D6EDC;
/* 4D6ED8 */ ToyED8Data* Toy_sbss_804D6ED8;
/* 4D6ED4 */ ToyCameraControl* Toy_sbss_804D6ED4;
/* 4D6ED0 */ HSD_Archive* _Toy_sbss_804D6ED0;
/* 4D6ECC */ HSD_Archive* _Toy_sbss_804D6ECC;
/* 4D6EC8 */ HSD_Archive* Toy_sbss_804D6EC8;
/* 4D6EC4 */ struct TrophyData* _Toy_sbss_804D6EC4;
/* 4D6EC0 */ struct TrophyData* _Toy_sbss_804D6EC0;
/* 4D6EBC */ void* _Toy_sbss_804D6EBC;
/* 4D6EB8 */ void* _Toy_sbss_804D6EB8;
/* 4D6EB4 */ short* _Toy_sbss_804D6EB4;
/* 4D6EB0 */ TyDspEntry* Toy_sbss_804D6EB0;
/* 4D6EAC */ TyDspEntry* Toy_sbss_804D6EAC;
/* 4D6EA8 */ void* _Toy_sbss_804D6EA8;
/* 4D6EA4 */ void* _Toy_sbss_804D6EA4;
/* 4D6EA2 */ s8 _Toy_sbss_804D6EA2;
/* 4D6EA1 */ u8 _Toy_sbss_804D6EA1;
/* 4D6EA0 */ u8 _Toy_sbss_804D6EA0;
/* 4D6E9C */ DevText* _Toy_sbss_804D6E9C;
/* 4D6E98 */ DevText* _Toy_sbss_804D6E98;
/* 4D6E94 */ f32 _Toy_sbss_804D6E94;
/* 4D6E90 */ f32 _Toy_sbss_804D6E90;
/* 4D6E8C */ f32 _Toy_sbss_804D6E8C;
/* 4D6E88 */ f32 _Toy_sbss_804D6E88;
/* 4D6E84 */ f32 _Toy_sbss_804D6E84;
/* 4D6E80 */ f32 _Toy_sbss_804D6E80;
/* 4D6E7C */ s32 _Toy_sbss_804D6E7C;
/* 4D6E78 */ s32 _Toy_sbss_804D6E78;
/* 4D6E74 */ s32 _Toy_sbss_804D6E74;
/* 4D6E70 */ s32 _Toy_sbss_804D6E70;
/* 4D6E6C */ TyViewData* _Toy_sbss_804D6E6C;
/* 4D6E68 */ Toy6E68* _Toy_sbss_804D6E68;
/* 4D6E64 */ s16* _Toy_sbss_804D6E64;
/* 4D6E60 */ s32 _Toy_sbss_804D6E60;
/* 4D6E5C */ void** _Toy_sbss_804D6E5C;
/* 4D6E58 */ s32 _Toy_sbss_804D6E58;
/* 4D6E54 */ s32 _Toy_sbss_804D6E54;
/* 4D6E50 */ s8 _Toy_sbss_804D6E50;

STATIC_ASSERT(sizeof(_Toy_803B8910) == 0x48);
STATIC_ASSERT(sizeof(_Toy_devtext_buf_804A26C4) == 0x8C);
STATIC_ASSERT(sizeof(_Toy_devtext_buf_804A2750) == 0xFC);

/// @todo .sdata2 order hack
static void order_sdata2_0(void)
{
    /*   +0 */ (void) 100.0f;
    /*   +8 */ (void) S32_TO_F32;
    /*  +10 */ (void) 0.0f;
    /*  +14 */ (void) 0.1f;
    /*  +18 */ (void) 1.0f;
    /*  +1C */ (void) -3000.0f;
    /*  +20 */ (void) 3000.0f;
    /*  +24 */ (void) deg_to_rad;
    /*  +28 */ (void) 2.0f;
    /*  +2C */ (void) 38.0f;
    /*  +30 */ (void) 0.25f;
}
#endif

/* 4DDCFC */ static GXColor const _Toy_color_FFBA00FF = { 0xFF, 0xBA, 0x00,
                                                          0xFF };

/// @todo .sdata2 order hack
static void order_sdata2_38(void)
{
    /*  +38 */ (void) 0.9f;
    /*  +3C */ (void) -10.9f;
    /*  +40 */ (void) 384.0f;
    /*  +44 */ (void) 64.0f;
    /*  +48 */ (void) 0.044f;
    /*  +4C */ (void) 0.103f;
    /*  +50 */ (void) 1.75f;
    /*  +54 */ (void) 0.2f;
    /*  +58 */ (void) -5.1f;
    /*  +5C */ (void) 17.2f;
    /*  +60 */ (void) 0.035f;
    /*  +64 */ (void) 0.034f;
    /*  +68 */ (void) -5.0f;
    /*  +6C */ (void) 0.033f;
    /*  +70 */ (void) 0.7f;
    /*  +74 */ (void) 7.9f;
    /*  +78 */ (void) 9.0f;
    /*  +7C */ (void) 0.03f;
    /*  +80 */ (void) 25.0f;
    /*  +84 */ (void) -3.0f;
    /*  +88 */ (void) 15.0f;
    /*  +8C */ (void) 10.0f;
    /*  +90 */ (void) 0.0013187003f;
    /*  +94 */ (void) 0.036397f;
    /*  +98 */ (void) 0.00008119978f;
    /*  +9C */ (void) -0.036397f;
    /*  +A0 */ (void) 0.0032531999f;
    /*  +A4 */ (void) 0.044307f;
    /*  +A8 */ (void) 0.0017468001f;
    /*  +AC */ (void) -0.044307f;
    /*  +B0 */ (void) 0.049584f;
    /*  +B4 */ (void) -0.035585f;
    /*  +B8 */ (void) 0.076839f;
    /*  +BC */ (void) -0.026839f;
    /*  +C0 */ (void) 0.5;
    /*  +C8 */ (void) 3.0;
    /*  +D0 */ (void) -0.2f;
    /*  +D4 */ (void) 0.8f;
    /*  +D8 */ (void) 2400.0f;
    /*  +DC */ (void) 0.01f;
    /*  +E0 */ (void) -360.0f;
    /*  +E4 */ (void) 360.0f;
    /*  +E8 */ (void) 7200.0f;
    /*  +EC */ (void) 8.0f;
    /*  +F0 */ (void) -0.3f;
    /*  +F4 */ (void) 0.3f;
    /*  +F8 */ (void) 0.025f;
    /*  +FC */ (void) -0.025f;
    /* +100 */ (void) 5.0f;
    /* +104 */ (void) 250.0f;
    /* +108 */ (void) 3.0f;
    /* +10C */ (void) -89.0f;
    /* +110 */ (void) 89.0f;
    /* +118 */ (void) U32_TO_F32;
    /* +120 */ (void) 0.001f;
    /* +124 */ (void) -0.01f;
    /* +128 */ (void) 57.29578f;
    /* +12C */ (void) -1.0f;
    /* +130 */ (void) -25.0f;
    /* +134 */ (void) -0.8f;
    /* +138 */ (void) 0.57595867f;
    /* +13C */ (void) -0.6f;
    /* +140 */ (void) 0.6f;
}

/* 4DDE0C */ static GXColor const _Toy_color_4080D060_0 = { 0x40, 0x80, 0xD0,
                                                            0x60 };

/// @todo .sdata2 order hack
static void order_sdata2_148(void)
{
    /* +148 */ (void) 12.0f;
    /* +14C */ (void) 18.0f;
}

/* 4DDE18 */ static GXColor const _Toy_color_40B0D060_1 = { 0x40, 0x80, 0xD0,
                                                            0x60 };

/// @todo .sdata2 order hack
static void order_sdata2_154(void)
{
    /* +154 */ (void) -3.25f;
    /* +158 */ (void) 3.25f;
}

// STATIC_ASSERT(sizeof(*Toy_sbss_804D6ED4) == 0xE4);
// STATIC_ASSERT(sizeof(*_Toy_sbss_804D6EA4) == 0x54);
// STATIC_ASSERT(sizeof(*_Toy_sbss_804D6E64) == 0x6DE);
// STATIC_ASSERT(sizeof(*_Toy_sbss_804D6E68) == 0x64);
// STATIC_ASSERT(sizeof(*_Toy_sbss_804D6E6C) == 0x8);
// STATIC_ASSERT(sizeof(*Toy_sbss_804D6ED8) == 0x5C);
// STATIC_ASSERT(sizeof(*Toy_sbss_804D6EDC) == 0x24A);
// STATIC_ASSERT(sizeof(*Toy_sbss_804D6EE0) == 0x158);

/// @todo begin .sdata hack

/// @todo .sdata order hack
static void order_sdata_8(void)
{
    /*  +8 */ (void) "toy.c";
    /* +10 */ (void) "0";
    /* +14 */ (void) "lobj.h";
    /* +1C */ (void) "lobj";
    /* +24 */ (void) "jobj.h";
    /* +2C */ (void) "jobj";
}

/// @todo end .sdata hack

/// @todo Should be a literal, probably a getter function
///       or part of #_Toy_803FDDE4.
/* 3FDD18 */ static char _Toy_str_TyLight_dat[] = "TyLight.dat";

/* 3FDDE4 */ static struct lbl_803FDDE4_t _Toy_803FDDE4 = {
    {
        { "ScToyLightMaster0_scene_lights", 0 },
        { "ScToyLightMaster1_scene_lights", 0 },
        { "ScToyLightMaster2_scene_lights", 0 },
        { "ScToyLightMaster4_scene_lights", 0 },
        { "ScToyLightMaster5_scene_lights", 0 },
        { "ScToyLightMaster6_scene_lights", 0 },
    },
    {
        { 0, { 0x00, 0x00, 0x19, 0xFF }, true },
        { 1, { 0x10, 0x20, 0x20, 0xFF }, true },
        { 2, { 0x26, 0x13, 0x30, 0xFF }, false },
        { 3, { 0x12, 0x12, 0x12, 0xFF }, true },
        { 4, { 0x00, 0x00, 0x19, 0xFF }, false },
        { 5, { 0x00, 0x00, 0x19, 0xFF }, false },
    },
};

/// @todo .data order hack
static void order_data_144(void)
{
    /* +144 */ (void) "TyStand.dat";
    /* +150 */ (void) "ToyStandModel_TopN_joint";
}

/// @todo Should be @c static but changing it affects .data order.
///       #_Toy_803FDEA0 points to #_Toy_803FDEA4, which contains the string.
/* 3FDEA0 */ char* _Toy_803FDEA0[] = {
    "ToyFigurePanel_Top_joint",
};

/* 3FDEBC */ static char* _Toy_803FDEBC[] = {
    "ToyFigureBack_Top_joint",
    "ToyFigureBack_Top_joint",
    NULL,
    "ToyFigureBack_Top_joint",
    NULL,
    NULL,
};

struct ModelNamesDesc {
    char* animjoint;
    char* matanim_joint;
    char* shapeanim_joint;
};

/* 3FDF3C */ static struct ModelNamesDesc _Toy_803FDF3C = {
    "ToyFigurePanel_Top_animjoint",
    "ToyFigurePanel_Top_matanim_joint",
    "ToyFigurePanel_Top_shapeanim_joint",
};

/* 3FDFA8 */ static struct ModelNamesDesc _Toy_803FDFA8[6] = {
    {
        "ToyFigureBack_Top_animjoint",
        "ToyFigureBack_Top_matanim_joint",
        "ToyFigureBack_Top_shapeanim_joint",
    },
    {
        "ToyFigureBack_Top_animjoint",
        "ToyFigureBack_Top_matanim_joint",
        "ToyFigureBack_Top_shapeanim_joint",
    },
    { 0 },
    {
        "ToyFigureBack_Top_animjoint",
        "ToyFigureBack_Top_matanim_joint",
        "ToyFigureBack_Top_shapeanim_joint",
    }
};

/* 3FE038 */ static char* _Toy_803FE038[3] = {
    "ToyFigureBg3_sobjdesc",
    "ToyFigureBg5_sobjdesc",
    "ToyFigureBg6_sobjdesc",
};

/* 3FE108 */ static char* _Toy_803FE108[7] = {

    "ToyCameraInfoBoad_sobjdesc",   "ToyCameraInfoNext_sobjdesc",
    "ToyCameraInfoPrev_sobjdesc",   "ToyCameraInfoButton_sobjdesc",
    "ToyCameraInfoReturn_sobjdesc", "ToyCameraInfoL_sobjdesc",
    "ToyCameraInfoR_sobjdesc",
};

/* 3FE244 */ static struct ModelNamesDesc _Toy_803FE244[2] = {

    {
        "ToyStandModel_TopN_ACTION_action1_animjoint",
        "ToyStandModel_TopN_ACTION_action1_matanim_joint",
        "ToyStandModel_TopN_ACTION_action1_shapeanim_joint",
    },
    {
        "ToyStandModel_TopN_ACTION_action2_animjoint",
        "ToyStandModel_TopN_ACTION_action2_matanim_joint",
        "ToyStandModel_TopN_ACTION_action2_shapeanim_joint",
    },
};

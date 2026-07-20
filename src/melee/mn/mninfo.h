#ifndef MELEE_MN_INFO_H
#define MELEE_MN_INFO_H

#include "placeholder.h"

#include "baselib/forward.h"
#include "sc/forward.h"

/// seems like each menu probably has its own struct, and isnt just the 'Menu'
/// in types.h
typedef struct MnInfoData {
    /* +00 */ u8 scroll_idx;
    /* +04 */ u32 anim_timer; ///< decrements from 10 when transitioning from
                              ///< main menu to special menu
    /* +08 */ HSD_Text*
        left_column[4]; ///< date and time of achievement unlock
    /* +18 */ HSD_Text* right_column[4]; ///< achievement
    /* +28 */ HSD_Text* description;
} MnInfoData;

#define GET_MNINFO(gobj) ((MnInfoData*) HSD_GObjGetUserData(gobj))

typedef struct HSD_GObj MenuInfo_GObj;

extern StaticModelDesc mnInfo_804A0958;
extern u8 mnInfo_804A0968[0x48];

/* 251A08 */ s32 mnInfo_80251A08(s32);
/* 251AA4 */ s32 mnInfo_80251AA4(void);
/* 251AFC */ void mnInfo_80251AFC(void);
/* 251D58 */ s32 mnInfo_80251D58(MenuInfo_GObj*, s32, u32, u32);
/* 251F04 */ void mnInfo_80251F04(MenuInfo_GObj*, s32, u32);
/* 251FE4 */ void fn_80251FE4(void);
/* 2522B8 */ void mnInfo_802522B8(HSD_GObj*);
/* 2523B8 */ void fn_802523B8(HSD_GObj*);
/* 2523D8 */ void fn_802523D8(HSD_GObj*);
/* 252548 */ void fn_80252548(HSD_GObj*);
/* 252720 */ void mnInfo_80252720(MnInfoData*);
/* 252758 */ s32 mnInfo_80252758(void);

#endif

#ifndef MELEE_MN_INFO_H
#define MELEE_MN_INFO_H

#include "placeholder.h"

#include "baselib/forward.h"

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

/// was using this to try and fix some matches, unsuccessfully
#ifdef M2CTX
typedef struct MenuInfo_GObj MenuInfo_GObj;
struct MenuInfo_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ MenuInfo_GObj* next;
    /*  +C */ MenuInfo_GObj* prev;
    /* +10 */ MenuInfo_GObj* next_gx;
    /* +14 */ MenuInfo_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ void (*rendered)(MenuInfo_GObj* gobj, s32 code);
    /* +20 */ u64 gxlink_prios;
    /* +28 */ HSD_JObj* hsd_obj;
    /* +2C */ MnInfoData* user_data;
    /* +30 */ void (*user_data_remove_func)(MenuInfo_GObj* data);
    /* +34 */ void* x34_unk;
};
#else
typedef struct HSD_GObj MenuInfo_GObj;
#endif

/* 251A08 */ s32 mnInfo_80251A08(s32);
/* 251AA4 */ s32 mnInfo_80251AA4(void);
/* 251AFC */ UNK_RET mnInfo_80251AFC(UNK_PARAMS);
/* 251D58 */ UNK_RET mnInfo_80251D58(UNK_PARAMS);
/* 251F04 */ void mnInfo_80251F04(MenuInfo_GObj*, u32, u32);
/* 251FE4 */ UNK_RET fn_80251FE4(UNK_PARAMS);
/* 2522B8 */ void mnInfo_802522B8(HSD_GObj*);
/* 2523B8 */ void fn_802523B8(HSD_GObj*);
/* 2523D8 */ UNK_RET fn_802523D8(UNK_PARAMS);
/* 252548 */ UNK_RET fn_80252548(UNK_PARAMS);
/* 252720 */ void mnInfo_80252720(MnInfoData*);
/* 252758 */ UNK_RET mnInfo_80252758(UNK_PARAMS);

#endif

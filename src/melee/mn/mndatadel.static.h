#ifndef MELEE_MN_STATIC_DATADEL_H
#define MELEE_MN_STATIC_DATADEL_H

#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "lb/lb_00F9.h"

#include "mn/forward.h"

#include "mn/mnmainrule.h"
#include "mn/types.h"
#include "sc/types.h"

extern void HSD_Free(void*);

struct MnDataDelSelectData {
    s32 x0;
    s32 x4;
};

struct MnDataDelUserData {
    /* +0x00 */ u8 selected_item;  ///< Current menu selection (0-5)
    /* +0x01 */ u8 confirm_active; ///< Confirmation dialog active
    /* +0x02 */ u8 x2;
    /* +0x03 */ u8 item_deleted[6]; ///< Flags for deleted items (0-5)
    /* +0x09 */ u8 pad[3];          ///< Padding for alignment
    /* +0x0C */ HSD_Text* label_text;
    /* +0x10 */ struct mn_80231634_t* menu_joints[8];
};

struct WarnCmnData {
    /* +00 */ u8 x0;          ///< Menu item being confirmed (0-5, compared with 5 in confirm handler)
    /* +01 */ u8 visible;     ///< Dialog visibility state: 0=hidden, 1/2=showing
    /* +02 */ u8 cursor_idx;  ///< Yes/No cursor selection (0 or 1)
};

enum WarnCommonJoints {
    WARN_JOINT_ROOT,
    WARN_JOINT_BACKGROUND,
    WARN_JOINT_PANEL,             ///< main panel root
    WARN_JOINT_PANEL_TOP,         ///< top position of the panel/text box
    WARN_JOINT_PANEL_TEXT_BOTTOM, ///< bottom position of the text box
    WARN_JOINT_PANEL_BOTTOM,      ///< bottom position of the panel
    WARN_JOINT_CURSOR_YES,
    WARN_JOINT_CURSOR_NO,
    WARN_JOINT_EXCLAIM,
    WARN_JOINT_EXCLAIM_MARK,
    WARN_JOINT_EXCLAIM_ARROW,
    WARN_JOINT_PROGRESS_BAR,
    WARN_JOINT_PROGRESS_BAR_START,
    WARN_JOINT_PROGRESS_BAR_END,
};

struct MnDataDelData {
    AnimLoopSettings x0;
    AnimLoopSettings xC;
    AnimLoopSettings x18;
    AnimLoopSettings x24;
    AnimLoopSettings x30;
    /* +0x3C */ s32 item_joint_indices[7]; ///< Joint indices for menu items
    /* +0x58 */ s16 item_label_ids[6];     ///< SIS label IDs for menu items
    f32 x64;
    f32 x68;
    f32 x6C;
};

static inline void JObj_GetChildAtIdx(HSD_JObj* parent, HSD_JObj** child,
                                      s32 idx)
{
    lb_80011E24(parent, child, idx, -1);
}

static inline void JObj_HideChildAtIdx(HSD_JObj* root, s32 idx)
{
    HSD_JObj* child;
    lb_80011E24(root, &child, idx, -1);
    HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
}

static inline bool Anim_IsFrameInRange(float frame, AnimLoopSettings* settings)
{
    return frame >= settings->start_frame && frame < settings->end_frame;
}

#define FRAME_IN_RANGE(frame, settings)                                       \
    ((frame) >= (settings).start_frame && (frame) < (settings).end_frame)

extern HSD_GObj* mnDataDel_804D6C68;
extern HSD_Text* mnDataDel_804D6C6C;
extern struct MnDataDelSelectData mnDataDel_803EF8AC;
extern f32 mnDataDel_804DC1A8;
extern f32 mnDataDel_804DC1AC;
extern f32 mnDataDel_804DC1B0;
extern f32 mnDataDel_804DC1B4;
extern f32 mnDataDel_804DC1B8;
extern f32 mnDataDel_804DC1BC;
extern f32 mnDataDel_804DC1C0;
extern f32 mnDataDel_804DC1C4;
extern f32 mnDataDel_804DC1C8;
extern f32 mnDataDel_804DC1CC;
extern f32 mnDataDel_804DC1D0;
static struct MnDataDelData mnDataDel_803EF870;
static AnimLoopSettings mnDataDel_803EF8A0 = {
    0.0f, 9.0f, -0.1f
}; /// mnDataDel_803EF870[4]
static StaticModelDesc mnDataDel_804A0918;
static StaticModelDesc mnDataDel_804A0928;
static StaticModelDesc mnDataDel_804A0938;

#endif

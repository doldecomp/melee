#ifndef MELEE_MN_STATIC_DATADEL_H
#define MELEE_MN_STATIC_DATADEL_H

#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"
#include "lb/lb_00F9.h"

#include "mn/forward.h"

#include "mn/types.h"
#include "sc/types.h"

struct WarnCmnData {
    /* +00 */ u8 x0;
    /* +01 */ u8 visible;
    /* +02 */ u8 cursor_idx;
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
};

struct MnDataDelGObjUserData {
    /* +00 */ u8 x0;
    /* +01 */ u8 x1;
    /* +02 */ u8 x2;
    /* +03 */ u8 x3[6];
    /* +0C */ HSD_Text* xC;
    /* +10 */ HSD_JObj* x10[8];
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
static struct MnDataDelData mnDataDel_803EF870 = {
    { 0, 19, -0.1 },
    { 20, 29, -0.1 },
};
static AnimLoopSettings mnDataDel_803EF888 = { 0, 5, -0.1 };
static AnimLoopSettings mnDataDel_803EF894 = { 0, 0, -0.1 };
static AnimLoopSettings mnDataDel_803EF8A0 = {
    0.0f, 9.0f, -0.1f
}; /// mnDataDel_803EF870[4]
static u32 mnDataDel_803EF8AC[] = { 1, 2, 3, 4, 5, 6, 7 };
static u16 mnDataDel_803EF8C8[] = {
    0xC0,
    0xC1,
    0xC2,
    0xC3,
    0xC4,
    0xC6,
};
static Vec3 lbl_803EF8D4 = { -5.5, -2.8, 23 };
static StaticModelDesc mnDataDel_804A0918;
static StaticModelDesc mnDataDel_804A0928;
static StaticModelDesc mnDataDel_804A0938;

#endif

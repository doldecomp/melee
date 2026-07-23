#ifndef MELEE_GR_INLINES_H
#define MELEE_GR_INLINES_H

#include "gr/granime.h"
#include "gr/grcorneria.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/types.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"
#include "MSL/math.h"

#include <baselib/forward.h>

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

#define GET_GROUND(gobj) ((Ground*) HSD_GObjGetUserData(gobj))

static inline void Ground_JObjInline1(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

/// @todo Call sites have a lot of duplicate code
static inline void Ground_SetupStageCallbacks(Ground_GObj* gobj,
                                              StageCallbacks* callbacks)
{
    Ground* gp = GET_GROUND(gobj);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
    if (callbacks->callback3 != NULL) {
        gp->x1C_callback = callbacks->callback3;
    }
    if (callbacks->callback0 != NULL) {
        callbacks->callback0(gobj);
    }
    if (callbacks->callback2 != NULL) {
        HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
    }
}

static inline void Ground_InitTargetStage(HSD_GObj* (*create_gobj)(int) )
{
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    create_gobj(0);
    create_gobj(1);
    create_gobj(2);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C4210();
    Ground_801C42AC();
}

static inline void Ground_ClearStarFoxArwingGObjs(Ground* gp)
{
    gp->u.starfox.article_gobjs[3] = NULL;
    gp->u.starfox.article_gobjs[2] = NULL;
    gp->u.starfox.article_gobjs[1] = NULL;
    gp->u.starfox.article_gobjs[0] = NULL;
}

static inline void Ground_AnimateStarFoxArwing(Ground_GObj* gobj)
{
    grAnime_801C7FF8(gobj, 0, 7, 1, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 2, 7, 3, 0.0F, 1.0F);
}

static inline void Ground_AnimateStarFoxArwingWithBackground(Ground_GObj* gobj)
{
    grAnime_801C7FF8(gobj, 7, 7, 0, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 8, 7, 0, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 2, 7, 3, 0.0F, 1.0F);
}

static inline void Ground_LinkStarFoxArwing(Ground* gp, HSD_GObj* linked_gobj)
{
    gp->u.starfox.linked_gobj = linked_gobj;
    if (linked_gobj != NULL) {
        Ground* linked_gp = GET_GROUND(gp->u.starfox.linked_gobj);
        if (linked_gp != NULL) {
            linked_gp->u.starfox.arwing_slot = gp->u.starfox.arwing_slot;
        }
    }
}

static inline void Ground_DisableStarFoxArwingGObjs(Ground* gp)
{
    gp->u.starfox.article_gobjs[0] = (HSD_GObj*) -1;
    gp->u.starfox.article_gobjs[1] = (HSD_GObj*) -1;
}

static inline void Ground_ResetStarFoxArwingState(Ground* gp)
{
    gp->u.starfox.xC4.flags.b0 = false;
    gp->u.starfox.xD4 = 0;
    gp->u.starfox.xF0 = 0;
    gp->u.starfox.xF4 = 0;
}

static inline void Ground_AttachStarFoxArwingModel(Ground_GObj* gobj,
                                                   Ground* gp,
                                                   Ground_GObj* arwing_gobj,
                                                   int joint_id)
{
    lb_8000C2F8(Ground_801C3FA4(gobj, 0),
                Ground_801C3FA4(arwing_gobj, joint_id));
    gp->u.starfox.linked_gobj = NULL;
}

static inline void Ground_UpdateStarFoxArwingVisibility(Ground* gp,
                                                        HSD_JObj* jobj,
                                                        f32 depth_limit)
{
    f32 angle = ABS(gp->u.arwing.xE0.z);
    if (angle < depth_limit) {
        gp->u.arwing.xE0.z = 0.0F;
        while (gp->u.arwing.xDC < -M_PI) {
            gp->u.arwing.xDC += M_TAU;
        }
        while (gp->u.arwing.xDC > M_PI) {
            gp->u.arwing.xDC -= M_TAU;
        }
        if (ABS(gp->u.arwing.xDC) < 1.0471976F) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
    HSD_JObjSetTranslate(jobj, &gp->u.arwing.xE0);
}

static inline void
Ground_UpdateStarFoxSequence(Ground_GObj* gobj, Ground* gp,
                             int sequence_gobj_id,
                             Ground_GObj* (*create_gobj)(int) )
{
    ifStatus_802F6898();
    un_802FF570();

    if (Ground_801C2BA4(sequence_gobj_id) == NULL) {
        if (grCorneria_801E2598(gp->u.starfox.xC4.word,
                                gp->u.starfox.arwing_slot))
        {
            if ((s32) gp->u.starfox.xCC-- < 0) {
                Ground_GObj* sequence_gobj = create_gobj(sequence_gobj_id);
                grCorneria_801E2738(
                    sequence_gobj, &GET_GROUND(sequence_gobj)->u,
                    gp->u.starfox.xC4.word, gp->u.starfox.arwing_slot);
                gp->u.starfox.arwing_slot++;
                gp->u.starfox.xCC = 0;
            }
        } else if ((s32) gp->u.starfox.xCC-- < 0) {
            Ground_801C4A08(gobj);
        }
    }
}

static inline void Ground_ClampSymmetric(f32 value, f32 limit, f32* out)
{
    if (value > limit) {
        *out = limit;
    } else {
        limit = -limit;
        if (value < limit) {
            *out = limit;
        }
    }
}

static inline void Ground_WrapAngle(f32* angle)
{
    if (*angle > M_TAU) {
        *angle -= M_TAU;
    } else if (*angle < -M_TAU) {
        *angle += M_TAU;
    }
}

#define ZRANDI(n) ((n) != 0 ? HSD_Randi(n) : 0)

static inline int rand_range(int a, int b)
{
    if (a > b) {
        return b + ZRANDI(a - b);
    } else if (a < b) {
        return a + ZRANDI(b - a);
    } else {
        return a;
    }
}

#endif

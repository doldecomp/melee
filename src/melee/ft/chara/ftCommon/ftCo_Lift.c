#include <platform.h>

#include "it/forward.h"

#include "ftCo_Lift.h"

#include "ftCo_DamageFall.h"
#include "ftCo_ItemThrow.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "it/it_26B1.h"
#include "it/item.h"

#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>

void ftCo_80096D9C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.lift.x0 = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_LiftWait, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->take_dmg_cb = ftCo_800974C4;
}

void ftCo_LiftWait_Anim(ftCo_GObj* gobj) {}

void ftCo_LiftWait_IASA(ftCo_GObj* arg0)
{
    RETURN_IF(ftCo_80094EA4(arg0));
    RETURN_IF(ftCo_800970E0(arg0));
    RETURN_IF(ftCo_80096EF8(arg0));
    ;
}

void ftCo_LiftWait_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_80096E68(ftCo_GObj* gobj)
{
    u8 _[4] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        Vec3 vec;
        u8 _[4] = { 0 };
        vec.x = vec.y = vec.z = 0.0f;
        Item_8026ABD8(fp->item_gobj, &vec, 0.0f);
        ftCo_80090780(gobj);
    } else {
        ftCo_800CC730(gobj);
    }
}

void ftCo_LiftWait_Coll(ftCo_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_80096E68);
}

bool ftCo_80096EF8(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.lstick.x * fp->facing_dir >= p_ftCommonData->x228) {
        ftCo_80096F48(gobj);
        return true;
    }
    return false;
}

void ftCo_80096F48(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    FtMotionId msid;
    if (!fp->mv.co.lift.x0) {
        msid = ftCo_MS_LiftWalk1;
    } else {
        msid = ftCo_MS_LiftWalk2;
    }
    fp->mv.co.lift.x0 ^= true;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    fp->take_dmg_cb = ftCo_800974C4;
}

void ftCo_LiftWalk_Anim(HSD_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (!ftAnim_IsFramesRemaining(gobj) && !ftCo_80096EF8(gobj)) {
        ftCo_Fighter* fp = gobj->user_data;
        Fighter_ChangeMotionState(gobj, ftCo_MS_LiftWait, Ft_MF_Unk24, 0, 1, 0,
                                  NULL);
        fp->take_dmg_cb = ftCo_800974C4;
    }
}

void ftCo_LiftWalk_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_80094EA4(gobj));
}

void ftCo_LiftWalk_Phys(ftCo_GObj* gobj)
{
    ft_80085088(gobj);
}

void ftCo_LiftWalk_Coll(ftCo_GObj* gobj)
{
    ft_8008403C(gobj, ftCo_80096E68);
}

bool ftCo_800970E0(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.lstick.x * fp->facing_dir <= p_ftCommonData->x22C) {
        ftCo_80097130(gobj);
        return true;
    }
    return false;
}

void ftCo_80097130(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.lift.x4 = p_ftCommonData->x230;
    fp->mv.co.lift.x8 = false;
    Fighter_ChangeMotionState(gobj, ftCo_MS_LiftTurn, Ft_MF_Unk24, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->take_dmg_cb = ftCo_800974C4;
    ftCo_LiftTurn_Anim(gobj);
}

void ftCo_LiftTurn_Anim(HSD_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_Part part = ftParts_8007500C(fp, FtPart_TransN);
    HSD_JObj* jobj = fp->parts[part].x4_jobj2;
    fp->mv.co.lift.x4 -= 1;
    if (!fp->x2222_b6) {
        float angle = 180 / p_ftCommonData->x230 * deg_to_rad +
                      ftParts_80075F48(fp, part);
        ftParts_80075AF0(fp, part, angle);
        HSD_JObjSetRotationY(jobj, angle);
    }
    if (!fp->mv.co.lift.x8) {
        if (fp->mv.co.lift.x4 <= 0.5f * p_ftCommonData->x230) {
            float f = ftParts_80075F48(fp, part);
            fp->facing_dir = -fp->facing_dir;
            ftParts_80075AF0(fp, FtPart_TopN, M_PI_2 * fp->facing_dir);
            {
                ftParts_80075AF0(fp, part, -f);
                HSD_JObjSetRotationY(jobj, -f);
            }
            fp->gr_vel = -fp->gr_vel;
            fp->mv.co.lift.x8 = true;
        }
    }
    if (fp->mv.co.lift.x4 <= 0) {
        ftCo_Fighter* fp = gobj->user_data;
        Fighter_ChangeMotionState(gobj, 174, Ft_MF_Unk24, 0, 1, 0, NULL);
        fp->take_dmg_cb = ftCo_800974C4;
    }
}

void ftCo_LiftTurn_IASA(HSD_GObj* arg0)
{
    RETURN_IF(ftCo_80094EA4(arg0));
}

void ftCo_LiftTurn_Phys(HSD_GObj* arg0)
{
    ft_80084F3C(arg0);
}

void ftCo_LiftTurn_Coll(HSD_GObj* arg0)
{
    ft_8008403C(arg0, ftCo_80096E68);
}

void ftCo_800974C4(HSD_GObj* gobj)
{
    u8 _[4] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        Vec3 vec;
        u8 _[4] = { 0 };
        vec.x = vec.y = vec.z = 0;
        Item_8026ABD8(fp->item_gobj, &vec, 0);
    }
}

void ftCo_8009750C(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Item_GObj* item_gobj = fp->item_gobj;
    if (item_gobj && it_8026B2B4(item_gobj) == 1) {
        Vec3 vec;
        u8 _[4] = { 0 };
        vec.x = vec.y = vec.z = 0;
        Item_8026ABD8(item_gobj, &vec, 0);
    }
}

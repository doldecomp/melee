#include "ft/ft_081B.h"

#include "inlines.h"
#include "stdbool.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0819.h"
#include "ft/ft_0892.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftwalljump.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/ftCo_MissFoot.h"
#include "ftCommon/ftCo_Ottotto.h"
#include "ftCommon/ftCo_StopCeil.h"
#include "ftCommon/ftCo_StopWall.h"
#include "lb/types.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <MSL/math.h>

void ft_80081B38(Fighter_GObj* gobj)
{
    u8* sp8;
    Fighter* fp;
    CollData* coll;
    FighterBone* bones;
    ftData_x44_t* temp_r29;
    f32 temp_f0;
    f32 temp_f3;
    u8 _[8];

    fp = GET_FIGHTER(gobj);
    fp->ecb_lock = 0;
    coll = &fp->coll_data;
    fp->coll_data.cur_pos = fp->cur_pos;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    mpColl_80041EE4(coll);
    coll->x34_flags.b1234 = 1;
    bones = fp->parts;
    temp_r29 = fp->ft_data->x44;
    mpColl_SetECBSource_JObj(
        coll, gobj, bones->joint, bones[temp_r29->unk0].joint,
        bones[temp_r29->unk2].joint, bones[temp_r29->unk4].joint,
        bones[temp_r29->unk6].joint, bones[temp_r29->unk8].joint,
        bones[temp_r29->unkA].joint, temp_r29->unkC * fp->x34_scale.y);
    temp_f3 = fp->x34_scale.y;
    mpColl_SetLedgeSnap(coll, temp_r29->ledge_snap_x * temp_f3,
                        temp_r29->ledge_snap_y * temp_f3,
                        temp_r29->ledge_snap_height * temp_f3);
    coll->x50 = fp->co_attrs.weight;
    temp_f0 = 10.0F * fp->x34_scale.y;
    if (coll->ecb_source.kind == ECBSource_JObj) {
        coll->ecb_source.x128 = temp_f0;
        coll->ecb_source.x12C = temp_f0;
    }
}

void ft_80081C88(Fighter_GObj* dst_gobj, f32 scl_y)
{
    float temp_f0;

    Fighter* fp = GET_FIGHTER(dst_gobj);
    ftData_x44_t* temp_r3 = fp->ft_data->x44;
    {
        CollData* temp_r5 = &fp->coll_data;

        float tmp = temp_r3->unkC * scl_y;
        ;
        if (fp->coll_data.ecb_source.kind == ECBSource_JObj) {
            temp_r5->ecb_source.x124 = tmp;
        }

        {
            float ledge_snap_height = temp_r3->ledge_snap_height * scl_y;
            float ledge_snap_y = temp_r3->ledge_snap_y * scl_y;
            float ledge_snap_x = temp_r3->ledge_snap_x * scl_y;

            if (temp_r5->ecb_source.kind == ECBSource_JObj) {
                temp_r5->ledge_snap_x = ledge_snap_x;
                temp_r5->ledge_snap_y = ledge_snap_y;
                temp_r5->ledge_snap_height = ledge_snap_height;
            }
        }
        temp_r5->x50 = fp->co_attrs.weight;
        temp_f0 = 10.0F * fp->x34_scale.y;
        if (temp_r5->ecb_source.kind == ECBSource_JObj) {
            temp_r5->ecb_source.x128 = temp_f0;
            temp_r5->ecb_source.x12C = temp_f0;
        }
    }
}

GroundOrAir ft_80081D0C(Fighter_GObj* gobj)
{
    bool temp_r31;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    temp_r31 = mpColl_800471F8(coll);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return GA_Ground;
    }
    if (temp_r31) {
        return GA_Air;
    } else {
        return GA_Ground;
    }
}

bool ft_80081DD4(Fighter_GObj* gobj)
{
    Fighter* fp;
    CollData* coll;
    ftData_x44_t* temp_r28;
    int var_r28;

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x221A_b2) {
        var_r28 = mpColl_800477E0(coll);
    } else if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_800471F8(coll);
    } else {
        float tmp;
        temp_r28 = fp->ft_data->x44;

        tmp = temp_r28->ledge_snap_height * fp->x34_scale.y *
              p_ftCommonData->x1CC;
        if (coll->ecb_source.kind == ECBSource_JObj) {
            coll->ledge_snap_height = tmp;
        }

        var_r28 = mpColl_800473CC(coll);

        tmp = temp_r28->ledge_snap_height * fp->x34_scale.y;
        if (coll->ecb_source.kind == ECBSource_JObj) {
            coll->ledge_snap_height = tmp;
        }
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj) != 0) {
        return false;
    }

    if (var_r28) {
        return true;
    } else {
        return false;
    }
}

bool ft_80081F2C(Fighter_GObj* gobj)
{
    Fighter* fp;
    CollData* coll;
    ftData_x44_t* temp_r28;
    bool var_r28;

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x221A_b2) {
        var_r28 = mpColl_80048274(coll);
    } else if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_80048160(coll);
    } else {
        float tmp;
        temp_r28 = fp->ft_data->x44;

        tmp = temp_r28->ledge_snap_height * fp->x34_scale.y *
              p_ftCommonData->x1CC;
        if (coll->ecb_source.kind == ECBSource_JObj) {
            coll->ledge_snap_height = tmp;
        }

        var_r28 = mpColl_80048464(coll);

        tmp = temp_r28->ledge_snap_height * fp->x34_scale.y;
        if (coll->ecb_source.kind == ECBSource_JObj) {
            coll->ledge_snap_height = tmp;
        }
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (var_r28) {
        return true;
    } else {
        return false;
    }
}

bool ft_80082084(Fighter_GObj* gobj)
{
    Fighter* fp;
    CollData* coll;
    ftData_x44_t* temp_r28;
    bool var_r28;

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x221A_b2) {
        var_r28 = mpColl_80048388(coll);
    } else if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_80048768(coll);
    } else {
        float tmp;
        temp_r28 = fp->ft_data->x44;

        tmp = temp_r28->ledge_snap_height * fp->x34_scale.y *
              p_ftCommonData->x1CC;
        if (coll->ecb_source.kind == ECBSource_JObj) {
            coll->ledge_snap_height = tmp;
        }

        var_r28 = mpColl_80048578(coll);

        tmp = temp_r28->ledge_snap_height * fp->x34_scale.y;
        if (coll->ecb_source.kind == ECBSource_JObj) {
            coll->ledge_snap_height = tmp;
        }
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (var_r28) {
        return true;
    } else {
        return false;
    }
}

bool ft_800821DC(Fighter_GObj* gobj)
{
    bool temp_r31;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    temp_r31 = mpColl_80048160(coll);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (temp_r31) {
        return true;
    } else {
        return false;
    }
}

bool ft_CheckGroundAndLedge(Fighter_GObj* gobj, int dir)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    bool var_r28;

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_800471F8(coll);
    } else {
        mpCollSetFacingDir(coll, dir);
        var_r28 = mpColl_800473CC(coll);
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }

    return var_r28 ? true : false;
}

bool ft_8008239C(Fighter_GObj* gobj, int dir,
                 ftCollisionBox* height_attributes)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCollisionBox* collbox;
    CollData* coll = &fp->coll_data;
    bool var_r28;
    ftCollisionBox box;

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    collbox = ft_80082838(&box, height_attributes, fp->facing_dir);
    if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_8004730C(coll, collbox);
    } else {
        mpCollSetFacingDir(coll, dir);
        var_r28 = mpColl_800475F4(coll, collbox);
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (var_r28) {
        return true;
    } else {
        return false;
    }
}

bool ft_800824A0(Fighter_GObj* gobj, ftCollisionBox* ecb)
{
    bool temp_r31;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    ftCollisionBox collbox;
    ftCollisionBox* box;

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    box = ft_80082838(&collbox, ecb, fp->facing_dir);
    temp_r31 = mpColl_8004730C(coll, box);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (temp_r31) {
        return true;
    }
    return false;
}

bool ft_80082578(Fighter_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    CollData* coll = &fp->coll_data;
    u8 _[4];

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    mpColl_800477E0(coll);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(arg0)) {
        return false;
    }
    if (coll->env_flags & Collide_FloorMask) {
        return true;
    } else {
        return false;
    }
}

bool ft_80082638(Fighter_GObj* gobj, ftCollisionBox* arg1)
{
    Fighter* fp;
    CollData* coll;
    ftCollisionBox sp18;
    ftCollisionBox* box;
    u8 _[4];

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    box = ft_80082838(&sp18, arg1, fp->facing_dir);
    mpColl_80047A08(coll, box);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj) != 0) {
        return false;
    }
    if (coll->env_flags & Collide_FloorMask) {
        return true;
    } else {
        return false;
    }
}

/// EnvironmentCollision_AllowGroundToAir(SpecialAttackGround)
GroundOrAir ft_80082708(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CollData* cd = &fp->coll_data;
    cd->last_pos = cd->cur_pos;
    cd->cur_pos = fp->cur_pos;
    {
        bool fall_off_ledge = mpColl_8004B108(cd);
        fp->cur_pos = cd->cur_pos;
        return fall_off_ledge ? GA_Air : GA_Ground;
    }
}

bool ft_800827A0(Fighter_GObj* gobj)
{
    Fighter* fp;
    CollData* coll;
    bool tmp;

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    tmp = mpColl_8004B2DC(coll);
    fp->cur_pos = coll->cur_pos;

    if (tmp) {
        return true;
    } else {
        return false;
    }
}

ftCollisionBox* ft_80082838(ftCollisionBox* arg0, ftCollisionBox* arg1,
                            f32 arg2)
{
    if (arg2 < 0.0f) {
        arg0->top = arg1->top;
        arg0->bottom = arg1->bottom;
        arg0->left.y = arg1->left.y;
        arg0->right.y = arg1->right.y;
        arg0->right.x = -arg1->left.x;
        arg0->left.x = -arg1->right.x;
        return arg0;
    }
    return (ftCollisionBox*) arg1;
}

bool ft_80082888(Fighter_GObj* arg0, ftCollisionBox* arg1)
{
    Fighter* fp;
    CollData* coll;
    bool tmp;
    ftCollisionBox sp18;
    ftCollisionBox* box;

    fp = GET_FIGHTER(arg0);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;

    box = ft_80082838(&sp18, arg1, fp->facing_dir);
    tmp = mpColl_8004B21C(coll, box);
    fp->cur_pos = coll->cur_pos;

    if (tmp) {
        return true;
    } else {
        return false;
    }
}

bool ft_80082978(HSD_GObj* gobj, ftCollisionBox* arg1)
{
    Fighter* fp;
    CollData* coll;
    ftCollisionBox sp18;
    ftCollisionBox* box;
    bool tmp;

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    box = ft_80082838(&sp18, arg1, fp->facing_dir);
    tmp = mpColl_8004B3F0(coll, box);
    fp->cur_pos = coll->cur_pos;

    if (tmp) {
        return true;
    } else {
        return false;
    }
}

bool ft_80082A68(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    fp->coll_data.cur_pos = fp->cur_pos;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.last_pos.y += 10.0f;
    fp->coll_data.cur_pos.y -= 10.0f;
    if (mpColl_800471F8(coll)) {
        fp->cur_pos = coll->cur_pos;
        return true;
    } else {
        return false;
    }
}

void ft_80082B1C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->self_vel.y > ftCo_800D0EC8(fp)) {
        ft_8008A2BC(gobj);
    } else {
        ftCo_Landing_Enter_Basic(gobj);
    }
}

void ftCo_AirCatchHit_Coll(Fighter_GObj* gobj)
{
    CollData* coll;
    Fighter* fp;
    Fighter* fp2;
    bool temp_r31;
    bool var_r0;
    u8 _[8];

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    temp_r31 = mpColl_800471F8(coll);
    fp->cur_pos = coll->cur_pos;

    if (ft_80081A00(gobj)) {
        var_r0 = false;
    } else if (temp_r31) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }

    if (var_r0) {
        fp2 = GET_FIGHTER(gobj);
        if (fp2->self_vel.y > ftCo_800D0EC8(fp2)) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_Landing_Enter_Basic(gobj);
        }
    }
}

// void ft_80082C74(Fighter_GObj* gobj, void (*arg1)(Fighter_GObj*))
void ft_80082C74(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    bool var_r0 = ft_80081D0C(gobj);
    PAD_STACK(8);
    if (var_r0) {
        cb(gobj);
    }
}

void ft_80082D40(Fighter_GObj* gobj, f32 arg1)
{
    bool temp_r31;
    CollData* coll;
    Fighter* fp;
    Fighter* fp2;
    bool var_r0;
    u8 _[4];

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    temp_r31 = mpColl_80048768(coll);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj) != 0) {
        var_r0 = false;
    } else if (temp_r31 != 0) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        fp2 = GET_FIGHTER(gobj);
        if (fp2->self_vel.y > ftCo_800D0EC8(fp2)) {
            ft_8008A2BC(gobj);
        } else {
            ftCo_Landing_Enter_Basic(gobj);
        }
    }
}

Fighter_GObj* ft_80082E3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* cur;
    u8 _[8];

    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        if (cur != gobj) {
            Fighter* cur_fp = GET_FIGHTER(cur);
            if (cur_fp->x221D_b7) {
                if (cur_fp->facing_dir > 0.0F &&
                    (fp->coll_data.env_flags & Collide_LeftLedgeGrab))
                {
                    int r4 = fp->coll_data.ledge_id_left;
                    int floor_id = cur_fp->mv.co.common.x0;
                    if (mpLinesConnected(floor_id, r4)) {
                        return cur;
                    }
                }
                if (cur_fp->facing_dir < 0.0f &&
                    (fp->coll_data.env_flags & Collide_RightLedgeGrab))
                {
                    int r4 = fp->coll_data.ledge_id_right;
                    int floor_id = cur_fp->mv.co.common.x0;
                    if (mpLinesConnected(floor_id, r4)) {
                        return cur;
                    }
                }
            }
        }
    }
    return NULL;
}

void ft_80082F28(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt2(gobj))) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->self_vel.y > ftCo_800D0EC8(fp)) {
            ft_8008A2BC(gobj);
            return;
        }
        ftCo_Landing_Enter_Basic(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

static inline bool ft_80083090_inline(Fighter_GObj* gobj,
                                      bool (*arg1)(Fighter_GObj*, int),
                                      HSD_GObjEvent cb)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    bool temp;
    int dir;

    if (fp->facing_dir < 0.0F) {
        dir = -1;
    } else {
        dir = 1;
    }
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x2064_ledgeCooldown || fp->x2224_b2) {
        temp = mpColl_80047AC8(coll, arg1, gobj);
    } else {
        mpCollSetFacingDir(coll, dir);
        temp = mpColl_80047E14(coll, arg1, gobj);
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (temp) {
        return true;
    }
    return false;
}

void ft_80083090(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj*, int),
                 HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80083090_inline(gobj, arg1, cb)) {
        cb(gobj);
        return;
    }
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

void ft_800831CC(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj*, int),
                 HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80083090_inline(gobj, arg1, cb)) {
        cb(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

static inline bool ft_80083318_inline(Fighter_GObj* gobj,
                                      bool (*arg1)(Fighter_GObj*, int),
                                      HSD_GObjEvent cb)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    bool temp;
    int dir;

    if (fp->facing_dir < 0.0F) {
        dir = -1;
    } else {
        dir = 1;
    }
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x2064_ledgeCooldown || fp->x2224_b2) {
        temp = mpColl_80047BF4(coll, arg1, gobj);
    } else {
        mpCollSetFacingDir(coll, dir);
        temp = mpColl_80047F40(coll, arg1, gobj);
    }
    fp->cur_pos = coll->cur_pos;

    if (ft_80081A00(gobj)) {
        return false;
    }
    if (temp) {
        return true;
    }
    return false;
}

void ft_80083318(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj*, int),
                 HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80083318_inline(gobj, arg1, cb)) {
        cb((HSD_GObj*) gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

static inline bool ft_80083464_inline(Fighter_GObj* gobj,
                                      bool (*arg1)(Fighter_GObj*, int),
                                      HSD_GObjEvent cb)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 var_r0;
    s32 temp;
    int dir;

    if (fp->facing_dir < 0.0F) {
        dir = -1;
    } else {
        dir = 1;
    }
    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x2064_ledgeCooldown || fp->x2224_b2) {
        temp = mpColl_80047D20(coll, arg1, gobj);
    } else {
        mpCollSetFacingDir(coll, dir);
        temp = mpColl_8004806C(coll, arg1, gobj);
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (temp) {
        return true;
    }
    return false;
}

void ft_80083464(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj*, int),
                 HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80083464_inline(gobj, arg1, cb)) {
        cb(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

void ft_800835B0(Fighter_GObj* gobj, bool (*arg1)(Fighter_GObj*, int),
                 HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80083090_inline(gobj, arg1, cb)) {
        cb(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
    RETURN_IF(ftCo_8009EF68(gobj));
}

static inline bool ft_8008370C_inline(Fighter_GObj* gobj)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    bool temp;
    int dir;

    if (fp->facing_dir < 0.0F) {
        dir = -1;
    } else {
        dir = 1;
    }

    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x2064_ledgeCooldown || fp->x2224_b2) {
        temp = mpColl_800471F8(coll);
    } else {
        mpCollSetFacingDir(coll, dir);
        temp = mpColl_800473CC(coll);
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (temp) {
        return true;
    }
    return false;
}

void ft_8008370C(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_8008370C_inline(gobj)) {
        cb(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

static inline bool ft_80083844_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    bool temp_r31;

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    temp_r31 = mpColl_80048654(coll);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }

    if (temp_r31) {
        return true;
    }
    return false;
}

void ft_80083844(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(8);
    if (ft_80083844_inline(gobj)) {
        cb(gobj);
    }
}

static inline bool ft_80083910_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll;
    bool temp;
    int dir;
    if (fp->facing_dir < 0.0F) {
        dir = -1;
    } else {
        dir = 1;
    }

    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        temp = mpColl_80048654(coll);
    } else {
        mpCollSetFacingDir(coll, dir);
        temp = mpColl_800474E0(coll);
    }
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }

    if (temp) {
        return true;
    }

    return false;
}

void ft_80083910(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80083910_inline(gobj)) {
        cb(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

void ft_80083A48(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(8);
    if (ft_CheckGroundAndLedge(gobj, 0)) {
        cb(gobj);
        return;
    }

    RETURN_IF(ftWallJump_8008169C(gobj));
    RETURN_IF(ftCliffCommon_80081298(gobj));
}

void ft_80083B68(Fighter_GObj* gobj)
{
    PAD_STACK(16);
    ft_80082578(gobj);
}

void ft_80083C00(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (ft_80082578(gobj)) {
        cb(gobj);
    }
}

static inline bool ft_80083CE4_inline(Fighter_GObj* gobj,
                                      bool (*cb1)(Fighter_GObj*, int),
                                      HSD_GObjEvent cb2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;

    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    mpColl_800476B4(coll, cb1, gobj);
    fp->cur_pos = coll->cur_pos;
    if (ft_80081A00(gobj)) {
        return false;
    }

    if (coll->env_flags & Collide_FloorMask) {
        return true;
    } else {
        return false;
    }
}

void ft_80083CE4(Fighter_GObj* gobj, bool (*cb1)(Fighter_GObj*, int),
                 HSD_GObjEvent cb2)
{
    PAD_STACK(16);

    if (ft_80083CE4_inline(gobj, cb1, cb2)) {
        cb2(gobj);
    }
}

void ft_80083DCC(Fighter_GObj* gobj)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);

    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    mpColl_800478F4(coll);
    fp->cur_pos = coll->cur_pos;
    ft_80081A00(gobj);
}

void ft_80083E64(Fighter_GObj* gobj, ftCollisionBox* ecb, HSD_GObjEvent cb)
{
    bool do_cb = ft_800824A0(gobj, ecb);
    PAD_STACK(8);

    if (do_cb) {
        cb(gobj);
    }
}

void ft_80083F88(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    }
}

void ft_8008403C(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(16);
    if (!ft_80082708(gobj)) {
        cb(gobj);
    }
}

void ft_80084104(Fighter_GObj* gobj)
{
    bool skip = ft_800827A0(gobj);

    if (!skip) {
        ftCo_Fall_Enter(gobj);
    }
}

void ft_800841B8(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    bool skip = ft_800827A0(gobj);
    PAD_STACK(8);

    if (!skip) {
        cb(gobj);
    }
}

static inline bool ft_80084280_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    bool temp;
    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    coll->lstick_x = fp->input.lstick.x;
    mpCollSetFacingDir(coll, ftGetFacingDirInt(fp));
    temp = mpColl_8004B4B0(coll);
    fp->cur_pos = coll->cur_pos;

    if (temp) {
        return true;
    } else {
        return false;
    }
}

void ft_80084280(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool var_r0;
    PAD_STACK(16);

    if (fp->xF8_playerNudgeVel.x &&
        ((fp->xF8_playerNudgeVel.x * fp->facing_dir) < 0.0F))
    {
        var_r0 = ft_800827A0(gobj);
    } else {
        var_r0 = ft_80084280_inline(gobj);
    }

    RETURN_IF(var_r0);
    RETURN_IF(ftCo_8009A3C8(gobj));

    ftCo_Fall_Enter(gobj);
}

static inline bool ft_800843FC_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll;
    bool temp;

    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    fp->coll_data.lstick_x = fp->input.lstick.x;
    mpCollSetFacingDir(coll, ftGetFacingDirInt(fp));
    temp = mpColl_8004B5C4(coll);
    fp->cur_pos = coll->cur_pos;
    if (temp) {
        return true;
    } else {
        return false;
    }
}

void ft_800843FC(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    RETURN_IF(ft_800843FC_inline(gobj));
    RETURN_IF(ftCo_8009A3C8(gobj));
    ftCo_Fall_Enter(gobj);
}

void ft_800844EC(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_80082708(gobj)) {
        RETURN_IF(ftCo_8009EDA4(gobj));
    } else {
        ftCo_Fall_Enter(gobj);
    }
}

void ft_800845B4(Fighter_GObj* gobj)
{
    PAD_STACK(16);
    if (!ft_80082708(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (((fp->facing_dir < 0.0F) &&
             (fp->coll_data.env_flags & Collide_RightLedgeSlip)) ||
            ((fp->facing_dir > 0.0F) &&
             (fp->coll_data.env_flags & Collide_LeftLedgeSlip)))
        {
            ftCo_8009F39C(gobj);
            return;
        }
        ftCo_Fall_Enter(gobj);
    }
}

void ft_800846B0(Fighter_GObj* gobj, ftCollisionBox* box, HSD_GObjEvent cb)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCollisionBox temp_box;
    bool temp;
    bool ret;
    PAD_STACK(8);

    coll = &fp->coll_data;
    coll->last_pos = coll->cur_pos;
    coll->cur_pos = fp->cur_pos;
    temp = mpColl_8004B21C(coll, ft_80082838(&temp_box, box, fp->facing_dir));
    fp->cur_pos = coll->cur_pos;
    if (temp) {
        ret = true;
    } else {
        ret = false;
    }

    if (!ret) {
        cb(gobj);
    }
}

void ft_800847D0(Fighter_GObj* gobj, ftCollisionBox* box)
{
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCollisionBox temp_box;
    float dir;
    bool temp;
    bool ret;
    PAD_STACK(8);

    coll = &fp->coll_data;
    fp->coll_data.last_pos = fp->coll_data.cur_pos;
    fp->coll_data.cur_pos = fp->cur_pos;
    dir = fp->facing_dir;
    temp = mpColl_8004B3F0(coll, ft_80082838(&temp_box, box, dir));
    fp->cur_pos = coll->cur_pos;
    if (temp) {
        ret = true;
    } else {
        ret = false;
    }
    if (!ret) {
        ftCo_Fall_Enter(gobj);
    }
}

void ft_800848DC(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    PAD_STACK(8);
    if (!ft_80082708(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if ((fp->facing_dir < 0.0F &&
             fp->coll_data.env_flags & Collide_RightLedgeSlip) ||
            (fp->facing_dir > 0.0F &&
             fp->coll_data.env_flags & Collide_LeftLedgeSlip))
        {
            ftCo_8009F39C(gobj);
            return;
        }
        cb(gobj);
    }
}

void ft_800849EC(Fighter* fp1, Fighter* fp2)
{
    mpCopyCollData(&fp1->coll_data, &fp2->coll_data, 2);
}

int ft_80084A18(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return mpLib_80054ED8(fp->coll_data.floor.index);
}

float ft_GetGroundFrictionMultiplier(Fighter* fp)
{
    if (fp->kind == FTKIND_POPO || fp->kind == FTKIND_NANA) {
        return 1.0F;
    }
    return mpColl_8004CA6C(&fp->coll_data);
}

bool ft_80084A80(int arg0, Fighter_GObj* gobj, int* arg1, int* arg2, int* arg3)
{
    int sp24;
    Fighter* fp = GET_FIGHTER(gobj);
    int temp_r0;
    int var_r31;
    u32 temp_r26;
    int* var_r25;
    PAD_STACK(4);

    if (fp->ground_or_air == GA_Ground) {
        temp_r0 = fp->coll_data.floor.index;
        if (temp_r0 != -1) {
            temp_r26 = mpLineGetFlags(temp_r0);
            switch (arg0) {
            case 0:
                var_r25 = mpLib_80056A1C(temp_r26, arg2);
                break;
            case 1:
                var_r25 = mpLib_80056A8C(temp_r26, arg2);
                break;
            case 2:
                var_r25 = mpLib_80056AFC(temp_r26, arg2);
                break;
            }
            if (var_r25[0] != -1) {
                arg1[0] = var_r25[0];
                if (arg0 == 2) {
                    arg1[1] = var_r25[1];
                    arg1[2] = var_r25[2];
                    arg1[3] = var_r25[3];
                }
            } else {
                arg1[0] = -1;
                arg2[0] = 1;
            }
            switch (arg0) {
            case 0:
                var_r31 = mpLib_80056A54(temp_r26, &sp24);
                break;
            case 1: /* switch 1 */
                var_r31 = mpLib_80056AC4(temp_r26, &sp24);
                break;
            case 2: /* switch 1 */
                var_r31 = mpLib_80056B34(temp_r26, &sp24);
                break;
            }
            if (var_r31 != -1) {
                arg3[0] = var_r31;
            } else {
                arg3[0] = -1;
            }
            return true;
        }
    }
    return false;
}

bool ft_80084BFC(Fighter_GObj* gobj, int* arg1, int* arg2, int* arg3)
{
    return ft_80084A80(0, gobj, arg1, arg2, arg3);
}

bool ft_80084C38(Fighter_GObj* gobj, int* arg1, int* arg2, int* arg3)
{
    return ft_80084A80(1, gobj, arg1, arg2, arg3);
}

bool ft_80084C74(Fighter_GObj* gobj, int* arg1, int* arg2, int* arg3)
{
    return ft_80084A80(2, gobj, arg1, arg2, arg3);
}

void ft_80084CB0(Fighter* fp, ftCollisionBox* box)
{
    box->top = fp->coll_data.ecb.top.y;
    box->bottom = fp->coll_data.ecb.bottom.y;
    box->right.x = fp->coll_data.ecb.right.x;
    box->right.y = fp->coll_data.ecb.right.y;
    box->left.x = fp->coll_data.ecb.left.x;
    box->left.y = fp->coll_data.ecb.left.y;
}

bool ft_80084CE4(Fighter* attacker, Fighter* victim)
{
    float attacker_x;
    float attacker_y;
    float victim_x;
    float victim_y;

    attacker_y =
        (attacker->coll_data.ecb.top.y + attacker->coll_data.ecb.bottom.y) *
        0.5F;
    attacker_y += attacker->cur_pos.y;

    attacker_x = 0.0F;
    attacker_x += attacker->cur_pos.x;

    victim_y =
        (victim->coll_data.ecb.top.y + victim->coll_data.ecb.bottom.y) * 0.5F;
    victim_y += victim->cur_pos.y;

    victim_x = 0.0F;
    victim_x += victim->cur_pos.x;

    if (attacker_x > victim_x) {
        if (mpCheckRightWall(attacker_x, attacker_y, victim_x, victim_y, NULL,
                             NULL, NULL, NULL, -1, -1))
        {
            return true;
        }
    } else if (mpCheckLeftWall(attacker_x, attacker_y, victim_x, victim_y,
                               NULL, NULL, NULL, NULL, -1, -1))
    {
        return true;
    }

    return false;
}

void ft_80084DB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);

    ftCommon_CheckFallFast(fp);
    if (fp->fall_fast) {
        ftCommon_FallFast(fp);
    } else {
        ftCommon_Fall(fp, co_attrs->grav, co_attrs->terminal_vel);
    }
    ftCommon_8007D268(fp);
}

void ft_80084E1C(Fighter_GObj* gobj, float threshold, float drift_max,
                 float target_max)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);
    float drift;
    float target_vel;

    ftCommon_CheckFallFast(fp);
    if (fp->fall_fast) {
        ftCommon_FallFast(fp);
    } else {
        ftCommon_Fall(fp, co_attrs->grav, co_attrs->terminal_vel);
    }

    if (ABS(fp->input.lstick.x) >= threshold) {
        drift = fp->input.lstick.x * drift_max;
        target_vel = fp->input.lstick.x * target_max;
    } else {
        target_vel = 0.0F;
        drift = 0.0F;
    }
    ftCommon_8007D140(fp, drift, target_vel, co_attrs->aerial_friction);
}

void ft_80084EEC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);

    ftCommon_Fall(fp, co_attrs->grav, co_attrs->terminal_vel);
    ftCommon_ApplyFrictionAir(fp, co_attrs->aerial_friction);
}

void ft_80084F3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    f32 friction = co->gr_friction;
    PAD_STACK(8);
    if (ABS(fp->gr_vel) > co->walk_max_vel) {
        friction *= p_ftCommonData->x6C;
    }
    ftCommon_ApplyFrictionGround(fp, friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ft_80084FA8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    f32 var_f2 = fp->gr_vel;
    f32 var_f1 = co->gr_friction;
    if (var_f2 < 0.0F) {
        var_f2 = -var_f2;
    }
    if (var_f2 > co->walk_max_vel) {
        var_f1 *= p_ftCommonData->x6C;
    }
    ft_80085030(gobj, var_f1, fp->facing_dir);
}

void ft_80085004(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;

    ft_80085030(gobj, co_attrs->gr_friction, fp->facing_dir1);
}

void ft_80085030(Fighter_GObj* gobj, float gr_friction, float facing_dir)
{
    Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->xE4_ground_accel_1 =
            fp->x6A4_transNOffset.z * facing_dir - fp->gr_vel;
    } else {
        ftCommon_ApplyFrictionGround(fp, gr_friction);
    }
    ftCommon_ApplyGroundMovement(gobj);
}

void ft_80085088(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;

    ft_800850E0(gobj, co_attrs->gr_friction, fp->facing_dir);
}

void ft_800850B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float dir = fp->facing_dir1;
    ft_800850E0(gobj, fp->co_attrs.gr_friction, dir);
}

void ft_800850E0(Fighter_GObj* gobj, float arg8, float arg9)
{
    Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->gr_vel = fp->x6A4_transNOffset.z * arg9;
    } else {
        ftCommon_ApplyFrictionGround(fp, arg8);
    }
    ftCommon_ApplyGroundMovement(gobj);
}

void ft_80085134(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir;
    fp->self_vel.y = fp->x6A4_transNOffset.y;
}

void ft_80085154(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 lstick_x = cosf(fp->lstick_angle);
    f32 lstick_y = sinf(fp->lstick_angle);
    f32 temp_f0 = fp->x6A4_transNOffset.y;
    f32 temp_f3 = fp->x6A4_transNOffset.z * fp->facing_dir;
    fp->self_vel.x = (temp_f3 * lstick_x) - (temp_f0 * lstick_y);
    fp->self_vel.y = (temp_f3 * lstick_y) + (temp_f0 * lstick_x);
}

void ft_800851C0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.y = fp->x6A4_transNOffset.y;
}

void ft_800851D0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x197C != NULL) {
        fp->self_vel.y =
            fp->x6A4_transNOffset.y * ((f32*) Fighter_804D6520)[5];
    } else {
        fp->self_vel.y = fp->x6A4_transNOffset.y;
    }
}

void ft_80085204(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = fp->x6A4_transNOffset.z * fp->facing_dir;
}

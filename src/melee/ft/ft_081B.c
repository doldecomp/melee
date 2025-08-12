#include "ft/ft_081B.h"

#include "inlines.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_0819.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
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
    fp->coll_data.cur_topn = fp->cur_pos;
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    mpColl_80041EE4(coll);
    coll->x34_flags.b1234 = 1;
    bones = fp->parts;
    temp_r29 = fp->ft_data->x44;
    mpColl_80042078(coll, gobj, bones->joint, bones[temp_r29->unk0].joint,
                    bones[temp_r29->unk2].joint, bones[temp_r29->unk4].joint,
                    bones[temp_r29->unk6].joint, bones[temp_r29->unk8].joint,
                    bones[temp_r29->unkA].joint,
                    temp_r29->unkC * fp->x34_scale.y);
    temp_f3 = fp->x34_scale.y;
    mpColl_80042374(coll, temp_r29->unk10 * temp_f3, temp_r29->unk14 * temp_f3,
                    temp_r29->unk18 * temp_f3);
    coll->x50 = fp->co_attrs.weight;
    temp_f0 = 10.0f * fp->x34_scale.y;
    if (coll->x104 == 1) {
        coll->x128 = temp_f0;
        coll->x12C = temp_f0;
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
        if (fp->coll_data.x104 == 1) {
            temp_r5->x124 = tmp;
        }

        {
            float c = temp_r3->unk18 * scl_y;
            float b = temp_r3->unk14 * scl_y;
            float a = temp_r3->unk10 * scl_y;

            if (temp_r5->x104 == 1) {
                temp_r5->x54 = a;
                temp_r5->x58 = b;
                temp_r5->x5C = c;
            }
        }
        temp_r5->x50 = fp->co_attrs.weight;
        temp_f0 = 10.0f * fp->x34_scale.y;
        if (temp_r5->x104 == 1) {
            temp_r5->x128 = temp_f0;
            temp_r5->x12C = temp_f0;
        }
    }
}

GroundOrAir ft_80081D0C(Fighter_GObj* gobj)
{
    bool temp_r31;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;

    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    temp_r31 = mpColl_800471F8(coll);
    fp->cur_pos = coll->cur_topn;
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    if (fp->x221A_b2) {
        var_r28 = mpColl_800477E0(coll);
    } else if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_800471F8(coll);
    } else {
        float tmp;
        temp_r28 = fp->ft_data->x44;

        tmp = temp_r28->unk18 * fp->x34_scale.y * p_ftCommonData->x1CC;
        if (coll->x104 == 1) {
            coll->x5C = tmp;
        }

        var_r28 = mpColl_800473CC(coll);

        tmp = temp_r28->unk18 * fp->x34_scale.y;
        if (coll->x104 == 1) {
            coll->x5C = tmp;
        }
    }
    fp->cur_pos = coll->cur_topn;
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    if (fp->x221A_b2) {
        var_r28 = mpColl_80048274(coll);
    } else if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_80048160(coll);
    } else {
        float tmp;
        temp_r28 = fp->ft_data->x44;

        tmp = temp_r28->unk18 * fp->x34_scale.y * p_ftCommonData->x1CC;
        if (coll->x104 == 1) {
            coll->x5C = tmp;
        }

        var_r28 = mpColl_80048464(coll);

        tmp = temp_r28->unk18 * fp->x34_scale.y;
        if (coll->x104 == 1) {
            coll->x5C = tmp;
        }
    }
    fp->cur_pos = coll->cur_topn;
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    if (fp->x221A_b2) {
        var_r28 = mpColl_80048388(coll);
    } else if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_80048768(coll);
    } else {
        float tmp;
        temp_r28 = fp->ft_data->x44;

        tmp = temp_r28->unk18 * fp->x34_scale.y * p_ftCommonData->x1CC;
        if (coll->x104 == 1) {
            coll->x5C = tmp;
        }

        var_r28 = mpColl_80048578(coll);

        tmp = temp_r28->unk18 * fp->x34_scale.y;
        if (coll->x104 == 1) {
            coll->x5C = tmp;
        }
    }
    fp->cur_pos = coll->cur_topn;
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    temp_r31 = mpColl_80048160(coll);
    fp->cur_pos = coll->cur_topn;
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
    Fighter* fp;
    CollData* coll;
    ftData_x44_t* temp_r28;
    bool var_r28;

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_800471F8(coll);
    } else {
        mpColl_800436D8(coll, dir);
        var_r28 = mpColl_800473CC(coll);
    }
    fp->cur_pos = coll->cur_topn;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (var_r28) {
        return true;
    } else {
        return false;
    }
}

bool ft_8008239C(Fighter_GObj* gobj, int dir,
                 ftCollisionBox* height_attributes)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCollisionBox* collbox;
    CollData* coll = &fp->coll_data;
    bool var_r28;
    ftCollisionBox box;

    coll->prev_topn = coll->cur_topn;
    coll->cur_topn = fp->cur_pos;
    collbox = ft_80082838(&box, height_attributes, fp->facing_dir);
    if (fp->x2064_ledgeCooldown != 0 || fp->x2224_b2) {
        var_r28 = mpColl_8004730C(coll, collbox);
    } else {
        mpColl_800436D8(coll, dir);
        var_r28 = mpColl_800475F4(coll, collbox);
    }
    fp->cur_pos = coll->cur_topn;
    if (ft_80081A00(gobj)) {
        return false;
    }
    if (var_r28) {
        return true;
    } else {
        return false;
    }
}

bool ft_800824A0(Fighter_GObj* arg0, ftCollisionBox* arg1)
{
    bool temp_r31;
    Fighter* fp;
    CollData* coll;
    ftCollisionBox collbox;

    fp = GET_FIGHTER(arg0);
    coll = &fp->coll_data;
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    temp_r31 =
        mpColl_8004730C(coll, ft_80082838(&collbox, arg1, fp->facing_dir));
    fp->cur_pos = coll->cur_topn;
    if (ft_80081A00(arg0)) {
        return false;
    }
    if (temp_r31) {
        return true;
    } else {
        return false;
    }
}

bool ft_80082578(Fighter_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    CollData* coll = &fp->coll_data;
    u8 _[4];

    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    mpColl_800477E0(coll);
    fp->cur_pos = coll->cur_topn;
    if (ft_80081A00(arg0)) {
        return false;
    }
    if (coll->env_flags & 0x18000) {
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    box = ft_80082838(&sp18, arg1, fp->facing_dir);
    mpColl_80047A08(coll, box);
    fp->cur_pos = coll->cur_topn;
    if (ft_80081A00(gobj) != 0) {
        return false;
    }
    if (coll->env_flags & 0x18000) {
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    {
        bool fall_off_ledge = mpColl_8004B108(cd);
        fp->cur_pos = cd->cur_topn;
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    tmp = mpColl_8004B2DC(coll);
    fp->cur_pos = coll->cur_topn;

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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;

    box = ft_80082838(&sp18, arg1, fp->facing_dir);
    tmp = mpColl_8004B21C(coll, box);
    fp->cur_pos = coll->cur_topn;

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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    box = ft_80082838(&sp18, arg1, fp->facing_dir);
    tmp = mpColl_8004B3F0(coll, box);
    fp->cur_pos = coll->cur_topn;

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
    fp->coll_data.cur_topn = fp->cur_pos;
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.prev_topn.y += 10.0f;
    fp->coll_data.cur_topn.y -= 10.0f;
    if (mpColl_800471F8(coll)) {
        fp->cur_pos = coll->cur_topn;
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
        ftCo_800D5BF8(gobj);
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
    fp->coll_data.prev_topn = fp->coll_data.cur_topn;
    fp->coll_data.cur_topn = fp->cur_pos;
    temp_r31 = mpColl_800471F8(coll);
    fp->cur_pos = coll->cur_topn;

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
            ftCo_800D5BF8(gobj);
        }
    }
}

// void ft_80082C74(Fighter_GObj* gobj, void (*arg1)(Fighter_GObj*))
void ft_80082C74(void* gobj, void (*arg1)(Fighter_GObj*))
{
    CollData* coll;
    Fighter* fp;
    bool temp_r31;
    bool var_r0;
    u8 _[8];

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;

    coll->prev_topn = coll->cur_topn;
    coll->cur_topn = fp->cur_pos;

    temp_r31 = mpColl_800471F8(coll);
    fp->cur_pos = coll->cur_topn;

    if (ft_80081A00(gobj)) {
        var_r0 = false;
    } else if (temp_r31) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        arg1(gobj);
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
    coll->prev_topn = coll->cur_topn;
    coll->cur_topn = fp->cur_pos;
    temp_r31 = mpColl_80048768(coll);
    fp->cur_pos = coll->cur_topn;
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
            ftCo_800D5BF8(gobj);
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
                if (cur_fp->facing_dir > 0.0f &&
                    (fp->coll_data.env_flags & 0x1000000))
                {
                    int r4 = fp->coll_data.ledge_id_unk1;
                    int floor_id = cur_fp->mv.co.common.x0;
                    if (mpLib_80054F68(floor_id, r4)) {
                        return cur;
                    }
                }
                if (cur_fp->facing_dir < 0.0f &&
                    (fp->coll_data.env_flags & 0x2000000))
                {
                    int r4 = fp->coll_data.ledge_id_unk0;
                    int floor_id = cur_fp->mv.co.common.x0;
                    if (mpLib_80054F68(floor_id, r4)) {
                        return cur;
                    }
                }
            }
        }
    }
    return NULL;
}

// #ft_80082F28

/// #ft_80083090

/// #ft_800831CC

/// #ft_80083318

/// #ft_80083464

/// #ft_800835B0

/// #ft_8008370C

/// #ft_80083844

/// #ft_80083910

/// #ft_80083A48

void ft_80083B68(Fighter_GObj* gobj)
{
    u32 unused[4];
    CollData* coll;
    Fighter* fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    coll->prev_topn = coll->cur_topn;
    coll->cur_topn = fp->cur_pos;
    mpColl_800477E0(coll);
    fp->cur_pos = coll->cur_topn;
    ft_80081A00(gobj);
}

/// #ft_80083C00

/// #ft_80083CE4

/// #ft_80083DCC

/// #ft_80083E64

void ft_80083F88(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_Fall_Enter(gobj);
    }
}

/// #ft_8008403C

/// #ft_80084104

/// #ft_800841B8

/// #ft_80084280

/// #ft_800843FC

/// #ft_800844EC

/// #ft_800845B4

/// #ft_800846B0

/// #ft_800847D0

/// #ft_800848DC

void ft_800849EC(Fighter* fp1, Fighter* fp2)
{
    mpColl_8004CC00(&fp1->coll_data, &fp2->coll_data, 2);
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

/// #ft_80084A80

/// #ft_80084BFC

/// #ft_80084C38

/// #ft_80084C74

/// #ft_80084CB0

/// #ft_80084CE4

/// #ft_80084DB0

/// #ft_80084E1C

/// #ft_80084EEC

void ft_80084F3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    f32 var_f1 = co->gr_friction;
    PAD_STACK(8);
    if (ABS(fp->gr_vel) > co->walk_max_vel) {
        var_f1 *= p_ftCommonData->x6C;
    }
    ftCommon_8007C930(fp, var_f1);
    ftCommon_8007CB74(gobj);
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

/// #ft_80085004

void ft_80085030(HSD_GObj* gobj, float gr_friction, float facing_dir)
{
    Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->xE4_ground_accel_1 =
            fp->x6A4_transNOffset.z * facing_dir - fp->gr_vel;
    } else {
        ftCommon_8007C930(fp, gr_friction);
    }
    ftCommon_8007CB74(gobj);
}

/// #ft_800850E0;

/// #ft_80085088

void ft_800850B4(Fighter_GObj* gobj, UNK_T unused)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float dir = fp->facing_dir1;
    ft_800850E0(gobj, unused, fp->co_attrs.gr_friction, dir);
}

void ft_800850E0(Fighter_GObj* gobj, UNK_T unused, float arg8, float arg9)
{
    Fighter* fp = gobj->user_data;
    if (fp->x594_b0) {
        fp->gr_vel = fp->x6A4_transNOffset.z * arg9;
    } else {
        ftCommon_8007C930(fp, arg8);
    }
    ftCommon_8007CB74(gobj);
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

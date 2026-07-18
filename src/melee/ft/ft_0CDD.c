#include "ft_0CDD.h"

#include <melee/ft/chara/ftCommon/ftCo_Attack100.h>
#include <melee/ft/chara/ftCommon/ftpickupitem.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftcommon.h>
#include <melee/it/it_26B1.h>

void ftCo_800CE0CC(HSD_GObj*); /* extern */
void ftCo_800CE14C(HSD_GObj*); /* extern */
void ftCo_800CE650(HSD_GObj*); /* extern */
void it_8028E938(Item_GObj*);  /* extern */

/// grounded
void ftCo_Attack_800CDD14(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    if (ftpickupitem_80094790(fighter_gobj) == false) {
        switch (itGetKind(fighter->item_gobj)) {
        case It_Kind_L_Gun:
            ftCo_800CDF5C(fighter_gobj);
            return;
        case It_Kind_F_Flower:
            ftCo_800CE3E0(fighter_gobj);
            return;
        case It_Kind_S_Scope:
            ft_800D76B8(fighter_gobj);
            break;
        }
    }
}

/// in air
void ftCo_800CDDA0(Fighter_GObj* fighter_gobj)
{
    Fighter* fighter = GET_FIGHTER(fighter_gobj);

    switch (itGetKind(fighter->item_gobj)) {
    case It_Kind_L_Gun:
        ftCo_800CE010(fighter_gobj);
        return;
    case It_Kind_F_Flower:
        ftCo_800CE480(fighter_gobj);
        return;
    case It_Kind_S_Scope:
        ft_800D7770(fighter_gobj);
        return;
    }
}

#pragma push
#pragma dont_inline on
void ftCo_800CDE18(Fighter_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == false) {
        ftCommon_8007D92C(fighter_gobj);
    }
}

void ftCo_800CDE54(Fighter_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftCo_800CDE74(Fighter_GObj* fighter_gobj)
{
    ft_80084DB0(fighter_gobj);
}
#pragma pop

void ftCo_800CDE94(Fighter* fighter, Vec3* arg1, Vec3* arg2)
{
    Vec3 pos;
    HSD_JObj* fighterbone_jobj;
    f32 scale;
    f32 inverse_scale;

    fighterbone_jobj = fighter->parts[fighter->ft_data->x8->x10].joint;
    pos = *arg1;

    scale = fighter->x34_scale.y;
    if (scale != 1.0f) {
        inverse_scale = 1.0f / scale;
        pos.x *= inverse_scale;
        pos.y *= inverse_scale;
        pos.z *= inverse_scale;
    }
    MTXMultVec(HSD_JObjGetMtxPtr(fighterbone_jobj), &pos, arg2);
}

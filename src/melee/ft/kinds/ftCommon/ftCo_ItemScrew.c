#include "ftCo_ItemScrew.h"

#include "ftCo_Fall.h"
#include "ftCo_FallAerial.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_Jump.h"
#include "ftCo_JumpAerial.h"

#include "forward.h"
#include <melee/ft/forward.h>

#include <stdbool.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCo_ItemScrew_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_ItemScrew, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftCo_800CB110(gobj, false, p_ftCommonData->x800);
    fp->x2227_b0 = true;
}

void ftCo_ItemScrew_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_ItemScrew_IASA(Fighter_GObj* gobj)
{
    ftCo_Jump_IASA(gobj);
}

void ftCo_ItemScrew_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftCo_ItemScrew_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

void ft_800D2E7C(Fighter_GObj* gobj, Vec3* arg1)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    arg1->x *= p_ftCommonData->x800;
    arg1->y *= p_ftCommonData->x800;
    *(volatile f32*) &arg1->z;
    ftCommon_8007D5D4(fp);
    ftCo_800CBAC4(gobj, ftCo_MS_ItemScrewAir, arg1, 1);
}

void ftCo_ItemScrewAir_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_FallAerial_Enter(gobj);
    }
}

void ftCo_ItemScrewAir_IASA(Fighter_GObj* gobj)
{
    ftCo_JumpAerial_IASA(gobj);
}

void ftCo_ItemScrewAir_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_ItemScrewAir_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

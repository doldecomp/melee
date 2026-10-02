/**
 * @file ftpeachfloatfall.c
 * @brief Float Fall
 * @details Float Fall logic for Peach.
 * Module prefix: ftPe
 */
#include "ftpeachfloatfall.h"

#include <Runtime/platform.h>

#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallAerial.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_JumpAerial.h>
#include <melee/ft/types.h>

/**
 * @brief Float Fall - getFloatDir
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
static ftPeach_MotionState getFloatDir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick[0].x * fp->facing_dir > -p_ftCommonData->x78
               ? ftPe_MS_FloatFallF
               : ftPe_MS_FloatFallB;
}

/**
 * @brief Float Fall - ftPe_UpdateFloatDir
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_UpdateFloatDir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    ftPeach_MotionState msid = getFloatDir(gobj);
    float anim_start = msid == ftPe_MS_FloatFallF ? da->floatfallf_anim_start
                                                  : da->floatfallb_anim_start;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_KeepGfx,
                              anim_start - da->floatfall_anim_start_offset,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Float Fall - ftPe_FloatFall_Anim
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_FloatFall_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_FallAerial_Enter(gobj);
    }
}

/**
 * @brief Float Fall - ftPe_FloatFall_IASA
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_FloatFall_IASA(HSD_GObj* gobj) {}

/**
 * @brief Float Fall - ftPe_FloatFall_Phys
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_FloatFall_Phys(HSD_GObj* gobj)
{
    ftCo_JumpAerial_Phys_Cb(gobj);
}

/**
 * @brief Float Fall - ftPe_FloatFall_Coll
 * @param gobj The fighter's game object
 * @todo Identify game mechanics and inline frame data
 */
void ftPe_FloatFall_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

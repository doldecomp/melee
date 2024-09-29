#include <platform.h>

#include <dolphin/mtx/forward.h>

#include "ftPe_FloatFall.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftPeach/types.h"

static ftPeach_MotionState getFloatDir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick.x * fp->facing_dir > -p_ftCommonData->x78
               ? ftPe_MS_FloatFallF
               : ftPe_MS_FloatFallB;
}

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

void ftPe_FloatFall_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CCDA8(gobj);
    }
}

void ftPe_FloatFall_IASA(HSD_GObj* gobj) {}

void ftPe_FloatFall_Phys(HSD_GObj* gobj)
{
    ftCo_800CC6C8(gobj);
}

void ftPe_FloatFall_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

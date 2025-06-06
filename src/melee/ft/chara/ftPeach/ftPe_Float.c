#include <platform.h>

#include "ft/forward.h"

#include "ftPe_Float.h"

#include "ftPe_FloatAttack.h"
#include "ftPe_FloatFall.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftPeach/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

bool ftPe_Float_CheckContinueInput(Fighter* fp)
{
    return fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax ||
           fp->input.held_inputs & HSD_PAD_XY;
}

static bool checkStartFloatInput(HSD_GObj* gobj)
{
    Fighter* temp_r6 = GET_FIGHTER(gobj);
    return temp_r6->input.lstick.y <= -p_ftCommonData->x88 &&
           temp_r6->input.held_inputs & HSD_PAD_XY;
}

bool ftPe_8011BA54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool float_input = checkStartFloatInput(gobj);
    if (fp->kind == FTKIND_PEACH && fp->fv.pe.has_float && float_input) {
        ftPe_8011BB6C(gobj, true);
        return true;
    }
    return false;
}

bool ftPe_8011BAD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_PEACH) {
        if (fp->self_vel.y <= 0 && fp->fv.pe.has_float) {
            if (ftPe_Float_CheckContinueInput(fp)) {
                ftPe_8011BB6C(gobj, true);
                return true;
            }
        }
    }
    return false;
}

static void spawnParticle(HSD_GObj* gobj, HSD_JObj* joint)
{
    Fighter* fp = GET_FIGHTER(gobj);
    efAsync_Spawn(gobj, &fp->x60C, 0, 1236, joint);
}

void ftPe_8011BB6C(HSD_GObj* gobj, bool arg1)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    HSD_JObj* joint;

    Fighter_ChangeMotionState(gobj, ftPe_MS_Float, 0, 0, 1, 0, NULL);
    fp->fv.pe.has_float = false;
    if (arg1) {
        fp->fv.pe.x4 = da->xC;
    }
    fp->self_vel.y = 0;
    fp->x2219_b0 = true;
    joint = fp->parts[ftParts_8007500C(fp, FtPart_TransN)].joint;
    spawnParticle(gobj, joint);
}

void ftPe_Float_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.x4 > 0) {
        fp->fv.pe.x4 -= 1;
    }
    if (fp->fv.pe.x4 <= 0) {
        ftPe_UpdateFloatDir(gobj);
    }
}

void ftPe_Float_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!ftCo_SpecialAir_CheckInput(gobj) && !ftPe_8011BE80(gobj)) {
        /// @todo Call #checkContinueFloatInput
        bool float_input =
            fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax ||
            fp->input.held_inputs & HSD_PAD_XY;
        if (!float_input) {
            ftPe_UpdateFloatDir(gobj);
        }
    }
}

void ftPe_Float_Phys(HSD_GObj* gobj)
{
    ftCommon_8007D268(GET_FIGHTER(gobj));
}

void ftPe_Float_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}

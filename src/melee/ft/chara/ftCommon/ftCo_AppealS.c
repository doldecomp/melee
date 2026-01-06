#include "ftCo_AppealS.h"

#include "platform.h"
#include "stdbool.h"

#include "db/db.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCLink/ftCl_Init.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftDrMario/ftDr_Init.h"
#include "ftKirby/ftKb_Init.h"
#include "ftPeach/ftPe_Init.h"
#include "ftZelda/ftZd_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/gobj.h>
#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

bool ftCo_800DE9B8(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->input.x668 & HSD_PAD_DPADUP) {
        return true;
    }
    return false;
}

bool ftCo_800DE9D8(Fighter_GObj* gobj)
{
    if (ftCo_800DE9B8(gobj)) {
        ftCo_800DEA28(gobj);
        return true;
    }
    return false;
}

void ftCo_800DEA28(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->kind) {
    case FTKIND_CLINK:
        ftCl_Init_80149318(gobj);
        break;
    case FTKIND_DRMARIO:
        ftDr_Init_80149910(gobj);
        break;
    case FTKIND_GANON: {
        Vec3 pos;
        lb_8000B1CC(fp->parts->joint, NULL, &pos);
        lb_800119DC(&pos, 80, 1.0f, 0.003f, 1.0471976f);
        ftCo_800DEBD0(gobj);
    }
    default:
        ftCo_800DEBD0(gobj);
        break;
    }
    pl_80040120(fp->player_id, fp->x221F_b4);
}

void ftCo_800DEAE8(Fighter_GObj* gobj, FtMotionId msid0, FtMotionId msid1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MotionState* ms = msid1 >= fp->x18
                          ? &fp->x20_actionStateList[msid1 - fp->x18]
                          : &fp->x1C_actionStateList[msid1];
    fp->allow_interrupt = false;
    if (fp->facing_dir == -1.0f &&
        ftData_80085FD4(fp, ms->anim_id)->x8 != NULL)
    {
        Fighter_ChangeMotionState(gobj, msid1, 0, 0.0f, 1.0f, 0.0f, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, msid0, 0, 0.0f, 1.0f, 0.0f, NULL);
    }
}

void ftCo_800DEBD0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (g_debugLevel >= 3) {
        if (fp->kind == FTKIND_PEACH) {
            ftPe_Init_8011B93C(gobj);
        }
        if (fp->kind == FTKIND_ZELDA) {
            ftZd_Init_801395C8(gobj);
        }
    }
    if (fp->kind == FTKIND_KIRBY) {
        ftKb_SpecialN_800F5D04(gobj, true);
    }
    ftCo_800DEAE8(gobj, ftCo_MS_AppealSR, ftCo_MS_AppealSL);
}

void ftCo_AppealS_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_AppealS_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    RETURN_IF(!fp->allow_interrupt);
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80099794(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
}

void ftCo_AppealS_Phys(Fighter_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_AppealS_Coll(Fighter_GObj* gobj)
{
    ft_80084104(gobj);
}

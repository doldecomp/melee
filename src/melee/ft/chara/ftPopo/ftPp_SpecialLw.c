#include "ft/chara/ftPopo/ftPp_SpecialS.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftPopo/ftPp_SpecialHi.h"
#include "ftPopo/ftPp_SpecialLw.h"
#include "ftPopo/ftPp_Init.h"
#include "it/items/itclimbersblizzard.h"
#include "lb/lb_00B0.h"
#include "pl/player.h"

#include <trigf.h>

void ftPp_SpecialHi_80122898(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(16);
    if (fp->fv.pp.x2230_b0) {
        efLib_DestroyAll(gobj);
        fp = gobj->user_data;
        fp->fv.pp.x2230_b0 = false;
        fp->death2_cb = NULL;
        fp->take_dmg_cb = NULL;
        ftPartSetRotX(gobj->user_data, 0, 0.0f);
    }
}

void ftPp_SpecialLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[3] = 0;
    fp->mv.pp.speciallw.x0 = 0;
    fp->mv.pp.speciallw.x4_b0 = false;
    Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialLw, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_80122D2C;
}

void ftPp_SpecialAirLw_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    PAD_STACK(8);
    fp->throw_flags = 0;
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[3] = 0;
    fp->mv.pp.speciallw.x0 = 0;
    fp->mv.pp.speciallw.x4_b0 = false;
    Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirLw, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_80122D2C;
}

void ftPp_SpecialLw_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        if (fp->fv.pp.x2230_b0) {
            efLib_DestroyAll(gobj);
            fp = gobj->user_data;
            fp->fv.pp.x2230_b0 = false;
            fp->death2_cb = NULL;
            fp->take_dmg_cb = NULL;
            ftPartSetRotX(gobj->user_data, 0, 0.0f);
        }
        ft_8008A2BC(gobj);
    }
}

void ftPp_SpecialAirLw_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(16);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = gobj->user_data;
        if (fp->fv.pp.x2230_b0) {
            efLib_DestroyAll(gobj);
            fp = gobj->user_data;
            fp->fv.pp.x2230_b0 = false;
            fp->death2_cb = NULL;
            fp->take_dmg_cb = NULL;
            ftPartSetRotX(gobj->user_data, 0, 0.0f);
        }
        ftCo_Fall_Enter(gobj);
    }
}

void ftPp_SpecialLw_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialAirLw_IASA(Fighter_GObj* gobj) {}

void ftPp_SpecialLw_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialAirLw_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

static inline void ftPp_set_cbs(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->death2_cb = ftPp_Init_8011F060;
    fp->take_dmg_cb = ftPp_Init_8011F060;
}

static inline void ftPp_SpecialLw_Coll_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[3]) {
        ftPartSetRotX(fp, 0,
                      fp->facing_dir * atan2f(fp->coll_data.floor.normal.x,
                                              fp->coll_data.floor.normal.y));
    } else {
        ftPartSetRotX(fp, 0, 0.0F);
    }
}

void fn_80122B54(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    Fighter* fp = gobj->user_data;
    Fighter* fp2;
    new_var = gobj;
    PAD_STACK(8);
    ftCommon_8007D7FC(fp);
    fp2 = fp;
    Fighter_ChangeMotionState(new_var, ftPp_MS_SpecialLw, 0x0C4C5282,
                              fp2->cur_anim_frame, 1.0F, 0.0F, 0L);
    ftPp_set_cbs(new_var);
    ftPp_SpecialLw_Coll_inline(gobj);
    fp->accessory4_cb = fn_80122D2C;
}

static inline void ftPp_SpecialLw_Coll_Land(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPp_MS_SpecialAirLw, 0x0C4C5282,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftPp_set_cbs(gobj);
    fp->accessory4_cb = fn_80122D2C;
    ftCommon_ClampAirDrift(fp);
}

void ftPp_SpecialLw_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftPartSetRotX(fp, 0, 0.0f);
        ftPp_SpecialLw_Coll_Land(gobj);
    } else {
        ftPp_SpecialLw_Coll_inline(gobj);
    }
}

void ftPp_SpecialAirLw_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_80122B54);
}

void fn_80122D2C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    PAD_STACK(8);
    if (fp->mv.pp.speciallw.x4_b0) {
        if (fp->mv.pp.speciallw.x0 == 0) {
            ftIceClimberAttributes* da = fp->dat_attrs;
            lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, NULL, &pos);
            pos.x += da->xBC * fp->facing_dir;
            pos.y += da->xC0;
            itClimbersBlizzard_Spawn(gobj, &pos, fp->facing_dir);
            fp->mv.pp.speciallw.x0 = da->xB8;
        }
        fp->mv.pp.speciallw.x0--;
    }
    switch (fp->cmd_vars[0]) {
    case 1:
        efSync_Spawn(0x4EC, gobj, fp->parts[FtPart_L4thNb].joint);
        fp->mv.pp.speciallw.x4_b0 = true;
        fp->fv.pp.x2230_b0 = true;
        ftPp_set_cbs(gobj);
        fp->cmd_vars[0] = 0;
        if (fp->kind == FTKIND_POPO) {
            ft_800881D8(fp, 0x1FC42, 0x7F, 0x40);
            ft_80088510(fp, 0x1FBEB, 0x7F, 0x40);
        } else {
            ft_800881D8(fp, 0x1FC0F, 0x7F, 0x40);
            ft_80088510(fp, 0x1FBEE, 0x7F, 0x40);
        }
        break;
    case 2:
        fp->mv.pp.speciallw.x4_b0 = false;
        fp->cmd_vars[0] = 0;
        break;
    }
}

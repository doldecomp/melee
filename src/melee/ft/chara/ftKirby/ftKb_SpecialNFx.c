#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_CaptureWaitKirby.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "ftLink/types.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/items/it_27CF.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2F28.h"
#include "it/items/itclimbersice.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirby_2F23.h"
#include "it/items/itkirbycutterbeam.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itkirbyyoshispecialn.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbow.h"
#include "it/items/itmewtwoshadowball.h"
#include "it/items/itnesspkflush.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itseakneedleheld.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "lb/lbvector.h"
#include "melee/lb/lbrefract.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/// #ftKb_SpecialNFx_800FDC70

void fn_800FDCE0(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK_8;

    ft_800892A0(gobj);
    ft_80089824(gobj);
}

bool ftKb_SpecialNFx_800FDD14(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = gobj->user_data;
        if (ft != NULL) {
            if (!ft->fv.kb.xB0) {
                return true;
            }
            return false;
        }
    }
    return true;
}

/// #ftKb_SpecialNFx_800FDD4C

/// #ftKb_SpecialNFx_800FDDF4

void ftKb_SpecialNFx_800FDEB4(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = gobj->user_data;
        if ((ft != NULL) && (ft->fv.kb.xB0 != 0)) {
            ft->fv.kb.xB0 = 0;
        }
    }
}

void ftKb_SpecialNFx_800FDEE0(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (gobj != NULL) {
        Fighter* fp = gobj->user_data;
        if (fp != NULL) {
            if (fp->fv.kb.xB0 != 0) {
                it_802AEAB4((Item_GObj*) fp->fv.kb.xB0);
                fp->fv.kb.xB0 = 0;
            }
        }
    }
}

/// #ftKb_SpecialNFx_800FDF30

void fn_800FE0E0(Fighter_GObj* gobj)
{
    ftKb_SpecialNFx_800FDF30(gobj);
}

/// #ftKb_SpecialNFx_800FE100

/// #ftKb_SpecialNFx_800FE240

/// #ftKb_FxSpecialNStart_Anim

/// #ftKb_FxSpecialNLoop_Anim

void ftKb_FxSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    volatile short pad2;
    Fighter* fp = GET_FIGHTER(gobj);

    it_802ADDD0((Item_GObj*) fp->fv.kb.xB0, fp->cmd_vars[1]);

    if (fp->cmd_vars[1] == 2) {
        ftpickupitem_80094818(gobj, 0);
    }

    if (fp->cmd_vars[3] == 2 && fp->fv.kb.xB0 != 0) {
        unsigned long long pad;
        fp->cmd_vars[3] = 0;
        it_802AE608((Item_GObj*) fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNFx_800FDEB4(gobj);
        ft_8008A2BC(gobj);
    }
}

/// #ftKb_FxSpecialAirNStart_Anim

/// #ftKb_FxSpecialAirNLoop_Anim

void ftKb_FxSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* new_var;
    ftKb_DatAttrs* da = fp->dat_attrs;
    volatile int pad;
    int new_var2;
    float landing_lag;

    it_802ADDD0((Item_GObj*) fp->fv.kb.xB0, fp->cmd_vars[1]);

    new_var = fp;
    if (new_var->cmd_vars[1] == 2) {
        ftpickupitem_80094818(gobj, 0);
    }

    if (fp->cmd_vars[3] == 2 && fp->fv.kb.xB0 != 0) {
        new_var2 = 0;
        fp->cmd_vars[3] = new_var2;
        it_802AE608((Item_GObj*) fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNFx_800FDEB4(gobj);
        switch (fp->fv.kb.hat.kind) {
        case FTKIND_FOX:
            do {
            } while (0);
            landing_lag = da->specialn_fx_freefall_toggle;
            break;
        case FTKIND_FALCO:
            landing_lag = da->specialn_fc_freefall_toggle;
            break;
        default:
            break;
        }
        if (landing_lag == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, landing_lag);
    }
}

void ftKb_FxSpecialNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

void ftKb_FxSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

void ftKb_FxSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_FxSpecialAirNStart_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

void ftKb_FxSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if ((ft->cmd_vars[0] != 0) && (ft->input.x668 & HSD_PAD_B)) {
        ft->mv.kb.specialhi.x0 = 1;
    }
}

void ftKb_FxSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_FxSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_FxSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_FxSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_FxSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_FxSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_FxSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_FxSpecialNStart_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

void ftKb_FxSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

void ftKb_FxSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    ft_80083F88(gobj);
}

void ftKb_FxSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

void ftKb_FxSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

void ftKb_FxSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    ftCo_AirCatchHit_Coll(gobj);
}

bool ftKb_SpecialNNs_800FEC78(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.ns_flash_gobj != NULL &&
            (fp->motion_id == ftKb_MS_NsSpecialNHold0 ||
             fp->motion_id == ftKb_MS_NsSpecialAirNHold0))
        {
            return true;
        }
    }
    return false;
}

void ftKb_SpecialNNs_800FECBC(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.ns_flash_gobj != NULL) {
            fp->fv.kb.ns_flash_gobj = NULL;
        }
    }
}

void ftKb_SpecialNNs_800FECE8(HSD_GObj* gobj)
{
    Fighter* fp;
    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->fv.kb.ns_flash_gobj != NULL) {
            it_802AAA50(fp->fv.kb.ns_flash_gobj);
            fp->fv.kb.ns_flash_gobj = NULL;
        }
    }
}

void ftKb_SpecialNNs_800FED38(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNStart, Ft_MF_None, 0, 1,
                              0, NULL);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    {
        /// @todo @c da can't move below @c fp
        ftKb_DatAttrs* da;
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4 * 4);
        da = fp->dat_attrs;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_ground =
            da->specialn_ns_frames_to_loop_charge_ground;
        fp->mv.kb.specialn_ns.frames_to_loop_charge_air =
            da->specialn_ns_frames_to_loop_charge_air;
        fp->mv.kb.specialn_ns.falling_acceleration_delay =
            da->specialn_ns_falling_acceleration_delay;
        fp->fv.kb.ns_flash_gobj = NULL;
        fp->mv.kb.specialn_ns.charge_release_delay =
            da->specialn_ns_charge_release_delay;
        ftAnim_8006EBA4(gobj);
    }
}

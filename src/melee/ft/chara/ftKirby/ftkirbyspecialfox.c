#include "ftKb_Init.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/debug.h"

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/chara/ftCommon/ftpickupitem.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "it/items/itfoxblaster.h"
#include "it/items/itnesspkflush.h"
#include "lb/lb_00B0.h"
#include "lb/lbrefract.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

void ftKb_SpecialNFx_800FDC70(Fighter_GObj* gobj, Vec3* vec)
{
    Vec3 pos1;
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            pos1.x = 0.0f;
            pos1.y = 1.45f;
            pos1.z = 0.016f;
            lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &pos1, vec);
            return;
        }
    }
    vec->x = vec->y = vec->z = 0.0f;
}

void ftKb_SpecialNFx_OnChangeAction(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK_8;

    ft_800892A0(gobj);
    ft_80089824(gobj);
}

bool ftKb_SpecialNFx_800FDD14(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = GET_FIGHTER(gobj);
        if (ft != NULL) {
            if (!ft->fv.kb.xB0) {
                return true;
            }
            return false;
        }
    }
    return true;
}

ftFx_SpecialNIndex ftKb_SpecialNFx_800FDD4C(Fighter_GObj* gobj)
{
    s32 msid = 9;

    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_FOX: {
                s32 motion_id = fp->motion_id;
                switch (motion_id) {
                case ftKb_MS_FxSpecialNStart:
                case ftKb_MS_FxSpecialNLoop:
                case ftKb_MS_FxSpecialNEnd:
                case ftKb_MS_FxSpecialAirNStart:
                case ftKb_MS_FxSpecialAirNLoop:
                case ftKb_MS_FxSpecialAirNEnd:
                    msid = motion_id - 0x1A7;
                    break;
                case ftCo_MS_ThrowB:
                case ftCo_MS_ThrowHi:
                case ftCo_MS_ThrowLw:
                    msid = motion_id - 0xD6;
                    break;
                }
                break;
            }
            case FTKIND_FALCO: {
                s32 motion_id = fp->motion_id;
                switch (motion_id) {
                case ftKb_MS_FcSpecialNStart:
                case ftKb_MS_FcSpecialNLoop:
                case ftKb_MS_FcSpecialNEnd:
                case ftKb_MS_FcSpecialAirNStart:
                case ftKb_MS_FcSpecialAirNLoop:
                case ftKb_MS_FcSpecialAirNEnd:
                    msid = motion_id - 0x208;
                    break;
                case ftCo_MS_ThrowB:
                case ftCo_MS_ThrowHi:
                case ftCo_MS_ThrowLw:
                    msid = motion_id - 0xD6;
                    break;
                }
                break;
            }
            }
        }
    }
    return msid;
}

bool ftKb_SpecialNFx_800FDDF4(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_FOX: {
                s32 motion_id = fp->motion_id;
                switch (motion_id) {
                case ftKb_MS_FxSpecialNStart:
                case ftKb_MS_FxSpecialNLoop:
                case ftKb_MS_FxSpecialNEnd:
                case ftKb_MS_FxSpecialAirNStart:
                case ftKb_MS_FxSpecialAirNLoop:
                case ftKb_MS_FxSpecialAirNEnd:
                case ftCo_MS_ThrowB:
                case ftCo_MS_ThrowHi:
                case ftCo_MS_ThrowLw:
                    if (fp->x2070.x2071_b6) {
                        return true;
                    }
                    return false;
                }
                break;
            }
            case FTKIND_FALCO: {
                s32 motion_id = fp->motion_id;
                switch (motion_id) {
                case ftKb_MS_FcSpecialNStart:
                case ftKb_MS_FcSpecialNLoop:
                case ftKb_MS_FcSpecialNEnd:
                case ftKb_MS_FcSpecialAirNStart:
                case ftKb_MS_FcSpecialAirNLoop:
                case ftKb_MS_FcSpecialAirNEnd:
                case ftCo_MS_ThrowB:
                case ftCo_MS_ThrowHi:
                case ftCo_MS_ThrowLw:
                    if (fp->x2070.x2071_b6) {
                        return true;
                    }
                    return false;
                }
                break;
            }
            }
        }
    }
    return true;
}

void ftKb_SpecialNFx_800FDEB4(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* ft = GET_FIGHTER(gobj);
        if ((ft != NULL) && (ft->fv.kb.xB0 != 0)) {
            ft->fv.kb.xB0 = 0;
        }
    }
}

void ftKb_SpecialNFx_800FDEE0(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            if (fp->fv.kb.xB0 != 0) {
                it_802AEAB4((Item_GObj*) fp->fv.kb.xB0);
                fp->fv.kb.xB0 = 0;
            }
        }
    }
}

inline void ftKb_SpecialNFx_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

/// #ftKb_SpecialNFx_800FDF30

void ftKb_SpecialNFx_CreateBlasterShot(Fighter_GObj* gobj)
{
    ftKb_SpecialNFx_800FDF30(gobj);
}

inline u32 ftKbGetBlasterId(Fighter* fp, ftKb_DatAttrs* da)
{
    u32 blaster_id;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FOX:
        blaster_id = da->specialn_fx_blaster_item_id;
        break;
    case FTKIND_FALCO:
        blaster_id = da->specialn_fc_blaster_item_id;
        break;
    }
    return blaster_id;
}

inline FtMotionId ftKbGetStartMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ftKb_MS_FxSpecialNStart;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FALCO:
        msid = ftKb_MS_FcSpecialNStart;
        break;
    case FTKIND_FOX:
        msid = ftKb_MS_FxSpecialNStart;
        break;
    }
    return msid;
}

void ftKb_SpecialNFx_800FE100(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    HSD_GObj* blasterGObj;

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftKbGetStartMotionId(gobj), 0.0f, 0.0f,
                              1.0f, 0.0f, NULL);

    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;

    ftAnim_8006EBA4(gobj);

    fp->gr_vel = 0.0f;
    fp->self_vel.z = 0.0f;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x = 0.0f;

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    blasterGObj = it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                              FtPart_R3rdNa, ftKbGetBlasterId(fp, da));
    fp->fv.kb.xB0 = blasterGObj;

    if (blasterGObj != NULL) {
        ftKb_SpecialNFx_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    HSD_ASSERT(429, 0);
}

inline FtMotionId ftKbGetAirStartMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ftKb_MS_FxSpecialAirNStart;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FALCO:
        msid = ftKb_MS_FcSpecialAirNStart;
        break;
    case FTKIND_FOX:
        msid = ftKb_MS_FxSpecialAirNStart;
        break;
    }
    return msid;
}

void ftKb_SpecialNFx_800FE240(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    HSD_GObj* blasterGObj;

    Fighter_ChangeMotionState(gobj, ftKbGetAirStartMotionId(gobj), 0.0f, 0.0f,
                              1.0f, 0.0f, NULL);

    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;

    ftAnim_8006EBA4(gobj);

    fp->mv.fx.SpecialN.isBlasterLoop = false;
    blasterGObj = it_802AE8A8(fp->facing_dir, gobj, &fp->cur_pos,
                              FtPart_R3rdNa, ftKbGetBlasterId(fp, da));
    fp->fv.kb.xB0 = blasterGObj;

    if (blasterGObj != NULL) {
        ftKb_SpecialNFx_SetCall(gobj);
        return;
    }

    OSReport("ftToSpecialNFox::Caution!!!\n");
    HSD_ASSERT(465, 0);
}

inline FtMotionId ftKbGetLoopMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ftKb_MS_FxSpecialNLoop;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FALCO:
        msid = ftKb_MS_FcSpecialNLoop;
        break;
    case FTKIND_FOX:
        msid = ftKb_MS_FxSpecialNLoop;
        break;
    }
    return msid;
}

void ftKb_FxSpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_802ADDD0(fp->fv.kb.xB0, 1);
    if (fp->cmd_vars[3] == 1 && fp->fv.kb.xB0 != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE538(fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKbGetLoopMotionId(gobj),
                                  (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1, 0,
                                  NULL);
        ftKb_SpecialNFx_SetCall(gobj);
        fp->accessory4_cb = ftKb_SpecialNFx_CreateBlasterShot;
        it_802ADDD0(fp->fv.kb.xB0, 1);
    }
}

inline FtMotionId ftKbGetEndMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ftKb_MS_FxSpecialNEnd;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FALCO:
        msid = ftKb_MS_FcSpecialNEnd;
        break;
    case FTKIND_FOX:
        msid = ftKb_MS_FxSpecialNEnd;
        break;
    }
    return msid;
}

void ftKb_FxSpecialNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* temp;

    it_802ADDD0(fp->fv.kb.xB0, 1);
    if (fp->cmd_vars[3] == 1 && fp->fv.kb.xB0 != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE538(fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.fx.SpecialN.isBlasterLoop == true) {
            fp->x21EC = ftKb_SpecialNFx_OnChangeAction;
            Fighter_ChangeMotionState(
                temp = gobj, ftKbGetLoopMotionId(gobj),
                (Ft_MF_SkipAttackCount | Ft_MF_SkipModel | Ft_MF_KeepGfx), 0,
                1, 0, NULL);
            fp->accessory4_cb = ftKb_SpecialNFx_CreateBlasterShot;
            fp->mv.fx.SpecialN.isBlasterLoop = false;
            it_802ADDD0(fp->fv.kb.xB0, 1);
        } else {
            HSD_GObj* temp;
            Fighter_ChangeMotionState(gobj, ftKbGetEndMotionId(gobj),
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1,
                                      0, NULL);
            temp = fp->fv.kb.xB0;
            fp->cmd_vars[1] = 1;
            it_802ADDD0(temp, 1);
        }
        ftKb_SpecialNFx_SetCall(gobj);
    }
    ftKb_SpecialNFx_800FDF30(gobj);
}

void ftKb_FxSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_802ADDD0(fp->fv.kb.xB0, fp->cmd_vars[1]);

    if (fp->cmd_vars[1] == 2) {
        ftpickupitem_80094818(gobj, 0);
    }

    if (fp->cmd_vars[3] == 2 && fp->fv.kb.xB0 != 0) {
        unsigned long long pad;
        fp->cmd_vars[3] = 0;
        it_802AE608(fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNFx_800FDEB4(gobj);
        ft_8008A2BC(gobj);
    }
}

inline FtMotionId ftKbGetAirLoopMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ftKb_MS_FxSpecialAirNLoop;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FALCO:
        msid = ftKb_MS_FcSpecialAirNLoop;
        break;
    case FTKIND_FOX:
        msid = ftKb_MS_FxSpecialAirNLoop;
        break;
    }
    return msid;
}

void ftKb_FxSpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_802ADDD0(fp->fv.kb.xB0, 1);
    if (fp->cmd_vars[3] == 1 && fp->fv.kb.xB0 != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE538(fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKbGetAirLoopMotionId(gobj),
                                  (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1, 0,
                                  NULL);
        ftKb_SpecialNFx_SetCall(gobj);
        fp->accessory4_cb = ftKb_SpecialNFx_CreateBlasterShot;
        it_802ADDD0(fp->fv.kb.xB0, 1);
    }
}

inline FtMotionId ftKbGetAirEndMotionId(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId msid = ftKb_MS_FxSpecialAirNEnd;
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_FALCO:
        msid = ftKb_MS_FcSpecialAirNEnd;
        break;
    case FTKIND_FOX:
        msid = ftKb_MS_FxSpecialAirNEnd;
        break;
    }
    return msid;
}

void ftKb_FxSpecialAirNLoop_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* temp;
    PAD_STACK(8);

    it_802ADDD0(fp->fv.kb.xB0, 1);
    if (fp->cmd_vars[3] == 1 && fp->fv.kb.xB0 != NULL) {
        fp->cmd_vars[3] = 0;
        it_802AE538(fp->fv.kb.xB0);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.fx.SpecialN.isBlasterLoop == true) {
            fp->x21EC = ftKb_SpecialNFx_OnChangeAction;
            Fighter_ChangeMotionState(
                temp = gobj, ftKbGetAirLoopMotionId(gobj),
                (Ft_MF_SkipAttackCount | Ft_MF_SkipModel | Ft_MF_KeepGfx), 0,
                1, 0, NULL);
            ftKb_SpecialNFx_SetCall(gobj);
            fp->accessory4_cb = ftKb_SpecialNFx_CreateBlasterShot;
            fp->mv.fx.SpecialN.isBlasterLoop = false;
            it_802ADDD0(fp->fv.kb.xB0, 1);
        } else {
            Fighter_ChangeMotionState(gobj, ftKbGetAirEndMotionId(gobj),
                                      (Ft_MF_SkipModel | Ft_MF_KeepGfx), 0, 1,
                                      0, NULL);
            ftKb_SpecialNFx_SetCall(gobj);
            temp = fp->fv.kb.xB0;
            fp->cmd_vars[1] = 1;
            it_802ADDD0(temp, 1);
        }
        ftKb_SpecialNFx_SetCall(gobj);
    }
    ftKb_SpecialNFx_800FDF30(gobj);
}

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
        fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.kb.ns_flash_gobj != NULL) {
            it_802AAA50(fp->fv.kb.ns_flash_gobj);
            fp->fv.kb.ns_flash_gobj = NULL;
        }
    }
}

extern const f32 ftKb_Init_804D9478;
extern const f32 ftKb_Init_804D9480;

void ftKb_SpecialNNs_800FED38(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_NsSpecialNStart, Ft_MF_None,
                              ftKb_Init_804D9478, ftKb_Init_804D9480,
                              ftKb_Init_804D9478, NULL);
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

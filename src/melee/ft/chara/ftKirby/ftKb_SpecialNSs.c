#include "ftKb_Init.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Escape.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Fall.h"
#include "it/items/itsamuschargeshot.h"
#include "lb/lb_00B0.h"

#include <MSL/math.h>

static inline void ftKb_SpecialN_set_cbs(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = ftKb_Init_800EE74C;
    fp->take_dmg_cb = ftKb_Init_800EE7B8;
}

long ftKb_SpecialNSs_800FCC14(Fighter_GObj* gobj, long* out1, long* out2)
{
    Fighter* fp;
    ftKb_DatAttrs* da;
    PAD_STACK(8);

    /// @todo float hack
    (void) S32_TO_F32;
    (void) 4.0F;
    (void) 0.0F;
    (void) 1.0F;
    (void) 0.0;
    (void) M_PI;
    (void) U32_TO_F32;
    (void) 5.0F;

    if (gobj == NULL) {
        goto return_error;
    }

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    if (fp->fv.kb.xA4 == NULL) {
        return -1;
    }

    *out1 = fp->fv.kb.xA8;
    *out2 = (long) da->specialn_ss_charge_time;

    return 0;

return_error:
    return -1;
}

bool ftKb_SpecialNSs_800FCC6C(Fighter_GObj* gobj)
{
    Fighter* fp;

    if (!gobj) {
        goto end_true;
    }

    fp = GET_FIGHTER(gobj);

    switch (fp->motion_id) {
    case 0x197:
    case 0x198:
    case 0x199:
    case 0x19A:
    case 0x19B:
    case 0x19C:
        if (fp->x2070.x2071_b6) {
            return true;
        }
        return false;
    default:
        return true;
    }

end_true:
    return true;
}

bool ftKb_SpecialNSs_800FCCBC(Fighter_GObj* gobj)
{
    Fighter* fp;
    s32 motion_id;

    if (!gobj) {
        goto end_true;
    }

    fp = GET_FIGHTER(gobj);
    motion_id = fp->motion_id;

    if (motion_id == 0x199) {
        goto ret_true;
    }

    if (motion_id >= 0x199) {
        goto check_upper;
    }

    if (motion_id >= 0x197) {
        goto ret_false;
    }
    goto ret_true;

check_upper:
    if (motion_id >= 0x19D) {
        goto ret_true;
    }

ret_false:
    return false;

ret_true:
    return true;

end_true:
    return true;
}

static inline void ftKb_SpecialNSs_it_802B5974(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xA4 != NULL) {
        it_802B5974(fp->fv.kb.xA4);
        fp->fv.kb.xA4 = NULL;
    }
}

static inline void ftKb_SpecialNSs_DestroyChargeShot(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        efLib_DestroyAll(gobj);
        fp->fv.kb.xAC = NULL;
    }
}

static inline void ftKb_ChargeShot_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (gobj != NULL) {
        ftKb_SpecialNSs_it_802B5974(gobj);
        ftKb_SpecialNSs_DestroyChargeShot(gobj);
    }
}

void ftKb_SpecialNSs_800FCD04(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.kb.xA4 != NULL) {
            fp->fv.kb.xA4 = NULL;
        }
        ftKb_SpecialNSs_DestroyChargeShot(gobj);
    }
}

void ftKb_SpecialNSs_800FCD60(Fighter_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKb_ChargeShot_inline(gobj);
        fp->fv.kb.xA8 = 0;
    }
}

static inline void ftKb_SpecialNSs_800FCDE0_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    fp->self_vel.x =
        fp->facing_dir * (da->specialn_ss_aerial_shot_recoil * fp->fv.kb.xA8);
}

static inline f64 facing_to_angle(Fighter* fp)
{
    if (fp->facing_dir == 1.0F) {
        return 0.0;
    } else {
        return M_PI;
    }
}

static inline void ftKb_SpecialNSs_UnsetChargeShot(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.xA4 != NULL) {
        fp->fv.kb.xA4 = NULL;
    }
}

void ftKb_SpecialNSs_800FCDE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Item_GObj* saved_item;
    PAD_STACK(20);
    if (fp->cmd_vars[1] == 1 && fp->fv.kb.xA4 != NULL) {
        Vec3 pos;
        Vec3 offset;
        PAD_STACK(16);
        fp->cmd_vars[1] = 2;
        offset.x = offset.y = offset.z = 0.0F;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &offset, &pos);
        pos.z = 0.0F;
        saved_item = fp->item_gobj;
        it_802B56E4(fp->fv.kb.xA4, &pos, facing_to_angle(fp),
                    (u32) fp->fv.kb.xA8, da->specialn_ss_charge_time);
        if (fp->motion_id == ftKb_MS_SsSpecialAirN ||
            fp->ground_or_air == GA_Air)
        {
            ftKb_SpecialNSs_800FCDE0_inline(gobj);
        }
        fp->fv.kb.xA8 = 0;

        if (gobj != NULL) {
            ftKb_SpecialNSs_UnsetChargeShot(gobj);
            ftKb_SpecialNSs_DestroyChargeShot(gobj);
        }
        efSync_Spawn(0x4A4, gobj, &pos, &fp->facing_dir);
        fp->item_gobj = saved_item;
    }
}

void ftKb_SpecialNSs_800FCF74(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007D7FC(fp);
    fp->self_vel.y = 0.0F;
    ftKb_SpecialN_set_cbs(gobj);
    fp->mv.kb.specialhi.x0 = 0;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.f = 0.0F;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNSs_800FD020(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirNStart, 0, 0.0F, 1.0F,
                              0.0F, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftKb_SpecialN_set_cbs(gobj);
    fp->mv.kb.specialhi.x0 = 1;
    fp->mv.kb.specialhi.x4 = 0;
    fp->mv.kb.specialhi.x8.f = 0.0F;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SsSpecialNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->cmd_vars[0] == 1 && fp->fv.kb.xA4 == 0) {
        Vec3 offset;
        Vec3 pos;
        PAD_STACK(12);
        fp->cmd_vars[0] = 0;
        offset.z = 4.0F;
        offset.y = 0.0F;
        offset.x = 0.0F;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &offset, &pos);
        pos.z = 0.0F;
        if ((fp->fv.kb.xA4 = it_802B55C8(gobj, &pos, FtPart_R3rdNa, 0x97,
                                         fp->facing_dir)) != NULL)
        {
            ftKb_SpecialN_set_cbs(gobj);
        } else {
            fp->fv.kb.xA4 = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.kb.specialhi.x0 == 1 ||
            fp->fv.kb.xA8 == da->specialn_ss_charge_time)
        {
            Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialN, 0, 0.0F, 1.0F,
                                      0.0F, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNHold, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
            GET_FIGHTER(gobj)->fv.kb.xAC = 0;
        }
        ftKb_SpecialN_set_cbs(gobj);
    }
}

extern u32 ftKb_Init_803CB6C0[];
void ftKb_SsSpecialNHold_Anim(Fighter_GObj* gobj)
{
    Fighter* fp3;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 ratio;
    int i;
    Fighter* fp2 = GET_FIGHTER(gobj);
    fp3 = (fp2 = fp);
    PAD_STACK(0x18);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (fp->fv.kb.xA8 != 0) {
            ratio = fp->fv.kb.xA8 / da->specialn_ss_charge_time;
        } else {
            ratio = 0.0F;
        }
        i = 5.0F * ratio;
        ft_80088510(fp, ftKb_Init_803CB6C0[i], 0x7F, 0x40);
    }
    fp3->mv.kb.specialhi.x4 += 1;
    if (fp3->mv.kb.specialhi.x4 > da->specialn_ss_frames_per_charge_level) {
        fp3->mv.kb.specialhi.x4 = 0;
        fp3->fv.kb.xA8 += 1;
        if (fp3->fv.kb.xA8 >= da->specialn_ss_charge_time) {
            ftCo_800BFFD0(fp3, 0x36, 0);
            fp3->fv.kb.xA8 = da->specialn_ss_charge_time;
            Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNCancel, 0, 0.0F,
                                      1.0F, 0.0F, NULL);
            ftKb_ChargeShot_inline(gobj);
            ftKb_SpecialN_set_cbs(gobj);
        }
    }
}

void ftKb_SsSpecialNCancel_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    ftKb_ChargeShot_inline(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SsSpecialN_Anim(Fighter_GObj* gobj)
{
    u8 _[24];

    ftKb_SpecialNSs_800FCDE0(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SsSpecialAirNStart_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] == 1 && fp->fv.kb.xA4 == 0) {
        Vec3 offset;
        Vec3 pos;
        u8 _[4];
        fp->cmd_vars[0] = 0;
        offset.z = 4.0F;
        offset.y = 0.0F;
        offset.x = 0.0F;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, &offset, &pos);
        pos.z = 0.0F;
        if ((fp->fv.kb.xA4 = it_802B55C8(gobj, &pos, FtPart_R3rdNa, 0x97,
                                         fp->facing_dir)) != NULL)
        {
            ftKb_SpecialN_set_cbs(gobj);
        } else {
            fp->fv.kb.xA4 = 0;
        }
    }
    fp->mv.kb.specialhi.x0 = 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SsSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    ftKb_SpecialNSs_800FCDE0(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (da->specialn_ss_freefall_toggle == 0.0F) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0F, da->specialn_ss_freefall_toggle);
    }
}

void ftKb_SsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialNHold_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    if (ftCo_8009917C(gobj) != 0) {
        ftKb_ChargeShot_inline(gobj);
    } else {
        if (fp->input.x668 & 0x200) {
            Fighter_ChangeMotionState(gobj, 0x19A, 0U, 0.0f, 1.0f, 0.0f, NULL);
            ftKb_SpecialN_set_cbs(gobj);
            return;
        }
        if (fp->input.x668 & 0x80000000) {
            Fighter_ChangeMotionState(gobj, 0x199, 0U, 0.0f, 1.0f, 0.0f, NULL);
            ftKb_ChargeShot_inline(gobj);
            ftKb_SpecialN_set_cbs(gobj);
        }
    }
}

void ftKb_SsSpecialNCancel_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_SsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialNHold_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialNCancel_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SsSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SsSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirNStart,
                                  0x0C4C5080U, fp->cur_anim_frame, 1.0f, 0.0f,
                                  NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SsSpecialNHold_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = HSD_GObjGetUserData(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp2;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080,
                                  fp->cur_anim_frame, 1.0F, 0.0F, NULL);
        ftKb_SpecialN_set_cbs(gobj);
        ft_PlaySFX(fp, 0x3F7B5, 0x7F, 0x40);
        fp->cmd_vars[1] = 1;
    }
}

void ftKb_SsSpecialNCancel_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SsSpecialN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialAirN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialNStart, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

void ftKb_SsSpecialAirN_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == GA_Air) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_SsSpecialN, 0x0C4C5080U,
                                  fp->cur_anim_frame, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_set_cbs(gobj);
    }
}

#include "ftkirbyspecialmars.h"

#include "types.h"

#include <placeholder.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

/* 10B2E8 */ static void fn_8010B2E8(Fighter_GObj* gobj);
/* 4D9570 */ extern f32 ftKb_Init_804D9570;
/* 4D9574 */ extern f32 ftKb_Init_804D9574;

void fn_8010B1F4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        if ((s32) fp->fv.kb.hat.kind == FTKIND_MARS) {
            if ((s32) fp->ground_or_air == GA_Ground) {
                efSync_Spawn(0x4B4, gobj, fp->parts[FtPart_TopN].joint);
            } else {
                efSync_Spawn(0x4B5, gobj, fp->parts[FtPart_TopN].joint);
            }
        } else {
            if ((s32) fp->ground_or_air == GA_Ground) {
                efSync_Spawn(0x4B8, gobj, fp->parts[FtPart_TopN].joint);
            } else {
                efSync_Spawn(0x4B9, gobj, fp->parts[FtPart_TopN].joint);
            }
        }
        fp->x2219_b0 = true;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void fn_8010B2E8(Fighter_GObj* gobj)
{
    ftKb_Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->mv.kb.specialn_ms.cur_frame = 0;
}

inline void setupStartAccessory(HSD_GObj* gobj, Vec3* scale)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj;
    KirbyHatStruct* mars_hat;
    KirbyHatStruct* fe_hat;

    mars_hat = ft_80459B88.hats[FTKIND_MARS - 1];
    fe_hat = ft_80459B88.hats[FTKIND_EMBLEM - 1];

    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        ftCommon_SetAccessory(fp, (HSD_Joint*) mars_hat->hat_dynamics[0]);
    } else {
        ftCommon_SetAccessory(fp, (HSD_Joint*) fe_hat->hat_dynamics[0]);
    }

    scale->x = scale->y = scale->z = ftCommon_GetModelScale(fp);
    jobj = fp->x20A0_accessory;
    HSD_JObjSetScale(jobj, scale);
    lb_8000C2F8(fp->x20A0_accessory,
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint);
}

void ftKb_SpecialNMs_8010B2FC(HSD_GObj* gobj)
{
    UNUSED u64 pad;
    Vec3 scale;
    PAD_STACK(4 * 2);
    {
        ftKb_DatAttrs* da;
        struct ftKb_SpecialNMs_DatAttrs* ms_da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ms_da = &da->ms;
        } else {
            ms_da = &da->fe;
        }

        // InStateChange callback
        fp->x21EC = fn_8010B2E8;

        fp->gr_vel = fp->gr_vel / ms_da->air_horizontal_momentum_preservation;
    }

    {
        ftKirby_MotionState msid;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                msid = ftKb_MS_MsSpecialNStart;
            } else {
                msid = ftKb_MS_FeSpecialNStart;
            }
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    }

    ftAnim_8006EBA4(gobj);
    setupStartAccessory(gobj, &scale);
}

void ftKb_SpecialNMs_8010B4A0(HSD_GObj* gobj)
{
    PAD_STACK(4 * 6);
    {
        ftKb_DatAttrs* da;
        struct ftKb_SpecialNMs_DatAttrs* ms_da;
        Fighter* fp = GET_FIGHTER(gobj);
        da = fp->dat_attrs;

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ms_da = &da->ms;
        } else {
            ms_da = &da->fe;
        }

        // InStateChange callback
        fp->x21EC = fn_8010B2E8;

        fp->self_vel.x =
            fp->self_vel.x / ms_da->air_horizontal_momentum_preservation;
        if (fp->self_vel.y <= 0.0f) {
            fp->self_vel.y = 0.0f;
        }
    }

    {
        ftKirby_MotionState msid;
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                msid = ftKb_MS_MsSpecialAirNStart;
            } else {
                msid = ftKb_MS_FeSpecialAirNStart;
            }
        }
        Fighter_ChangeMotionState(gobj, msid, 0, 0, 1, 0, NULL);
    }

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        Vec3 scale;
        KirbyHatStruct* mars_hat = ft_80459B88.hats[FTKIND_MARS - 1];
        KirbyHatStruct* fe_hat = ft_80459B88.hats[FTKIND_EMBLEM - 1];

        if (fp->fv.kb.hat.kind == FTKIND_MARS) {
            ftCommon_SetAccessory(fp, (HSD_Joint*) mars_hat->hat_dynamics[0]);
        } else {
            ftCommon_SetAccessory(fp, (HSD_Joint*) fe_hat->hat_dynamics[0]);
        }

        scale.x = scale.y = scale.z = ftCommon_GetModelScale(fp);
        HSD_JObjSetScale(fp->x20A0_accessory, &scale);
        lb_8000C2F8(
            fp->x20A0_accessory,
            fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint);
    }
}

void ftKb_MsSpecialNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNMs_8010BC40(gobj);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                ftCo_800BFFD0(fp, 99, 0);
            } else {
                ftCo_800BFFD0(fp, 100, 0);
            }
        }
    }
}

void ftKb_MsSpecialAirNStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialNMs_8010BC90(gobj);
        {
            Fighter* fp = GET_FIGHTER(gobj);
            if (fp->fv.kb.hat.kind == FTKIND_MARS) {
                ftCo_800BFFD0(fp, 99, 0);
            } else {
                ftCo_800BFFD0(fp, 100, 0);
            }
        }
    }
}

void ftKb_MsSpecialNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialAirNStart_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialNStart_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    PAD_STACK(16);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    ftCommon_ApplyFrictionGround(fp, ms_da->air_horizontal_deceleration_rate);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftKb_MsSpecialAirNStart_Phys(Fighter_GObj* gobj)
{
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    Fighter* fp = getFighter(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    ftCommon_FallBasic(fp);
    ftCommon_ApplyFrictionAir(fp, ms_da->air_horizontal_deceleration_rate);
}

void ftKb_MsSpecialNStart_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNMs_8010B868(gobj);
    }
}

void ftKb_MsSpecialAirNStart_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNMs_8010B8E0(gobj);
    }
}

inline FtMotionId getAirSpecialMotionId(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        return ftKb_MS_MsSpecialAirNStart;
    } else {
        return ftKb_MS_FeSpecialAirNStart;
    }
}

void ftKb_SpecialNMs_8010B868(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, getAirSpecialMotionId(gobj), 0x0C4C7084,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

inline FtMotionId getGroundSpecialMotionId(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        return ftKb_MS_MsSpecialNStart;
    } else {
        return ftKb_MS_FeSpecialNStart;
    }
}

void ftKb_SpecialNMs_8010B8E0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, getGroundSpecialMotionId(gobj), 0x0C4C7084,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
}

void ftKb_MsSpecialNLoop_Anim(Fighter_GObj* gobj)
{
    s32* charge;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        charge = (s32*) &da->ms.charge_iterations;
    } else {
        charge = (s32*) &da->fe.charge_iterations;
    }
    fp->mv.kb.specialn_ms.cur_frame++;
    if (fp->mv.kb.specialn_ms.cur_frame > (*charge * 30)) {
        fp->cmd_vars[0] = 1;
        ftKb_SpecialNPe_8010C148(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_Anim(Fighter_GObj* gobj)
{
    u32* charge;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->fv.kb.hat.kind == FTKIND_MARS) {
        charge = &da->ms.charge_iterations;
    } else {
        charge = &da->fe.charge_iterations;
    }
    fp->mv.kb.specialn_ms.cur_frame++;
    if (fp->mv.kb.specialn_ms.cur_frame > (s32) (*charge * 30)) {
        fp->cmd_vars[0] = 1;
        ftKb_SpecialNPe_8010C1E8(gobj);
    }
}

void ftKb_MsSpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        ftKb_SpecialNPe_8010C148(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->cmd_vars[0] = 0;
        ftKb_SpecialNPe_8010C1E8(gobj);
    }
}

void ftKb_MsSpecialNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MsSpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MsSpecialNLoop_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNMs_8010BB50(gobj);
    }
}

void ftKb_MsSpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNMs_8010BBC8(gobj);
    }
}

void ftKb_SpecialNMs_8010BB50(Fighter_GObj* gobj)
{
    FtMotionId msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    if ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind == FTKIND_MARS) {
        msid = ftKb_MS_MsSpecialAirNLoop;
    } else {
        msid = ftKb_MS_FeSpecialAirNLoop;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C7A86, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

void ftKb_SpecialNMs_8010BBC8(Fighter_GObj* gobj)
{
    FtMotionId msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    if ((s32) GET_FIGHTER(gobj)->fv.kb.hat.kind == FTKIND_MARS) {
        msid = ftKb_MS_MsSpecialNLoop;
    } else {
        msid = ftKb_MS_FeSpecialNLoop;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C7A86, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

void ftKb_SpecialNMs_8010BC40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;

    if ((s32) fp->fv.gw.x2238_panicCharge == 0x12) {
        i = ftKb_MS_MsSpecialNLoop;
    } else {
        i = ftKb_MS_FeSpecialNLoop;
    }

    Fighter_ChangeMotionState(gobj, i, 0x3200U, 0.0f, 1.0f, 0.0f, NULL);
}

void ftKb_SpecialNMs_8010BC90(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;

    if ((s32) fp->fv.gw.x2238_panicCharge == 0x12) {
        i = ftKb_MS_MsSpecialAirNLoop;
    } else {
        i = ftKb_MS_FeSpecialAirNLoop;
    }

    Fighter_ChangeMotionState(gobj, i, 0x3200U, 0.0f, 1.0f, 0.0f, NULL);
}

void ftKb_MsSpecialNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    Fighter* hit_fp;
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(24);
    if ((s32) fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    if (fp->cmd_vars[0] == 0U) {
        hit_fp = fp;
        i = 0;
        do {
            if ((s32) hit_fp->x914[0].state == 1) {
                f32 dmg =
                    (f32) (s32) (ms_da->base_damage +
                                 (fp->mv.kb.specialn_ms.cur_frame / 30) *
                                     ms_da->additional_damage_per_iteration);
                ftColl_8007ABD0(hit_fp->x914, (u32) dmg, gobj);
            }
            i += 1;
            hit_fp = (Fighter*) ((u8*) hit_fp + sizeof(HitCapsule));
        } while (i < 4);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_MsSpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 i;
    struct ftKb_SpecialNMs_DatAttrs* ms_da;
    Fighter* hit_fp;
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(24);
    if ((s32) fp->fv.kb.hat.kind == FTKIND_MARS) {
        ms_da = &da->ms;
    } else {
        ms_da = &da->fe;
    }
    if (fp->cmd_vars[0] == 0U) {
        hit_fp = fp;
        i = 0;
        do {
            if ((s32) hit_fp->x914[0].state == 1) {
                f32 dmg =
                    (f32) (s32) (ms_da->base_damage +
                                 (fp->mv.kb.specialn_ms.cur_frame / 30) *
                                     ms_da->additional_damage_per_iteration);
                ftColl_8007ABD0(hit_fp->x914, (u32) dmg, gobj);
            }
            i += 1;
            hit_fp = (Fighter*) ((u8*) hit_fp + sizeof(HitCapsule));
        } while (i < 4);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_MsSpecialNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialAirNEnd_IASA(Fighter_GObj* gobj) {}

void ftKb_MsSpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MsSpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_MsSpecialNEnd_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNPe_8010BF90(gobj);
    }
}

void ftKb_MsSpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNPe_8010C06C(gobj);
    }
}

void ftKb_SpecialNPe_8010BF90(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(16);
    if (((Fighter*) gobj->user_data)->cmd_vars[0] == 0) {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0
                   : ftKb_MS_FeSpecialAirNEnd0;
    } else {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0 + 1
                   : ftKb_MS_FeSpecialAirNEnd0 + 1;
    }
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C708E, fp->cur_anim_frame,
                              ftKb_Init_804D9574, ftKb_Init_804D9570, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftKb_SpecialNPe_8010C06C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(16);
    if (((Fighter*) gobj->user_data)->cmd_vars[0] == 0) {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0
                   : ftKb_MS_FeSpecialNEnd0;
    } else {
        msid = (((Fighter*) gobj->user_data)->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0 + 1
                   : ftKb_MS_FeSpecialNEnd0 + 1;
    }
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, 0x0C4C708E, fp->cur_anim_frame,
                              ftKb_Init_804D9574, ftKb_Init_804D9570, NULL);
    if (fp->x2219_b0 == true) {
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
    }
}

void ftKb_SpecialNPe_8010C148(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(4 * 6);
    if (fp->cmd_vars[0] == 0U) {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0
                   : ftKb_MS_FeSpecialNEnd0;
    } else {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialNEnd0 + 1
                   : ftKb_MS_FeSpecialNEnd0 + 1;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x2000, 1.0F, 1.0F, 0.0F, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = fn_8010B1F4;
}

void ftKb_SpecialNPe_8010C1E8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;
    PAD_STACK(4 * 6);
    if (fp->cmd_vars[0] == 0U) {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0
                   : ftKb_MS_FeSpecialAirNEnd0;
    } else {
        msid = ((s32) fp->fv.kb.hat.kind == FTKIND_MARS)
                   ? ftKb_MS_MsSpecialAirNEnd0 + 1
                   : ftKb_MS_FeSpecialAirNEnd0 + 1;
    }
    Fighter_ChangeMotionState(gobj, msid, 0x2000, 1.0F, 1.0F, 0.0F, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = fn_8010B1F4;
}

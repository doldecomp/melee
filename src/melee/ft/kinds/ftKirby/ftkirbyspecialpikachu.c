#include "ftkirbyspecialpikachu.h"

#include "types.h"

#include <placeholder.h>

#include <melee/ft/fighter.h>

#include <melee/ft/forward.h>

#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/types.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>

#include "forward.h"
#include <melee/ft/kinds/ftPikachu/forward.h>

#include <melee/it/kinds/itpikachutjoltground.h>

#include <stddef.h>

static void doEnter(Fighter_GObj* gobj, ftKirby_MotionState pk_msid,
                    ftKirby_MotionState pc_msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirby_MotionState msid = pk_msid;
    switch (fp->u.kb.hat.kind) {
    case FTKIND_PIKACHU:
        break;
    case FTKIND_PICHU:
        msid = pc_msid;
        break;
    default:
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[ftPk_SpecialN_Cmd0] = fp->cmd_vars[ftPk_SpecialN_Cmd1] =
        fp->cmd_vars[ftPk_SpecialN_Cmd2] = fp->cmd_vars[ftPk_SpecialN_Cmd3] =
            false;
    ftAnim_8006EBA4(gobj);
}

void ftKb_SpecialNPk_800F9FD4(Fighter_GObj* gobj)
{
    doEnter(gobj, ftKb_MS_PkSpecialN, ftKb_MS_PcSpecialN);
    PAD_STACK(8);
}

void ftKb_SpecialNPk_800FA064(Fighter_GObj* gobj)
{
    doEnter(gobj, ftKb_MS_PkSpecialAirN, ftKb_MS_PcSpecialAirN);
    PAD_STACK(8);
}

void ftKb_PkSpecialN_Anim(Fighter_GObj* gobj)
{
    Vec3 it_pos;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4);

    if (fp->cmd_vars[ftPk_SpecialN_Cmd0] == true) {
        fp->cmd_vars[ftPk_SpecialN_Cmd0] = false;

        if (!fp->cmd_vars[ftPk_SpecialN_Cmd1]) {
            fp->cmd_vars[ftPk_SpecialN_Cmd1] = true;
            switch (fp->u.kb.hat.kind) {
            case FTKIND_PIKACHU:
                it_pos.x = (fp->x34_scale.y * (da->specialn_pk_spawn_offset.x *
                                               fp->facing_dir)) +
                           fp->cur_pos.x;
                it_pos.y = (da->specialn_pk_spawn_offset.y * fp->x34_scale.y) +
                           fp->cur_pos.y;
                it_pos.z = 0.0f;
                itPikachuThunderJolt_Spawn(gobj, &it_pos, fp->facing_dir,
                                           da->specialn_pk_itkind);
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                it_pos.x = (fp->x34_scale.y * (da->specialn_pc_spawn_offset.x *
                                               fp->facing_dir)) +
                           fp->cur_pos.x;
                it_pos.y = (da->specialn_pc_spawn_offset.y * fp->x34_scale.y) +
                           fp->cur_pos.y;
                it_pos.z = 0.0f;
                itPikachuThunderJolt_Spawn(gobj, &it_pos, fp->facing_dir,
                                           da->specialn_pc_itkind);
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            default:
                break;
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_PkSpecialAirN_Anim(Fighter_GObj* gobj)
{
    Vec3 it_pos;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    float landing_lag;
    PAD_STACK(4);

    if (fp->cmd_vars[ftPk_SpecialN_Cmd0] == true) {
        fp->cmd_vars[ftPk_SpecialN_Cmd0] = false;

        if (!fp->cmd_vars[ftPk_SpecialN_Cmd1]) {
            fp->cmd_vars[ftPk_SpecialN_Cmd1] = true;
            switch (fp->u.kb.hat.kind) {
            case FTKIND_PIKACHU:
                it_pos.x =
                    (fp->x34_scale.y *
                     (da->specialairn_pk_spawn_offset.x * fp->facing_dir)) +
                    fp->cur_pos.x;
                it_pos.y =
                    (da->specialairn_pk_spawn_offset.y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                it_pos.z = 0.0f;
                itPikachuThunderJolt_Spawn(gobj, &it_pos, fp->facing_dir,
                                           da->specialn_pk_itkind);
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                it_pos.x =
                    (fp->x34_scale.y *
                     (da->specialairn_pc_spawn_offset.x * fp->facing_dir)) +
                    fp->cur_pos.x;
                it_pos.y =
                    (da->specialairn_pc_spawn_offset.y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                it_pos.z = 0.0f;
                itPikachuThunderJolt_Spawn(gobj, &it_pos, fp->facing_dir,
                                           da->specialn_pc_itkind);
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            default:
                break;
            }
        }
    }

    switch (fp->u.kb.hat.kind) {
    case FTKIND_PIKACHU:
        landing_lag = da->specialairn_pk_landing_lag;
        break;
    case FTKIND_PICHU:
        landing_lag = da->specialairn_pc_landing_lag;
        break;
    default:
        break;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (landing_lag == 0.0f) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, true, 1.0f, landing_lag);
        }
    }
}

void ftKb_PkSpecialN_IASA(Fighter_GObj* gobj) {}

void ftKb_PkSpecialAirN_IASA(Fighter_GObj* gobj) {}

void ftKb_PkSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_PkSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

static MotionFlags const coll_mf =
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftKb_PkSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        {
            ftKirby_MotionState msid = ftKb_MS_PkSpecialAirN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->u.kb.hat.kind) {
            case FTKIND_PIKACHU:
                break;
            case FTKIND_PICHU:
                msid = ftKb_MS_PcSpecialAirN;
                break;
            default:
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, coll_mf, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

void ftKb_PkSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) == GA_Air) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        fp->self_vel.y = 0.0f;
        {
            ftKirby_MotionState msid = ftKb_MS_PkSpecialN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->u.kb.hat.kind) {
            case FTKIND_PIKACHU:
                break;
            case FTKIND_PICHU:
                msid = ftKb_MS_PcSpecialN;
                break;
            default:
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, coll_mf, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

#include "ftkirbyspecialpikachu.h"

#include "types.h"

#include <placeholder.h>

#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "ftKirby/ftKb_Init.h"
#include "it/items/itpikachutjoltground.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

void ftKb_SpecialNPk_800F9FD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_PkSpecialN;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_PIKACHU:
        break;
    case FTKIND_PICHU:
        msid = ftKb_MS_PcSpecialN;
        break;
    default:
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}

inline void ftKirbyDmgInline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE74C;
    fp->take_dmg_cb = (void (*)(HSD_GObj*)) ftKb_Init_800EE7B8;
}

void ftKb_SpecialNPk_800FA064(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_PkSpecialAirN;
    PAD_STACK(8);
    switch (fp->fv.kb.hat.kind) {
    case FTKIND_PIKACHU:
        break;
    case FTKIND_PICHU:
        msid = ftKb_MS_PcSpecialAirN;
        break;
    default:
        break;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftAnim_8006EBA4(gobj);
}

void ftKb_PkSpecialN_Anim(Fighter_GObj* gobj)
{
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    u8 _[4];

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 0;

        if (!fp->cmd_vars[1]) {
            fp->cmd_vars[1] = 1;
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                sp14.x =
                    (fp->x34_scale.y * (da->specialn_pk_ground_spawn_offset_x *
                                        fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pk_ground_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0f;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pk_grounded_item_id);
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                sp14.x =
                    (fp->x34_scale.y * (da->specialn_pc_ground_spawn_offset_x *
                                        fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pc_ground_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0f;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pc_grounded_item_id);
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
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    float freefall_toggle;

    u8 _[4];

    if (fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 0;

        if (!fp->cmd_vars[1]) {
            fp->cmd_vars[1] = 1;
            switch (fp->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                sp14.x =
                    (fp->x34_scale.y *
                     (da->specialn_pk_air_spawn_offset_x * fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pk_air_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0f;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pk_grounded_item_id);
                ft_PlaySFX(fp, 240076, 127, 64);
                break;
            case FTKIND_PICHU:
                sp14.x =
                    (fp->x34_scale.y *
                     (da->specialn_pc_air_spawn_offset_x * fp->facing_dir)) +
                    fp->cur_pos.x;
                sp14.y =
                    (da->specialn_pc_air_spawn_offset_y * fp->x34_scale.y) +
                    fp->cur_pos.y;
                sp14.z = 0.0f;
                it_802B338C(gobj, &sp14, fp->facing_dir,
                            da->specialn_pc_grounded_item_id);
                ft_PlaySFX(fp, 230067, 127, 64);
                break;
            default:
                break;
            }
        }
    }

    switch (fp->fv.kb.hat.kind) {
    case FTKIND_PIKACHU:
        freefall_toggle = da->specialn_pk_freefall_toggle;
        break;
    case FTKIND_PICHU:
        freefall_toggle = da->specialn_pc_freefall_toggle;
        break;
    default:
        break;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0f == freefall_toggle) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f, freefall_toggle);
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

void ftKb_PkSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        {
            s32 msid = ftKb_MS_PkSpecialAirN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                break;
            case FTKIND_PICHU:
                msid = ftKb_MS_PcSpecialAirN;
                break;
            default:
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5082, anim_frame, 1.0f,
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
            s32 msid = ftKb_MS_PkSpecialN;
            f32 anim_frame = fp->cur_anim_frame;
            switch (GET_FIGHTER(gobj)->fv.kb.hat.kind) {
            case FTKIND_PIKACHU:
                break;
            case FTKIND_PICHU:
                msid = ftKb_MS_PcSpecialN;
                break;
            default:
                break;
            }
            Fighter_ChangeMotionState(gobj, msid, 0x0C4C5082, anim_frame, 1.0f,
                                      0.0f, NULL);
        }
    }
}

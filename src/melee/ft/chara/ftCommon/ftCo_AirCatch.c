#include "ftCo_AirCatch.h"

#include "ftCo_FallSpecial.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/types.h"
#include "ftLink/types.h"

#include "ftSamus/forward.h"

#include "ftSamus/types.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itsamusgrapple.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <baselib/jobj.h>

bool ftCo_800C3A14(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData coll = *getFtColl(fp);
    PAD_STACK(8);
    coll.ledge_snap_y += 5.0;
    coll.ledge_snap_height += 5.0;
    if (fp->facing_dir > (f64) 0.0F) {
        if (mpColl_80044164(&coll, &fp->coll_data.ledge_id_left)) {
            fp->coll_data.env_flags |= Collide_LeftLedgeGrab;
            fp->self_vel.x = 0;
            fp->self_vel.y = 0;
            return true;
        }
        return false;
    }
    if (mpColl_800443C4(&coll, &fp->coll_data.ledge_id_right)) {
        fp->coll_data.env_flags |= Collide_RightLedgeGrab;
        fp->self_vel.x = 0;
        fp->self_vel.y = 0;
        return true;
    }
    return false;
}

bool ftCo_800C3B10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->used_tether) {
        return false;
    }
    if (fp->kind != FTKIND_LINK && fp->kind != FTKIND_CLINK &&
        fp->kind != FTKIND_SAMUS)
    {
        return false;
    }
    if (fp->accessory2_cb != NULL || fp->death1_cb != NULL ||
        fp->accessory3_cb != NULL)
    {
        return false;
    }
    if (fp->item_gobj != NULL) {
        return false;
    }
    if (fp->input.held_inputs & HSD_PAD_LR && fp->input.x668 & HSD_PAD_A) {
        ftCo_800C3BE8(gobj);
        fp->used_tether = true;
        return true;
    }
    return false;
}

void ftCo_800C3BE8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 anim_vel = { 0 };
    if (fp->ground_or_air == GA_Air) {
        fp->mv.co.aircatch.x0 = 0;
        fp->x74_anim_vel = anim_vel;

        if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_AirCatch, Ft_MF_None, 0, 1,
                                      0, NULL);
        } else if (fp->kind == FTKIND_SAMUS) {
            Fighter_ChangeMotionState(gobj, ftSs_MS_AirCatch, Ft_MF_None, 0, 1,
                                      0, NULL);
        }
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftCo_800C3CC0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 drift;
    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_AirCatchHit,
                                  Ft_MF_KeepFastFall, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftSs_MS_AirCatchHit,
                                  Ft_MF_KeepFastFall, 0, 1, 0, NULL);
    }
    drift = fp->co_attrs.air_drift_max;
    ftCommon_ClampSelfVelX(fp, drift);
    fp->mv.co.aircatchhit.x0 = 20;
    fp->mv.co.aircatchhit.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}

void ftCo_AirCatch_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        ftLk_DatAttrs* da = fp->dat_attrs;
        fp->mv.co.aircatch.x0 += 1.0;
        if (fp->mv.co.aircatch.x0 == da->xA4) {
            Vec3 pos;
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                NULL, &pos);
            fp->fv.lk.xC = it_802A2BA4(gobj, &pos, fp->facing_dir, da->xBC);
            if (fp->fv.lk.xC == NULL) {
                ftCo_800968C8(gobj);
            } else {
                fp->accessory2_cb = it_802A7AF0;
                fp->death1_cb = it_802A7AAC;
                fp->accessory3_cb = it_802A7B34;
            }
        } else if (fp->mv.co.aircatch.x0 > da->xA4) {
            if (fp->mv.co.aircatch.x0 <= da->xB0) {
                Item_GObj* tether_gobj = fp->fv.lk.xC;
                Item* tether_ip = GET_ITEM(fp->fv.lk.xC);
                struct TetherAttributes* tether_data =
                    tether_ip->xC4_article_data->x4_specialAttributes;

                if (fp->mv.co.aircatch.x0 == da->xA8) {
                    Vec3 pos = { 1.8, 0, 0 };
                    HSD_JObj* jobj =
                        fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)]
                            .joint;
                    HSD_JObjSetupMatrix(jobj);
                    {
                        float var_f3;

                        if (fp->kind == FTKIND_LINK) {
                            var_f3 = 8.0 * fp->facing_dir * fp->x34_scale.y +
                                     jobj->mtx[0][3];
                        } else {
                            var_f3 = 8.0 * fp->facing_dir * fp->x34_scale.y +
                                     jobj->mtx[0][3];
                        }
                        if (mpCheckAllRemap(
                                0, 0, 0, 0, -1, -1, fp->coll_data.cur_pos.x,
                                jobj->mtx[1][3], var_f3, jobj->mtx[1][3]) != 0)
                        {
                            it_802A2B10(fp->fv.lk.xC);
                            ftCo_800968C8(gobj);
                            return;
                        }
                    }
                    pos.x = tether_data->pos_x_0;
                    pos.x *= fp->facing_dir;
                    {
                        float x = pos.x;
                        pos.x = x + fp->pos_delta.x;
                        it_802A78B8(tether_gobj, &pos, x);
                    }
                    if (fp->kind == FTKIND_CLINK) {
                        ft_PlaySFX(fp, 0x111B9, 0x7F, 0x40);
                    } else {
                        ft_PlaySFX(fp, 0x27149, 0x7F, 0x40);
                    }
                } else if (fp->mv.co.aircatch.x0 == da->xAC) {
                    it_802A77DC(tether_gobj);
                    if (fp->kind == FTKIND_CLINK) {
                        ft_PlaySFX(fp, 0x111BC, 0x7F, 0x40);
                    } else {
                        ft_PlaySFX(fp, 0x2714C, 0x7F, 0x40);
                    }
                } else if (fp->mv.co.aircatch.x0 == da->xB0) {
                    it_802A2B10(fp->fv.lk.xC);
                }
            }
        }
    } else if (fp->kind == FTKIND_SAMUS) {
        ftSs_DatAttrs* da = fp->dat_attrs;
        PAD_STACK(3 * 4);
        fp->mv.co.aircatch.x0 += 1.0;
        if (fp->mv.co.aircatch.x0 == da->xBC) {
            Vec3 pos;
            lb_8000B1CC(fp->parts[FtPart_ThrowN].joint, NULL, &pos);
            fp->fv.ss.x223C = it_802B7C18(gobj, &pos, fp->facing_dir);
            if (fp->fv.ss.x223C == NULL) {
                ftCo_800968C8(gobj);
            } else {
                fp->accessory2_cb = it_802BAC80;
                fp->death1_cb = it_802BAC3C;
                fp->accessory3_cb = it_802BACC4;
            }
        } else if (fp->mv.co.aircatch.x0 > da->xBC) {
            if (fp->mv.co.aircatch.x0 <= da->xC8) {
                Item_GObj* temp_r29_2 = fp->fv.ss.x223C;
                Item* tether_ip = GET_ITEM(temp_r29_2);
                struct TetherAttributes* tether_data =
                    tether_ip->xC4_article_data->x4_specialAttributes;
                if (fp->mv.co.aircatch.x0 == da->xC0) {
                    {
                        Vec3 pos = { 1.8, 0, 0 };
                        PAD_STACK(3 * 4);
                        {
                            HSD_JObj* jobj = fp->parts[FtPart_ThrowN].joint;
                            HSD_JObjSetupMatrix(jobj);
                            if (mpCheckAllRemap(
                                    0, 0, 0, 0, -1, -1,
                                    fp->coll_data.cur_pos.x, jobj->mtx[1][3],
                                    (2.0 * fp->facing_dir * fp->x34_scale.y) +
                                        jobj->mtx[0][3],
                                    jobj->mtx[1][3]))
                            {
                                it_802B7B84(fp->fv.ss.x223C);
                                ftCo_800968C8(gobj);
                                return;
                            }
                            pos.x = tether_data->pos_x_1;
                            ;
                            pos.x *= fp->facing_dir;
                            {
                                float x = pos.x;
                                pos.x = x + fp->pos_delta.x;
                                it_802BAAE4(temp_r29_2, &pos, x);
                            }
                        }
                    }
                } else {
                    if (fp->mv.co.aircatch.x0 == da->xC4) {
                        it_802BAA58(temp_r29_2);
                    } else if (fp->mv.co.aircatch.x0 == da->xC8) {
                        it_802B7B84(fp->fv.ss.x223C);
                    }
                }
            }
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800968C8(gobj);
    }
}

void ftCo_AirCatchHit_Anim(Fighter_GObj* gobj) {}

void ftCo_AirCatch_IASA(Fighter_GObj* gobj) {}

void ftCo_AirCatchHit_IASA(Fighter_GObj* gobj) {}

void ftCo_AirCatch_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    PAD_STACK(8);
    ftCommon_CheckFallFast(fp);
    if (fp->fall_fast) {
        ftCommon_FallFast(fp);
    } else if (fp->mv.co.aircatch.x0 < 20 && fp->pos_delta.y < 0.0) {
        ftCommon_Fall(fp, co->grav * 0.2, co->terminal_vel);
    } else {
        ftCommon_Fall(fp, co->grav, co->terminal_vel);
    }
    ftCommon_8007D268(fp);
}

void ftCo_AirCatchHit_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel = fp->pos_delta;
    ftCommon_Fall(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
}

void ftCo_AirCatch_Coll(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_Landing_Enter(gobj, ftCo_MS_Landing, false, Ft_MF_None, 0.0F,
                           1.0F);
    }
}

#include <platform.h>
#include <placeholder.h>

#include "ftSamus/forward.h"
#include "it/forward.h"

#include "ftCo_AirCatch.h"

#include "ftCo_FallSpecial.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/types.h"
#include "ftLink/types.h"
#include "ftSamus/types.h"
#include "it/inlines.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itsamusgrapple.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <baselib/jobj.h>

#pragma force_active on

/* literal */ double const ftCo_804D8CF0 = 5;
/* literal */ double const ftCo_804D8CF8 = 0;
/* literal */ float const ftCo_804D8D00 = 0;
/* literal */ float const ftCo_804D8D04 = 1;
/* literal */ double const ftCo_804D8D08 = 1;
/* literal */ double const ftCo_804D8D10 = 8;
/* literal */ double const ftCo_804D8D18 = 2;
/* literal */ double const ftCo_804D8D20 = S32_TO_F32;
/* literal */ float const ftCo_804D8D28 = 20;
/* literal */ double const ftCo_804D8D30 = 0.2;
/* literal */ Vec3 const lbl_803B74C8 = { 0 };
/* literal */ Vec3 const lbl_803B74D4 = { 1.8, 0, 0 };
/* literal */ Vec3 const lbl_803B74E0 = { 1.8, 0, 0 };
/* literal */ SDATA char ftCo_804D3C48[] = "jobj.h";
/* literal */ SDATA char ftCo_804D3C50[] = "jobj";

bool ftCo_800C3A14(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData coll = *getFtColl(fp);
    PAD_STACK(8);
    coll.x58 += 5.0;
    coll.x5C += 5.0;
    if (fp->facing_dir > (f64) 0.0F) {
        if (mpColl_80044164(&coll, &fp->coll_data.ledge_id_unk1)) {
            fp->coll_data.env_flags |= MPCOLL_FLAGS_B24;
            fp->self_vel.x = 0;
            fp->self_vel.y = 0;
            return true;
        }
        return false;
    }
    if (mpColl_800443C4(&coll, &fp->coll_data.ledge_id_unk0)) {
        fp->coll_data.env_flags |= MPCOLL_FLAGS_B25;
        fp->self_vel.x = 0;
        fp->self_vel.y = 0;
        return true;
    }
    return false;
}

bool ftCo_800C3B10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2228_b6) {
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
        fp->x2228_b6 = true;
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
    ftCommon_8007D440(fp, drift);
    fp->mv.co.aircatchhit.x0 = 20;
    fp->mv.co.aircatchhit.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}

void ftCo_AirCatch_Anim(Fighter_GObj* gobj)
{
    u8 _[16] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        ftLk_DatAttrs* da = fp->dat_attrs;
        fp->mv.co.aircatch.x0 += 1.0;
        if (fp->mv.co.aircatch.x0 == da->xA4) {
            Vec3 pos;
            u8 _[4] = { 0 };
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
                void* tether_data =
                    M2C_FIELD(tether_ip->xC4_article_data, void**, 4);
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
                        if (mpLib_800524DC(
                                0, 0, 0, 0, -1, -1, fp->coll_data.cur_topn.x,
                                jobj->mtx[1][3], var_f3, jobj->mtx[1][3]) != 0)
                        {
                            it_802A2B10(fp->fv.lk.xC);
                            ftCo_800968C8(gobj);
                            return;
                        }
                    }
                    pos.x = M2C_FIELD(tether_data, float*, 0x38);
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
                } else if (fp->mv.co.aircatch.x0 ==
                           (float) M2C_FIELD(da, int*, 0xAC))
                {
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
        fp->mv.co.aircatch.x0 += 1.0;
        if (fp->mv.co.aircatch.x0 == da->xBC) {
            Vec3 pos;
            u8 _[4] = { 0 };
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
                void* tether_data =
                    M2C_FIELD(tether_ip->xC4_article_data, void**, 4);
                if (fp->mv.co.aircatch.x0 == da->xC0) {
                    Vec3 pos = { 1.8, 0, 0 };
                    HSD_JObj* jobj = fp->parts[FtPart_ThrowN].joint;
                    HSD_JObjSetupMatrix(jobj);
                    if (mpLib_800524DC(
                            0, 0, 0, 0, -1, -1, fp->coll_data.cur_topn.x,
                            jobj->mtx[1][3],
                            (2.0 * fp->facing_dir * fp->x34_scale.y) +
                                jobj->mtx[0][3],
                            jobj->mtx[1][3]))
                    {
                        it_802B7B84(fp->fv.ss.x223C);
                        ftCo_800968C8(gobj);
                        return;
                    }
                    pos.x = M2C_FIELD(tether_data, float*, 0x40);
                    pos.x *= fp->facing_dir;
                    {
                        float x = pos.x;
                        pos.x = x + fp->pos_delta.x;
                        it_802BAAE4(temp_r29_2, &pos, x);
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
    return;
}

void ftCo_AirCatchHit_Anim(Fighter_GObj* gobj) {}

void ftCo_AirCatch_IASA(Fighter_GObj* gobj) {}

void ftCo_AirCatchHit_IASA(Fighter_GObj* gobj) {}

void ftCo_AirCatch_Phys(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    ftCommon_8007D528(fp);
    if (fp->x221A_b4) {
        ftCommon_8007D4E4(fp);
    } else if (fp->mv.co.aircatch.x0 < 20 && fp->pos_delta.y < 0.0) {
        ftCommon_8007D494(fp, co->grav * 0.2, co->terminal_vel);
    } else {
        ftCommon_8007D494(fp, co->grav, co->terminal_vel);
    }
    ftCommon_8007D268(fp);
}

void ftCo_AirCatchHit_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel = fp->pos_delta;
    ftCommon_8007D494(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
}

void ftCo_AirCatch_Coll(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_800D5AEC(gobj, 42, 0, 0, 0, 1);
    }
}

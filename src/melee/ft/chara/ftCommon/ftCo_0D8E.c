#include "ftCo_Attack100.h"

#include "ft/chara/ftLink/ftLk_Init.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/inlines.h"
#include "it/items/itlinkhookshot.h"
#include "lb/lb_00B0.h"

typedef struct {
    u8 pad_0[0x84];
    s32 x84;
    s32 x88;
    s32 x8C;
    s32 x90;
    s32 x94;
    s32 x98;
    s32 x9C;
    s32 xA0;
    u8 pad_A4[0xBC - 0xA4];
    s32 xBC;
} ftCo_LinkCatchAttrs;

bool fn_800D8EC8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_LinkCatchAttrs* attrs;
    Vec3 bonePos;
    u32 unused;
    Item_GObj* item;
    HSD_JObj* jobj;
    itLinkHookshotAttributes* hookAttrs;
    f32 grav;
    Vec3 vel;
    f32 var_f3;
    f32 mtxY;
    UNUSED u32 unused1;
    UNUSED u32 unused2;
    UNUSED u32 unused3;
    UNUSED u32 unused4;

    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        attrs = fp->dat_attrs;
        fp->mv.ca.specials.grav += 1.0;
        grav = fp->mv.ca.specials.grav;
        if (grav == (f32) attrs->x84) {
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                NULL, &bonePos);
            fp->u.lk.xC =
                it_802A2BA4(gobj, &bonePos, fp->facing_dir, attrs->xBC);
            if (fp->u.lk.xC == NULL) {
                ft_8008A2BC(gobj);
                return 1;
            }
            fp->accessory2_cb = it_802A7AF0;
            fp->death1_cb = it_802A7AAC;
            fp->accessory3_cb = it_802A7B34;
        } else if (grav > (f32) attrs->x84) {
            if (grav <= (f32) attrs->x90) {
                item = fp->u.lk.xC;
                hookAttrs =
                    GET_ITEM(item)->xC4_article_data->x4_specialAttributes;
                if (grav == (f32) attrs->x88) {
                    jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)]
                               .joint;
                    HSD_JObjSetupMatrix(jobj);
                    if (fp->kind == FTKIND_LINK) {
                        var_f3 = 8.0 * fp->facing_dir * fp->x34_scale.y +
                                 jobj->mtx[0][3];
                    } else {
                        var_f3 = 8.0 * fp->facing_dir * fp->x34_scale.y +
                                 jobj->mtx[0][3];
                    }
                    mtxY = jobj->mtx[1][3];
                    if (mpCheckAllRemap(NULL, NULL, NULL, NULL, -1, -1,
                                        fp->coll_data.cur_pos.x, mtxY, var_f3,
                                        mtxY))
                    {
                        it_802A2B10(fp->u.lk.xC);
                        ft_8008A2BC(gobj);
                        return 1;
                    }
                    vel.x = hookAttrs->x38 * fp->facing_dir;
                    vel.y = 0.0f;
                    vel.z = 0.0f;
                    it_802A78B8((HSD_GObj*) item, &vel);
                    if (fp->kind == FTKIND_CLINK) {
                        ft_PlaySFX(fp, 0x111B9, 0x7F, 0x40);
                    } else {
                        ft_PlaySFX(fp, 0x27149, 0x7F, 0x40);
                    }
                } else if (grav == (f32) attrs->x8C) {
                    it_802A77DC(item);
                    if (fp->kind == FTKIND_CLINK) {
                        ft_PlaySFX(fp, 0x111BC, 0x7F, 0x40);
                    } else {
                        ft_PlaySFX(fp, 0x2714C, 0x7F, 0x40);
                    }
                } else if (grav == (f32) attrs->x90) {
                    it_802A2B10(fp->u.lk.xC);
                }
            }
        }
    }
    return 0;
}

bool fn_800D9228(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->kind == FTKIND_LINK) || (fp->kind == FTKIND_CLINK)) {
        ftCo_LinkCatchAttrs* da = fp->dat_attrs;

        fp->mv.co.catch.x0 += 1.0;
        if (fp->mv.co.catch.x0 == (f32) da->x94) {
            Vec3 pos;

            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                NULL, &pos);
            fp->u.lk.xC = it_802A2BA4(gobj, &pos, fp->facing_dir, da->xBC);
            if (fp->u.lk.xC == NULL) {
                ft_8008A2BC(gobj);
                return true;
            }
            fp->accessory2_cb = it_802A7AF0;
            fp->death1_cb = it_802A7AAC;
            fp->accessory3_cb = it_802A7B34;
        } else if (fp->mv.co.catch.x0 > (f32) da->x94 &&
                   fp->mv.co.catch.x0 <= (f32) da->xA0)
        {
            Item_GObj* tether_gobj = fp->u.lk.xC;
            Item* tether_ip = tether_gobj->user_data;
            struct TetherAttributes* tether_data =
                tether_ip->xC4_article_data->x4_specialAttributes;

            if (fp->mv.co.catch.x0 == (f32) da->x98) {
                Vec3 pos;
                PAD_STACK(8);

                pos.x = tether_data->pos_x_0 * fp->facing_dir;
                pos.y = 0.0F;
                pos.z = 0.0F;
                it_802A78B8(tether_gobj, &pos);
                if (fp->kind == FTKIND_CLINK) {
                    ft_PlaySFX(fp, 0x111B9, 0x7F, 0x40);
                } else {
                    ft_PlaySFX(fp, 0x27149, 0x7F, 0x40);
                }
            } else if (fp->mv.co.catch.x0 == (f32) da->x9C) {
                it_802A77DC(tether_gobj);
                if (fp->kind == FTKIND_CLINK) {
                    ft_PlaySFX(fp, 0x111BC, 0x7F, 0x40);
                } else {
                    ft_PlaySFX(fp, 0x2714C, 0x7F, 0x40);
                }
            } else if (fp->mv.co.catch.x0 == (f32) da->xA0) {
                it_802A2B10(tether_gobj);
            }
        }
    }

    return false;
}

void fn_800D949C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        it_802A2B10(fp->u.lk.xC);
    }
}

void ftCo_800D94D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.lk.xC != NULL) {
        it_802A2B10(fp->u.lk.xC);
        fp->u.lk.xC = NULL;
    }
    ftLk_Init_BoomerangExists(gobj);
}

bool fn_800D952C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->kind == FTKIND_SAMUS) && (fp->u.ss.x223C != NULL)) {
        return false;
    }
    return true;
}

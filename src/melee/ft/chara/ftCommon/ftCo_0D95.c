#include "ftCo_Attack100.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/inlines.h"
#include "it/inlines.h"
#include "it/items/itsamusgrapple.h"
#include "lb/lb_00B0.h"

#include <baselib/random.h>

bool fn_800D9558(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* attrs;
    Item_GObj* item;
    s32 frame;
    s32 i;
    itSamusGrappleAttributes* grappleAttrs;
    HSD_GObj* segGobj;
    HSD_JObj* jobj;
    Vec3 bonePos;
    Vec3 effPos;
    Vec3 vel;
    f32 grav;
    f32 my;
    f32 r;
    PAD_STACK(0x10);
    if (fp->kind == FTKIND_SAMUS) {
        attrs = fp->dat_attrs;
        fp->mv.ca.specials.grav += 1.0;
        grav = fp->mv.ca.specials.grav;
        if (grav == (f32) attrs->x9C) {
            lb_8000B1CC(fp->parts[51].joint, NULL, &bonePos);
            fp->u.ss.x223C = it_802B7C18(gobj, &bonePos, fp->facing_dir);
            if (fp->u.ss.x223C == NULL) {
                ft_8008A2BC(gobj);
                return 1;
            }
            fp->accessory2_cb = (void (*)(HSD_GObj*)) it_802BAC80;
            fp->death1_cb = (void (*)(HSD_GObj*)) it_802BAC3C;
            fp->accessory3_cb = (void (*)(HSD_GObj*)) it_802BACC4;
        } else if (grav > (f32) attrs->x9C) {
            if (grav <= (f32) attrs->xA8) {
                Item* it;
                it = GET_ITEM(fp->u.ss.x223C);
                item = fp->u.ss.x223C;
                grappleAttrs = it->xC4_article_data->x4_specialAttributes;
                if (item != NULL) {
                    for (i = 0, frame = 0x14; i < 6; i++, frame += 3) {
                        if (fp->mv.ca.specials.grav == (f32) frame) {
                            segGobj = it->xDD4_itemVar.samusgrapple.x0->gobj;
                            jobj = (HSD_JObj*) segGobj->hsd_obj;
                            HSD_JObjSetupMatrix(jobj);
                            effPos.x = jobj->mtx[0][3];
                            effPos.y = jobj->mtx[1][3];
                            effPos.z = jobj->mtx[2][3];
                            r = HSD_Randf();
                            effPos.x = 4.0 * (r - 0.5f) + effPos.x;
                            effPos.y = 4.0 * (HSD_Randf() - 0.5f) + effPos.y;
                            r = HSD_Randf() - 0.5f;
                            effPos.z = 4.0 * r + effPos.z;
                            efSync_Spawn(0x3F3, segGobj, &effPos);
                        }
                    }
                }
                grav = fp->mv.ca.specials.grav;
                if (grav == (f32) attrs->xA0) {
                    HSD_JObj* joint = fp->parts[51].joint;

                    HSD_JObjSetupMatrix(joint);
                    my = joint->mtx[1][3];
                    if (mpCheckAllRemap(NULL, NULL, NULL, NULL, -1, -1,
                                        fp->coll_data.cur_pos.x, my,
                                        2.0 * fp->facing_dir *
                                                fp->x34_scale.y +
                                            joint->mtx[0][3],
                                        my))
                    {
                        it_802B7B84(fp->u.ss.x223C);
                        ft_8008A2BC(gobj);
                        return 1;
                    }
                    vel.x = grappleAttrs->x40;
                    vel.y = 0.0f;
                    vel.z = 0.0f;
                    vel.x = vel.x * fp->facing_dir;
                    it_802BAAE4(item, &vel);
                } else if (grav == (f32) attrs->xA4) {
                    it_802BAA58(item);
                } else if (grav == (f32) attrs->xA8) {
                    it_802B7B84(fp->u.ss.x223C);
                }
            }
        }
    }
    return 0;
}

static const Vec3 lbl_803B7510 = { 1.0f, 0.0f, 0.0f };

bool fn_800D9930(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* attrs;
    Item_GObj* item;
    s32 frame;
    s32 i;
    itSamusGrappleAttributes* grappleAttrs;
    HSD_GObj* segGobj;
    HSD_JObj* jobj;
    Vec3 bonePos;
    Vec3 effPos;
    Vec3 vel;
    f32 grav;
    f32 r;
    PAD_STACK(4);

    if (fp->kind == FTKIND_SAMUS) {
        attrs = fp->dat_attrs;
        fp->mv.ca.specials.grav += 1.0;
        grav = fp->mv.ca.specials.grav;
        if (grav == (f32) attrs->xAC) {
            lb_8000B1CC(fp->parts[51].joint, NULL, &bonePos);
            fp->u.ss.x223C = it_802B7C18(gobj, &bonePos, fp->facing_dir);
            if (fp->u.ss.x223C == NULL) {
                ft_8008A2BC(gobj);
                return 1;
            }
            fp->accessory2_cb = (void (*)(HSD_GObj*)) it_802BAC80;
            fp->death1_cb = (void (*)(HSD_GObj*)) it_802BAC3C;
            fp->accessory3_cb = (void (*)(HSD_GObj*)) it_802BACC4;
        } else if (grav > (f32) attrs->xAC) {
            if (grav <= (f32) attrs->xB8) {
                Item* it;
                it = GET_ITEM(fp->u.ss.x223C);
                item = fp->u.ss.x223C;
                grappleAttrs = it->xC4_article_data->x4_specialAttributes;
                if (item != NULL) {
                    for (i = 0, frame = 0x14; i < 4; i++, frame += 3) {
                        if (fp->mv.ca.specials.grav == (f32) frame) {
                            segGobj = it->xDD4_itemVar.samusgrapple.x0->gobj;
                            jobj = (HSD_JObj*) segGobj->hsd_obj;
                            HSD_JObjSetupMatrix(jobj);
                            effPos.x = jobj->mtx[0][3];
                            effPos.y = jobj->mtx[1][3];
                            effPos.z = jobj->mtx[2][3];
                            r = HSD_Randf();
                            effPos.x = 4.0 * (r - 0.5f) + effPos.x;
                            effPos.y = 4.0 * (HSD_Randf() - 0.5f) + effPos.y;
                            r = HSD_Randf() - 0.5f;
                            effPos.z = 4.0 * r + effPos.z;
                            efSync_Spawn(0x3F3, segGobj, &effPos);
                        }
                    }
                }
                grav = fp->mv.ca.specials.grav;
                if (grav == (f32) attrs->xB0) {
                    vel = lbl_803B7510;
                    vel.x = grappleAttrs->x40;
                    vel.x *= fp->facing_dir;
                    it_802BAAE4(item, &vel);
                } else if (grav == (f32) attrs->xB4) {
                    it_802BAA58(item);
                } else if (grav == (f32) attrs->xB8) {
                    it_802B7B84(fp->u.ss.x223C);
                }
            }
        }
    }
    return 0;
}

void fn_800D9C64(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_SAMUS) {
        it_802B7B84(fp->u.ss.x223C);
    }
}

void ftCo_800D9C98(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.ss.x223C != NULL) {
        it_802B7B84(fp->u.ss.x223C);
        fp->u.ss.x223C = NULL;
    }

    fp->death2_cb = NULL;
    fp->take_dmg_2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

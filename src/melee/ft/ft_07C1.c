#include "ft/ft_07C1.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftcoll.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_HammerWait.h"

#include "it/forward.h"

#include "it/it_26B1.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"

#include <baselib/gobj.h>

void ft_8007C224(HSD_GObj* gobj);

void ft_8007C114(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        switch (itGetKind(fp->item_gobj)) {
        case It_Kind_Hammer:
            ftCo_800C555C(gobj);
            break;
        }
    }
    fp->x2219_b4 = 0;
}

void ft_8007C17C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->x1064_thrownHitbox;
    struct ftData_x34* x34 = fp->ft_data->x34;
    fp->x1064_thrownHitbox.x4 = 0;
    fp->x1064_thrownHitbox.state = HitCapsule_Enabled;
    lbColl_80008440(hit);
    hit->jobj = fp->parts[x34->x0].joint;
    hit->scale = x34->scale;
    hit->b_offset.x = hit->b_offset.y = hit->b_offset.z = 0;
    hit->x43_b1 = false;
    hit->x43_b2 = false;
    fp->x2227_b2 = false;
    ft_8007C224(gobj);
}

void ft_8007C224(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    HitCapsule* hitbox = &ft->x1064_thrownHitbox;

    switch (hitbox->state) {
    case HitCapsule_Disabled:
        break;
    case HitCapsule_Enabled:
        lb_8000B1CC(hitbox->jobj, &hitbox->b_offset, &hitbox->x4C);
        hitbox->x58 = hitbox->x4C;
        hitbox->state = HitCapsule_Unk2;
        break;
    case HitCapsule_Unk2:
        hitbox->state = HitCapsule_Unk3;
    case HitCapsule_Unk3:
        hitbox->x58 = hitbox->x4C;
        lb_8000B1CC(hitbox->jobj, &hitbox->b_offset, &hitbox->x4C);
        break;
    }
}

static inline void inlineA0(Fighter* fp0, Fighter* fp1, HitCapsule* hit1)
{
    lbColl_80008688(hit1, 3, fp0);
    if (fp1->ground_or_air == GA_Air) {
        float temp_f1 = fp0->co_attrs.weight / fp1->co_attrs.weight;
        float temp_f5;
        if (temp_f1 > 1) {
            temp_f1 = 1;
        }
        temp_f5 = temp_f1 * p_ftCommonData->hit_weight_mul;
        if (fp0->pos_delta.x * fp1->pos_delta.x >= 0) {
            fp1->x98_atk_shield_kb.x +=
                (fp0->pos_delta.x - fp1->pos_delta.x) * temp_f5;
        } else {
            fp1->x98_atk_shield_kb.x += fp0->pos_delta.x * temp_f5;
        }
        if (fp0->pos_delta.y * fp1->pos_delta.y >= 0) {
            fp1->x98_atk_shield_kb.y +=
                (fp0->pos_delta.y - fp1->pos_delta.y) * temp_f5;
        } else {
            fp1->x98_atk_shield_kb.y += fp0->pos_delta.y * temp_f5;
        }
    }
}

/// @@todo This is just the same inline twice.
void ft_8007C2E0(Fighter* fp0, HitCapsule* hit0, Fighter* fp1,
                 HitCapsule* hit1)
{
    PAD_STACK(4 * 4);

    if (lbColl_8000ACFC(fp1, hit0)) {
        return;
    }

    { // inlineA0(fp0, fp1, hit1);
        lbColl_80008688(hit1, 3, fp0);
        if (fp1->ground_or_air == GA_Air) {
            float weight_ratio = fp0->co_attrs.weight / fp1->co_attrs.weight;
            if (weight_ratio > 1) {
                weight_ratio = 1;
            }
            weight_ratio *= p_ftCommonData->hit_weight_mul;
            if (fp0->pos_delta.x * fp1->pos_delta.x >= 0) {
                fp1->x98_atk_shield_kb.x +=
                    (fp0->pos_delta.x - fp1->pos_delta.x) * weight_ratio;
            } else {
                fp1->x98_atk_shield_kb.x += fp0->pos_delta.x * weight_ratio;
            }
            if (fp0->pos_delta.y * fp1->pos_delta.y >= 0) {
                fp1->x98_atk_shield_kb.y +=
                    (fp0->pos_delta.y - fp1->pos_delta.y) * weight_ratio;
            } else {
                fp1->x98_atk_shield_kb.y += fp0->pos_delta.y * weight_ratio;
            }
        }
    }

    { // inlineA0(fp1, fp0, hit0);
        lbColl_80008688(hit0, 3, fp1);
        if (fp0->ground_or_air == 1) {
            float weight_ratio = fp1->co_attrs.weight / fp0->co_attrs.weight;
            if (weight_ratio > 1) {
                weight_ratio = 1;
            }
            weight_ratio *= p_ftCommonData->hit_weight_mul;
            if (fp0->pos_delta.x * fp1->pos_delta.x >= 0) {
                fp0->x98_atk_shield_kb.x +=
                    (fp1->pos_delta.x - fp0->pos_delta.x) * weight_ratio;
            } else {
                fp0->x98_atk_shield_kb.x += fp1->pos_delta.x * weight_ratio;
            }
            if (fp0->pos_delta.y * fp1->pos_delta.y >= 0) {
                fp0->x98_atk_shield_kb.y +=
                    (fp1->pos_delta.y - fp0->pos_delta.y) * weight_ratio;
            } else {
                fp0->x98_atk_shield_kb.y += fp1->pos_delta.y * weight_ratio;
            }
        }
    }
}

void ft_8007C4BC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2227_b2) {
        return;
    }
    if (ftColl_8007B868(gobj) == 2) {
        return;
    }
    if (fp->x221F_b4) {
        return;
    }

    {
        bool seen = false;
        Fighter_GObj* cur;
        HSD_GObj* grab_attacker;
        PAD_STACK(4 * 2);
        if (fp->victim_gobj != NULL) {
            grab_attacker = (Fighter_GObj*) fp->victim_gobj;
        } else if (fp->x221C_b6) {
            grab_attacker = (Fighter_GObj*) fp->dmg.x1868_source;
        } else {
            grab_attacker = NULL;
        }
        {
            Fighter* fp1;
            HitCapsule* throw_hitbox = &fp->x1064_thrownHitbox;

            for (cur = HSD_GObj_Entities->fighters; cur != NULL;
                 cur = cur->next)
            {
                if (gobj == cur) {
                    seen = true;
                    continue;
                }

                if (cur != grab_attacker) {
                    fp1 = GET_FIGHTER(cur);

                    if (fp1->x2219_b1 || !fp1->x2227_b2 ||
                        ftColl_8007B868(cur) == 2 || fp1->x221F_b4 ||
                        (fp1->x221C_b6 && fp1->dmg.x1868_source == gobj))
                    {
                        continue;
                    }

                    {
                        HitCapsule* hit = &fp1->x1064_thrownHitbox;
                        if (fp1->x1064_thrownHitbox.state ==
                                HitCapsule_Disabled ||
                            !seen)
                        {
                            continue;
                        }

                        if (lbColl_80007AFC(hit, throw_hitbox,
                                            fp1->x34_scale.y, fp->x34_scale.y))
                        {
                            ft_8007C2E0(fp1, hit, fp, throw_hitbox);
                        } else {
                            lbColl_800089B8(throw_hitbox, fp1);
                            lbColl_800089B8(hit, fp);
                        }
                    }
                }
            }
        }
    }
}

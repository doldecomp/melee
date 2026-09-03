#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0852.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Landing.h"

#include "ftKirby/forward.h"

#include "it/kinds/itkirbyhammer.h"
#include "lb/lb_00B0.h"

#include <stddef.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>

char ftKb_Init_803CB510[] = "Other Dead_Proc Existence";
char ftKb_Init_803CB52C[] = "ftkirbyspecials.c";

char ftKb_Init_804D3DB0[2] = "0";

void ftKb_SpecialAirLw_800F539C(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->u.kb.hat.x0 = 0;
}

static inline void fn_800F53AC_SpawnEffect(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 ef_id;
    if (fp->ground_or_air == GA_Air) {
        ef_id = 0x497;
    } else {
        ef_id = 0x496;
    }
    efSync_Spawn(ef_id, gobj, fp->parts[FtPart_HipN].joint, &fp->facing_dir);
    fp->x2219_b0 = true;
    Fighter_SetEffectHitlagCallbacks(fp);
}

static inline void fn_800F53AC_CleanupItem(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Item_GObj* item = fp->u.kb.hat.x0;
    if (item != NULL) {
        it_802ADC34(item);
        fp->u.kb.hat.x0 = NULL;
    }
}

void fn_800F53AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;

    if (fp->cmd_vars[0] == 1) {
        f32 dir;
        lb_8000B1CC(fp->parts[FtPart_R3rdNa].joint, NULL, &pos);
        dir = fp->facing_dir;
        fp->u.kb.hat.x0 =
            it_802ADC54(gobj, &pos, FtPart_R3rdNa, fp->ground_or_air, dir);
        fp->x1984_heldItemSpec = fp->u.kb.hat.x0;
        fp->cmd_vars[0] = 0;
        if (fp->u.kb.hat.x0 != NULL) {
            if (fp->death2_cb != NULL && fp->death2_cb != ftKb_Init_800EE74C) {
                OSReport(ftKb_Init_803CB510);
                __assert(ftKb_Init_803CB52C, 0x66, ftKb_Init_804D3DB0);
            }
            fp->death2_cb = ftKb_Init_800EE74C;
            fp->take_dmg_cb = ftKb_Init_800EE7B8;
            fn_800F53AC_SpawnEffect(gobj);
        }
    }
    if (fp->cmd_vars[0] == 2) {
        fn_800F53AC_CleanupItem(gobj);
        fp->cmd_vars[0] = 0;
    }
}

void ftKb_SpecialAirLw_800F5524(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.x0 != NULL) {
        it_802ADC34(fp->u.kb.hat.x0);
        fp->u.kb.hat.x0 = NULL;
    }
}

void ftKb_SpecialS_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &fn_800F53AC;
}

void ftKb_SpecialAirS_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(8);
    fp->cmd_vars[0] = 0;
    if (!fp->u.kb.x64) {
        fp->self_vel.y = da->specials_aerial_vertical_momentum;
        fp->u.kb.x64 = true;
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = &fn_800F53AC;
}

void ftKb_SpecialS_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialAirS_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(0x08);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialS_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirS_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialS_Coll(Fighter_GObj* gobj)
{
    Fighter* fp;
    if (ft_80082708(gobj) != 0) {
        return;
    }
    fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.x0 != NULL) {
        it_802ADC34(fp->u.kb.hat.x0);
        fp->u.kb.hat.x0 = NULL;
    }
    ftCo_Fall_Enter(gobj);
}

void ftKb_SpecialAirS_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (ft_80081D0C(gobj)) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        if (fp2->u.kb.hat.x0 != NULL) {
            it_802ADC34(fp2->u.kb.hat.x0);
            fp2->u.kb.hat.x0 = NULL;
        }
        fp->u.kb.x64 = false;
        ftCo_LandingFallSpecial_Enter(gobj, 0, da->specials_landing_lag);
    }
}

void ftKb_SpecialN_800F5800(HSD_GObj* gobj, Vec3* vec)
{
    Fighter* ft = GET_FIGHTER(gobj);
    *vec = ft->cur_pos;
}

void ftKb_SpecialN_800F5820(Fighter_GObj* gobj,
                            ftCollisionBox* victim_coll_box,
                            float victim_scale_x)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    victim_coll_box->top = da->specialn_unk1 * victim_scale_x;
    victim_coll_box->bottom =
        da->specialn_swallow_star_y_release * victim_scale_x;
    victim_coll_box->left.x = da->specialn_unk2 * victim_scale_x;
    victim_coll_box->left.y = da->specialn_unk3 * victim_scale_x;
    victim_coll_box->right.x = da->specialn_unk4 * victim_scale_x;
    victim_coll_box->right.y = da->specialn_unk5 * victim_scale_x;
}

void ftKb_SpecialN_800F5874(Vec2* arg0)
{
    ftCommonData* cd = gFtDataList[FTKIND_KIRBY]->ext_attr;
    arg0->x = cd->x9C_radians;
    arg0->y = cd->xA0_radians;
}

HSD_Joint* ftKb_SpecialN_800F5898(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* ca = fp->ft_data;
    return M2C_FIELD(&ca->x48_items[0], HSD_Joint**, 0x10);
}

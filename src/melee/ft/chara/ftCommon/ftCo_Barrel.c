#include "ftCo_Barrel.h"

#include "ftCo_CaptureCut.h"
#include "ftCo_Throw.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_Damage.h"
#include "ftCommon/ftCo_Lift.h"
#include "ftCommon/inlines.h"
#include "ftCommon/types.h"
#include "it/items/ittarucann.h"
#include "lb/lbcollision.h"
#include "mp/mpcoll.h"

/* 0C9290 */ static void fn_800C9290(Fighter_GObj* gobj);

void ftCo_Barrel_Death2_Cb(Fighter_GObj* gobj)
{
    ftCo_Barrel_Take_Dmg_Cb(gobj);
}

void ftCo_Barrel_Enter(Fighter_GObj* gobj, Item_GObj* item_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Barrel, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->death2_cb = ftCo_Barrel_Death2_Cb;
    fp->accessory1_cb = ftCo_Barrel_Accessory1_Cb;
    fp->take_dmg_cb = ftCo_Barrel_Take_Dmg_Cb;
    fp->x221D_b5 = true;
    fp->mv.co.barrel.x0 = it_802960B8(item_gobj);
    fp->mv.co.barrel.x4 = it_802960CC(item_gobj);
    fp->mv.co.barrel.x8 = item_gobj;
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2FC(gobj);
    fp->x1988 = 2;
    fp->invisible = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007EFC0(fp, 1U);
    ftColl_800787B4(fp->mv.co.barrel.x8, gobj, 0);
}

void ftCo_Barrel_Take_Dmg_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_80295F38(fp->mv.co.barrel.x8);
}

void ftCo_Barrel_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.barrel.x0 != 0) {
        fp->mv.co.barrel.x0 -= 1;
        if (fp->mv.co.barrel.x0 == 0) {
            it_80295F38(fp->mv.co.barrel.x8);
        }
    }
}

void ftCo_Barrel_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.co.barrel.x4 != 0) {
        fp->mv.co.barrel.x4 -= 1;
    }

    if (fp->mv.co.barrel.x4 == 0 && fp->input.x668 & HSD_PAD_AB) {
        it_80295F38(fp->mv.co.barrel.x8);
    }
}

void ftCo_Barrel_Phys(Fighter_GObj* gobj) {}

void ftCo_Barrel_Coll(Fighter_GObj* gobj) {}

void ftCo_Barrel_Accessory1_Cb(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    it_8026C334(fp->mv.co.barrel.x8, &fp->cur_pos);
}

void fn_800C9290(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_GObj* owner = it_8026BC78(fp->mv.co.barrel.x8);
    if (ftLib_80086960(owner)) {
        ftColl_8007B8CC(fp, owner);
    }
}

void ftCo_800C92E4(Fighter_GObj* gobj, Vec3* arg1, Vec3* arg2,
                   lbColl_80008D30_arg1* arg3, float kb_angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct SmallerHitCapsule hit;

    {
        HSD_JObj* jobj = GET_JOBJ(gobj);
        Vec3 sp_vec1;
        Vec3 sp_vec2;
        HSD_JObjGetTranslation(jobj, &sp_vec1);
        ftLib_800866DC(gobj, &sp_vec2);
        fp->cur_pos.x = (arg1->x + sp_vec1.x) - sp_vec2.x;
        fp->cur_pos.y = (arg1->y + sp_vec1.y) - sp_vec2.y;
        fp->cur_pos.z = 0.0F;
    }

    mpColl_80043680(&fp->coll_data, arg2);
    lbColl_80008D30((HitCapsule*) &hit, arg3);
    ftCo_Barrel_ApplyKnockback(fp, kb_angle, (HitCapsule*) &hit);
    ftColl_800787B4(fp->mv.co.barrel.x8, gobj, 0);
    fp->x21EC = fn_800C9290;
    ftCo_8008DCE0(gobj, 0x5B, 0.0F);
}

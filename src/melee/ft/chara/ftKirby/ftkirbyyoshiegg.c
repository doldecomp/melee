#include "ftkirbyyoshiegg.h"

#include "types.h"

#include <placeholder.h>

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Bury.h"
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

#include "ftKirby/ftkirby.h"
#include "ftKirby/ftkirbyspecialdonkey.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/random.h>
#include <MSL/math.h>

static void fn_8010AA64(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    if (fp->mv.co.yoshiegg.x14 <= 0.0f) {
        Fighter_UpdateModelScale(gobj);
        fp->accessory4_cb = NULL;
        return;
    }
    fp->mv.co.yoshiegg.x14 -= 1.0f;
    {
        Vec3 vec1, vec0;
        f32 temp0 = (fp->mv.co.yoshiegg.x10 - fp->mv.co.yoshiegg.x14) /
                    fp->mv.co.yoshiegg.x10;
        temp0 *= fp->mv.co.yoshiegg.xC;
        {
            f32 temp1 = (1.0f - fp->mv.co.yoshiegg.xC) + temp0;
            vec1.x = vec1.y = vec1.z = temp1;
            vec0 = vec1;
            vec1.x = vec1.x * fp->mv.co.yoshiegg.x18.x;
            vec1.y *= fp->mv.co.yoshiegg.x18.y;
            vec1.z *= fp->mv.co.yoshiegg.x18.z;
            HSD_JObjSetScale(jobj, &vec1);
            vec0.x = vec0.x * fp->mv.co.yoshiegg.scale.x;
            vec0.y *= fp->mv.co.yoshiegg.scale.y;
            vec0.z *= fp->mv.co.yoshiegg.scale.z;
            HSD_JObjSetScale(fp->x20A0_accessory, &vec0);
        }
    }
}

static inline void inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftHurtboxInit hurt;
    ftColl_8007B0C0(gobj, Intangible);
    hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_TransN);
    hurt.height = HurtHeight_Mid;
    hurt.is_grabbable = false;
    hurt.a_offset = fp->co_attrs.xBC.x4;
    hurt.b_offset = fp->co_attrs.xBC.x10;
    hurt.scale = fp->co_attrs.xBC.x1C;
    ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
}

void ftKb_SpecialNYs_8010AC78(Fighter_GObj* victim, Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(victim);
    HSD_JObj* jobj = victim->hsd_obj;
    Vec3 scale;

    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
    Fighter_ChangeMotionState(victim, ftCo_MS_KirbyYoshiEgg, Ft_MF_Unk06, 0.0f,
                              1.0f, 0.0f, gobj);
    fp->take_dmg_cb = fn_8010B1D4;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->invisible = true;
    scale.x = scale.y = scale.z = fp->co_attrs.xBC.size;
    ftCommon_SetAccessory(fp, (HSD_Joint*) ftKb_SpecialNYs_801093A0());
    HSD_JObjSetScale(fp->x20A0_accessory, &scale);
    lb_8000C2F8(HSD_JObjGetChild(fp->x20A0_accessory),
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].joint);
    fp->mv.co.yoshiegg.scale = scale;
    inlineB0(victim);
    ftKb_SpecialNYs_80109260(gobj, &fp->self_vel);
    fp->facing_dir = ftKb_SpecialNYs_80109290(gobj);
    fp->dmg.x182c_behavior = ftKb_SpecialNYs_8010929C(gobj);
    fp->mv.ca.specialhi.vel.y = 0.0f;
    fp->mv.co.yoshiegg.x0 = gobj;
    fp->take_dmg_2_cb = fn_8010B16C;
    ftCommon_8007EFC0(fp, 1);
    fp->mv.co.walk.fast_anim_frame = ftKb_SpecialNYs_801092BC(gobj);
    fp->mv.co.common.x14 = fp->mv.co.walk.fast_anim_frame;
    fp->mv.co.common.x4.z = ftKb_SpecialNYs_801092AC(gobj);
    ftCommon_InitGrab(fp, 0, ftKb_SpecialNYs_801092CC(gobj));
    HSD_JObjGetScale(jobj, &fp->mv.co.yoshiegg.x18);
    fp->accessory4_cb = fn_8010AA64;
}

#pragma dont_inline on
void ftCo_KirbyYoshiEgg_Anim(Fighter_GObj* gobj)
{
    f32 temp_ret;
    Fighter* fp = gobj->user_data;
    PAD_STACK(16);
    temp_ret = ftKb_SpecialNYs_801092DC();
    fp->grab_timer -= temp_ret;
    fp->mv.kb.specialhi.x4 = ftCommon_GrabMash(fp, ftKb_SpecialNYs_801092F4());
    if (fp->grab_timer <= 0.0f) {
        Fighter* fp2;
        ftCo_DatAttrs_xBC_t* xBCp;
        ft_PlaySFX(fp, 0x44618, 0x7F, 0x40);
        fp2 = gobj->user_data;
        efAsync_Spawn(gobj, &fp2->x60C, 4, 0x4CF, fp->parts[0].joint,
                      (xBCp = &fp->co_attrs.xBC));
        ftKb_SpecialNYs_80109354(&fp->self_vel);
        ftCommon_8007D5D4(fp);
        ftColl_8007B760(gobj, ftKb_SpecialNYs_8010933C());
        ftCo_Fall_Enter_YoshiEgg_Kirby(gobj);
        return;
    }
    if (fp->mv.kb.specialhi.x8.f) {
        fp->mv.kb.specialhi.x8.f--;
        if (fp->mv.kb.specialhi.x8.f <= 0.0f && fp->mv.kb.specialhi.x4 == 0) {
            ftAnim_SetAnimRate(gobj, 1.0f);
            fp->mv.kb.specialhi.x8.f = 0.0f;
        }
    }
    if (fp->mv.kb.specialhi.x8.f <= 0.0f && fp->mv.kb.specialhi.x4 != 0) {
        fp->mv.kb.specialhi.x8.f = ftKb_SpecialNYs_8010930C();
        ftAnim_SetAnimRate(gobj, ftKb_SpecialNYs_80109324());
    }
}
#pragma dont_inline reset

void ftCo_KirbyYoshiEgg_IASA(Fighter_GObj* gobj) {}

void ftCo_KirbyYoshiEgg_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((enum GroundOrAir) fp->ground_or_air == GA_Ground) {
        ft_80084F3C(gobj);
        return;
    }
    ft_80084DB0(gobj);
}

void ftCo_KirbyYoshiEgg_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((enum GroundOrAir) fp->ground_or_air == GA_Ground) {
        ft_8008403C(gobj, fn_8010B148);
        return;
    }
    ft_80082C74(gobj, fn_8010B124);
}

void fn_8010B124(Fighter_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
}

void fn_8010B148(Fighter_GObj* gobj)
{
    ftCommon_8007D5D4(GET_FIGHTER(gobj));
}

#pragma dont_inline on
void fn_8010B16C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->grab_timer -= fp->dmg.x1838_percentTemp * ftKb_SpecialNYs_80109380();
    if ((s32) fp->dmg.x18CC == 3 && ftCo_800C0C88(fp->dmg.x18D0) != 0) {
        fp->grab_timer = 0.0f;
    }
    fp->x1828 = 4;
}
#pragma dont_inline reset

void fn_8010B1D4(Fighter_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
}

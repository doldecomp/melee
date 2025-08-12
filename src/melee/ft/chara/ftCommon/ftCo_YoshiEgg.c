#include "ftCo_YoshiEgg.h"

#include "ftCo_Bury.h"
#include "ftCo_CaptureKoopa.h"

#include <platform.h>

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/types.h"
#include "ftYoshi/ftYs_Guard.h"
#include "ftYoshi/ftYs_SpecialN.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 09D7E4 */ static void ftCo_800BBC88(Fighter_GObj* gobj);
/* 0BBCC0 */ static void ftCo_800BBCC0(Fighter_GObj* gobj);

float const ftCo_804D8B68 = 0;
float const ftCo_804D8B6C = 1;
extern char* ftCo_804D3B88;
extern char* ftCo_804D3B90;
extern char* ftCo_804D3B98;

#pragma force_active on

void ftCo_800BBC88(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b0 = true;
    ftColl_8007B62C(gobj, 2);
}

void ftCo_800BBCC0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj1 = gobj->hsd_obj;
    if (fp->mv.co.yoshiegg.x14 <= 0) {
        Fighter_UpdateModelScale(gobj);
        fp->accessory4_cb = NULL;
        return;
    }
    fp->mv.co.yoshiegg.x14 -= 1;
    {
        Vec3 vec1, vec0;
        float temp0 = (fp->mv.co.yoshiegg.x10 - fp->mv.co.yoshiegg.x14) /
                      fp->mv.co.yoshiegg.x10;
        temp0 *= fp->mv.co.yoshiegg.xC;
        {
            float temp1 = (1 - fp->mv.co.yoshiegg.xC) + temp0;
            vec1.x = vec1.y = vec1.z = temp1;
            vec0 = vec1;
            vec1.x = vec1.x * fp->mv.co.yoshiegg.x18.x;
            vec1.y *= fp->mv.co.yoshiegg.x18.y;
            vec1.z *= fp->mv.co.yoshiegg.x18.z;
            HSD_JObjSetScale(jobj1, &vec1);
            vec0.x = vec0.x * fp->mv.co.yoshiegg.scale.x;
            vec0.y *= fp->mv.co.yoshiegg.scale.y;
            vec0.z *= fp->mv.co.yoshiegg.scale.z;
            HSD_JObjSetScale(fp->x20A0_accessory, &vec0);
        }
    }
}

void ftCo_800BBED4(Fighter_GObj* gobj, Fighter_GObj* arg1)
{
    Vec3 scale;
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_YoshiEgg, Ft_MF_Unk06, 0, 1, 0,
                              arg1);
    fp->take_dmg_cb = ftCo_800BC438;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221E_b0 = true;
    scale.x = scale.y = scale.z = fp->co_attrs.xBC.size;
    ftCommon_SetAccessory(fp, ftYs_SpecialN_8012CDD4(arg1));
    HSD_JObjSetScale(fp->x20A0_accessory, &scale);
    fp->mv.co.yoshiegg.scale = scale;
    lb_8000C2F8(fp->x20A0_accessory == NULL ? NULL
                                            : fp->x20A0_accessory->child,
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].joint);
    {
        ftCo_DatAttrs_xBC_t* temp_r27;
        Fighter* fp = GET_FIGHTER(gobj);
        ftHurtboxInit hurt;
        PAD_STACK(16);

        ftColl_8007B0C0(gobj, Intangible);
        temp_r27 = &fp->co_attrs.xBC;
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_TransN);
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = false;
        hurt.a_offset = temp_r27->x4;
        hurt.b_offset = temp_r27->x10;
        hurt.scale = temp_r27->x1C;
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }
    ftYs_Shield_8012CC94(arg1, &fp->self_vel);
    fp->facing_dir = ftYs_Shield_8012CCC4(arg1);
    fp->dmg.x182c_behavior = ftYs_Shield_8012CCD0(arg1);
    fp->mv.ca.specialhi.vel.y = 0;
    fp->mv.co.yoshiegg.x0 = arg1;
    fp->take_dmg_2_cb = ftCo_800BC3D0;
    ftCommon_8007EFC0(fp, 1);
    fp->mv.co.yoshiegg.x10 = ftYs_Shield_8012CCF0(arg1);
    fp->mv.co.yoshiegg.x14 = fp->mv.co.walk.fast_anim_frame;
    fp->mv.co.yoshiegg.xC = ftYs_Shield_8012CCE0(arg1);
    ftCommon_InitGrab(fp, 0, ftYs_Shield_8012CD00(arg1));
    HSD_JObjGetScale(jobj, &fp->mv.co.yoshiegg.x18);
    fp->accessory4_cb = ftCo_800BBCC0;
}

void ftCo_YoshiEgg_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= ftYs_SpecialN_8012CD10(gobj);
    fp->mv.co.yoshiegg.x4 = ftCommon_8007DC08(fp, ftYs_SpecialN_8012CD28());
    if (fp->grab_timer <= 0) {
        ft_PlaySFX(fp, 280088, 127, 64);
        {
            HSD_JObj* jobj = fp->parts[FtPart_TopN].joint;
            ftCo_DatAttrs* ca = &fp->co_attrs;
            ftCo_DatAttrs_xBC_t* ca_xBC = &ca->xBC;
            efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 4, 1231, jobj,
                          ca_xBC);
            ftYs_SpecialN_8012CD88(&fp->self_vel);
        }
        ftCommon_8007D5D4(fp);
        Fighter_UpdateModelScale(gobj);
        ftColl_8007B760(gobj, ftYs_SpecialN_8012CD70());
        ftCo_Fall_Enter_YoshiEgg(gobj);
        return;
    }
    if (fp->mv.co.yoshiegg.x8) {
        fp->mv.co.yoshiegg.x8 -= 1;
        if (fp->mv.co.yoshiegg.x8 <= 0 && !fp->mv.co.yoshiegg.x4) {
            ftAnim_SetAnimRate(gobj, 1);
            fp->mv.co.yoshiegg.x8 = 0;
        }
    }
    if (fp->mv.co.yoshiegg.x8 <= 0 && fp->mv.co.yoshiegg.x4) {
        fp->mv.co.yoshiegg.x8 = ftYs_SpecialN_8012CD40();
        ftAnim_SetAnimRate(gobj, ftYs_SpecialN_8012CD58());
    }
}

void ftCo_YoshiEgg_IASA(Fighter_GObj* gobj) {}

void ftCo_YoshiEgg_Phys(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->ground_or_air == GA_Ground) {
        ft_80084F3C(gobj);
    } else {
        ft_80084DB0(gobj);
    }
}

void ftCo_YoshiEgg_Coll(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->ground_or_air == GA_Ground) {
        ft_8008403C(gobj, ftCo_800BC3AC);
    } else {
        ft_80082C74(gobj, ftCo_800BC388);
    }
}

void ftCo_800BC388(Fighter_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
}

void ftCo_800BC3AC(Fighter_GObj* gobj)
{
    ftCommon_8007D5D4(GET_FIGHTER(gobj));
}

void ftCo_800BC3D0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer =
        -(fp->dmg.x1838_percentTemp * ftYs_SpecialN_8012CDB4(gobj) -
          fp->grab_timer);
    if (fp->dmg.x18CC == 3 && ftCo_800C0C88(fp->dmg.x18D0)) {
        fp->grab_timer = 0;
    }
    fp->x1828 = 4;
}

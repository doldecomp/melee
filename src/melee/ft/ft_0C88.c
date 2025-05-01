#include <placeholder.h>

#include <dolphin/mtx/forward.h>

#include "ft/ft_0C88.h"

#include "common_structs.h"

#include "ft/chara/ftCommon/ftCo_Attack1.h"
#include "ft/chara/ftCommon/ftCo_AttackHi3.h"
#include "ft/chara/ftCommon/ftCo_AttackHi4.h"
#include "ft/chara/ftCommon/ftCo_AttackLw3.h"
#include "ft/chara/ftCommon/ftCo_AttackLw4.h"
#include "ft/chara/ftCommon/ftCo_AttackS3.h"
#include "ft/chara/ftCommon/ftCo_AttackS4.h"
#include "ft/chara/ftCommon/ftCo_DamageFall.h"
#include "ft/chara/ftCommon/ftCo_DownBound.h"
#include "ft/chara/ftCommon/ftCo_Guard.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_SpecialS.h"
#include "ft/chara/ftCrazyHand/ftCh_Init.h"
#include "ft/chara/ftMasterHand/ftMh_Damage_0.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"

// #include "ft/ftchangeparam.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/ftmetal.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "gm/gm_1601.h"
#include "it/items/ittarucann.h"
#include "lb/lbbgflash.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <baselib/gobj.h>

// allocate common fighter?
void ftCo_800C884C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->x2040 = HSD_ObjAlloc(&Fighter_80459080);
    ftParts_80074148();
    ft_800C85B8(gobj);
    ftParts_80074170();
}

// some sort of initalization
void ftCo_800C88A0(ftCo_Fighter* fp)
{
    fp->x2226_b4 = 0;
    fp->x2226_b5 = 0;
    fp->smash_attrs.x2134_vibrateFrame = 0;
    fp->x2030 = 0;
    fp->x2226_b7 = 0;
}

void ftCo_800C88D4(ftCo_GObj* gobj, u32 cloakingDeviceDurationFrames,
                   bool pickingUpItem)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    void* unused; // needed to match

    fp->x2030 = cloakingDeviceDurationFrames;
    if (!fp->x2226_b4 || fp->x2226_b7) {
        fp->x2226_b4 = 1;
        ftOnCloakingDevice(gobj);
        if (pickingUpItem)
        { // this is passed in as false if transforming (ie sheik/zelda)
            ftCo_800C8B2C(fp, 0x7C, 0); // currently unsure of function
            return;
        }
        ft_800C0098(fp); // also unsure
    }
}

void ftCo_800C89A0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    void* unused; // needed for matching

    fp->x2226_b4 = 0;
    fp->x2226_b5 = 0;
    fp->smash_attrs.x2134_vibrateFrame = 0;
    fp->x2030 = 0; // sets cloakingDeviceDurationFrames to zero
    fp->x2226_b7 = 0;
    fp->x2226_b4 = fp->x2226_b3;
    if (fp->x2226_b4) {
        ftOnCloakingDevice(gobj);
    }
    ft_800C0098(fp); // unsure of function
}

void ftCo_800C8A64(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->x2030 = 0; // set cloaking device frames to zero
    if (!fp->x2226_b3) {
        fp->x2226_b4 = 0;
        fp->x2226_b5 = 0;
        fp->smash_attrs.x2134_vibrateFrame = 0;
        fp->x2030 = 0;
        fp->x2226_b7 = 0;
        ft_800C0098(fp);
        ft_800C8170(fp);
        lbRefract_80022BD0();
        fp->x221F_b2 = 0;
    }
}

void ftCo_800C8AF0(ftCo_Fighter* fp)
{
    if (fp->x2226_b5) {
        lbRefract_800225D4();
    }
}

void fn_800C8B1C(ftCo_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.x2134_vibrateFrame = 0;
}

int ftCo_800C8B2C(ftCo_Fighter* fp, int arg1, int arg2)
{
    if (!fp->x2226_b6) {
        return ftCo_800BFFD0(fp, arg1, arg2);
    }
    return 0;
}

void ftCo_800C8B60(ftCo_Fighter* fp, bool unk1, s8 unk2)
{
    fp->x2226_b5 = unk1;
    fp->smash_attrs.x2134_vibrateFrame = unk2;
}

void ftCo_800C8B74(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftPickDownSpot(fp), Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->mv.co.downspot.x4 = 0;
}

void ftCo_DownSpot_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80097E8C(gobj);
    }
}

void ftCo_DownSpot_IASA(ftCo_GObj* gobj) {}

void ftCo_DownSpot_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownSpot_Coll(ftCo_GObj* gobj)
{
    ft_80083F88(gobj);
}

bool ftCo_800C8C84(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2224_b2 && fp->x2225_b7 && !fp->dmg.x18F0 &&
        !Player_GetRemainingHPByIndex(fp->player_id, fp->x221F_b4))
    {
        fn_800C8E74(gobj);
        return true;
    }
    return false;
}

#pragma push
#pragma dont_inline on
void ftCo_800C8D00(ftCo_GObj* gobj)
{
    FtSFX* sfx;
    ftCo_Fighter* fp;
    ftCo_GObj* victim;
    void* unused; // required to match

    if ((fp = gobj->user_data)->x2224_b3) {
        if (!fp->x2224_b2) {
            sfx = fp->ft_data->x4C_sfx;
            fp->x2224_b2 = 1;
            Fighter_ResetInputData_80068854(gobj);
            ftCo_800BFFD0(fp, 0x7A, 0);
            fn_800C8E40(fp, sfx);
            fp->x2225_b6 = 1;
            lbBgFlash_80021C48(0xEU, 0U);
            gm_80167470(fp->player_id, fp->x221F_b4);
        }
        ftCommon_8007DB58(gobj);
        ftCo_8009750C(gobj);
        {
            // this area is pretty messy.
            // it was very annoying to get it to match...
            ftCo_GObj* victim = fp->victim_gobj;
            if (fp->victim_gobj) {
                if (fp->x221B_b5) {
                    ftCo_800DC750(victim);
                } else {
                    ftCo_GObj* victim_again = fp->victim_gobj;
                    ftCo_800DC750(gobj);
                    ftCo_800DA698(victim_again, false);
                }
                ftCommon_8007DB58(victim);
            }
        }
        if (GA_Air == fp->ground_or_air) {
            ftCo_80090780(gobj);
        } else {
            ftCo_800C8B74(gobj);
        }
        fp->x2224_b3 = 0;
    }
}
#pragma pop

void fn_800C8E40(ftCo_Fighter* fp, FtSFX* unused)
{
    ft_80088148(fp, fp->ft_data->x4C_sfx->xC, 0x7F, 0x40);
}

void fn_800C8E74(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp;
    fp = GET_FIGHTER(gobj);
    if ((fp->kind == FTKIND_MASTERH) || (fp->kind == FTKIND_CREZYH)) {
        if (fp->kind == FTKIND_MASTERH) {
            ftMh_MS_343_80151484(gobj);
        } else {
            ftCh_GrabUnk1_8015ADD0(gobj);
        }
        gm_80167470(fp->player_id, fp->x221F_b4);
        return;
    }
    fp->x2224_b3 = 1;
    if (0.0F == fp->dmg.kb_applied) {
        fp = GET_FIGHTER(gobj);
        fp->x2224_b2 = 1;
        Fighter_ResetInputData_80068854(gobj);
        ftCo_800BFFD0(fp, 0x7A, 0);
        ft_80088148(fp, fp->ft_data->x4C_sfx->xC, 0x7F, 0x40);
        fp->x2225_b6 = 1;
        lbBgFlash_80021C48(0xEU, 0U);
        gm_80167470(fp->player_id, fp->x221F_b4);
    }
}

void ftCo_800C8F6C(void)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(HSD_JObjLoadJoint(Fighter_804D6504));
    HSD_MObj* mobj = ft_804D6588 = dobj ? dobj->mobj : NULL;
    if (mobj->mat) {
        mobj->mat->diffuse = p_ftCommonData->x7D8_gxcolor;
    }
}

void ftCo_800C8FC4(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetMoreFlagsBit0(fp->player_id)) {
        fp->x2034 = p_ftCommonData->x7DC;
        fp->x2038 = p_ftCommonData->x7E0;
        fp->x2227_b3 = 1;
        ft_800C80A4(fp);
        ftCommon_80080460(fp);
    }
}

void ftCo_800C9034(ftCo_GObj* gobj)
{
    ftCo_800D4F24(gobj, 0);
}

void fn_800C9058(ftCo_GObj* gobj)
{
    fn_800C9198(gobj);
}

void ftCo_800C9078(ftCo_GObj* gobj, Item_GObj* itemGobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    ;
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Barrel, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->death2_cb = fn_800C9058;
    fp->accessory1_cb = fn_800C9264;
    fp->take_dmg_cb = fn_800C9198;
    fp->x221D |= 4;
    fp->mv.co.barrel.datAttr_x2C = it_802960B8(itemGobj);
    fp->mv.co.barrel.datAttr_x28 = it_802960CC(itemGobj);
    fp->mv.co.barrel.item_gobj = itemGobj;
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2FC(gobj);
    fp->x1988 = 2;
    fp->x221E_b0 = 1;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftCommon_8007EFC0(fp, 1U);
    ftColl_800787B4(fp->mv.co.barrel.item_gobj, gobj, 0);
}

void fn_800C9198(ftCo_GObj* gobj)
{
    it_80295F38(GET_FIGHTER(gobj)->mv.co.barrel.item_gobj);
}

void ftCo_Barrel_Anim(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.barrel.datAttr_x2C) {
        fp->mv.co.barrel.datAttr_x2C -= 1;
        if (!fp->mv.co.barrel.datAttr_x2C) {
            it_80295F38(fp->mv.co.barrel.item_gobj);
        }
    }
}

void ftCo_Barrel_IASA(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp;

    fp = gobj->user_data;
    if (fp->mv.co.barrel.datAttr_x28) {
        fp->mv.co.barrel.datAttr_x28 -= 1;
    }
    if ((!fp->mv.co.barrel.datAttr_x28) && (fp->input.x668 & HSD_PAD_AB)) {
        it_80295F38(fp->mv.co.barrel.item_gobj);
    }
}

void ftCo_Barrel_Phys(ftCo_GObj* gobj) {}

void ftCo_Barrel_Coll(ftCo_GObj* gobj) {}

void fn_800C9264(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    it_8026C334(fp->mv.co.barrel.item_gobj, &fp->cur_pos);
}

void fn_800C9290(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* item_gobj = it_8026BC78(fp->mv.co.barrel.item_gobj);
    if (ftLib_80086960(item_gobj)) {
        ftColl_8007B8CC(fp, item_gobj);
    }
}

/* rough, look at later
void ftCo_800C92E4(HSD_GObj* arg0, void* arg1, Vec3* arg2, s32 arg3, f32 arg8)
{
    HitCapsule sp3C;
    s32 sp38;
    f32 sp34;
    f32 sp30;
    Vec3 sp24;
    Fighter* temp_r30;
    f32 var_f31;
    void* temp_r31;

    var_f31 = arg8;
    temp_r31 = arg0->hsd_obj;
    temp_r30 = arg0->user_data;
    if (temp_r31 == NULL) {
        __assert(ftCo_804D3C98, 0x3D3U, ftCo_804D3CA0);
    }
    sp30 = temp_r31->unk38;
    sp34 = temp_r31->unk3C;
    sp38 = temp_r31->unk40;
    ftLib_800866DC(arg0, &sp24);
    temp_r30->cur_pos.x = (arg1->unk0 + sp30) - (bitwise f32) sp24;
    temp_r30->cur_pos.y = (arg1->unk4 + sp34) - sp24.y;
    temp_r30->cur_pos.z = 0.0f;
    mpColl_80043680(temp_r30 + 0x6F0, arg2);
    lbColl_80008D30(&sp3C, arg3);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (temp_r30->facing_dir < 0.0f) {
    } else {
        var_f31 = 180.0f - var_f31;
    }
    temp_r30->dmg.kb_applied =
        ftColl_80079EA8(temp_r30, &sp3C, (s32) sp3C.unk_count);
    temp_r30->dmg.x1848_kb_angle = (s32) var_f31;
    temp_r30->dmg.facing_dir_1 = temp_r30->facing_dir;
    temp_r30->dmg.x184c_damaged_hurtbox = 0;
    temp_r30->dmg.x1854_collpos.x = temp_r30->cur_pos.x;
    temp_r30->dmg.x1854_collpos.y = temp_r30->cur_pos.y;
    temp_r30->dmg.x1854_collpos.z = temp_r30->cur_pos.z;
    temp_r30->dmg.x1860_element = sp3C.element;
    ftColl_800787B4((bitwise Item_GObj*) temp_r30->mv.ca.specialhi.vel.y,
                    (Fighter_GObj*) arg0, 0);
    temp_r30->x21EC = fn_800C9290;
    ftCo_8008DCE0((Fighter_GObj*) arg0, 0x5B, 0.0f);
}
*/

bool ftCo_Walk_CheckInput(ftCo_GObj* gobj)
{
    void* unused;  // needed to match
    void* unused2; // needed to match

    if (ftWalkCommon_800DFC70(gobj)) {
        fn_800C9528(gobj, 0.0F);
        return true;
    }
    return false;
}

bool ftCo_800C94B4(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);

    if (((fp->input.lstick.x * fp->facing_dir) >= p_ftCommonData->x474) &&
        ftWalkCommon_800DFC70(gobj))
    {
        fn_800C9528(gobj, 0.0F);
        return true;
    }
    return false;
}

/* work on later
void fn_800C9528(Fighter_GObj* gobj, f32 arg1)
{
    Fighter* fp;
    f32* x2DC;
    f32 temp_f2;
    f32 var_f8;

    fp = gobj->user_data;
    var_f8 = 1.0F;
    x2DC = &fp->x2DC;
    if (fp->x2223_b7) {
        var_f8 = *Fighter_804D651C;
    }
    temp_f2 = fp->x34_scale.y;
    if (temp_f2 != 1.0F) {
        var_f8 = ftCo_CalcYScaledKnockback(Fighter_804D6524, var_f8, temp_f2,
                                           Fighter_804D6524->unkC);
    }
    if ((HSD_GObj*) fp->x197C != NULL) {
        var_f8 *= *Fighter_804D6520;
    }
    ftWalkCommon_800DFCA4(gobj, 0xF, 0U, arg1, x2DC->unk0, x2DC->unk4,
                          x2DC->unk8, fp->co_attrs.slow_walk_max,
                          fp->co_attrs.mid_walk_point,
                          fp->co _attrs.fast_walk_min, var_f8);
}
*/

void ftCo_Walk_Anim(ftCo_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftCo_Walk_IASA(ftCo_GObj* gobj)
{
    void* unused;  // needed to match
    void* unused2; // needed to match
    if (!ftCo_Catch_CheckInput(gobj) && !ftCo_SpecialS_CheckInput(gobj) &&
        !ftCo_Attack100_CheckInput(gobj) && !ftCo_800D6824(gobj) &&
        !ftCo_800D68C0(gobj) && !ftCo_AttackS4_CheckInput(gobj) &&
        !ftCo_AttackHi4_CheckInput(gobj) && !ftCo_AttackLw4_CheckInput(gobj) &&
        !ftCo_AttackS3_CheckInput(gobj) && !ftCo_AttackHi3_CheckInput(gobj) &&
        !ftCo_AttackLw3_CheckInput(gobj) && !ftCo_Attack1_CheckInput(gobj) &&
        !ftCo_80091A4C(gobj) && !ftCo_800DE9D8(gobj) &&
        !ftCo_Jump_CheckInput(gobj) && !ftCo_Dash_CheckInput(gobj) &&
        !ftCo_800D5FB0(gobj) && !ft_8008A244(gobj))
    {
        ftWalkCommon_800DFEC8(gobj, fn_800C9528);
    }
}

/// #ftCo_Walk_Phys

/// #ftCo_Walk_Coll

/// #ftCo_800C97A8

/// #ftCo_Turn_CheckInput

/// #ftCo_800C9840

/// #fn_800C98AC

/// #ftCo_800C9924

/// #ftCo_Turn_Anim

/// #ftCo_Turn_IASA

/// #ftCo_Turn_Phys

/// #ftCo_Turn_Coll

/// #fn_800C9C2C

/// #fn_800C9C74

/// #fn_800C9CEC

/// #fn_800C9D40

/// #fn_800C9D94

/// #ftCo_TurnRun_Anim

/// #ftCo_TurnRun_IASA

/// #ftCo_TurnRun_Phys

/// #ftCo_TurnRun_Coll

/// #ftCo_Dash_CheckInput

/// #fn_800CA120

/// #ftCo_Dash_Anim

/// #ftCo_Dash_IASA

/// #ftCo_Dash_Phys

/// #ftCo_Dash_Coll

/// #fn_800CA5F0

/// #fn_800CA644

/// #fn_800CA698

/// #fn_800CA6F4

/// #fn_800CA71C

/// #ftCo_Run_Anim

/// #ftCo_Run_IASA

/// #ftCo_Run_Phys

/// #ftCo_Run_Coll

/// #ftCo_RunDirect_Anim

/// #ftCo_RunDirect_IASA

/// #ftCo_RunDirect_Phys

/// #ftCo_RunDirect_Coll

/// #fn_800CABC4

/// #fn_800CAC18

/// #ftCo_RunBrake_Anim

/// #ftCo_RunBrake_IASA

/// #ftCo_RunBrake_Phys

/// #ftCo_RunBrake_Coll

/// #ftCo_800CAE80

/// #ftCo_Jump_CheckInput

/// #fn_800CAF78

/// #ftCo_800CB024

/// #ftCo_800CB110

/// #fn_800CB250

/// #ftCo_Jump_Anim

/// #ftCo_Jump_IASA

/// #ftCo_800CB438

/// #ftCo_Jump_Phys

/// #ftCo_Jump_Coll

/// #fn_800CB4E0

/// #ftCo_KneeBend_Anim

/// #ftCo_800CB59C

/// #ftCo_KneeBend_IASA

/// #ftCo_KneeBend_Phys

/// #ftCo_KneeBend_Coll

/// #ft_800CB6EC

/// #ft_800CB804

/// #ftCo_800CB870

/// #ftCo_800CB8E0

/// #ftCo_800CB950

/// #ftCo_800CBAC4

/// #ftCo_800CBBC0

/// #ftCo_800CBD18

/// #ftCo_800CBE98

/// #ftCo_800CC0E8

/// #ftCo_800CC238

/// #ftCo_JumpAerial_Anim

/// #fn_800CC3C4

/// #ftCo_JumpAerial_IASA

/// #ftCo_JumpAerial_Phys

/// #fn_800CC654

/// #ftCo_800CC6C8

/// #ftCo_JumpAerial_Coll

/// #ftCo_800CC730

/// #ftCo_800CC830

/// #ftCo_800CC8DC

/// #ftCo_800CC988

/// #ftCo_Fall_Anim

/// #ftCo_800CCAAC

/// #ftCo_800CCBE0

/// #ftCo_Fall_IASA

/// #ftCo_Fall_Phys

/// #ftCo_Fall_Coll

/// #ftCo_800CCDA8

/// #ftCo_FallAerial_Anim

/// #ftCo_FallAerial_IASA

/// #ftCo_FallAerial_Phys

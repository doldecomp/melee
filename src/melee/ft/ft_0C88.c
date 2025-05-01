#include <placeholder.h>

#include <dolphin/mtx/forward.h>

#include "ft/ft_0C88.h"

#include "common_structs.h"

#include "ft/chara/ftCommon/ftCo_DamageFall.h"
#include "ft/chara/ftCommon/ftCo_DownBound.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCrazyHand/ftCh_Init.h"
#include "ft/chara/ftMasterHand/ftMh_Damage_0.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftmetal.h"
#include "ft/ftparts.h"
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
#pragma dont_inline reset

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
    Fighter* fp = GET_FIGHTER(gobj);
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

/// #ftCo_Barrel_Anim

/// #ftCo_Barrel_IASA

void ftCo_Barrel_Phys(ftCo_GObj* gobj) {}

void ftCo_Barrel_Coll(ftCo_GObj* gobj) {}

/// #fn_800C9264

/// #fn_800C9290

/// #ftCo_800C92E4

/// #ftCo_Walk_CheckInput

/// #ftCo_800C94B4

/// #fn_800C9528

/// #ftCo_Walk_Anim

/// #ftCo_Walk_IASA

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

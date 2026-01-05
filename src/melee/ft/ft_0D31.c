#include "ft/ft_0D31.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Throw.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

bool ftCo_800D3158(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int* temp_r29 = &p_ftCommonData->x520;

    if (fp->x222A_b1 || fp->x2228_b5 || fp->x2228_b2) {
        return false;
    }
    if (fp->x2219_b2) {
        return false;
    }
    if (fp->x2219_b1) {
        return false;
    }
    if (fp->cur_pos.x > Stage_GetBlastZoneRightOffset()) {
        ftCo_800D3950(gobj);
        return true;
    }
    if (fp->cur_pos.x < Stage_GetBlastZoneLeftOffset()) {
        ftCo_800D3680(gobj);
        return true;
    }
    if (fp->cur_pos.y > Stage_GetBlastZoneTopOffset() &&
        (fp->ground_or_air == GA_Ground || fp->x2222_b3 ||
         fp->x8c_kb_vel.y > p_ftCommonData->x4F0))
    {
        if (Player_GetMoreFlagsBit5(fp->player_id)) {
            ftCo_800D3E40(gobj);
        } else {
            int temp_r28 = HSD_Randi(100) + 1;
            if (!Camera_8003010C() && *temp_r29 >= temp_r28) {
                if (fp->motion_id == ftCo_MS_DamageIce) {
                    ftCo_800D47B8(gobj);
                } else {
                    ftCo_800D4780(gobj);
                }
            } else if (fp->motion_id == ftCo_MS_DamageIce) {
                ftCo_800D41C4(gobj);
            } else {
                ftCo_800D40B8(gobj);
            }
        }
        return true;
    }
    if (fp->cur_pos.y < Stage_GetBlastZoneBottomOffset()) {
        ftCo_800D3BC8(gobj);
        return true;
    }
    return false;
}

void ftCo_800D331C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->victim_gobj != NULL) {
        if (fp->x221B_b5) {
            Fighter* temp_r3_2 = GET_FIGHTER(fp->victim_gobj);
            if (!temp_r3_2->x221F_b4) {
                temp_r3_2->x2180 = fp->player_id;
            }
        } else if (!fp->x221F_b4) {
            pl_8004065C((u8) ftLib_80086BE0(fp->victim_gobj),
                        ftLib_800874BC(fp->victim_gobj));
        }
    }
    if (fp->x2180 != 6) {
        pl_8004065C(fp->x2180, 0);
    }
    if (fp->death2_cb != NULL) {
        fp->death2_cb(gobj);
    }
    if (fp->death3_cb != NULL) {
        fp->death3_cb(gobj);
    }
    if (fp->death1_cb != NULL) {
        fp->death1_cb(gobj);
    }
    ftCo_800DD100(gobj);
    ftCommon_8007E2FC(gobj);
    if (fp->item_gobj != NULL) {
        Item_8026A8EC(fp->item_gobj);
        fp->item_gobj = NULL;
        pl_8003EA08(fp->player_id, fp->x221F_b4);
        pl_8003EA74(fp->player_id, fp->x221F_b4);
    }
    if (fp->x197C != NULL) {
        ftCommon_8007F8E8(gobj);
        Item_8026A8EC(fp->x197C);
        ftCommon_8007F9B4(gobj);
    }
    if (fp->x1980 != NULL) {
        ftCommon_8007F8E8(gobj);
        Item_8026A8EC(fp->x1980);
        ftCommon_8007FF74(gobj);
    }
    if (fp->is_metal) {
        ftCo_800C8540(gobj);
    }
    if (fp->x2226_b4) {
        ftCo_800C8A64(gobj);
    }
    ftCommon_8007DB24(gobj);
    fp->mv.co.unk_800D331C.x6C = fp->motion_id;
    fp->mv.co.unk_800D331C.x70 = fp->x2070.x2073;
}

void ftCo_800D34E0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Player_SetFallsByIndex(
        fp->player_id, fp->x221F_b4,
        Player_GetFallsByIndex(fp->player_id, fp->x221F_b4) + 1);
    plStale_ResetStaleMoveTableForPlayer(fp->player_id);
    if ((gm_8016B094() || gm_8016B0E8()) &&
        Player_GetEntity(fp->player_id) == gobj)
    {
        Player_LoseStock(fp->player_id);
    }
    if (gm_8016B094() && Player_GetStocks(fp->player_id) <= 0) {
        Player_UpdateMatchFrameCount(fp->player_id, fp->x221F_b4);
    }
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_UpdateKOsBySlot(fp->dmg.x18c4_source_ply, fp->x221F_b4,
                               fp->player_id);
    } else {
        Player_IncSuicideCount(fp->player_id, fp->x221F_b4);
    }
    pl_8003D644(fp->player_id, fp->x221F_b4, fp->mv.co.unk_800D34E0.x6C,
                fp->mv.co.unk_800D34E0.x70);
    Player_SetHPByIndex(fp->player_id, fp->x221F_b4, 0);
}

void ftCo_800D35FC(Fighter* fp)
{
    u8 _[8];
    HSD_GObj* cur_gobj;

    ftCommon_8007EBAC(fp, 5, p_ftCommonData->x4F8);
    cur_gobj = HSD_GObj_Entities->fighters;
    while (cur_gobj != NULL) {
        Fighter* cur_fp = GET_FIGHTER(cur_gobj);
        if (cur_fp != fp && !cur_fp->x221F_b3) {
            ftCommon_8007EBAC(cur_fp, 6, p_ftCommonData->x4FC);
        }
        cur_gobj = cur_gobj->next;
    }
}

#pragma push
#pragma dont_inline on

void ftCo_800D3680(Fighter_GObj* gobj)
{
    Vec3 sp2C;
    f32 sp24;
    Fighter* temp_r27;
    Fighter* temp_r27_2;
    Fighter* temp_r28;
    Fighter* temp_r28_3;
    Fighter* temp_r31;
    FtSFX* temp_r28_2;
    f32 temp_f1;
    f32 temp_f31;
    s32 temp_r29;
    s32 temp_r6;
    s32 var_r3;
    u8* temp_r8;
    u8 temp_r3;
    u8 temp_r4;
    u8 temp_r5;
    u8 temp_r7;
    u8 temp_r8_2;
    u8* temp_r9;

    temp_r27 = gobj->user_data;
    temp_r31 = temp_r27;
    ftCo_800D331C(gobj);
    temp_r27->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, 1, 0U, 0.0F, 1.0F, 0.0F, NULL);
    temp_r28 = gobj->user_data;
    if (temp_r28->x221D_b6) {
        ft_800880D8(temp_r28);
        temp_r28->x2004 = 0;
    }
    temp_r28->x2219_b1 = 1;
    temp_r28->x221E_b1 = 1;
    temp_r28->x221E_b2 = 1;
    pl_8003DF44(temp_r27->player_id, temp_r27->x221F_b2);

    temp_r27_2 = gobj->user_data;
    temp_r28_2 = temp_r27_2->ft_data->x4C_sfx;
    temp_r27_2->invisible = true;
    temp_r27_2->x221F_b1 = 1;
    Camera_80030E44(4, &temp_r27_2->cur_pos);
    ftCo_800D35FC(temp_r27_2);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x4);
    ftCo_800D38B8(temp_r27_2, temp_r28_2->x8);

    ft_PlaySFX(temp_r31, 0x88, 0x7F, 0x40);
    ft_8008805C(temp_r31, 0x88);
    sp2C = temp_r31->cur_pos;
    temp_f31 = Stage_GetBlastZoneTopOffset();
    temp_f1 = Stage_GetBlastZoneBottomOffset();
    if (sp2C.y > temp_f31) {
        sp2C.y = temp_f31;
    }
    if (sp2C.y < temp_f1) {
        sp2C.y = temp_f1;
    }
    sp24 = -1.5707964f;
    temp_r28_3 = gobj->user_data;
    temp_r3 = Player_GetUnk45(temp_r28_3->player_id);
    temp_r8 = &Fighter_804D650C[temp_r3];
    temp_r9 = &Fighter_804D6508[temp_r3];
    temp_r7 = temp_r8[0];
    temp_r4 = temp_r9[0];
    temp_r6 = ((temp_r8[1] << 8) & ~0xFF0000) | ((temp_r7 << 0x10) & 0xFF0000);
    temp_r8_2 = temp_r8[2];
    temp_r5 = temp_r9[2];
    temp_r29 = temp_r5 | (((temp_r9[1] << 8) & ~0xFF0000) |
                          ((temp_r4 << 0x10) & 0xFF0000));
    if (gm_801693BC(temp_r28_3->player_id)) {
        var_r3 = 0x42C;
    } else {
        var_r3 = 0x42B;
    }
    efSync_Spawn(var_r3, gobj, &sp2C, &sp24, &p_ftCommonData->x4F4,
                 temp_r8_2 | temp_r6, temp_r29);
    sp2C.x = Stage_GetBlastZoneLeftOffset();
    ftCo_800D4E50(temp_r31, &sp2C, 1, 0.0F);
}

#pragma pop

void ftCo_800D38B8(Fighter* fp, int arg1)
{
    ft_800881D8(fp, arg1, 0x7F, 0x40);
    if (!fp->x2225_b6) {
        ft_8008805C(fp, arg1);
    }
}

void ftCo_DeadLeft_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadLeft_Cam(Fighter_GObj* gobj) {}

/// #ftCo_800D3950

void ftCo_DeadRight_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadRight_Cam(Fighter_GObj* gobj) {}

/// #ftCo_800D3BC8

void ftCo_DeadDown_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadDown_Cam(Fighter_GObj* gobj) {}

/// #ftCo_800D3E40

void ftCo_DeadUp_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftMaterial_800BFD9C(gobj);
    }
}

void ftCo_DeadUp_Cam(Fighter_GObj* gobj) {}

static inline void ftCo_800D40B8_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221D_b6) {
        ft_800880D8(fp);
        fp->x2004 = false;
    }
    fp->x2219_b1 = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    ft_80088C5C(gobj);
}

void ftCo_800D40B8(Fighter_GObj* gobj)
{
    u8 _[8];
    int* temp_r31 = &p_ftCommonData->x504;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800D331C(gobj);
    fp->mv.co.unk_deadup.x40 = *temp_r31;
    fp->mv.co.unk_deadup.x44 = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStar, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftCo_800D40B8_inline(gobj);
    ftCommon_8007EFC0(fp, true);
    ft_800881D8(fp, fp->ft_data->x4C_sfx->xC, 127, 64);
    pl_8003DF44(fp->player_id, fp->x221F_b4);
    fp->mv.co.unk_deadup.x68 = 0;
}

void ftCo_800D41C4(Fighter_GObj* gobj)
{
    u8 _[8];
    int* temp_r31;
    Fighter* temp_r30;
    Fighter* temp_r28;

    temp_r28 = GET_FIGHTER(gobj);
    temp_r28->x2227_b6 = true;
    temp_r30 = GET_FIGHTER(gobj);
    temp_r31 = &p_ftCommonData->x504;
    ftCo_800D331C(gobj);
    temp_r30->mv.co.unk_deadup.x40 = *temp_r31;
    temp_r30->mv.co.unk_deadup.x44 = 0.0F;
    Fighter_ChangeMotionState(gobj, 5, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftCo_800D40B8_inline(gobj);
    ftCommon_8007EFC0(temp_r30, true);
    ft_800881D8(temp_r30, temp_r30->ft_data->x4C_sfx->xC, 127, 64);
    pl_8003DF44(temp_r30->player_id, temp_r30->x221F_b4);
    ftCo_80090AC0(temp_r28);
    ftCommon_8007EBAC(temp_r28, true, false);
    temp_r28->mv.co.unk_deadup.x68 = 1;
}
/// #ftCo_DeadUpStar_Anim

void ftCo_DeadUpStar_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

/// #ftCo_800D4580

void ftCo_800D4780(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800D4580(gobj, 6);
    fp->mv.co.unk_deadup.x68 = 0;
}

void ftCo_800D47B8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2227_b6 = true;
    ftCo_800D4580(gobj, 9);
    ftCo_80090AC0(fp);
    ftCommon_8007EBAC(fp, 1, 0);
    fp->mv.co.unk_deadup.x68 = 1;
}

/// #ftCo_800D481C

/// #ftCo_DeadUpFall_Anim

/// #ftCo_DeadUpFall_Phys

/// #fn_800D4DD4

void ftCo_DeadUpFall_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

void ftCo_800D4E50(Fighter* fp, Vec3* arg1, int arg2, float arg8)
{
    if (gm_8016B0B4() && !fp->x221F_b4) {
        int coins = Player_GetCoins(fp->player_id);
        int var_r31 = coins / 2;
        Player_SetCoins(fp->player_id, coins - var_r31);
        Player_SetUnk9C(fp->player_id,
                        var_r31 + Player_GetUnk9C(fp->player_id));
        if (var_r31 > p_ftCommonData->x5C8) {
            var_r31 = p_ftCommonData->x5C8;
        }
        it_802E5F8C(fp->gobj, arg1, var_r31, arg2, arg8, p_ftCommonData->x5CC);
    }
}

static inline void ftCo_800D4F24_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);
    if (temp_r31->x221D_b6) {
        ft_800880D8(temp_r31);
        temp_r31->x2004 = 0;
    }
    temp_r31->x2219_b1 = 1;
    temp_r31->x221E_b1 = 1;
    temp_r31->x221E_b2 = 1;
    ftMaterial_800BFD04(gobj);
}

void ftCo_800D4F24(Fighter_GObj* gobj, int index)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221F_b3) {
        return;
    }
    if (index != 0) {
        f32 sp1C = fp->ft_data->x0->x168 * fp->x34_scale.y;
        u8 _[4];
        efSync_Spawn(0x43F, 0, &fp->cur_pos, &sp1C);
    }
    ftCo_800D331C(gobj);
    ftCo_800D4F24_inline(gobj);
}

/// #ftCo_800D4FF4

void ftCo_Rebirth_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_8008A7A8(gobj, fp->ft_data->x24);
    fp->mv.co.unk_deadup.x40--;
    if (fp->mv.co.unk_deadup.x40 == 0) {
        ftCo_800D5600(gobj);
    }
}
void ftCo_Rebirth_IASA(Fighter_GObj* gobj) {}

float const ftCo_804D8FC8 = 0.0f;
float const ftCo_804D8FCC = 1.0f;

void ftCo_Rebirth_Phys(Fighter_GObj* gobj)
{
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    u8 _pad[12];
    Fighter* fp;
    s8 platform;
    Fighter_GObj* other_gobj;
    Fighter* other_fp;
    f32 factor;

    fp = gobj->user_data;
    if (!fp->x221F_b4) {
        platform = fp->smash_attrs.x2135;
        if ((s8) platform != (s8) -1) {
            Stage_80224E38(&sp18, (s8) platform);
            Player_GetSomePos(fp->player_id, &sp24);
            M2C_FIELD(&fp->mv.co.unk_deadup, float*, 0x44 - 0x40) =
                sp18.x + sp24.x + fp->facing_dir * ftCommon_800804EC(fp);
            M2C_FIELD(&fp->mv.co.unk_deadup, float*, 0x48 - 0x40) =
                sp18.y + sp24.y;
            M2C_FIELD(&fp->mv.co.unk_deadup, float*, 0x4C - 0x40) =
                ftCo_804D8FC8;
        }
        ftCommon_8007F8B4(fp, &sp30);
        factor = ftCo_804D8FCC / (f32) fp->mv.co.unk_deadup.x40;
        fp->self_vel.x =
            factor *
            (M2C_FIELD(&fp->mv.co.unk_deadup, float*, 0x44 - 0x40) - sp30.x);
        fp->self_vel.y =
            factor *
            (M2C_FIELD(&fp->mv.co.unk_deadup, float*, 0x48 - 0x40) - sp30.y);
    } else {
        other_gobj = Player_GetEntityAtIndex(fp->player_id, 0);
        other_fp = other_gobj->user_data;
        fp->self_vel.x = other_fp->self_vel.x;
        fp->self_vel.y = other_fp->self_vel.y;
    }
}
void ftCo_Rebirth_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->smash_attrs.x2135 == -1) {
        ft_80083DCC(gobj);
    }
}
static void fn_800D54A4(Fighter_GObj*);
/// #fn_800D54A4

static void fn_800D55B4(Fighter_GObj*);
/// #fn_800D55B4

void ftCo_800D5600(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    mpColl_80043680(&fp->coll_data, &fp->cur_pos);
    fp->self_vel.y = 0.0f;
    fp->mv.co.unk_deadup.x40 = (int) p_ftCommonData->x5D4;
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait,
                              Ft_MF_KeepGfx | Ft_MF_SkipColAnim |
                                  Ft_MF_KeepAccessory | Ft_MF_SkipNametagVis,
                              0.0f, 1.0f, 0.0f, NULL);
    fp->x221E_b5 = true;
    fp->x2219_b6 = true;
    fp->x221E_b6 = true;
    fp->x221D_b2 = true;
    if (!fp->x221F_b4) {
        fp->accessory1_cb = fn_800D54A4;
    } else {
        fp->accessory1_cb = fn_800D55B4;
    }
    if (fp->smash_attrs.x2135 != -1) {
        mpColl_80043680(&fp->coll_data, &fp->cur_pos);
    }
}

static void fn_800D5A30(Fighter_GObj* gobj);

void ftCo_RebirthWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    
    ftCo_8008A7A8(gobj, fp->ft_data->x24);
    fp->mv.co.unk_deadup.x40--;
    if (fp->mv.co.unk_deadup.x40 == 0) {
        ftColl_8007B7A4(gobj, (int)p_ftCommonData->x5D8);
        ftCo_Fall_Enter(gobj);
    }
}
/// #ftCo_RebirthWait_IASA

/// #ftCo_RebirthWait_Phys

static void fn_800D5A30(Fighter_GObj* gobj)
{
    ftColl_8007B7A4(gobj, (int)p_ftCommonData->x5D8);
    ft_8008A2BC(gobj);
}
void ftCo_Rebirth_Cam(Fighter_GObj* gobj)
{
    u8 _0[8];
    Vec3 pos;
    u8 _1[4];
    Fighter* fp = gobj->user_data;
    CmSubject* cam = fp->x890_cameraBox;

    ftCamera_80076018((UnkFloat6_Camera*) fp->ft_data->x3C,
                      (UnkFloat6_Camera*) &pos, fp->x34_scale.y);

    cam->x10.x = *(float*) &fp->mv.co.unk_deadup.x44;
    cam->x10.y = M2C_FIELD(&fp->mv.co.unk_deadup, float*, 0x48 - 0x40) + pos.x;
    cam->x10.z = 0.0f;

    ftLib_800866DC(gobj, &cam->x1C);
}
#include "ft/ft_0D4D.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftwalkcommon.h"
#include "lb/lbvector.h"

#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_AirCatch.h>
#include <melee/ft/chara/ftCommon/ftCo_AppealS.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack100.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackAir.h>
#include <melee/ft/chara/ftCommon/ftCo_EscapeAir.h>
#include <melee/ft/chara/ftCommon/ftCo_Fall.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_JumpAerial.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialAir.h>
#include <melee/ft/chara/ftCommon/ftCo_Squat.h>
#include <melee/ft/chara/ftCommon/ftCo_Turn.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0D31.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/gr/stage.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>

void fn_800D4DD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* temp_r31 = fp;
    f32 bottom_offset;

    switch (temp_r31->mv.co.unk_deadup.x44) {
    case 3:
        bottom_offset = Stage_GetCamBoundsBottomOffset();
        if (temp_r31->cur_pos.y < bottom_offset) {
            ftCommon_8007E2FC(gobj);
        }
        break;
    default:
        break;
    }
}

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

void ftCo_800D4FF4(Fighter_GObj* gobj)
{
    Vec3 sp44;
    Vec3 scale_vec;
    Vec3 pos_vec;
    Vec3 sp20;
    Vec3 sp14;
    u8 _[4];
    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_UnkProcessDeath_80068354(gobj);
    fp->smash_attrs.x2135 = Player_80032F30(fp->player_id);

    if ((s8) fp->smash_attrs.x2135 == -1) {
        Player_GetSpawnPlatformPos(fp->player_id, &sp44);
        fp->mv.co.turn.facing_after =
            fp->facing_dir * ftCommon_800804EC(fp) + sp44.x;
        fp->mv.co.turn.x8 = sp44.y;
        fp->mv.co.walk.middle_anim_frame = 0.0f;
    } else {
        Stage_80224E38(&sp14, (s8) fp->smash_attrs.x2135);
        Player_GetSomePos(fp->player_id, &sp20);
        fp->mv.co.turn.facing_after =
            fp->facing_dir * ftCommon_800804EC(fp) + (sp14.x + sp20.x);
        fp->mv.co.turn.x8 = sp14.y + sp20.y;
        fp->mv.co.walk.middle_anim_frame = 0.0f;
    }

    ftCommon_8007D5D4(fp);
    fp->mv.co.unk_deadup.x40 = (int) p_ftCommonData->x5D0;
    Fighter_ChangeMotionState(gobj, 0xC, 0x1002, 0.0f, 1.0f, -1.0f, NULL);

    fp->x221E_b2 = 1;
    fp->x2219_b1 = 1;
    fp->x221E_b1 = 1;
    fp->x2222_b7 = 1;
    fp->x221D_b5 = 1;
    ftCo_800BFFD0(fp, 0xA, 0);

    if (!fp->x221F_b4) {
        ftCommon_SetAccessory(fp, ((void**) Fighter_804D6534)[0]);
        {
            f32 s = fp->x34_scale.y * fp->co_attrs.respawn_platform_scale;
            scale_vec.z = s;
            scale_vec.y = s;
            scale_vec.x = s;
        }
        HSD_JObjSetScale(fp->x20A0_accessory, &scale_vec);

        ftCommon_8007E690(fp, ((void**) Fighter_804D6534)[1]);

        pos_vec.x = -(fp->facing_dir * ftCommon_800804EC(fp) - fp->cur_pos.x);
        pos_vec.y = fp->cur_pos.y;
        pos_vec.z = fp->cur_pos.z;
        HSD_JObjSetTranslate(fp->x20A0_accessory, &pos_vec);

        fp->accessory1_cb = fn_800D54A4;
    } else {
        fp->accessory1_cb = fn_800D55B4;
    }

    ftCommon_8007EFC0(fp, 1);
}

void ftCo_Rebirth_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_8008A7A8(gobj, fp->ft_data->x24);
    fp->mv.co.common.x0 -= 1;
    if (fp->mv.co.common.x0 == 0) {
        ftCo_800D5600(gobj);
    }
}

void ftCo_Rebirth_IASA(Fighter_GObj* gobj) {}

void ftCo_Rebirth_Phys(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Vec3 cur_pos;
    Vec3 player_pos;
    Vec3 stage_pos;
    Fighter* fp = gobj->user_data;
    new_var = fp;
    if (!new_var->x221F_b4) {
        if (new_var->smash_attrs.x2135 != -1) {
            Stage_80224E38(&stage_pos, new_var->smash_attrs.x2135);
            Player_GetSomePos(new_var->player_id, &player_pos);
            new_var->mv.co.common.x4.x =
                stage_pos.x + player_pos.x +
                new_var->facing_dir * ftCommon_800804EC(new_var);
            new_var->mv.co.common.x4.y = stage_pos.y + player_pos.y;
            new_var->mv.co.common.x4.z = 0.0f;
        }
        ftCommon_8007F8B4(new_var, &cur_pos);
        {
            float inv = 1.0f / (float) new_var->mv.co.common.x0;
            new_var->self_vel.x =
                (new_var->mv.co.common.x4.x - cur_pos.x) * inv;
            new_var->self_vel.y =
                (new_var->mv.co.common.x4.y - cur_pos.y) * inv;
        }
    } else {
        HSD_GObj* other_gobj = Player_GetEntityAtIndex(new_var->player_id, 0);
        Fighter* other_fp = other_gobj->user_data;
        new_var->self_vel.x = other_fp->self_vel.x;
        new_var->self_vel.y = other_fp->self_vel.y;
    }
    PAD_STACK(12);
}

void ftCo_Rebirth_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->smash_attrs.x2135 == -1) {
        ft_80083DCC(gobj);
    }
}
void fn_800D54A4(Fighter_GObj* gobj)
{
    Vec3 sp;
    u8 _[8];
    Fighter* fp = gobj->user_data;
    HSD_GObj* other_gobj = Player_GetEntityAtIndex(fp->player_id, 1);

    if (other_gobj != NULL) {
        Fighter* other_fp = other_gobj->user_data;
        if (!other_fp->x221F_b3) {
            f32 other_y = other_fp->cur_pos.y;
            if (other_y > fp->cur_pos.y) {
                fp->cur_pos.y = other_y;
            }
        }
    }

    sp.x = -(fp->facing_dir * ftCommon_800804EC(fp) - fp->cur_pos.x);
    sp.y = fp->cur_pos.y;
    sp.z = fp->cur_pos.z;

    HSD_JObjSetTranslate(fp->x20A0_accessory, &sp);
}

void fn_800D55B4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter* new_var;
    HSD_GObj* other_gobj = Player_GetEntityAtIndex(fp->player_id, 0);
    Fighter* other_fp = other_gobj->user_data;
    new_var = other_fp;
    if (new_var->cur_pos.y > fp->cur_pos.y) {
        fp->cur_pos.y = other_fp->cur_pos.y;
    }
}
void ftCo_800D5600(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    mpColl_80043680(&fp->coll_data, &fp->cur_pos);
    fp->self_vel.y = 0;
    fp->mv.co.common.x0 = (int) p_ftCommonData->x5D4;
    Fighter_ChangeMotionState(gobj, ftCo_MS_RebirthWait,
                              Ft_MF_KeepGfx | Ft_MF_SkipColAnim |
                                  Ft_MF_KeepAccessory | Ft_MF_SkipNametagVis,
                              0, 1, 0, NULL);
    fp->x221E_b2 = 1;
    fp->x2219_b1 = 1;
    fp->x221E_b1 = 1;
    fp->x221D_b5 = 1;
    if (!fp->x221F_b4) {
        fp->accessory1_cb = fn_800D54A4;
    } else {
        fp->accessory1_cb = fn_800D55B4;
    }
    if (fp->smash_attrs.x2135 != -1) {
        mpColl_80043680(&fp->coll_data, &fp->cur_pos);
    }
}

void ftCo_RebirthWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8008A7A8(gobj, fp->ft_data->x24);
    fp->mv.co.common.x0 -= 1;
    if (fp->mv.co.common.x0 == 0) {
        ftColl_8007B7A4(gobj, p_ftCommonData->x5D8);
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_RebirthWait_IASA(Fighter_GObj* gobj)
{
    u8 _[8];
    s32 var_r30 = 0;
    Fighter* fp = gobj->user_data;

    if (!fp->x221F_b4) {
        HSD_GObj* companion = Player_GetEntityAtIndex(fp->player_id, 1);
        if (companion != NULL &&
            !((Fighter*) companion->user_data)->x221F_b3 &&
            ftLib_800873CC(companion) == 0)
        {
            var_r30 = 1;
        }
    } else {
        if (ftLib_800873CC(Player_GetEntityAtIndex(fp->player_id, 0)) != 0) {
            return;
        }
        var_r30 = 1;
    }

    if (ftCo_SpecialAir_CheckInput(gobj) || ftCo_800D7100(gobj) ||
        ftCo_800C3B10(gobj) || ftCo_80099A58(gobj) ||
        ftCo_AttackAir_CheckItemThrowInput(gobj) || ftCo_800D705C(gobj) ||
        ftCo_800CB870(gobj))
    {
        /* priority input detected */
    } else if (ftCo_80091A2C(gobj) || ftCo_800DE9B8(gobj) ||
               fn_800D5F84(gobj) || ftCo_800C97A8(gobj) ||
               ftWalkCommon_800DFC70(gobj) || var_r30)
    {
        ftCo_Fall_Enter(gobj);
    } else {
        return;
    }

    ftColl_8007B7A4(gobj, p_ftCommonData->x5D8);
    pl_80040374(fp->player_id, fp->x221F_b4);
}

void ftCo_RebirthWait_Phys(Fighter_GObj* gobj)
{
    Fighter* new_var;
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    u8 _[12];
    Fighter* fp = gobj->user_data;
    new_var = fp;

    if (!new_var->x221F_b4) {
        if (new_var->smash_attrs.x2135 != -1) {
            Stage_80224E38(&sp18, new_var->smash_attrs.x2135);
            Player_GetSomePos(new_var->player_id, &sp24);
            new_var->mv.co.common.x4.x =
                new_var->facing_dir * ftCommon_800804EC(new_var) +
                (sp18.x + sp24.x);
            new_var->mv.co.common.x4.y = sp18.y + sp24.y;
            new_var->mv.co.common.x4.z = 0.0f;
        }
        ftCommon_8007F8B4(new_var, &sp30);
        {
            f32 inv_timer = 1.0f / (f32) new_var->mv.co.common.x0;
            new_var->self_vel.x =
                inv_timer * (new_var->mv.co.common.x4.x - sp30.x);
            new_var->self_vel.y =
                inv_timer * (new_var->mv.co.common.x4.y - sp30.y);
        }
    } else {
        Fighter* other_fp =
            Player_GetEntityAtIndex(new_var->player_id, 0)->user_data;
        new_var->self_vel.x = other_fp->self_vel.x;
        new_var->self_vel.y = other_fp->self_vel.y;
    }
}

void ftCo_RebirthWait_Coll(Fighter_GObj* gobj)
{
    ft_80083844(gobj, fn_800D5A30);
}

void fn_800D5A30(Fighter_GObj* gobj)
{
    ftColl_8007B7A4(gobj, p_ftCommonData->x5D8);
    ft_8008A2BC(gobj);
}
void ftCo_Rebirth_Cam(Fighter_GObj* gobj)
{
    UnkFloat6_Camera spC;
    Fighter* fp = GET_FIGHTER(gobj);
    CmSubject* camera_box = fp->x890_cameraBox;
    ftCamera_80076018(fp->ft_data->x3C, &spC, fp->x34_scale.y);
    camera_box->x10.x = fp->mv.co.common.x4.x;
    camera_box->x10.y = fp->mv.co.common.x4.y + spC.x0.x;
    camera_box->x10.z = 0.0f;
    ftLib_800866DC(gobj, &camera_box->x1C);
}

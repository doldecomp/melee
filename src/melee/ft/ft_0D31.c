#include "ft_0D31.h"

#include "fighter.h"
#include "ft_0877.h"
#include "ft_0881.h"
#include "ft_0C88.h"
#include "ft_0D4D.h"
#include "ftcamera.h"
#include "ftcolanim.h"
#include "ftcommon.h"
#include "ftlib.h"
#include "ftmetal.h"
#include "ftparts.h"
#include "kinds/ftCommon/ftCo_DamageIce.h"
#include "kinds/ftCommon/ftCo_Throw.h"
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/efsync.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lbvector.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>
#include <sysdolphin/baselib/random.h>

const Quaternion lbl_803B7500 = { 0, 3.1415927f, 0, 0 };

bool ftCo_800D3158(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FallCommon* temp_r29 = &p_ftCommonData->fall_common;

    if (fp->x222A_b1 || fp->x2228_b5 || fp->is_sandbag) {
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
        if (Player_GetMoreFlagsBit5(fp->player_idx)) {
            ftCo_800D3E40(gobj);
        } else {
            int temp_r28 = HSD_Randi(100) + 1;
            if (!Camera_8003010C() && temp_r29->x520 >= temp_r28) {
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
            if (!temp_r3_2->is_sub_fighter) {
                temp_r3_2->x2180 = fp->player_idx;
            }
        } else if (!fp->is_sub_fighter) {
            pl_8004065C(ftLib_80086BE0(fp->victim_gobj),
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
        pl_8003EA08(fp->player_idx, fp->is_sub_fighter);
        pl_8003EA74(fp->player_idx, fp->is_sub_fighter);
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
        fp->player_idx, fp->is_sub_fighter,
        Player_GetFallsByIndex(fp->player_idx, fp->is_sub_fighter) + 1);
    plStale_ResetStaleMoveTableForPlayer(fp->player_idx);
    if ((gm_8016B094() || gm_8016B0E8()) &&
        Player_GetEntity(fp->player_idx) == gobj)
    {
        Player_LoseStock(fp->player_idx);
    }
    if (gm_8016B094() && Player_GetStocks(fp->player_idx) <= 0) {
        Player_UpdateMatchFrameCount(fp->player_idx, fp->is_sub_fighter);
    }
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_UpdateKOsBySlot(fp->dmg.x18c4_source_ply, fp->is_sub_fighter,
                               fp->player_idx);
    } else {
        Player_IncSelfDestructs(fp->player_idx, fp->is_sub_fighter);
    }
    pl_8003D644(fp->player_idx, fp->is_sub_fighter, fp->mv.co.unk_800D34E0.x6C,
                fp->mv.co.unk_800D34E0.x70);
    Player_SetHPByIndex(fp->player_idx, fp->is_sub_fighter, 0);
}

void ftCo_800D35FC(Fighter* fp)
{
    u8 _[8];
    HSD_GObj* cur_gobj;

    ftCommon_8007EBAC(fp, 5, p_ftCommonData->x4F8);
    cur_gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
    while (cur_gobj != NULL) {
        Fighter* cur_fp = GET_FIGHTER(cur_gobj);
        if (cur_fp != fp && !cur_fp->is_sleeping) {
            ftCommon_8007EBAC(cur_fp, 6, p_ftCommonData->x4FC);
        }
        cur_gobj = cur_gobj->next;
    }
}

static inline void setDeadFlags(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221D_b6) {
        ft_800880D8(fp);
        fp->x2004 = 0;
    }
    fp->x2219_b1 = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
}

static inline void setDeadInvisible(Fighter* fp)
{
    fp->invisible = true;
    fp->x221F_b1 = true;
}

static inline void playDeadSfx(Fighter* fp, FtSFX* sfx)
{
    ftCo_800D38B8(fp, sfx->x4);
    ftCo_800D38B8(fp, sfx->x8);
}

static inline void processDeath(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtSFX* sfx = fp->ft_data->x4C_sfx;
    setDeadInvisible(fp);
    Camera_RequestQuake(QuakeKind_Large, &fp->cur_pos);
    ftCo_800D35FC(fp);
    ftCo_800D34E0(gobj);
    ft_80088C5C(gobj);
    playDeadSfx(fp, sfx);
}

static inline void enterDead(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800D331C(gobj);
    fp->mv.co.unk_800D3680.x40 = p_ftCommonData->x500;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0.0F, 1.0F, 0.0F, NULL);
    setDeadFlags(gobj);
    pl_8003DF44(fp->player_idx, fp->is_sub_fighter);
    processDeath(gobj);
}

static inline void clampDeadPos(f32* v, f32 min, f32 max)
{
    if (*v > max) {
        *v = max;
    }
    if (*v < min) {
        *v = min;
    }
}

static inline void spawnDeadEffect(Fighter_GObj* gobj, Vec3* pos, f32 angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int offset = Player_GetUnk45(fp->player_idx) << 2;
    u8* color1 = Fighter_804D650C + offset;
    u8* color2 = Fighter_804D6508 + offset;
    int rgb1 = (color1[0] << 16) | (color1[1] << 8) | color1[2];
    int rgb2 = (color2[0] << 16) | (color2[1] << 8) | color2[2];
    int kind;
    if (gm_801693BC(fp->player_idx)) {
        kind = 0x42C;
    } else {
        kind = 0x42B;
    }
    efSync_Spawn(kind, gobj, pos, &angle, &p_ftCommonData->x4F4, rgb1, rgb2);
}

void ftCo_800D3680(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    f32 angle = -M_PI_2_F;

    enterDead(gobj, ftCo_MS_DeadLeft);
    ft_PlaySFX(fp, 0x88, 0x7F, 0x40);
    ft_8008805C(fp, 0x88);
    pos = fp->cur_pos;
    clampDeadPos(&pos.y, Stage_GetBlastZoneBottomOffset(),
                 Stage_GetBlastZoneTopOffset());
    spawnDeadEffect(gobj, &pos, angle);
    pos.x = Stage_GetBlastZoneLeftOffset();
    ftCo_800D4E50(fp, &pos, 1, 0.0F);
}

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
        ftCo_800BFD9C(gobj);
    }
}

void ftCo_DeadLeft_Cam(Fighter_GObj* gobj) {}

void ftCo_800D3950(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    f32 angle = M_PI_2_F;

    enterDead(gobj, ftCo_MS_DeadRight);
    ft_PlaySFX(fp, 0x89, 0x7F, 0x40);
    ft_8008805C(fp, 0x89);
    pos = fp->cur_pos;
    clampDeadPos(&pos.y, Stage_GetBlastZoneBottomOffset(),
                 Stage_GetBlastZoneTopOffset());
    spawnDeadEffect(gobj, &pos, angle);
    pos.x = Stage_GetBlastZoneRightOffset();
    ftCo_800D4E50(fp, &pos, 1, M_PI_F);
}

void ftCo_DeadRight_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftCo_800BFD9C(gobj);
    }
}

void ftCo_DeadRight_Cam(Fighter_GObj* gobj) {}

void ftCo_800D3BC8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    f32 angle = 0.0F;

    PAD_STACK(4);

    enterDead(gobj, ftCo_MS_DeadDown);
    ft_PlaySFX(fp, 0x61, 0x7F, 0x40);
    ft_8008805C(fp, 0x61);
    pos = fp->cur_pos;
    clampDeadPos(&pos.x, Stage_GetBlastZoneLeftOffset(),
                 Stage_GetBlastZoneRightOffset());
    spawnDeadEffect(gobj, &pos, angle);
    pos.y = Stage_GetBlastZoneBottomOffset();
    ftCo_800D4E50(fp, &pos, 1, M_PI_2_F);
}

void ftCo_DeadDown_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftCo_800BFD9C(gobj);
    }
}

void ftCo_DeadDown_Cam(Fighter_GObj* gobj) {}

void ftCo_800D3E40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    f32 angle = M_PI_F;

    PAD_STACK(4);

    enterDead(gobj, ftCo_MS_DeadUp);
    ft_PlaySFX(fp, 0x61, 0x7F, 0x40);
    ft_8008805C(fp, 0x61);
    pos = fp->cur_pos;
    clampDeadPos(&pos.x, Stage_GetBlastZoneLeftOffset(),
                 Stage_GetBlastZoneRightOffset());
    spawnDeadEffect(gobj, &pos, angle);
    pos.y = Stage_GetBlastZoneTopOffset();
    ftCo_800D4E50(fp, &pos, 1, M_PI_F + M_PI_2_F);
}

void ftCo_DeadUp_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.unk_deadleft.x40 -= 1;
    if (!fp->mv.co.unk_deadleft.x40) {
        ftCo_800BFD9C(gobj);
    }
}

void ftCo_DeadUp_Cam(Fighter_GObj* gobj) {}

static inline void ftCo_800D40B8_inline(Fighter_GObj* gobj)
{
    setDeadFlags(gobj);
    ft_80088C5C(gobj);
}

void ftCo_800D40B8(Fighter_GObj* gobj)
{
    u8 _[8];
    int* temp_r31 = (0, &p_ftCommonData->x504);
    Fighter* fp = (0, GET_FIGHTER(gobj));
    Fighter* new_var;
    ftCo_800D331C(gobj);
    fp->mv.co.unk_deadup.x40 = *temp_r31;
    fp->mv.co.unk_deadup.x44 = 0.0F;
    Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStar, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
    ftCo_800D40B8_inline(gobj);
    ftCommon_8007EFC0(fp, true);
    new_var = fp;
    ft_800881D8(new_var, fp->ft_data->x4C_sfx->xC, 127, 64);
    pl_8003DF44(fp->player_idx, fp->is_sub_fighter);
    fp->mv.co.unk_deadup.x68 = 0;
}

void ftCo_800D41C4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* new_var;
    fp->x2227_b6 = 1;
    {
        int* temp_r31 = (0, &p_ftCommonData->x504);
        Fighter* fp2 = (0, GET_FIGHTER(gobj));
        ftCo_800D331C(gobj);
        fp2->mv.co.unk_deadup.x40 = *temp_r31;
        fp2->mv.co.unk_deadup.x44 = 0;
        Fighter_ChangeMotionState(gobj, ftCo_MS_DeadUpStarIce, Ft_MF_None,
                                  0.0F, 1.0F, 0.0F, NULL);
        ftCo_800D40B8_inline(gobj);
        ftCommon_8007EFC0(fp2, true);
        new_var = fp2;
        new_var++;
        new_var--;

        ft_800881D8(new_var, fp2->ft_data->x4C_sfx->xC, 127, 64);
        pl_8003DF44(fp2->player_idx, fp2->is_sub_fighter);
    }
    ftCo_80090AC0(fp);
    ftCommon_8007EBAC(fp, 1, 0);
    fp->mv.co.unk_deadup.x68 = 1;
}

void ftCo_DeadUpStar_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32* data = (s32*) &p_ftCommonData->x504;

    switch (fp->mv.co.unk_deadup.x44) {
    case 1:
        if (fp->mv.co.unk_deadup.x68 != 0) {
            f32 rot_speed = *(f32*) (data + 6);
            HSD_JObj* jobj =
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
            HSD_JObjAddRotationX(jobj, rot_speed);
        }
        break;
    }

    if (fp->mv.co.unk_deadup.x40 != 0) {
        fp->mv.co.unk_deadup.x40 -= 1;
    }

    if (fp->mv.co.unk_deadup.x40 == 0) {
        switch (fp->mv.co.unk_deadup.x44) {
        case 0:
            fp->self_vel.y =
                (*(f32*) (data + 4) * Stage_GetCamBoundsTopOffset() -
                 fp->cur_pos.y) /
                (f32) data[1];
            fp->self_vel.z = *(f32*) (data + 3) / (f32) data[1];
            fp->mv.co.unk_deadup.x40 = data[1];
            fp->mv.co.unk_deadup.x44 = 1;
            return;
        case 1:
            ftCommon_8007E2FC(gobj);
            if (fp->mv.co.unk_deadup.x68 != 0) {
                ftCommon_8007DB24(gobj);
            }
            {
                Fighter* fp2 = GET_FIGHTER(gobj);
                efAsync_Spawn(gobj, &fp2->x60C, 2, 0x42D, NULL, &fp->cur_pos);
            }
            ftCo_800D4E50(fp, &fp->cur_pos, 0, 1.5707964f);
            fp->x221F_b1 = 1;
            fp->invisible = true;
            ft_80088C5C(gobj);
            ft_PlaySFX(fp, 0x83, 0x7F, 0x40);
            ft_8008805C(fp, 0x83);
            ftCo_800D34E0(gobj);
            fp->mv.co.unk_deadup.x40 = data[2];
            fp->mv.co.unk_deadup.x44 = 2;
            return;
        case 2:
            ftCo_800BFD9C(gobj);
            break;
        }
    }
}

void ftCo_DeadUpStar_Cam(Fighter_GObj* gobj)
{
    ftCamera_80076320(gobj);
}

void ftCo_800D4580(Fighter_GObj* gobj, int arg1)
{
    u8 _2[4];
    Quaternion q;
    u8 _[20];
    Fighter* fp;
    Fighter_GObj* new_var;
    FallCommon* datattrs;
    HSD_JObj* jobj;
    Fighter* fp2;

    new_var = gobj;
    fp = new_var->user_data;
    datattrs = &p_ftCommonData->fall_common;

    ftCo_800D331C(gobj);

    fp->mv.co.unk_deadup.x40 = datattrs->x524;
    fp->mv.co.unk_deadup.x44 = 0;
    fp->mv.co.unk_deadup.x50 = datattrs->x538;
    fp->mv.co.common.x24 = 0.0f;
    fp->mv.co.common.x20 = 0.0f;
    fp->mv.co.common.x1C = 0.0f;

    Fighter_ChangeMotionState(gobj, arg1, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    fp->x2220_b7 = true;

    jobj = GET_JOBJ(new_var);
    q = lbl_803B7500;
    if ((fp2 = (Fighter*) new_var->user_data)->x34_scale.z == 1.0f) {
        HSD_JObjSetRotation(jobj, &q);
    }

    fp2 = new_var->user_data;
    if (fp2->x221D_b6) {
        ft_800880D8(fp2);
        fp2->x2004 = 0;
    }
    fp2->x2219_b1 = true;
    fp2->x221E_b1 = true;
    fp2->x221E_b2 = true;

    ft_80088C5C(new_var);
    ftCommon_8007EFC0(fp, true);
    ftCo_800BFFD0(fp, 0x2B, 0);
    pl_8003DF44(fp->player_idx, fp->is_sub_fighter);
}

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

void ftCo_800D481C(Fighter_GObj* gobj, s32 arg1)
{
    Fighter* fp;
    HSD_JObj* jobj;
    u8 _1[4];
    Quaternion q;
    u8 _2[32];

    fp = gobj->user_data;

    Fighter_ChangeMotionState(gobj, arg1, Ft_MF_SkipRumble | Ft_MF_SkipColAnim,
                              0.0f, 1.0f, 0.0f, NULL);

    fp->x2220_b7 = true;

    jobj = GET_JOBJ(gobj);
    q = lbl_803B7500;

    if (((Fighter*) gobj->user_data)->x34_scale.z == 1.0f) {
        HSD_JObjSetRotation(jobj, &q);
    }

    fp->x2219_b1 = 1;
    fp->x221E_b1 = 1;
    fp->x221E_b2 = 1;
    ftCommon_8007EBAC(fp, 5, p_ftCommonData->x4F8);

    {
        HSD_GObj* cur;
        for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
             cur = cur->next)
        {
            Fighter* other = GET_FIGHTER(cur);
            if (((!fp) && (!fp)) && (!fp)) {
            };
            if (other != fp && !other->is_sleeping) {
                ftCommon_8007EBAC(other, 6, p_ftCommonData->x4FC);
            }
        }
    }

    Camera_RequestQuake(QuakeKind_Large, &fp->cur_pos);
    ft_800889F4(fp, fp->ft_data->x4C_sfx->x20);
    ftCo_800D4E50(fp, &fp->cur_pos, 0, 1.5707964f);
    fp->accessory4_cb = fn_800D4DD4;
}

void ftCo_DeadUpFall_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FallCommon* data = &p_ftCommonData->fall_common;
    u8 _[8];

    switch (fp->mv.co.unk_deadup.x44) {
    case 1:
        fp->mv.co.walk.middle_anim_frame += fp->mv.co.walk.slow_anim_frame;
        if (fp->mv.co.unk_deadup.x68 != 0) {
            f32 rot_speed = data->x560_radians;
            HSD_JObj* jobj =
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
            HSD_JObjAddRotationX(jobj, rot_speed);
        }
        break;
    }
    if (fp->mv.co.unk_deadup.x40 != 0) {
        fp->mv.co.unk_deadup.x40 -= 1;
    }

    if (fp->mv.co.unk_deadup.x40 == 0) {
        switch (fp->mv.co.unk_deadup.x44) {
        case 0:
            fp->mv.co.walk.slow_anim_frame = 1.0f / (f32) data->x528;
            fp->mv.co.walk.middle_anim_frame = fp->mv.co.walk.slow_anim_frame;
            fp->mv.co.unk_deadup.x40 = data->x528;
            fp->mv.co.unk_deadup.x44 = 1;
            return;
        case 1:
            if (fp->mv.co.unk_deadup.x68 != 0) {
                Fighter* fp2 = GET_FIGHTER(gobj);
                ftCo_800D481C(gobj, 0xA);
                ftCo_80090AC0(fp2);
            } else if (GET_FIGHTER(gobj)->x34_scale.z != 1.0f) {
                ftCo_800D481C(gobj, 8);
            } else {
                ftCo_800D481C(gobj, 7);
            }
            fp->mv.co.unk_deadup.x40 = data->x52C;
            fp->mv.co.unk_deadup.x44 = 2;
            return;
        case 2:
            fp->self_vel.y = data->x550;
            fp->self_vel.z = data->x55C;
            fp->mv.co.unk_deadup.x40 = data->x530;
            fp->mv.co.unk_deadup.x44 = 3;
            return;
        case 3:
            ftCommon_8007E2FC(gobj);
            if (fp->mv.co.unk_deadup.x68 != 0) {
                ftCommon_8007DB24(gobj);
            }
            fp->x221F_b1 = 1;
            fp->invisible = true;
            ftCo_800D34E0(gobj);
            ft_80088C5C(gobj);
            ft_PlaySFX(fp, 0x61, 0x7F, 0x40);
            ft_8008805C(fp, 0x61);
            ftCommon_8007EBAC(fp, 0xD, 0);
            Camera_RequestQuake(QuakeKind_Large, &fp->cur_pos);
            fp->mv.co.unk_deadup.x40 = data->x534;
            fp->mv.co.unk_deadup.x44 = 4;
            return;
        case 4:
            ftCo_800BFD9C(gobj);
            break;
        }
    }
}

void ftCo_DeadUpFall_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FallCommon* ca = &p_ftCommonData->fall_common;

    switch (fp->mv.co.unk_deadup.x44) {
    case 1:
        if (fp->x2222_b6) {
            if (!ftAnim_80070FD0(fp)) {
                break;
            }
        }
        lbVector_Lerp(&ca->x538, &ca->x544, &fp->mv.co.unk_deadup.x50,
                      fp->mv.co.unk_deadup.x4C);
        break;
    case 3:
        ftCommon_Fall(fp, ca->x554, ca->x558);
        lbVector_Add(&fp->mv.co.unk_deadup.x5C, &fp->self_vel);
        if (fp->x2222_b6) {
            if (!ftAnim_80070FD0(fp)) {
                break;
            }
        }
        lbVector_Add(&fp->mv.co.unk_deadup.x50, &fp->mv.co.unk_deadup.x5C);
        fp->mv.co.unk_deadup.x5C.z = 0;
        fp->mv.co.unk_deadup.x5C.y = 0;
        fp->mv.co.unk_deadup.x5C.x = 0;
        break;
    }
}

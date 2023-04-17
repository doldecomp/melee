#include "ftMr_SpecialN.h"

#include "ftmario.h"

#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftparts.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <baselib/random.h>

int ftDrMario_SpecialN_GetRandomInt(Fighter* fp, int* arr, int outpos)
{
    int r3;
    r3 = (int) arr[HSD_Randi(outpos)];
    fp->ev.mr.x2230_vitaminPrev = fp->ev.mr.x222C_vitaminCurr;
    fp->ev.mr.x222C_vitaminCurr = r3;
    return r3;
}

// 0x800E0D1C
// https://decomp.me/scratch/od8nq
int ftMr_SpecialN_VitaminRandom(
    HSD_GObj* gobj) // Get random Megavitamin color combo for Dr. Mario //
{
    Fighter* fp;
    int arr[9];
    int r3, i;

    fp = gobj->user_data;

    for (i = r3 = 0; i < 9; i++) {
        if (i != (int) fp->ev.mr.x222C_vitaminCurr &&
            i != (int) fp->ev.mr.x2230_vitaminPrev)
        {
            arr[r3] = i;
            r3++;
        }
    }

    r3 = ftDrMario_SpecialN_GetRandomInt(fp, arr, r3);

    return r3;
}

void ftMr_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, AS_MARIO_SPECIALN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

// 0x800E0E18
void ftMr_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x800E0E54
void ftMr_SpecialN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

// 0x800E0E84
void ftMr_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x800E0EA4
void ftMr_SpecialN_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftMr_SpecialN_GroundToAir(gobj);
    }
}

// 0x800E0EE0
// https://decomp.me/scratch/Of8qP
void ftMr_SpecialN_ItemFireSpawn(HSD_GObj* gobj)
{
    Vec3 coords;
    Fighter* fp;

    s32 flag_res;

    int rand_val_800E0D1C;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = gobj->user_data;

    if (fp->x2210_ThrowFlags.b0) {
        fp->x2210_ThrowFlags.b0 = false;
        flag_res = true;
    } else {
        flag_res = false;
    }

    if (flag_res != 0) {
        lb_8000B1CC(fp->x5E8_fighterBones[ftParts_8007500C(fp, 0x17)].x0_jobj,
                    NULL, &coords);
        if (fp->x4_fighterKind == FTKIND_MARIO) {
            it_8029B6F8(fp->facing_dir, gobj, &coords, 0x30);
            efSync_Spawn(
                0x47a, gobj,
                fp->x5E8_fighterBones[ftParts_8007500C(fp, 0x17)].x0_jobj,
                &fp->facing_dir);
        } else {
            rand_val_800E0D1C = ftMr_SpecialN_VitaminRandom(gobj);
            it_802C0510(gobj, &coords, rand_val_800E0D1C, 0x31,
                        fp->facing_dir);
        }
    }
}

void ftMr_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, AS_MARIO_SPECIALAIRN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

// 0x800E10B0
void ftMr_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

// 0x800E10EC
void ftMr_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0 != 0) {
        ft_800CCAAC(gobj);
    }
}

// 0x800E111C
void ftMr_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x800E113C
void ftMr_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftMr_SpecialAirN_AirToGround(gobj);
    }
}

// 0x800E1178
void ftMr_SpecialN_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(
        gobj, AS_MARIO_SPECIALAIRN,
        (FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

// 0x800E11E0
void ftMr_SpecialAirN_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(
        gobj, AS_MARIO_SPECIALN,
        (FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

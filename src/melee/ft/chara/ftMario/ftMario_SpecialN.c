#include <melee/ft/chara/ftMario/ftMario_SpecialN.h>

#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftMario/ftmario.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftparts.h>
#include <melee/it/code_8027CF30.h>
#include <melee/it/itkind.h>
#include <melee/lb/lbunknown_001.h>
#include <sysdolphin/baselib/random.h>

int ftDrMario_SpecialN_GetRandomInt(Fighter* fp, int* arr, int outpos)
{
    int r3;
    r3 = (int) arr[HSD_Randi(outpos)];
    fp->sa.mario.x2230_vitaminPrev = fp->sa.mario.x222C_vitaminCurr;
    fp->sa.mario.x222C_vitaminCurr = r3;
    return r3;
}

// 0x800E0D1C
// https://decomp.me/scratch/od8nq
int ftMario_SpecialN_VitaminRandom(
    HSD_GObj* gobj) // Get random Megavitamin color combo for Dr. Mario //
{
    Fighter* fp;
    int arr[9];
    int r3, i;

    fp = gobj->user_data;

    for (i = r3 = 0; i < 9; i++) {
        if (i != (int) fp->sa.mario.x222C_vitaminCurr &&
            i != (int) fp->sa.mario.x2230_vitaminPrev)
        {
            arr[r3] = i;
            r3++;
        }
    }

    r3 = ftDrMario_SpecialN_GetRandomInt(fp, arr, r3);

    return r3;
}

void ftMario_SpecialN_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj, AS_MARIO_SPECIALN, 0, NULL, 0.0f,
                                       1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

// 0x800E0E18
void ftMario_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

// 0x800E0E54
void ftMario_SpecialN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0)
        func_8008A4D4(gobj);
}

// 0x800E0E84
void ftMario_SpecialN_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

// 0x800E0EA4
void ftMario_SpecialN_Coll(HSD_GObj* gobj)
{
    if (func_80082708(gobj) == false)
        ftMario_SpecialN_GroundToAir(gobj);
}

// 0x800E0EE0
// https://decomp.me/scratch/Of8qP
void ftMario_SpecialN_ItemFireSpawn(HSD_GObj* gobj)
{
    Vec3 coords;
    Fighter* fp;

    s32 flag_res;

    int rand_val_800E0D1C;

    u8 padding[4];

    fp = gobj->user_data;

    if (fp->x2210_ThrowFlags.b0) {
        fp->x2210_ThrowFlags.b0 = false;
        flag_res = true;
    } else {
        flag_res = false;
    }

    if (flag_res != 0) {
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x17)].x0_jobj,
                      NULL, &coords);
        if (fp->x4_fighterKind == FTKIND_MARIO) {
            func_8029B6F8(fp->facing_dir, gobj, &coords, 0x30);
            ef_Spawn(0x47a, gobj,
                     fp->x5E8_fighterBones[func_8007500C(fp, 0x17)].x0_jobj,
                     &fp->facing_dir);
        } else {
            rand_val_800E0D1C = ftMario_SpecialN_VitaminRandom(gobj);
            func_802C0510(gobj, &coords, rand_val_800E0D1C, 0x31,
                          fp->facing_dir);
        }
    }
}

void ftMario_SpecialAirN_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj, AS_MARIO_SPECIALAIRN, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

// 0x800E10B0
void ftMario_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_800CC730(gobj);
    }
}

// 0x800E10EC
void ftMario_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0 != 0) {
        func_800CCAAC(gobj);
    }
}

// 0x800E111C
void ftMario_SpecialAirN_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x800E113C
void ftMario_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj) != false) {
        ftMario_SpecialAirN_AirToGround(gobj);
    }
}

// 0x800E1178
void ftMario_SpecialN_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(
        gobj, AS_MARIO_SPECIALAIRN,
        (FIGHTER_CMD_UPDATE | FIGHTER_COLANIM_NOUPDATE), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

// 0x800E11E0
void ftMario_SpecialAirN_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(
        gobj, AS_MARIO_SPECIALN,
        (FIGHTER_CMD_UPDATE | FIGHTER_COLANIM_NOUPDATE), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

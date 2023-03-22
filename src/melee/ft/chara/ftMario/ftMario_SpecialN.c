#include "ftMario_SpecialN.h"

#include "ftMario_Init.h"

#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>
#include <baselib/random.h>

static int pickMegavitamin(Fighter* fp, int* arr, int outpos)
{
    int result = arr[HSD_Randi(outpos)];
    fp->fv.mr.x2230_vitaminPrev = fp->fv.mr.x222C_vitaminCurr;
    fp->fv.mr.x222C_vitaminCurr = result;
    return result;
}

/// Get random Megavitamin color combo for Dr. Mario
int ftMario_SpecialN_VitaminRandom(HSD_GObj* gobj)
{
    Fighter* fp;
    int arr[9];
    int r3, i;

    fp = gobj->user_data;

    for (i = r3 = 0; i < 9; i++) {
        if (i != (int) fp->fv.mr.x222C_vitaminCurr &&
            i != (int) fp->fv.mr.x2230_vitaminPrev)
        {
            arr[r3] = i;
            r3++;
        }
    }

    r3 = pickMegavitamin(fp, arr, r3);

    return r3;
}

void ftMario_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftMario_MS_SpecialN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

void ftMario_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftMario_SpecialN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0)
        func_8008A4D4(gobj);
}

void ftMario_SpecialN_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftMario_SpecialN_Coll(HSD_GObj* gobj)
{
    if (func_80082708(gobj) == false)
        ftMario_SpecialN_GroundToAir(gobj);
}

void ftMario_SpecialN_ItemFireSpawn(HSD_GObj* gobj)
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
        func_8000B1CC(fp->ft_bones[ftParts_8007500C(fp, 0x17)].x0_jobj, NULL,
                      &coords);
        if (fp->x4_fighterKind == FTKIND_MARIO) {
            func_8029B6F8(fp->facing_dir, gobj, &coords, 0x30);
            ef_Spawn(0x47a, gobj,
                     fp->ft_bones[ftParts_8007500C(fp, 0x17)].x0_jobj,
                     &fp->facing_dir);
        } else {
            rand_val_800E0D1C = ftMario_SpecialN_VitaminRandom(gobj);
            func_802C0510(gobj, &coords, rand_val_800E0D1C, 0x31,
                          fp->facing_dir);
        }
    }
}

void ftMario_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftMario_MS_SpecialAirN, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

void ftMario_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_800CC730(gobj);
    }
}

void ftMario_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0 != 0) {
        func_800CCAAC(gobj);
    }
}

void ftMario_SpecialAirN_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

void ftMario_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        ftMario_SpecialAirN_AirToGround(gobj);
}

void ftMario_SpecialN_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ChangeMotionState(
        gobj, ftMario_MS_SpecialAirN,
        (FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

void ftMario_SpecialAirN_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ChangeMotionState(
        gobj, ftMario_MS_SpecialN,
        (FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialN_ItemFireSpawn;
}

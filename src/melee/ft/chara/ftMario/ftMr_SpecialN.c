#include "ftMr_SpecialN.h"

#include "ftMr_Init.h"

#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

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
int ftMr_SpecialN_VitaminRandom(HSD_GObj* gobj)
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

void ftMr_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialN, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

void ftMr_SpecialN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftMr_SpecialN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftMr_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftMr_SpecialN_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftMr_SpecialN_GroundToAir(gobj);
    }
}

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

    if (fp->throw_flags.b0) {
        fp->throw_flags.b0 = false;
        flag_res = true;
    } else {
        flag_res = false;
    }

    if (flag_res != 0) {
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_L1stNb)].joint, NULL,
                    &coords);
        if (fp->kind == FTKIND_MARIO) {
            it_8029B6F8(fp->facing_dir, gobj, &coords, FtPart_RThumbNa);
            efSync_Spawn(1146, gobj,
                         fp->parts[ftParts_8007500C(fp, FtPart_L1stNb)].joint,
                         &fp->facing_dir);
        } else {
            rand_val_800E0D1C = ftMr_SpecialN_VitaminRandom(gobj);
            it_802C0510(gobj, &coords, rand_val_800E0D1C, FtPart_RThumbNb,
                        fp->facing_dir);
        }
    }
}

void ftMr_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirN, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

void ftMr_SpecialAirN_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftMr_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0) {
        ftCo_800CCAAC(gobj);
    }
}

void ftMr_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftMr_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftMr_SpecialAirN_AirToGround(gobj);
    }
}

void ftMr_SpecialN_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialAirN,
                              (Ft_MF_UpdateCmd | Ft_MF_SkipColAnim), NULL,
                              fp->cur_anim_frame, 1, 0);

    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

void ftMr_SpecialAirN_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftMr_MS_SpecialN,
                              (Ft_MF_UpdateCmd | Ft_MF_SkipColAnim), NULL,
                              fp->cur_anim_frame, 1, 0);

    fp->cb.x21BC_callback_Accessory4 = ftMr_SpecialN_ItemFireSpawn;
}

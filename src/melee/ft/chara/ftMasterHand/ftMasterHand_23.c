#include "ftMasterHand_23.h"

#include "ftMasterHand.h"
#include "ftMasterHand_25.h"
#include "ftMasterHand_26.h"
#include "ftMasterHand_32.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"

// 80154A78 151658
// https://decomp.me/scratch/ci0xf
void func_80154A78(HSD_GObj* gobj)
{
    Fighter* fp;
    MasterHandAttributes* attr;

    fp = gobj->user_data;
    attr = fp->x10C_ftData->ext_attr;
    fp->x2204_ftcmd_var1 = 0;
    Fighter_ActionStateChange_800693AC(gobj, 0x17A, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->x2222_flag.bits.b2 = 1;
    func_8007E2F4(fp, 0x1FFU);
    func_8007E2FC(gobj);
    func_80155B80(fp->x1A58_interactedFighter);
    fp->masterhandVars.x234C_pos.x = attr->x118_pos.x;
    fp->masterhandVars.x234C_pos.y = attr->x118_pos.y;
    fp->masterhandVars.x234C_pos.z = 0.0f;
}

// 80154B2C 15170C
// https://decomp.me/scratch/6WD6p
void lbl_80154B2C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2204_ftcmd_var1 != 0) {
        func_8015C5F8(gobj);
        fp->x2204_ftcmd_var1 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->ev.masterhand.x2250 == 0x17B)
            func_80154E78(gobj);
        else
            func_80155014(gobj);
    }
}

// 80154BB0 151790
void lbl_80154BB0(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(arg0);
}

// 80154BF4 1517D4
// https://decomp.me/scratch/D7Kd4
void lbl_80154BF4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MasterHandAttributes* attr = fp->x10C_ftData->ext_attr;
    func_80085134(gobj);
    func_8015BE40(gobj, &fp->masterhandVars.x234C_pos,
                  &fp->masterhandVars.x2358, attr->x2C, attr->x28);
}

// 80154C54 151834
// https://decomp.me/scratch/Pp9nI
void lbl_80154C54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->masterhandVars.x2358 == 0) {
        fp->x80_self_vel.z = 0;
        fp->x80_self_vel.y = 0;
        fp->x80_self_vel.x = 0;
    }
}

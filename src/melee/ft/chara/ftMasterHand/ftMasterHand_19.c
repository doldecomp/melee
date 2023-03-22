#include "ftMasterHand_19.h"

#include "ftMasterHand_03.h"

#include "ft/ft_81B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

#include <dolphin/mtx/types.h>

// 80153AEC 1506CC
void ftMasterHand_80153AEC(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        ftMasterHand_80151018(gobj);
}

// 80153B28 150708
void ftMasterHand_80153B28(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(gobj);
}

// 80153B6C 15074C
void ftMasterHand_80153B6C(HSD_GObj* gobj)
{
    func_80085134(gobj);
}

// 80153B8C 15076C
void ftMasterHand_80153B8C(HSD_GObj* gobj)
{
    return;
}

// 80153B90 150770
// https://decomp.me/scratch/vgHNv
void ftMasterHand_80153B90(HSD_GObj* arg0)
{
    Fighter* temp_r31 = GET_FIGHTER(arg0);
    ftMasterHand_SpecialAttrs* temp_r30 = temp_r31->ft_data->ext_attr;
    Vec3 sp10;

    Fighter_ChangeMotionState(arg0, 0x172, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    temp_r31->mv.mh.unk0.x0 = temp_r30->x6C;
    func_8015C208(arg0, &sp10);
    temp_r31->cur_pos.x = sp10.x;
    temp_r31->cur_pos.y = temp_r30->x68;
    temp_r31->x80_self_vel.z = 0.0f;
    temp_r31->x80_self_vel.y = 0.0f;
    temp_r31->x80_self_vel.x = 0.0f;
}

// 80153C48 150828
// https://decomp.me/scratch/NrDG9
void ftMasterHand_80153C48(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        Fighter* fp = GET_FIGHTER(arg0);
        fp->x80_self_vel.x = 0.0f;
        ftMasterHand_80151018(arg0);
    }
}

// 80153C90 150870
// https://decomp.me/scratch/ijnCv
void ftMasterHand_80153C90(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(arg0);
}

// 80153CD4 1508B4
// https://decomp.me/scratch/qCZ0G
void ftMasterHand_80153CD4(HSD_GObj* gobj)
{
    Fighter* r4_fp = GET_FIGHTER(gobj);
    if (--r4_fp->mv.mh.unk0.x0 > 0.0f) {
        func_8015BF74(
            gobj,
            ((ftMasterHand_SpecialAttrs*) r4_fp->ft_data->ext_attr)->x58);
    } else {
        r4_fp->x80_self_vel.x = 0.0f;
    }
}

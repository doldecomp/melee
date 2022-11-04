#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/ft/ftanim.h>

static void ftMasterHand_80155388_inline(HSD_GObj* fighter_gobj)
{
    // shared with ftMasterHand_8015521C
    if (ftbosslib_8015C31C() || ftbosslib_8015C3A0() || !ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(fighter_gobj);
        fp->x1A5C = NULL;
        ftMasterHand_80151018(fighter_gobj);
    }
}
void ftMasterHand_80155388(HSD_GObj* fighter_gobj, unk_t, unk_t)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2204_ftcmd_var1 != 0) {
        func_8015C5F8(fighter_gobj);
        fp->x2204_ftcmd_var1 = 0;
    }

    ftMasterHand_80155388_inline(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_8015541C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80155460(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80155480(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155484(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* other_gobj = ftbosslib_8015C3E8(FTKIND_CREZYH);

    if (!ftbosslib_8015C31C())
        func_8015A560(other_gobj);

    fp->x1A5C = other_gobj;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x180, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}

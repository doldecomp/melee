#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

static void ftMasterHand_80153910(HSD_GObj* fighter_gobj);

void ftMasterHand_8015386C(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80153910(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_801538A8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801538EC(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_8015390C(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_80153910(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x170, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    /* inline? */ {
        Vec3 pos;
        u32 unused;
        ftbosslib_8015C208(fighter_gobj, &pos);

        fp->xB0_pos.x = pos.x;
        fp->xB0_pos.y = ext_attr->x5C;

        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;
    }
}

void ftMasterHand_801539A4(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        u32 unused;

        Fighter* fp = fighter_gobj->user_data;

        fp->x80_self_vel.x = 0.0F;
        ftMasterHand_80153A64(fighter_gobj);
    }
}

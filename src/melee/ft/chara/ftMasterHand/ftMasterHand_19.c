#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80153AEC(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

#include <melee/pl/player.h>

void ftMasterHand_80153B28(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80153B6C(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80153B8C(HSD_GObj* fighter_gobj)
{
    return;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_80153B90(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x172, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x2340_f32 = ext_attr->x6C;

    /* inline? */ {
        Vec3 sp10;
        s32 unk;
        ftbosslib_8015C208(fighter_gobj, &sp10);

        fp->xB0_pos.x = sp10.x;
        fp->xB0_pos.y = ext_attr->x68;

        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;
    }
}

void ftMasterHand_80153C48(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        u32 unused[2];

        getFighter(fighter_gobj)->x80_self_vel.x = 0.0F;
        ftMasterHand_80151018(fighter_gobj);
    }
}

void ftMasterHand_80153C90(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80153CD4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (--fp->x2340_f32 > 0.0F) {
        MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;
        ftbosslib_8015BF74(fighter_gobj, ext_attr->x58);
    } else {
        fp->x80_self_vel.x = 0.0F;
    }
}

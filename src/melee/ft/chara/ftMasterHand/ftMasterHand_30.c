#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

extern const f32 neg1;

void ftMasterHand_8015550C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    if (ftbosslib_8015C31C() || ftbosslib_8015C3A0() || !ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp = fighter_gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(fighter_gobj);
        fp->x1A5C = NULL;
        ftMasterHand_80151018(fighter_gobj);
    }
}

#include <melee/pl/player.h>

void ftMasterHand_80155580(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801555C4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801555E4(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_80155818(HSD_GObj* fighter_gobj);

void ftMasterHand_801555E8(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    if (ftbosslib_8015C31C() || ftbosslib_8015C3A0() || !ftAnim_IsFramesRemaining(fighter_gobj)) {
        fp = fighter_gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(fighter_gobj);
        fp->x1A5C = NULL;
        ftMasterHand_80155818(fighter_gobj);
    }
}

void ftMasterHand_8015565C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801556A0(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801556C0(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801556C4(HSD_GObj* fighter_gobj, unk_t, unk_t, unk_t, unk_t)
{
    {
        Fighter* fp = fighter_gobj->user_data;

        if (fp->x2200_ftcmd_var0 != 0) {
            fp->x2200_ftcmd_var0 = 0;
            ftMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);
            if (fp->x1A58_interactedFighter != NULL) {
                HSD_GObj* other_gobj = fp->x1A58_interactedFighter;
                Fighter* fp_2 = other_gobj->user_data;
                func_8007E2F4(fp, 0);
                func_800DE2A8(fighter_gobj, other_gobj);
                fp_2->dmg.x1844_direction *= neg1;
                func_800DE7C0(other_gobj, 0, 0);
            }
        }
    }

    if (ftbosslib_8015C31C() || !ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp_3 = fighter_gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(fighter_gobj);
        fp_3->x1A5C = NULL;
        ftMasterHand_80151018(fighter_gobj);
    }
}

void ftMasterHand_801557B0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801557F4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80155814(HSD_GObj* fighter_gobj)
{
    return;
}

static void ftMasterHand_80155818(HSD_GObj* fighter_gobj)
{
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x183, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}

void ftMasterHand_80155864(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_801558A0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801558E4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80155904(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155908(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (--fp->x2364 <= 0.0F && fp->x2200_ftcmd_var0) {
        ftMasterHand_80155D1C(fp->x1A58_interactedFighter);
        fp->x2200_ftcmd_var0 = FALSE;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_80155990(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801559D4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);
    ftbosslib_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80155A34(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2358_stateVar7 == 0.0F) {
        fp->x80_self_vel.z = 0.0F;
        fp->x80_self_vel.y = 0.0F;
        fp->x80_self_vel.x = 0.0F;
    }
}

const f32 neg1 = -1.0F;

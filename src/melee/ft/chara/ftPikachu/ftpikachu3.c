#include <melee/ft/chara/ftPikachu/ftpikachu.h>

#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/inlines.h>
#include <melee/lb/forward.h>

void ftPikachu_SpecialS_StartAction(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftPikachu_80124DC8;

    fp->xEC_ground_vel /= sa->x30;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 343, 0, 0, 0, 1, 0);
    func_8006EBA4(fighter_gobj);
}

void ftPikachu_SpecialAirS_StartAction(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftPikachu_80124DC8;

    fp->x80_self_vel.x /= sa->x30;
    fp->x80_self_vel.y = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 348, 0, 0, 0, 1, 0);
    func_8006EBA4(fighter_gobj);
}

void ftPikachu_ZeroVelocity_80124F24(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x80_self_vel.x = 0;

    if (fp->x80_self_vel.y >= 0)
        fp->x80_self_vel.y = 0;

    ftPikachu_ActionChange_80125D28(fighter_gobj);
}

void ftPikachu_80124F64(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftPikachu_ActionChange_801254D4(fighter_gobj);
}

void ftPikachu_80124FA0(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftPikachu_ActionChange_80125528(fighter_gobj);
}

void ftPikachu_Stub_80124FDC(HSD_GObj* arg0) {}

void ftPikachu_Stub_80124FE0(HSD_GObj* arg0) {}

void ftPikachu_80124FE4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* sa = getFtSpecialAttrsD(fp);
    f32 pika_attr_x34 = sa->x34;
    func_8007C930(fp, pika_attr_x34);
    func_8007CB74(fighter_gobj);
}

void ftPikachu_80125024(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = getFtSpecialAttrsD(fp);
    struct attr* attr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0)
        func_8007D494(fp, pika_attr->x38, attr->x170_TerminalVelocity);

    func_8007CE94(fp, pika_attr->x34);
}

void ftPikachu_80125084(HSD_GObj* fighter_gobj)
{
    if (!func_80082708(fighter_gobj))
        ftPikachu_ActionChange_801250FC(fighter_gobj);
}

void ftPikachu_801250C0(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj))
        ftPikachu_ActionChange_8012515C(fighter_gobj);
}

static const u32 transition_flags =
    FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_MATANIM_NOUPDATE |
    FIGHTER_SFX_PRESERVE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_CMD_UPDATE |
    FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_STATE_CHANGE_B19 |
    FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE |
    FIGHTER_STATE_CHANGE_B27;

void ftPikachu_ActionChange_801250FC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 348, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftPikachu_ActionChange_8012515C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 343, transition_flags, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_801251BC(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }

    fp->x2340_stateVar1++;

    if (fp->x2340_stateVar1 > sa->x24)
        ftPikachu_ActionChange_80125834(fighter_gobj);
}

void ftPikachu_8012525C(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007DB24(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }

    fp->x2340_stateVar1++;

    if (fp->x2340_stateVar1 > sa->x24) {
        ftPikachu_ActionChange_801258A0(fighter_gobj);
    }
}

void ftPikachu_801252FC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!(fp->input.x65C_heldInputs & 512)) {
        ftPikachu_ActionChange_80125834(fighter_gobj);
    }
}

void ftPikachu_8012532C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!(fp->input.x65C_heldInputs & 512)) {
        ftPikachu_ActionChange_801258A0(fighter_gobj);
    }
}

void ftPikachu_8012535C(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftPikachu_8012537C(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftPikachu_8012539C(HSD_GObj* fighter_gobj)
{
    if (!func_80082708(fighter_gobj)) {
        ftPikachu_ActionChange_80125414(fighter_gobj);
    }
}

void ftPikachu_801253D8(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj)) {
        ftPikachu_ActionChange_80125474(fighter_gobj);
    }
}

void ftPikachu_ActionChange_80125414(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 349, 206328454, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80125474(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 344, 206328454, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801254D4(HSD_GObj* fighter_gobj)
{
    s32 unused[3];
    Fighter* fp;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 344, 512, 0, 0.0f, 1.0f,
                                       0.0f);
    fp = GET_FIGHTER(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
}

void ftPikachu_ActionChange_80125528(HSD_GObj* fighter_gobj)
{
    s32 unused[3];
    Fighter* fp;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 349, 512, 0, 0.0f, 1.0f,
                                       0.0f);
    fp = GET_FIGHTER(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
}

void ftPikachu_8012557C(HSD_GObj* fighter_gobj)
{
    s32 unused[4];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    if (fp->x914[0].state == HitCapsule_Enabled) {
        f32 float_result =
            (fp->x2340_stateVar1 * pika_attr->x2C) + pika_attr->x28;
        func_8007ABD0(&fp->x914[0], float_result, fighter_gobj);
    }

    if (fp->x2200_ftcmd_var0) {
        func_8007D5D4(fp);
        ftPikachu_ActionChange_80125A54(fighter_gobj);
    }
}

void ftPikachu_8012561C(HSD_GObj* fighter_gobj)
{
    s32 unused[4];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    if (fp->x914[0].state == HitCapsule_Enabled) {
        f32 float_result =
            (fp->x2340_stateVar1 * pika_attr->x2C) + pika_attr->x28;
        func_8007ABD0(&fp->x914[0], float_result, fighter_gobj);
    }

    if (fp->x2200_ftcmd_var0) {
        ftPikachu_ActionChange_80125A54(fighter_gobj);
    }
}

void ftPikachu_Stub_801256B4(HSD_GObj* arg0) {}

void ftPikachu_Stub_801256B8(HSD_GObj* arg0) {}

void ftPikachu_801256BC(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

void ftPikachu_801256DC(HSD_GObj* fighter_gobj)
{
    func_80084EEC(fighter_gobj);
}

void ftPikachu_801256FC(HSD_GObj* fighter_gobj)
{
    if (!func_80082708(fighter_gobj)) {
        ftPikachu_ActionChange_80125774(fighter_gobj);
    }
}

void ftPikachu_80125738(HSD_GObj* fighter_gobj)
{
    if (func_80081D0C(fighter_gobj)) {
        ftPikachu_ActionChange_801257D4(fighter_gobj);
    }
}

void ftPikachu_ActionChange_80125774(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 352, 206327942, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801257D4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 347, 206327942, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_80125834(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 347, 0, 0, 0.0f, 1.0f,
                                       0.0f);
    fp = GET_FIGHTER(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    func_8007DB24(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124D2C;
}

void ftPikachu_ActionChange_801258A0(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 352, 0, 0, 0.0f, 1.0f,
                                       0.0f);
    fp = GET_FIGHTER(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    func_8007DB24(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124D2C;
}

void ftPikachu_Stub_8012590C(HSD_GObj* arg0) {}

void ftPikachu_80125910(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftPikachu_ActionChange_80125D28(fighter_gobj);
    }
}

void ftPikachu_Stub_8012594C(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125950(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125954(HSD_GObj* arg0) {}

void ftPikachu_80125958(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0) {
        func_8007D494(fp, pika_attr->x58, pika_attr->x4C);
    } else {
        func_8007D494(fp, pika_attr->x48, pika_attr->x4C);
    }

    if (fp->x2200_ftcmd_var0) {
        func_8007CE94(fp, pika_attr->x54);
    }
}

void ftPikachu_Stub_801259D4(HSD_GObj* arg0) {}

void ftPikachu_801259D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    CollData* collData = &fp->x6F0_collData;

    if (func_80081D0C(fighter_gobj)) {
        func_8007D7FC(fp);
        ftPikachu_ActionChange_80125CD0(fighter_gobj);
    }

    if (collData->x134_envFlags & 63 || collData->x134_envFlags & 4032) {
        ftPikachu_ActionChange_80125D28(fighter_gobj);
    }
}

void ftPikachu_ActionChange_80125A54(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;

    fp->x80_self_vel.x =
        (pika_attr->x40 * fp->x2340_stateVar1) + pika_attr->x3C;
    fp->x80_self_vel.x *= fp->facing_dir;

    fp->x80_self_vel.y =
        (0.5f * pika_attr->x44) +
        (pika_attr->x44 * (0.5f * fp->x2340_stateVar1 / pika_attr->x24));
    Fighter_ActionStateChange_800693AC(fighter_gobj, 350, 10, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21F8_callback = &func_8007F76C;
    fp->cb.x21C0_callback_OnGiveDamage = &ftPikachu_ZeroVelocity_80124F24;
}

void ftPikachu_80125B34(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

void ftPikachu_80125B70(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftPikachu_Stub_80125BAC(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125BB0(HSD_GObj* arg0) {}

void ftPikachu_80125BB4(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    func_8007C930(fp, pika_attr->x54);
    func_8007CB74(fighter_gobj);
}

void ftPikachu_80125BF4(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;
    func_8007D494(fp, pika_attr->x58, fp->x110_attr.x170_TerminalVelocity);
    func_8007CE94(fp, pika_attr->x54);
}

void ftPikachu_80125C44(HSD_GObj* fighter_gobj)
{
    if (!func_80082708(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}

void ftPikachu_80125C80(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (func_80081D0C(fighter_gobj)) {
        func_8007D7FC(fp);
        ftPikachu_ActionChange_80125CD0(fighter_gobj);
    }
}

void ftPikachu_ActionChange_80125CD0(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->xEC_ground_vel /= pika_attr->x50;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 346, 0, 0, 0.0f, 1.0f,
                                       0.0f);
}

void ftPikachu_ActionChange_80125D28(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.x /= pika_attr->x50;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 351, 0, 0, 0.0f, 1.0f,
                                       0.0f);
}

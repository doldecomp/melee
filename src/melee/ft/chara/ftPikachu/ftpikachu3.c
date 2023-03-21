#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcoll.h"
#include "ft/inlines.h"
#include "ftPikachu/ftpikachu.h"
#include "lb/forward.h"

void ftPikachu_SpecialS_StartAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftPikachu_80124DC8;

    fp->xEC_ground_vel /= sa->x30;
    Fighter_ActionStateChange_800693AC(gobj, 343, 0, 0, 0, 1, 0);
    func_8006EBA4(gobj);
}

void ftPikachu_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->cb.x21EC_callback = ftPikachu_80124DC8;

    fp->x80_self_vel.x /= sa->x30;
    fp->x80_self_vel.y = 0;
    Fighter_ActionStateChange_800693AC(gobj, 348, 0, 0, 0, 1, 0);
    func_8006EBA4(gobj);
}

void ftPikachu_ZeroVelocity_80124F24(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.x = 0;

    if (fp->x80_self_vel.y >= 0)
        fp->x80_self_vel.y = 0;

    ftPikachu_ActionChange_80125D28(gobj);
}

void ftPikachu_80124F64(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        ftPikachu_ActionChange_801254D4(gobj);
}

void ftPikachu_80124FA0(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        ftPikachu_ActionChange_80125528(gobj);
}

void ftPikachu_Stub_80124FDC(HSD_GObj* arg0) {}

void ftPikachu_Stub_80124FE0(HSD_GObj* arg0) {}

void ftPikachu_80124FE4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = getFtSpecialAttrsD(fp);
    f32 pika_attr_x34 = sa->x34;
    func_8007C930(fp, pika_attr_x34);
    func_8007CB74(gobj);
}

void ftPikachu_80125024(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = getFtSpecialAttrsD(fp);
    struct attr* attr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0)
        func_8007D494(fp, pika_attr->x38, attr->x170_TerminalVelocity);

    func_8007CE94(fp, pika_attr->x34);
}

void ftPikachu_80125084(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftPikachu_ActionChange_801250FC(gobj);
}

void ftPikachu_801250C0(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        ftPikachu_ActionChange_8012515C(gobj);
}

static const Fighter_ActionStateChangeFlags transition_flags0 =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_PreserveSfx | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

void ftPikachu_ActionChange_801250FC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 348, transition_flags0, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftPikachu_ActionChange_8012515C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 343, transition_flags0, 0,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_801251BC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8007DB24(gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }

    fp->sv.pk.unk3.x0++;

    if (fp->sv.pk.unk3.x0 > sa->x24)
        ftPikachu_ActionChange_80125834(gobj);
}

void ftPikachu_8012525C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8007DB24(gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }

    fp->sv.pk.unk3.x0++;

    if (fp->sv.pk.unk3.x0 > sa->x24)
        ftPikachu_ActionChange_801258A0(gobj);
}

void ftPikachu_801252FC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B))
        ftPikachu_ActionChange_80125834(gobj);
}

void ftPikachu_8012532C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B))
        ftPikachu_ActionChange_801258A0(gobj);
}

void ftPikachu_8012535C(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftPikachu_8012537C(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

void ftPikachu_8012539C(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftPikachu_ActionChange_80125414(gobj);
}

void ftPikachu_801253D8(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        ftPikachu_ActionChange_80125474(gobj);
}

static Fighter_ActionStateChangeFlags const transition_flags1 =
    FtStateChange_PreserveGfx | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_PreserveSfx |
    FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

void ftPikachu_ActionChange_80125414(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 349, transition_flags1, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftPikachu_ActionChange_80125474(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 344, transition_flags1, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftPikachu_ActionChange_801254D4(HSD_GObj* gobj)
{
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(gobj, 344, FtStateChange_PreserveSfx, 0,
                                       0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }
}

void ftPikachu_ActionChange_80125528(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(gobj, 349, FtStateChange_PreserveSfx, 0,
                                       0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124C90;
    }
}

void ftPikachu_8012557C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->x914[0].state == HitCapsule_Enabled) {
        f32 damage_amount = fp->sv.pk.unk3.x0 * sa->x2C + sa->x28;
        func_8007ABD0(&fp->x914[0], damage_amount, gobj);
    }

    if (fp->x2200_ftcmd_var0) {
        func_8007D5D4(fp);
        ftPikachu_ActionChange_80125A54(gobj);
    }
}

void ftPikachu_8012561C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->x914[0].state == HitCapsule_Enabled) {
        f32 damage_amount = fp->sv.pk.unk3.x0 * sa->x2C + sa->x28;
        func_8007ABD0(&fp->x914[0], damage_amount, gobj);
    }

    if (fp->x2200_ftcmd_var0) {
        ftPikachu_ActionChange_80125A54(gobj);
    }
}

void ftPikachu_Stub_801256B4(HSD_GObj* arg0) {}

void ftPikachu_Stub_801256B8(HSD_GObj* arg0) {}

void ftPikachu_801256BC(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftPikachu_801256DC(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

void ftPikachu_801256FC(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftPikachu_ActionChange_80125774(gobj);
}

void ftPikachu_80125738(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        ftPikachu_ActionChange_801257D4(gobj);
}

static Fighter_ActionStateChangeFlags const transition_flags2 =
    FtStateChange_PreserveGfx | FtStateChange_PreserveColAnimHitStatus |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

void ftPikachu_ActionChange_80125774(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 352, transition_flags2, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftPikachu_ActionChange_801257D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 347, transition_flags2, 0,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftPikachu_ActionChange_80125834(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(gobj, 347, 0, 0, 0, 1, 0);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2200_ftcmd_var0 = 0;
        func_8007DB24(gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124D2C;
    }
}

void ftPikachu_ActionChange_801258A0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(gobj, 352, 0, 0, 0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2200_ftcmd_var0 = 0;
        func_8007DB24(gobj);
        fp->cb.x21BC_callback_Accessory4 = &ftPikachu_EfSpawn_80124D2C;
    }
}

void ftPikachu_Stub_8012590C(HSD_GObj* arg0) {}

void ftPikachu_80125910(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        ftPikachu_ActionChange_80125D28(gobj);
}

void ftPikachu_Stub_8012594C(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125950(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125954(HSD_GObj* arg0) {}

void ftPikachu_80125958(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 != 0)
        func_8007D494(fp, pika_attr->x58, pika_attr->x4C);
    else
        func_8007D494(fp, pika_attr->x48, pika_attr->x4C);

    if (fp->x2200_ftcmd_var0 != 0)
        func_8007CE94(fp, pika_attr->x54);
}

void ftPikachu_Stub_801259D4(HSD_GObj* arg0) {}

void ftPikachu_801259D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->x6F0_collData;

    if (func_80081D0C(gobj)) {
        func_8007D7FC(fp);
        ftPikachu_ActionChange_80125CD0(gobj);
    }

    if (collData->x134_envFlags & MPCOLL_RIGHTWALL ||
        collData->x134_envFlags & MPCOLL_LEFTWALL)
    {
        ftPikachu_ActionChange_80125D28(gobj);
    }
}

static Fighter_ActionStateChangeFlags const transition_flags3 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit;

void ftPikachu_ActionChange_80125A54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;

    fp->x80_self_vel.x = sa->x40 * fp->sv.pk.unk3.x0 + sa->x3C;
    fp->x80_self_vel.x *= fp->facing_dir;

    {
        f32 temp = 0.5f * fp->sv.pk.unk3.x0 / sa->x24;
        fp->x80_self_vel.y = 0.5f * sa->x44 + sa->x44 * temp;
    }

    Fighter_ActionStateChange_800693AC(gobj, 350, transition_flags3, 0,
                                       fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21F8_callback = &func_8007F76C;
    fp->cb.x21C0_callback_OnGiveDamage = &ftPikachu_ZeroVelocity_80124F24;
}

void ftPikachu_80125B34(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftPikachu_80125B70(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void ftPikachu_Stub_80125BAC(HSD_GObj* arg0) {}

void ftPikachu_Stub_80125BB0(HSD_GObj* arg0) {}

void ftPikachu_80125BB4(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;
    func_8007C930(fp, sa->x54);
    func_8007CB74(gobj);
}

void ftPikachu_80125BF4(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;
    func_8007D494(fp, sa->x58, fp->x110_attr.x170_TerminalVelocity);
    func_8007CE94(fp, sa->x54);
}

void ftPikachu_80125C44(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        func_800CC730(gobj);
}

void ftPikachu_80125C80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (func_80081D0C(gobj)) {
        func_8007D7FC(fp);
        ftPikachu_ActionChange_80125CD0(gobj);
    }
}

void ftPikachu_ActionChange_80125CD0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->xEC_ground_vel /= sa->x50;

    Fighter_ActionStateChange_800693AC(gobj, 346, 0, 0, 0, 1, 0);
}

void ftPikachu_ActionChange_80125D28(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->x2D4_specialAttributes;

    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.x /= sa->x50;

    Fighter_ActionStateChange_800693AC(gobj, 351, 0, 0, 0, 1, 0);
}

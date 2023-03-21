#include "ftSamus/ftsamus3.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ftSamus/ftsamus.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"
#include "melee/ft/inlines.h"

#include <dolphin/mtx/types.h>

void ftSamus_801293BC_inner(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 x2230 = fp->ev.ss.x2230;
    fp->x80_self_vel.x = (fp->facing_dir * (samus_attr->x1C * x2230));
}

void ftSamus_801291F0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->ev.ss.x222C) {
            fp->ev.ss.x222C = 0;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

void ftSamus_80129258(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSamus_UnkAndDestroyAllEF(gobj);
        fp->ev.ss.x2230 = 0;
    }
}

s32 ftSamus_801292E4(HSD_GObj* gobj)
{
    Vec3 vec1;
    Vec3 vec2;

    HSD_GObj* result;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(gobj);

    if ((fp->x2200_ftcmd_var0 == 1U) && (!fp->ev.ss.x222C)) {
        fp->x2200_ftcmd_var0 = 0U;
        vec2.z = 4.0f;
        vec2.y = 0.0f;
        vec2.x = 0.0f;
        func_8000B1CC(fp->x5E8_fighterBones[50].x0_jobj, &vec2, &vec1);
        vec1.z = 0.0f;
        result = func_802B55C8(gobj, &vec1, 0x32, 0x5E, fp->facing_dir);
        fp->ev.ss.x222C = result;
        if (result != NULL) {
            ftSamus_updateDamageDeathCBs(gobj);
        } else {
            fp->ev.ss.x222C = 0U;
            return 1;
        }
    }
    return 0;
}

void ftSamus_801293BC(HSD_GObj* gobj)
{
    ftSamusAttributes* samus_attr;
    HSD_GObj* held_item;
    Fighter* fp;
    f64 var_f0;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[20];
#endif

    fp = getFighterPlus(gobj);
    samus_attr = fp->x2D4_specialAttributes;

    if ((fp->x2204_ftcmd_var1 == 1) && (fp->ev.ss.x222C)) {
        Vec3 vec1;
        u32 x2230;

        fp->x2204_ftcmd_var1 = 2;
        func_8000B1CC(fp->x5E8_fighterBones[51].x0_jobj, NULL, &vec1);
        vec1.z = 0.0f;
        held_item = fp->x1974_heldItem;
        if (1.0f == fp->facing_dir) {
            var_f0 = 0.0;
        } else {
            var_f0 = M_PI;
        }
        x2230 = fp->ev.ss.x2230;
        func_802B56E4(fp->ev.ss.x222C, &vec1, var_f0, x2230, samus_attr->x18);
        if ((fp->action_id == 0x15C) || (fp->ground_or_air == GA_Air)) {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 unused1[28];
#endif
            ftSamus_801293BC_inner(gobj);
        }
        fp->ev.ss.x2230 = 0U;

        ftSamus_801291F0(gobj);
        ef_Spawn(0x486, gobj, &vec1, &fp->facing_dir);
        fp->x1974_heldItem = held_item;
    }
}

void ftSamus_SpecialN_StartAction(HSD_GObj* gobj)
{
    Vec3* self_vel;
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(gobj, 0x157, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    func_8007D7FC(fp);
    self_vel = &fp->x80_self_vel;
    self_vel->y = 0.0f;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.unk3.x0 = 0;
    fp->mv.ss.unk3.x4 = 0;
    fp->mv.ss.unk3.x8 = 0.0f;
    func_8006EBA4(gobj);
}

void ftSamus_SpecialAirN_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.unk3.x0 = 1;
    fp->mv.ss.unk3.x4 = 0;
    fp->mv.ss.unk3.x8 = 0.0f;
    func_8006EBA4(gobj);
}

void ftSamus_80129684(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftSamus_801292E4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((fp->mv.ss.unk3.x0 == 1) || (fp->ev.ss.x2230 == samus_attr->x18)) {
            Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0, NULL, 0.0f,
                                               1.0f, 0.0f);
        } else {
            Fighter_ActionStateChange_800693AC(gobj, 0x158, 0, NULL, 0.0f,
                                               1.0f, 0.0f);
            ftSamus_SetAttrx2334(gobj);
        }
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

uint lbl_803CE6B8[] = {
    0x0003F7A6, 0x0003F7A9, 0x0003F7AC, 0x0003F7AF, 0x0003F7B2,
};

void ftSamus_80129774(HSD_GObj* gobj)
{
    Fighter* fp;
    Fighter* fighter2;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[40];
#endif

    fp = fighter2 = getFighter(gobj);
    samus_attr = samus_attr2 = fp->x2D4_specialAttributes;
    if (fighter2->x2208_ftcmd_var2) {
        /// this block might be an inline, but couldn't get the regalloc to
        /// behave
        f32 var_f1;
        s32 index;
        fighter2->x2208_ftcmd_var2 = 0;
        if (fighter2->ev.ss.x2230) {
            var_f1 = fighter2->ev.ss.x2230 / samus_attr->x18;
        } else {
            var_f1 = 0.f;
        }
        index = 5.0f * var_f1;
        func_80088510(fighter2, lbl_803CE6B8[index], 0x7F, 0x40);
    }

    fp->mv.ss.unk3.x4 += 1;
    if (fp->mv.ss.unk3.x4 > samus_attr->x20) {
        fp->mv.ss.unk3.x4 = 0;
        fp->ev.ss.x2230 += 1;
        if (fp->ev.ss.x2230 >= samus_attr->x18) {
            func_800BFFD0(fp, 0x35, 0);
            fp->ev.ss.x2230 = samus_attr->x18;
            Fighter_ActionStateChange_800693AC(gobj, 0x159, 0, 0, 0.0f, 1.0f,
                                               0.0f);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

void ftSamus_80129940(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    ftSamus_UnkAndDestroyAllEF(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8008A2BC(gobj);
    }
}

void ftSamus_801299D0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    ftSamus_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8008A2BC(gobj);
    }
}

void ftSamus_80129A14(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftSamus_801292E4(gobj);
    fp->mv.ss.unk3.x0 = 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, NULL, 0.0f, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSamus_80129A98(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    ftSamus_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (samus_attr->x24 == 0.0f) {
            func_800CC730(gobj);
            return;
        }
        func_80096900(gobj, 1, 0, 1, 1.0f, samus_attr->x24);
    }
}

void ftSamus_80129B18(HSD_GObj* gobj) {}

void ftSamus_80129B1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* fighterObj2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    if (func_8009917C(gobj)) {
        fighterObj2 = gobj;
        ftSamus_UnkAndDestroyAllEF(fighterObj2);
    } else {
        if ((fp->input.x668 & 0x200)) {
            Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0, NULL, 0.0f,
                                               1.0f, 0.0f);
            ftSamus_updateDamageDeathCBs(gobj);
            return;
        }
        if ((fp->input.x668 & 0x80000000)) {
            Fighter_ActionStateChange_800693AC(gobj, 0x159, 0, NULL, 0.0f,
                                               1.0f, 0.0f);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

void ftSamus_80129C78(HSD_GObj* gobj) {}

void ftSamus_80129C7C(HSD_GObj* gobj) {}

void ftSamus_80129C80(HSD_GObj* gobj) {}

void ftSamus_80129C84(HSD_GObj* gobj) {}

void ftSamus_80129C88(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSamus_80129CA8(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSamus_80129CC8(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSamus_80129CE8(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSamus_80129D08(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

void ftSamus_80129D28(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}

void ftSamus_80129D48(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!func_80082708(gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0x0C4C5080, NULL,
                                           fp->x894_currentAnimFrame, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSamus_80129DC8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!func_80082708(gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0x0C4C5080, NULL,
                                           fp->x894_currentAnimFrame, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
        func_80088148(fp, 0x3F7B5U, 0x7FU, 0x40U);
        fp->x2204_ftcmd_var1 = 1;
    }
}

void ftSamus_80129E68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!func_80082708(gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0x0C4C5080, NULL,
                                           fp->x894_currentAnimFrame, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSamus_80129EE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!func_80082708(gobj)) {
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0x0C4C5080, NULL,
                                           fp->x894_currentAnimFrame, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSamus_80129F68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (func_80081D0C(gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(gobj, 0x157, 0x0C4C5080, NULL,
                                           fp->x894_currentAnimFrame, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSamus_80129FE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (func_80081D0C(gobj) == 1) {
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0x0C4C5080, NULL,
                                           fp->x894_currentAnimFrame, 1.0f,
                                           0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

s32 ftSamus_8012A068(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->ev.ss.x2238;
}

void ftSamus_8012A074(HSD_GObj* gobj)
{
    bool bool1;
    Fighter* fp = getFighter(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    if (fp->x2210_ThrowFlags.b0) {
        fp->x2210_ThrowFlags.b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        Vec3 position;
        fp->ev.ss.x2238++;
        func_8000B1CC(fp->x5E8_fighterBones[56].x0_jobj, NULL, &position);
        position.x += (samus_attr->x34 * fp->facing_dir);

        if ((fp->action_id == 0x15D) || (fp->action_id == 0x15F)) {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[8];
#endif

            func_802B62D0(gobj, &position, 0, fp->facing_dir);
        } else {
            func_802B62D0(gobj, &position, 1, fp->facing_dir);
        }

        ftSamus_8012A168(gobj, &position);
        fp->cb.x21BC_callback_Accessory4 = 0;
    }
}

void ftSamus_8012A168(HSD_GObj* gobj, Vec3* spawnlocation)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_flag.bits.b0) {
        ef_Spawn(0x483, gobj, spawnlocation);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

#include "melee/ft/inlines.h"
#include <melee/ft/chara/ftSamus/ftsamus3.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftSamus/ftsamus.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/it/code_8027CF30.h>
#include <melee/lb/lbunknown_001.h>

void ftSamus_801293BC_inner(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 x2230 = fp->ev.ss.x2230;
    fp->x80_self_vel.x = (fp->facing_dir * (samus_attr->x1C * x2230));
}

void ftSamus_801291F0(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fighter_gobj) {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        if (fp->ev.ss.x222C) {
            fp->ev.ss.x222C = 0;
        }
        ftSamus_destroyAllEF(fighter_gobj);
    }
}

void ftSamus_80129258(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fighter_gobj) {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        ftSamus_UnkAndDestroyAllEF(fighter_gobj);
        fp->ev.ss.x2230 = 0;
    }
}

s32 ftSamus_801292E4(HSD_GObj* fighter_gobj)
{
    Vec3 vec1;
    Vec3 vec2;

    HSD_GObj* result;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->x2200_ftcmd_var0 == 1U) && (!fp->ev.ss.x222C)) {
        fp->x2200_ftcmd_var0 = 0U;
        vec2.z = 4.0f;
        vec2.y = 0.0f;
        vec2.x = 0.0f;
        lb_8000B1CC(fp->x5E8_fighterBones[50].x0_jobj, &vec2, &vec1);
        vec1.z = 0.0f;
        result = it_802B55C8(fighter_gobj, &vec1, 0x32, 0x5E, fp->facing_dir);
        fp->ev.ss.x222C = result;
        if (result != NULL) {
            ftSamus_updateDamageDeathCBs(fighter_gobj);
        } else {
            fp->ev.ss.x222C = 0U;
            return 1;
        }
    }
    return 0;
}

void ftSamus_801293BC(HSD_GObj* fighter_gobj)
{
    ftSamusAttributes* samus_attr;
    HSD_GObj* held_item;
    Fighter* fp;
    f64 var_f0;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[20];
#endif

    fp = getFighterPlus(fighter_gobj);
    samus_attr = fp->x2D4_specialAttributes;

    if ((fp->x2204_ftcmd_var1 == 1) && (fp->ev.ss.x222C)) {
        Vec3 vec1;
        u32 x2230;

        fp->x2204_ftcmd_var1 = 2;
        lb_8000B1CC(fp->x5E8_fighterBones[51].x0_jobj, NULL, &vec1);
        vec1.z = 0.0f;
        held_item = fp->x1974_heldItem;
        if (1.0f == fp->facing_dir) {
            var_f0 = 0.0;
        } else {
            var_f0 = M_PI;
        }
        x2230 = fp->ev.ss.x2230;
        it_802B56E4(fp->ev.ss.x222C, &vec1, var_f0, x2230, samus_attr->x18);
        if ((fp->action_id == 0x15C) || (fp->xE0_ground_or_air == GA_Air)) {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 unused1[28];
#endif
            ftSamus_801293BC_inner(fighter_gobj);
        }
        fp->ev.ss.x2230 = 0U;

        ftSamus_801291F0(fighter_gobj);
        efSync_Spawn(0x486, fighter_gobj, &vec1, &fp->facing_dir);
        fp->x1974_heldItem = held_item;
    }
}

void ftSamus_SpecialN_StartMotion(HSD_GObj* fighter_gobj)
{
    Vec3* self_vel;
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(fighter_gobj, 0x157, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftCommon_8007D7FC(fp);
    self_vel = &fp->x80_self_vel;
    self_vel->y = 0.0f;
    ftSamus_updateDamageDeathCBs(fighter_gobj);
    fp->sv.ss.unk3.x0 = 0;
    fp->sv.ss.unk3.x4 = 0;
    fp->sv.ss.unk3.x8 = 0.0f;
    ftAnim_8006EBA4(fighter_gobj);
}

void ftSamus_SpecialAirN_StartMotion(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(fighter_gobj, 0x15B, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftSamus_updateDamageDeathCBs(fighter_gobj);
    fp->sv.ss.unk3.x0 = 1;
    fp->sv.ss.unk3.x4 = 0;
    fp->sv.ss.unk3.x8 = 0.0f;
    ftAnim_8006EBA4(fighter_gobj);
}

void ftSamus_80129684(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftSamus_801292E4(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if ((fp->sv.ss.unk3.x0 == 1) || (fp->ev.ss.x2230 == samus_attr->x18)) {
            Fighter_ChangeMotionState(fighter_gobj, 0x15A, 0, NULL, 0.0f, 1.0f,
                                      0.0f);
        } else {
            Fighter_ChangeMotionState(fighter_gobj, 0x158, 0, NULL, 0.0f, 1.0f,
                                      0.0f);
            ftSamus_SetAttrx2334(fighter_gobj);
        }
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

uint lbl_803CE6B8[] = {
    0x0003F7A6, 0x0003F7A9, 0x0003F7AC, 0x0003F7AF, 0x0003F7B2,
};

void ftSamus_80129774(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* fighter2;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[40];
#endif

    fp = fighter2 = getFighter(fighter_gobj);
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
        ft_80088510(fighter2, lbl_803CE6B8[index], 0x7F, 0x40);
    }

    fp->sv.ss.unk3.x4 += 1;
    if (fp->sv.ss.unk3.x4 > samus_attr->x20) {
        fp->sv.ss.unk3.x4 = 0;
        fp->ev.ss.x2230 += 1;
        if (fp->ev.ss.x2230 >= samus_attr->x18) {
            ft_800BFFD0(fp, 0x35, 0);
            fp->ev.ss.x2230 = samus_attr->x18;
            Fighter_ChangeMotionState(fighter_gobj, 0x159, 0, 0, 0.0f, 1.0f,
                                      0.0f);
            ftSamus_UnkAndDestroyAllEF(fighter_gobj);
            ftSamus_updateDamageDeathCBs(fighter_gobj);
        }
    }
}

void ftSamus_80129940(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    ftSamus_UnkAndDestroyAllEF(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

void ftSamus_801299D0(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    ftSamus_801293BC(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ft_8008A2BC(fighter_gobj);
    }
}

void ftSamus_80129A14(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftSamus_801292E4(fighter_gobj);
    fp->sv.ss.unk3.x0 = 1;
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter_ChangeMotionState(fighter_gobj, 0x15C, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129A98(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    ftSamus_801293BC(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        if (samus_attr->x24 == 0.0f) {
            ft_800CC730(fighter_gobj);
            return;
        }
        ft_80096900(fighter_gobj, 1, 0, 1, 1.0f, samus_attr->x24);
    }
}

void ftSamus_80129B18(HSD_GObj* fighter_gobj) {}

void ftSamus_80129B1C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    HSD_GObj* fighterObj2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    if (ft_8009917C(fighter_gobj)) {
        fighterObj2 = fighter_gobj;
        ftSamus_UnkAndDestroyAllEF(fighterObj2);
    } else {
        if ((fp->input.x668 & 0x200)) {
            Fighter_ChangeMotionState(fighter_gobj, 0x15A, 0, NULL, 0.0f, 1.0f,
                                      0.0f);
            ftSamus_updateDamageDeathCBs(fighter_gobj);
            return;
        }
        if ((fp->input.x668 & 0x80000000)) {
            Fighter_ChangeMotionState(fighter_gobj, 0x159, 0, NULL, 0.0f, 1.0f,
                                      0.0f);
            ftSamus_UnkAndDestroyAllEF(fighter_gobj);
            ftSamus_updateDamageDeathCBs(fighter_gobj);
        }
    }
}

void ftSamus_80129C78(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C7C(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C80(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C84(HSD_GObj* fighter_gobj) {}

void ftSamus_80129C88(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSamus_80129CA8(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSamus_80129CC8(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSamus_80129CE8(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSamus_80129D08(HSD_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

void ftSamus_80129D28(HSD_GObj* fighter_gobj)
{
    ft_80084EEC(fighter_gobj);
}

void ftSamus_80129D48(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (!ft_80082708(fighter_gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x15B, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129DC8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (!ft_80082708(fighter_gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
        ft_80088148(fp, 0x3F7B5U, 0x7FU, 0x40U);
        fp->x2204_ftcmd_var1 = 1;
    }
}

void ftSamus_80129E68(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!ft_80082708(fighter_gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129EE8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!ft_80082708(fighter_gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129F68(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (ft_80081D0C(fighter_gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x157, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

void ftSamus_80129FE8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (ft_80081D0C(fighter_gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(fighter_gobj, 0x15A, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(fighter_gobj);
    }
}

s32 ftSamus_8012A068(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    return fp->ev.ss.x2238;
}

void ftSamus_8012A074(HSD_GObj* fighter_gobj)
{
    bool bool1;
    Fighter* fp = getFighter(fighter_gobj);
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
        lb_8000B1CC(fp->x5E8_fighterBones[56].x0_jobj, NULL, &position);
        position.x += (samus_attr->x34 * fp->facing_dir);

        if ((fp->action_id == 0x15D) || (fp->action_id == 0x15F)) {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[8];
#endif

            it_802B62D0(fighter_gobj, &position, 0, fp->facing_dir);
        } else {
            it_802B62D0(fighter_gobj, &position, 1, fp->facing_dir);
        }

        ftSamus_8012A168(fighter_gobj, &position);
        fp->cb.x21BC_callback_Accessory4 = 0;
    }
}

void ftSamus_8012A168(HSD_GObj* fighter_gobj, Vec3* spawnlocation)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x483, fighter_gobj, spawnlocation);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

#include "ftSs_SpecialN.h"

#include "ftSs_Init.h"
#include "ftSs_SpecialN.h"
#include "inlines.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>

static void ftSamus_801293BC_inner(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 x2230 = fp->fv.ss.x2230;
    fp->x80_self_vel.x = (fp->facing_dir * (samus_attr->x1C * x2230));
}

void ftSs_SpecialN_801291F0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.ss.x222C) {
            fp->fv.ss.x222C = 0;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

void ftSs_SpecialN_80129258(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSamus_UnkAndDestroyAllEF(gobj);
        fp->fv.ss.x2230 = 0;
    }
}

static s32 ftSs_SpecialN_801292E4(HSD_GObj* gobj)
{
    Vec3 vec1;
    Vec3 vec2;

    HSD_GObj* result;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(gobj);

    if ((fp->x2200_ftcmd_var0 == 1U) && (!fp->fv.ss.x222C)) {
        fp->x2200_ftcmd_var0 = 0U;
        vec2.z = 4.0f;
        vec2.y = 0.0f;
        vec2.x = 0.0f;
        lb_8000B1CC(fp->ft_bones[50].x0_jobj, &vec2, &vec1);
        vec1.z = 0.0f;
        result = it_802B55C8(gobj, &vec1, 0x32, 0x5E, fp->facing_dir);
        fp->fv.ss.x222C = result;
        if (result != NULL) {
            ftSamus_updateDamageDeathCBs(gobj);
        } else {
            fp->fv.ss.x222C = 0U;
            return 1;
        }
    }
    return 0;
}

static void ftSs_SpecialN_801293BC(HSD_GObj* gobj)
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

    if ((fp->x2204_ftcmd_var1 == 1) && (fp->fv.ss.x222C)) {
        Vec3 vec1;
        u32 x2230;

        fp->x2204_ftcmd_var1 = 2;
        lb_8000B1CC(fp->ft_bones[51].x0_jobj, NULL, &vec1);
        vec1.z = 0.0f;
        held_item = fp->x1974_heldItem;
        if (1.0f == fp->facing_dir) {
            var_f0 = 0.0;
        } else {
            var_f0 = M_PI;
        }
        x2230 = fp->fv.ss.x2230;
        it_802B56E4(fp->fv.ss.x222C, &vec1, var_f0, x2230, samus_attr->x18);
        if ((fp->motion_id == 0x15C) || (fp->ground_or_air == GA_Air)) {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 unused1[28];
#endif
            ftSamus_801293BC_inner(gobj);
        }
        fp->fv.ss.x2230 = 0U;

        ftSs_SpecialN_801291F0(gobj);
        efSync_Spawn(0x486, gobj, &vec1, &fp->facing_dir);
        fp->x1974_heldItem = held_item;
    }
}

void ftSs_SpecialN_Enter(HSD_GObj* gobj)
{
    Vec3* self_vel;
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, 0x157, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftCommon_8007D7FC(fp);
    self_vel = &fp->x80_self_vel;
    self_vel->y = 0.0f;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.unk3.x0 = 0;
    fp->mv.ss.unk3.x4 = 0;
    fp->mv.ss.unk3.x8 = 0.0f;
    ftAnim_8006EBA4(gobj);
}

void ftSs_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, 0x15B, 0, NULL, 0.0f, 1.0f, 0.0f);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.unk3.x0 = 1;
    fp->mv.ss.unk3.x4 = 0;
    fp->mv.ss.unk3.x8 = 0.0f;
    ftAnim_8006EBA4(gobj);
}

void ftSs_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftSs_SpecialN_801292E4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((fp->mv.ss.unk3.x0 == 1) || (fp->fv.ss.x2230 == samus_attr->x18)) {
            Fighter_ChangeMotionState(gobj, 0x15A, 0, NULL, 0.0f, 1.0f, 0.0f);
        } else {
            Fighter_ChangeMotionState(gobj, 0x158, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftSamus_SetAttrx2334(gobj);
        }
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

uint ftSs_Unk3_803CE6B8[] = {
    0x0003F7A6, 0x0003F7A9, 0x0003F7AC, 0x0003F7AF, 0x0003F7B2,
};

void ftSs_SpecialNLoop_Anim(HSD_GObj* gobj)
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
        if (fighter2->fv.ss.x2230) {
            var_f1 = fighter2->fv.ss.x2230 / samus_attr->x18;
        } else {
            var_f1 = 0.f;
        }
        index = 5.0f * var_f1;
        ft_80088510(fighter2, ftSs_Unk3_803CE6B8[index], 0x7F, 0x40);
    }

    fp->mv.ss.unk3.x4 += 1;
    if (fp->mv.ss.unk3.x4 > samus_attr->x20) {
        fp->mv.ss.unk3.x4 = 0;
        fp->fv.ss.x2230 += 1;
        if (fp->fv.ss.x2230 >= samus_attr->x18) {
            ft_800BFFD0(fp, 0x35, 0);
            fp->fv.ss.x2230 = samus_attr->x18;
            Fighter_ChangeMotionState(gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

void ftSs_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    ftSamus_UnkAndDestroyAllEF(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialNShoot_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    ftSs_SpecialN_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftSs_SpecialN_801292E4(gobj);
    fp->mv.ss.unk3.x0 = 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x15C, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialAirNShoot_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    ftSs_SpecialN_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (samus_attr->x24 == 0.0f) {
            ft_800CC730(gobj);
            return;
        }
        ft_80096900(gobj, 1, 0, 1, 1.0f, samus_attr->x24);
    }
}

void ftSs_SpecialNStart_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialNLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* fighterObj2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[32];
#endif

    if (ft_8009917C(gobj)) {
        fighterObj2 = gobj;
        ftSamus_UnkAndDestroyAllEF(fighterObj2);
    } else {
        if ((fp->input.x668 & 0x200)) {
            Fighter_ChangeMotionState(gobj, 0x15A, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftSamus_updateDamageDeathCBs(gobj);
            return;
        }
        if ((fp->input.x668 & 0x80000000)) {
            Fighter_ChangeMotionState(gobj, 0x159, 0, NULL, 0.0f, 1.0f, 0.0f);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

void ftSs_SpecialNEnd_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialNShoot_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirNShoot_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialNShoot_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSs_SpecialAirNShoot_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSs_SpecialNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15B, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialNLoop_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
        ft_80088148(fp, 0x3F7B5U, 0x7FU, 0x40U);
        fp->x2204_ftcmd_var1 = 1;
    }
}

void ftSs_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialNShoot_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x15C, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x157, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialAirNShoot_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 0x15A, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

s32 ftSs_SpecialS_8012A068(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->fv.ss.x2238;
}

static void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation);

void ftSs_SpecialS_8012A074(HSD_GObj* gobj)
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
        fp->fv.ss.x2238++;
        lb_8000B1CC(fp->ft_bones[56].x0_jobj, NULL, &position);
        position.x += (samus_attr->x34 * fp->facing_dir);

        if ((fp->motion_id == 0x15D) || (fp->motion_id == 0x15F)) {
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[8];
#endif

            it_802B62D0(gobj, &position, 0, fp->facing_dir);
        } else {
            it_802B62D0(gobj, &position, 1, fp->facing_dir);
        }

        ftSs_SpecialS_8012A168(gobj, &position);
        fp->cb.x21BC_callback_Accessory4 = 0;
    }
}

static void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_flag.bits.b0) {
        efSync_Spawn(0x483, gobj, spawnlocation);
        fp->x2219_flag.bits.b0 = 1;
    }
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

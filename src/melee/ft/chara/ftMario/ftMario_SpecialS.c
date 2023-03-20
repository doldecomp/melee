#include "ftMario_SpecialS.h"

#include "forward.h"
#include "ftmario.h"
#include "types.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/code_8027CF30.h"
#include "it/itkind.h"
#include "lb/lbunknown_001.h"
#include "lb/lbunknown_003.h"

#include <stddef.h>
#include <baselib/random.h>

void ftMario_SpecialS_SetCall(Fighter* fp)
{
    if (fp->ev.mr.x223C_capeGObj != NULL) {
        fp->cb.x21E4_callback_OnDeath2 = ftMario_OnTakeDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftMario_OnTakeDamage;
    }

    fp->cb.x21D4_callback_EnterHitlag = ftMario_SpecialS_EnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftMario_SpecialS_ExitHitlag;
}

void ftMario_SpecialS_CreateCape(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;

    if (!fp->x2208_ftcmd_var2) {
        /// @todo Can't move below @c _.
        Vec3 coords;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif

        fp->x2208_ftcmd_var2 = true;
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 49)].x0_jobj,
                      NULL, &coords);

        {
            HSD_GObj* cape =
                func_802B2560(gobj, fp->facing_dir, &coords,
                              func_8007500C(fp, 49), sa->specials.cape_kind);

            fp->ev.mr.x223C_capeGObj = cape;
        }

        fp->x1984_heldItemSpec = fp->ev.mr.x223C_capeGObj;
        ftMario_SpecialS_SetCall(fp);
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

void ftMario_SpecialS_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_SpecialS_ExitHitlag(gobj);
    fp->ev.mr.x223C_capeGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

void ftMario_SpecialS_RemoveCape(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ev.mr.x223C_capeGObj != NULL) {
        func_802B2674(fp->ev.mr.x223C_capeGObj);
        ftMario_SpecialS_SetNULL(gobj);
    }
}

void ftMario_SpecialS_EnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ev.mr.x223C_capeGObj != NULL)
        func_802B26C0(fp->ev.mr.x223C_capeGObj);
}

void ftMario_SpecialS_ExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ev.mr.x223C_capeGObj != NULL)
        func_802B26E0(fp->ev.mr.x223C_capeGObj);
}

bool ftMario_SpecialS_CheckItemCapeRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    enum_t asid = fp->action_id;

    if (asid >= ftMario_AS_SpecialS && asid <= ftMario_AS_SpecialAirS)
        return false;

    return true;
}

void ftMario_SpecialS_ChangeAction(HSD_GObj* gobj, enum_t asid)
{
    Fighter_ActionStateChange_800693AC(gobj, asid, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2208_ftcmd_var2 = 0;
        fp->x2204_ftcmd_var1 = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->sv.mr.SpecialS.isReflect = false;
        fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialS_CreateCape;
    }
}

void ftMario_SpecialS_StartAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.y = 0;

    ftMario_SpecialS_ChangeAction(gobj, ftMario_AS_SpecialS);
}

void ftMario_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;
    fp->x80_self_vel.x /= sa->specials.vel_x_decay;
    ftMario_SpecialS_ChangeAction(gobj, ftMario_AS_SpecialAirS);
}

void ftMario_SpecialS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftMario_SpecialAirS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void ftMario_SpecialS_IASA(HSD_GObj* gobj) {}

void ftMario_SpecialAirS_IASA(HSD_GObj* gobj) {}

void ftMario_SpecialS_ReflectThink(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa_tmp = fp->x2D4_specialAttributes;

    if (fp->x2204_ftcmd_var1 == 1U && !fp->sv.mr.SpecialS.isReflect) {
        fp->sv.mr.SpecialS.isReflect = true;
        ftColl_CreateReflectHit(gobj, &sa_tmp->specials_reflection, NULL);
    } else if ((fp->x2204_ftcmd_var1 == 0U) &&
               fp->sv.mr.SpecialS.isReflect == true)
    {
        fp->sv.mr.SpecialS.isReflect = false;
        fp->x2218_flag.bits.b3 = 0;
    }

    func_8007AEF8(gobj);
}

void ftMario_SpecialS_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    {
        /// @todo Cannot be moved above @c unused0 or below @c unused1.
        Vec3 coords;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused1[16];
#endif

        Fighter* fp = GET_FIGHTER(gobj);

        if (fp->x2200_ftcmd_var0 == 1U) {
            fp->x2200_ftcmd_var0 = 2U;
            func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj,
                          NULL, &coords);

            coords.x += 3 * fp->facing_dir;
            func_800119DC(&coords, 120, 0.9, 0.02, M_PI_3);
        }
    }

    func_80084F3C(gobj);
    ftMario_SpecialS_ReflectThink(gobj);
}

void ftMario_SpecialAirS_Phys(HSD_GObj* gobj)
{
    u32 ftcmd_var0_tmp;

    Fighter* fp;
    ftMario_SpecialS_DatAttrs* sa;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    Vec3 coords;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[24];
#endif

    fp = gobj->user_data;

    ftcmd_var0_tmp = fp->x2200_ftcmd_var0;
    sa = &((ftMario_DatAttrs*) fp->x2D4_specialAttributes)->specials;

    if (ftcmd_var0_tmp >= 1U) {
        if (ftcmd_var0_tmp == 1U) {
            fp->x2200_ftcmd_var0 = 2U;
            if (!fp->ev.mr.x2238_isCapeBoost) {
                fp->ev.mr.x2238_isCapeBoost = true;
                fp->x80_self_vel.y = sa->vel.y;
            } else {
                fp->x80_self_vel.y = 0;
            }
            func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj,
                          NULL, &coords);
            coords.x += 3 * fp->facing_dir;
            func_800119DC(&coords, 120, 3, 0.1, M_PI_3);
        }
        func_8007D494(fp, sa->grav, sa->terminal_vel);
    } else {
        func_8007D4B8(fp);
    }

    func_8007CE94(fp, sa->vel.x);
    ftMario_SpecialS_ReflectThink(gobj);
}

void ftMario_SpecialS_Coll(HSD_GObj* gobj)
{
    if (func_800827A0(gobj) == false) {
        ftMario_SpecialS_GroundToAir(gobj);
    }
}

void ftMario_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj) != false) {
        ftMario_SpecialAirS_AirToGround(gobj);
    }
}

void ftMario_SpecialS_UpdateVarsColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((s32) fp->sv.mr.SpecialS.isReflect != false) {
        fp->x2218_flag.bits.b3 = 1;
    }
    ftMario_SpecialS_SetCall(fp);
    fp->cb.x21BC_callback_Accessory4 = ftMario_SpecialS_CreateCape;
}

static usize_t const transition_flags =
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

void ftMario_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialAirS,
                                       transition_flags, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    if ((s32) fp->x2200_ftcmd_var0 == 1U) {
        fp->x2200_ftcmd_var0 = 2U;
    }

    ftMario_SpecialS_UpdateVarsColl(gobj);
}

void ftMario_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = gobj->user_data;
    fp->ev.mr.x2238_isCapeBoost = false;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialS,
                                       transition_flags, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    ftMario_SpecialS_UpdateVarsColl(gobj);
}

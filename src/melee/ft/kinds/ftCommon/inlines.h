#ifndef MELEE_FT_CHARA_FTCOMMON_INLINES_H
#define MELEE_FT_CHARA_FTCOMMON_INLINES_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <placeholder.h>

#include <melee/ef/efasync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_0D27.h>
#include <melee/ft/ftcmdscript.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_ItemParasolOpen.h>
#include <melee/ft/kinds/ftCommon/ftCo_Lift.h>
#include <melee/ft/kinds/ftCommon/ftCo_Throw.h>
#include <melee/ft/kinds/ftCommon/ftCo_Thrown.h>
#include <melee/ft/kinds/ftCommon/types.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/gobj.h>

static inline void ftCo_SpawnEf(Fighter_GObj* gobj, HSD_JObj* joint, u32 arg2,
                                enum_t arg3)
{
    Fighter* fp = gobj->user_data;
    FORCE_PAD_STACK_8;
    efAsync_Spawn((HSD_GObj*) gobj, &fp->x60C, arg2, arg3, joint);
}

static inline void ftCo_ReleaseItemAndVictim(Fighter_GObj* gobj)
{
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
}

static inline void ftCo_Thrown_Enter(Fighter_GObj* gobj, FtMotionId msid,
                                     MotionFlags mf, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = GET_FIGHTER(fp->victim_gobj)->facing_dir;
    fp->mv.co.capturekoopa.x0 = false;
    Fighter_ChangeMotionState(gobj, msid, mf, anim_start, 1, 0,
                              fp->victim_gobj);
    fp->accessory1_cb = (HSD_GObjEvent) ftCo_800DE508;
    ftCommon_8007E2F4(fp, 0x1FF);
}

static inline void ftCo_Barrel_ApplyKnockback(Fighter* fp, float kb_angle,
                                              HitCapsule* hit)
{
    if (kb_angle < 0) {
        kb_angle += 360;
    }
    kb_angle = fp->facing_dir < 0.0f ? kb_angle : 180.0f - kb_angle;
    fp->dmg.kb_applied = ftColl_80079EA8(fp, hit, hit->unk_count);
    fp->dmg.x1848_kb_angle = kb_angle;
    fp->dmg.facing_dir_1 = fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 0;
    fp->dmg.x1854_collpos = fp->cur_pos;
    fp->dmg.x1860_element = hit->element;
}

static inline FtMotionId ftCo_ItemParasolGetFallMotionId(
    Fighter_GObj* gobj, ftPeach_MotionState pe_msid, FtMotionId co_msid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == Ft_Kind_Peach && fp->u.pe.parasol_gobj_0 != NULL) {
        return pe_msid;
    } else {
        return co_msid;
    }
}

static inline void ftCo_ItemParasol_Phys(Fighter_GObj* gobj)
{
    ftCo_ItemParasolOpen_Phys(gobj);
}

static inline void ftCommon_GroundToAirStateChange(Fighter_GObj* gobj,
                                                   Fighter* fp,
                                                   FtMotionId msid,
                                                   MotionFlags flags)
{
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, msid, flags, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

static inline void ftCommon_AirToGroundStateChange(Fighter_GObj* gobj,
                                                   Fighter* fp,
                                                   FtMotionId msid,
                                                   MotionFlags flags)
{
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, flags, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
}

static inline void ftCo_CpuSetNeutralStick(Fighter* fp)
{
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
}

static inline void ftCo_Cliff_EnterState(Fighter_GObj* gobj, Fighter* fp,
                                         FtMotionId msid)
{
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 32);
    fp->x221D_b7 = true;
}

static inline void ftCo_Kinoko_Anim(Fighter_GObj* gobj, HSD_GObjEvent cb)
{
    if (!fn_800D2A3C(gobj)) {
        cb(gobj);
    }
}

#endif

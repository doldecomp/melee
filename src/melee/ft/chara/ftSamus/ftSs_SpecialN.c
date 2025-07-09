#include <platform.h>

#include <baselib/forward.h>

#include "ftSs_SpecialN.h"

#include "inlines.h"
#include "math.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftSamus/types.h"
#include "it/items/itsamuschargeshot.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

static void ftSamus_801293BC_inner(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    s32 x2230 = fp->fv.ss.x2230;
    fp->self_vel.x = (fp->facing_dir * (samus_attr->x1C * x2230));
}

void ftSs_SpecialN_801291F0(HSD_GObj* gobj)
{
    PAD_STACK(8);

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
    PAD_STACK(8);

    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSamus_UnkAndDestroyAllEF(gobj);
        fp->fv.ss.x2230 = 0;
    }
}

static bool ftSs_SpecialN_801292E4(HSD_GObj* gobj)
{
    Vec3 vec1;
    Vec3 vec2;

    HSD_GObj* result;

    u8 _[8];

    Fighter* fp = getFighter(gobj);

    if ((fp->cmd_vars[0] == 1U) && (!fp->fv.ss.x222C)) {
        fp->cmd_vars[0] = 0U;
        vec2.z = 4;
        vec2.y = 0;
        vec2.x = 0;
        lb_8000B1CC(fp->parts[FtPart_RHandNb].joint, &vec2, &vec1);
        vec1.z = 0;
        result = it_802B55C8(gobj, &vec1, FtPart_RHandNb, 94, fp->facing_dir);
        fp->fv.ss.x222C = result;
        if (result != NULL) {
            ftSamus_updateDamageDeathCBs(gobj);
        } else {
            fp->fv.ss.x222C = 0U;
            return true;
        }
    }
    return false;
}

static void ftSs_SpecialN_801293BC(HSD_GObj* gobj)
{
    ftSs_DatAttrs* samus_attr;
    HSD_GObj* held_item;
    Fighter* fp;
    f64 var_f0;
    u8 unused0[20];

    fp = getFighterPlus(gobj);
    samus_attr = fp->dat_attrs;

    if ((fp->cmd_vars[1] == 1) && (fp->fv.ss.x222C)) {
        Vec3 vec1;
        u32 x2230;

        fp->cmd_vars[1] = 2;
        lb_8000B1CC(fp->parts[FtPart_ThrowN].joint, NULL, &vec1);
        vec1.z = 0;
        held_item = fp->item_gobj;
        if (fp->facing_dir == +1) {
            var_f0 = 0;
        } else {
            var_f0 = M_PI;
        }
        x2230 = fp->fv.ss.x2230;
        it_802B56E4(fp->fv.ss.x222C, &vec1, var_f0, x2230, samus_attr->x18);
        if ((fp->motion_id == 348) || (fp->ground_or_air == GA_Air)) {
            u8 unused1[28];
            ftSamus_801293BC_inner(gobj);
        }
        fp->fv.ss.x2230 = 0U;

        ftSs_SpecialN_801291F0(gobj);
        efSync_Spawn(1158, gobj, &vec1, &fp->facing_dir);
        fp->item_gobj = held_item;
    }
}

void ftSs_SpecialN_Enter(HSD_GObj* gobj)
{
    Vec3* self_vel;
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    Fighter_ChangeMotionState(gobj, 343, 0, 0, 1, 0, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftCommon_8007D7FC(fp);
    self_vel = &fp->self_vel;
    self_vel->y = 0;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.unk3.x0 = 0;
    fp->mv.ss.unk3.x4 = 0;
    fp->mv.ss.unk3.x8 = 0;
    ftAnim_8006EBA4(gobj);
}

void ftSs_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    Fighter_ChangeMotionState(gobj, 347, 0, 0, 1, 0, NULL);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    ftSamus_updateDamageDeathCBs(gobj);
    fp->mv.ss.unk3.x0 = 1;
    fp->mv.ss.unk3.x4 = 0;
    fp->mv.ss.unk3.x8 = 0;
    ftAnim_8006EBA4(gobj);
}

void ftSs_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    ftSs_SpecialN_801292E4(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((fp->mv.ss.unk3.x0 == 1) || (fp->fv.ss.x2230 == samus_attr->x18)) {
            Fighter_ChangeMotionState(gobj, 346, 0, 0, 1, 0, NULL);
        } else {
            Fighter_ChangeMotionState(gobj, 344, 0, 0, 1, 0, NULL);
            ftSamus_SetAttrx2334(gobj);
        }
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

u32 ftSs_Unk3_803CE6B8[] = {
    0x0003F7A6, 0x0003F7A9, 0x0003F7AC, 0x0003F7AF, 0x0003F7B2,
};

void ftSs_SpecialNHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    Fighter* fighter2;
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;

    u8 unused1[40];

    fp = fighter2 = getFighter(gobj);
    samus_attr = samus_attr2 = fp->dat_attrs;
    if (fighter2->cmd_vars[2]) {
        /// this block might be an inline, but couldn't get the regalloc to
        /// behave
        float var_f1;
        s32 index;
        fighter2->cmd_vars[2] = 0;
        if (fighter2->fv.ss.x2230) {
            var_f1 = fighter2->fv.ss.x2230 / samus_attr->x18;
        } else {
            var_f1 = 0.f;
        }
        index = 5 * var_f1;
        ft_80088510(fighter2, ftSs_Unk3_803CE6B8[index], 127, 64);
    }

    fp->mv.ss.unk3.x4 += 1;
    if (fp->mv.ss.unk3.x4 > samus_attr->x20) {
        fp->mv.ss.unk3.x4 = 0;
        fp->fv.ss.x2230 += 1;
        if (fp->fv.ss.x2230 >= samus_attr->x18) {
            ftCo_800BFFD0(fp, 53, 0);
            fp->fv.ss.x2230 = samus_attr->x18;
            Fighter_ChangeMotionState(gobj, 345, 0, 0, 1, 0, 0);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

void ftSs_SpecialNCancel_Anim(HSD_GObj* gobj)
{
    u8 _[20];

    ftSamus_UnkAndDestroyAllEF(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialN_Anim(HSD_GObj* gobj)
{
    u8 _[24];

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
        Fighter_ChangeMotionState(gobj, 348, 0, 0, 1, 0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialAirN_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    ftSs_SpecialN_801293BC(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (samus_attr->x24 == 0) {
            ftCo_Fall_Enter(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1, samus_attr->x24);
    }
}

void ftSs_SpecialNStart_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialNHold_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* fighterObj2;

    u8 _[32];

    if (ftCo_8009917C(gobj)) {
        fighterObj2 = gobj;
        ftSamus_UnkAndDestroyAllEF(fighterObj2);
    } else {
        if ((fp->input.x668 & 512)) {
            Fighter_ChangeMotionState(gobj, 346, 0, 0, 1, 0, NULL);
            ftSamus_updateDamageDeathCBs(gobj);
            return;
        }
        if ((fp->input.x668 & 0x80000000)) {
            Fighter_ChangeMotionState(gobj, 345, 0, 0, 1, 0, NULL);
            ftSamus_UnkAndDestroyAllEF(gobj);
            ftSamus_updateDamageDeathCBs(gobj);
        }
    }
}

void ftSs_SpecialNCancel_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialN_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirN_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialNStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialNHold_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialNCancel_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSs_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftSs_SpecialNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 347, 0x0C4C5080, fp->cur_anim_frame, 1,
                                  0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialNHold_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 348, 0x0C4C5080, fp->cur_anim_frame, 1,
                                  0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
        ft_80088148(fp, 260021, 127, 64);
        fp->cmd_vars[1] = 1;
    }
}

void ftSs_SpecialNCancel_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 348, 0x0C4C5080, fp->cur_anim_frame, 1,
                                  0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialN_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 348, 0x0C4C5080, fp->cur_anim_frame, 1,
                                  0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 343, 0x0C4C5080, fp->cur_anim_frame, 1,
                                  0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

void ftSs_SpecialAirN_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj) == 1) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 346, 0x0C4C5080, fp->cur_anim_frame, 1,
                                  0, NULL);
        ftSamus_updateDamageDeathCBs(gobj);
    }
}

int ftSs_SpecialS_8012A068(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->fv.ss.x2238;
}

static void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation);

void ftSs_SpecialS_8012A074(HSD_GObj* gobj)
{
    bool bool1;
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    if (fp->throw_flags_b0) {
        fp->throw_flags_b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        Vec3 position;
        fp->fv.ss.x2238++;
        lb_8000B1CC(fp->parts[56].joint, NULL, &position);
        position.x += (samus_attr->x34 * fp->facing_dir);

        if ((fp->motion_id == 349) || (fp->motion_id == 351)) {
            u8 _[8];

            it_802B62D0(gobj, &position, 0, fp->facing_dir);
        } else {
            it_802B62D0(gobj, &position, 1, fp->facing_dir);
        }

        ftSs_SpecialS_8012A168(gobj, &position);
        fp->accessory4_cb = 0;
    }
}

static void ftSs_SpecialS_8012A168(HSD_GObj* gobj, Vec3* spawnlocation)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2219_b0) {
        efSync_Spawn(1155, gobj, spawnlocation);
        fp->x2219_b0 = 1;
    }
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

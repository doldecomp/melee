#include <platform.h>

#include "ftSs_SpecialLw_1.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "ftSamus/types.h"
#include "it/items/itsamusbomb.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

void ftSs_SpecialLw_8012ADF0(HSD_GObj* gobj)
{
    Vec3 vec;
    bool bool1;
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->throw_flags_b0) {
        fp->throw_flags_b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        float vec_x;
        lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &vec);
        vec_x = samus_attr->x74_vec.x;
        vec.x += (vec_x * fp->facing_dir);
        vec.y += samus_attr->x74_vec.y;
        vec.z += samus_attr->x74_vec.z;
        it_802B4AC8(gobj, &vec, fp->facing_dir, vec_x);
        fp->accessory4_cb = NULL;
    }
}

void ftSs_SpecialLw_8012AEBC(HSD_GObj* gobj)
{
    struct UNK_SAMUS_S2 unk_struct;
    Fighter* fp = GET_FIGHTER(gobj);
    ftColl_8007B0C0(gobj, 2);

    unk_struct.parts[0] = 2;
    unk_struct.parts[1] = 1;
    unk_struct.parts[2] = 0;
    unk_struct.vec1.x = unk_struct.vec1.y = unk_struct.vec1.z = 0;
    unk_struct.vec2.x = unk_struct.vec2.y = unk_struct.vec2.z = 0;
    unk_struct.scale = 3;
    ftColl_8007B5AC(fp, &fp->hurt_capsules[0], &unk_struct);
}

void ftSs_SpecialLw_8012AF38(HSD_GObj* gobj)
{
    ftColl_8007B0C0(gobj, 0);
}

static void ftSamus_SpecialLw_StartAction_inner(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags_b0 = 0;
    fp->mv.ss.unk6.x0 = 0;
    if (fp->cur_anim_frame == 3.0f) {
        fp->cmd_vars[1] = 1;
    }
    fp->accessory4_cb = &ftSs_SpecialLw_8012ADF0;
}

void ftSs_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    fp->gr_vel *= samus_attr->x6C;
    if (fp->motion_id == 0x28) {
        Fighter_ChangeMotionState(gobj, 0x163, 0, 3.0f, 1.0f, 0.0f, NULL);
        ftSamus_SpecialLw_StartAction_inner(gobj);
        fp->cmd_vars[1] = 2;
        ftSs_SpecialLw_8012B5F0(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, 0x163, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftSamus_SpecialLw_StartAction_inner(gobj);
}

void ftSs_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    fp->self_vel.x *= samus_attr->x70;
    fp->self_vel.y = samus_attr->x58;

    Fighter_ChangeMotionState(gobj, 0x164, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftSamus_SpecialLw_StartAction_inner(gobj);
}

inline static void setSamusBits(Fighter* fp, int val)
{
    fp->mv.ss.unk6.x0 = val;
}

inline static void checkStateVar1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->cmd_vars[0]) && (!fp->mv.ss.unk6.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        setSamusBits(fp, 1);
    }
    if ((!fp->cmd_vars[0]) && (fp->mv.ss.unk6.x0)) {
        ftColl_8007B0C0((Fighter_GObj*) gobj, 0);
        setSamusBits(fp, 0);
    }
}

void ftSs_SpecialLwBomb_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] == 1) {
        fp->cmd_vars[1] = 2;
        ftSs_SpecialLw_8012B5F0(gobj);
        return;
    }

    checkStateVar1(gobj);

    if (!ftAnim_IsFramesRemaining((Fighter_GObj*) gobj)) {
        ft_8008A2BC((Fighter_GObj*) gobj);
    }
}

void ftSs_SpecialAirLwBomb_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    checkStateVar1(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

void ftSs_SpecialLwBomb_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    if ((fp->cmd_vars[2]) && (fp->input.lstick.y < samus_attr->x80)) {
        fp->cmd_vars[2] = 0;
        ftCo_800D638C(gobj);
    }
}

void ftSs_SpecialAirLwBomb_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialLwBomb_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    ftCo_DatAttrs* ft_attr = &fp->co_attrs;

    if (fp->cmd_vars[0]) {
        ftCommon_8007CADC(fp, 0.0f, ft_attr->walk_init_vel * samus_attr->x64,
                          ft_attr->walk_max_vel * samus_attr->x5C);
        ftCommon_8007CB74(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftSs_SpecialAirLwBomb_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;
    ftCo_DatAttrs* ft_attr = &fp->co_attrs;

    u8 _[8];
    ftCommon_8007D4B8(fp);
    ftCommon_8007D3A8(fp, 0.0f, ft_attr->air_drift_stick_mul * samus_attr->x68,
                      ft_attr->air_drift_max * samus_attr->x60);
}

void ftSs_SpecialLwBomb_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (!ft_80082888(gobj, &samus_attr->height_attributes)) {
            ftSs_SpecialLw_8012B570(gobj);
        }
    } else if (!ft_800827A0(gobj)) {
        ftSs_SpecialLw_8012B570(gobj);
    }
}

void ftSs_SpecialAirLwBomb_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = fp->dat_attrs;

    u8 _[8];

    if (fp->cmd_vars[0]) {
        if (ft_800824A0(gobj, &samus_attr->height_attributes)) {
            ftSs_SpecialLw_8012B668(gobj);
        }
    } else if (ft_80081D0C(gobj)) {
        ftSs_SpecialLw_8012B668(gobj);
    }
}

static void ftSamus_UnkSetStateAndCb(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    fp->cmd_vars[1] = 2;
    fp->mv.ss.unk6.x0 = 0;
    fp->accessory4_cb = &ftSs_SpecialLw_8012ADF0;
}

void ftSs_SpecialLw_8012B570(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x164, 0x0C4C509C, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftSamus_UnkSetStateAndCb(gobj);
}

void ftSs_SpecialLw_8012B5F0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    fp->self_vel.y = samus_attr->x54;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x164, 0x0C4C509C, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    fp->accessory4_cb = ftSs_SpecialLw_8012ADF0;
}

void ftSs_SpecialLw_8012B668(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x163, 0x0C4C509C, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftSamus_UnkSetStateAndCb(gobj);
}

#include "ftMasterHand_20.h"

#include "ftMasterHand_03.h"

#include "ft/ftbosslib.h"

// 80153D28 150908
void ftMasterHand_80153D28(HSD_GObj* gobj)
{
    return;
}

/// @todo Figure out how to use #GET_JOBJ instead.
static inline HSD_JObj* get_jobj(HSD_GObj* gobj)
{
    return gobj->hsd_obj;
}

void ftMasterHand_80153D2C(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER and #GET_JOBJ both cause regswaps here,
    ///       but they probably shouldn't.
    Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = get_jobj(gobj);

    ftMasterHand_SpecialAttrs* attr = fp->x10C_ftData->ext_attr;
    Vec3 sp1C;
    Vec3 scale;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter_ChangeMotionState(gobj, 0x173, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    ftBossLib_8015C208(gobj, &sp1C);
    fp->xB0_pos.x = sp1C.x;
    fp->xB0_pos.y = attr->x70;

    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;

    fp->sv.mh.unk0.x0 = attr->x74;
    fp->sv.mh.unk0.x70 = attr->x7C;

    HSD_JObjGetScale(jobj, &scale);
    fp->sv.mh.unk0.x64.x = scale.x;
    fp->sv.mh.unk0.x64.y = scale.y;
    fp->sv.mh.unk0.x64.z = scale.z;

    fp->sv.mh.unk0.x58.x = scale.x - attr->x78;
    fp->sv.mh.unk0.x58.y = scale.y - attr->x78;
    fp->sv.mh.unk0.x58.z = scale.z - attr->x78;

    fp->sv.mh.unk0.x58.x /= attr->x7C;
    fp->sv.mh.unk0.x58.y /= attr->x7C;
    fp->sv.mh.unk0.x58.z /= attr->x7C;

    scale.x = attr->x78;
    scale.y = attr->x78;
    scale.z = attr->x78;
    HSD_JObjSetScale(jobj, &scale);

    fp->x2200_ftcmd_var0 = 1;
}

// 80153F8C 150B6C
// https://decomp.me/scratch/w6kte
void ftMasterHand_80153F8C(HSD_GObj* gobj_arg)
{
    HSD_GObj* gobj = gobj_arg;
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 scale;

    if (fp->x2200_ftcmd_var0 != 0) {
        /// @todo #GET_JOBJ
        HSD_JObj* jobj = get_jobj(gobj);
        if (--fp->sv.mh.unk0.x70 < 0) {
            fp->x2200_ftcmd_var0 = 0;
            scale.x = fp->sv.mh.unk0.x64.x;
            scale.y = fp->sv.mh.unk0.x64.y;
            scale.z = fp->sv.mh.unk0.x64.z;
        } else {
            HSD_JObjGetScale(jobj, &scale);
            scale.x += fp->sv.mh.unk0.x58.x;
            scale.y += fp->sv.mh.unk0.x58.y;
            scale.z += fp->sv.mh.unk0.x58.z;
        }
        HSD_JObjSetScale(jobj, &scale);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x80_self_vel.x = 0.0f;
        ftMasterHand_80151018(gobj);
    }
}

// 80154114 150CF4
void ftMasterHand_80154114(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80154158 150D38
// https://decomp.me/scratch/rgPDD
void ftMasterHand_80154158(HSD_GObj* gobj)
{
    Fighter* r3_fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (--r3_fp->sv.mh.unk0.x0 > 0.0f) {
        ftMasterHand_SpecialAttrs* r4_attributes =
            r3_fp->x10C_ftData->ext_attr;
        ftBossLib_8015BF74(gobj, r4_attributes->x58);
    } else {
        r3_fp->x80_self_vel.x = 0.0f;
    }
    ftBossLib_8015C190(gobj);
}

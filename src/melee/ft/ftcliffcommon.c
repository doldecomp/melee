#include <melee/ft/ftcliffcommon.h>

#include <melee/ef/efasync.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftcommon.h>
#include <melee/mp/mplib.h>
#include <melee/pl/pl_unknown_001.h>
#include <Runtime/platform.h>

bool func_80081298(HSD_GObj* gobj)
{
    Fighter* other_fp;
    HSD_GObj* other_gobj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = gobj->user_data;
    if (fp->input.x624_lstick_y <= -p_ftCommonData->x480) {
        return false;
    }
    if (((fp->x6F0_collData.x134_envFlags & 0x03000000) != 0) &&
        (((fp->x2228_flag.bits.b2 & 1) == 0)))
    {
        other_gobj = func_80082E3C(gobj);
        if (other_gobj == NULL) {
            func_80040048(fp->xC_playerID, fp->x221F_flag.bits.b4);
            func_80081370(gobj);
            return true;
        }
        other_fp = other_gobj->user_data;
        func_8003FFDC(other_fp->xC_playerID, other_fp->x221F_flag.bits.b4,
                      fp->xC_playerID, fp->x221F_flag.bits.b4,
                      other_fp->sv.co.cliff.ledge_id);
        fp->x213C = other_fp->sv.co.cliff.ledge_id;
        return false;
    }
    return false;
}

typedef struct _UnkParameterStruct {
    u8 data_filler_0[0x10];
    f32 x10[2];
    u8 data_filler_1[0x1];
} UnkParameterStruct;

void func_80081370(HSD_GObj* gobj)
{
    f32 facingDirection;
    f32 ledgeDirection;

    Fighter* fp = gobj->user_data;
    UnkParameterStruct unkParam;

    if ((fp->x6F0_collData.x134_envFlags & 0x01000000) != 0) {
        ledgeDirection = 1.0f;
    } else {
        ledgeDirection = -1.0f;
    }
    facingDirection = fp->facing_dir;
    if (facingDirection != ledgeDirection) {
        fp->facing_dir = -facingDirection;
    }
    func_8007D780(fp);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0xFC, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    func_8007D5D4(fp);
    func_8007EFC0(fp, p_ftCommonData->x5F0);
    func_8007E2FC(gobj);
    fp->x221D_flag.bits.b7 = 1;
    if (fp->facing_dir > 0.0f) {
        fp->sv.co.cliff.ledge_id = fp->x6F0_collData.x44;
    } else {
        fp->sv.co.cliff.ledge_id = fp->x6F0_collData.x40;
    }
    func_80081544(gobj);
    func_800881D8(fp, fp->x10C_ftData->x4C_collisionData->x28, 0x7F, 0x40);
    func_8007E2F4(fp, 0x1FF);
    func_8007EBAC(fp, 0xC, 0);

    if (fp->facing_dir > 0.0f) {
        func_80053ECC(fp->sv.co.cliff.ledge_id, unkParam.x10);
    } else {
        func_80053DA4(fp->sv.co.cliff.ledge_id, unkParam.x10);
    }
    efAsync_Spawn(gobj, (void*) ((u32) gobj->user_data + 0x60C), 2, 0x41C, 0,
                  &unkParam.x10);
    func_80088148(fp, 4, 0x7F, 0x40);
}

void func_80081504(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8009A804(gobj);
    }
}

void func_80081540(HSD_GObj* arg0) {}

void func_80081544(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused0[4];
#endif

    f32 sp10[2];

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused1[4];
#endif

    Fighter* fp = gobj->user_data;
    if (func_80054ED8(fp->sv.co.cliff.ledge_id) != 0) {
        if (fp->facing_dir > 0.0f) {
            func_80053ECC(fp->sv.co.cliff.ledge_id, sp10);
        } else {
            func_80053DA4(fp->sv.co.cliff.ledge_id, sp10);
        }
        fp->xB0_pos.x =
            (f32) ((fp->x68C_transNPos.z * fp->facing_dir) + sp10[0]);
        fp->xB0_pos.y = (f32) (sp10[1] + fp->x68C_transNPos.y);
        return;
    }
    func_800CC730(gobj);
}

void func_800815E4(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (func_800821DC()) {
        func_80082B1C(gobj);
        return;
    }

    if (func_8009EF68(gobj)) {
        Fighter* fp = gobj->user_data;
        fp->x2064_ledgeCooldown = p_ftCommonData->x498_ledgeCooldownTime;
    }
}

void func_80081644(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_800761C8(gobj);
    if ((s32) fp->xE0_ground_or_air == GA_Air) {
        func_8005811C(&fp->x6F0_collData, fp->sv.co.cliff.ledge_id);
        fp->x890_cameraBox->xC_flag.bits.b0 = 1;
    }
}

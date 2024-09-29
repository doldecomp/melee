#include <platform.h>

#include <dolphin/mtx/forward.h>

#include "ft/ftcliffcommon.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CliffWait.h"
#include "ftCommon/ftCo_StopCeil.h"
#include "ftCommon/types.h"
#include "mp/mplib.h"
#include "pl/pl_0371.h"

#include <common_structs.h>

bool ftCliffCommon_80081298(ftCo_GObj* gobj)
{
    Fighter* other_fp;
    ftCo_GObj* other_gobj;

    u8 _[8];

    Fighter* fp = gobj->user_data;
    if (fp->input.lstick.y <= -p_ftCommonData->x480) {
        return false;
    }
    if (((fp->coll_data.env_flags & 0x03000000) != 0) &&
        (((fp->x2228_b2 & 1) == 0)))
    {
        other_gobj = ft_80082E3C(gobj);
        if (other_gobj == NULL) {
            pl_80040048(fp->player_id, fp->x221F_b4);
            ftCliffCommon_80081370(gobj);
            return true;
        }
        other_fp = other_gobj->user_data;
        pl_8003FFDC(other_fp->player_id, other_fp->x221F_b4, fp->player_id,
                    fp->x221F_b4, other_fp->mv.co.cliff.ledge_id);
        fp->x213C = other_fp->mv.co.cliff.ledge_id;
        return false;
    }
    return false;
}

void ftCliffCommon_80081370(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec3 vec;
    u8 _[16] = { 0 };
    {
        float facing_dir;
        {
            float ledge_dir;
            if (fp->coll_data.env_flags & MPCOLL_FLAGS_B24) {
                ledge_dir = +1;
            } else {
                ledge_dir = -1;
            }
            facing_dir = fp->facing_dir;
            if (facing_dir != ledge_dir) {
                fp->facing_dir = -facing_dir;
            }
        }
        ftCommon_8007D780(fp);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 252, 0, 0, 1, 0, NULL);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007D5D4(fp);
        ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
        ftCommon_8007E2FC(gobj);
        fp->x221D_b7 = 1;
        if (fp->facing_dir > 0) {
            fp->mv.co.cliff.ledge_id = fp->coll_data.ledge_id_unk1;
        } else {
            fp->mv.co.cliff.ledge_id = fp->coll_data.ledge_id_unk0;
        }
        ftCo_CliffCatch_Phys(gobj);
        ft_800881D8(fp, fp->ft_data->x4C_sfx->x28, 127, 64);
        ftCommon_8007E2F4(fp, 511);
        ftCommon_8007EBAC(fp, 12, 0);

        if (fp->facing_dir > 0) {
            mpLib_80053ECC(fp->mv.co.cliff.ledge_id, &vec);
        } else {
            mpLib_80053DA4(fp->mv.co.cliff.ledge_id, &vec);
        }
    }
    {
        ftCo_Fighter* fp = gobj->user_data;
        efAsync_Spawn(gobj, &fp->x60C, 2, 1052, 0, &vec);
    }
    ft_80088148(fp, 4, 127, 64);
}

void ftCo_CliffCatch_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_8009A804(gobj);
    }
}

void ftCo_CliffCatch_IASA(ftCo_GObj* arg0) {}

void ftCo_CliffCatch_Phys(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (mpLib_80054ED8(fp->mv.co.cliff.ledge_id) != 0) {
        Vec3 vec;
        u8 _[4] = { 0 };
        if (fp->facing_dir > 0) {
            mpLib_80053ECC(fp->mv.co.cliff.ledge_id, &vec);
        } else {
            mpLib_80053DA4(fp->mv.co.cliff.ledge_id, &vec);
        }
        fp->cur_pos.x = fp->x68C_transNPos.z * fp->facing_dir + vec.x;
        fp->cur_pos.y = vec.y + fp->x68C_transNPos.y;
    } else {
        ftCo_800CC730(gobj);
    }
}

void ftCo_CliffCatch_Coll(ftCo_GObj* gobj)
{
    u8 _[8];

    if (ft_800821DC(gobj)) {
        ft_80082B1C(gobj);
        return;
    }

    if (ftCo_8009EF68(gobj)) {
        Fighter* fp = gobj->user_data;
        fp->x2064_ledgeCooldown = p_ftCommonData->ledge_cooldown;
    }
}

void ftCo_Cliff_Cam(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCamera_UpdateCameraBox(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        mpLib_8005811C(&fp->coll_data, fp->mv.co.cliff.ledge_id);
        fp->x890_cameraBox->xC_b0 = true;
    }
}

#include "ftNn_Init.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "ftPopo/forward.h"

#include "ftPopo/ftPp_1211.h"
#include "ftPopo/ftPp_Init.h"
#include "ftPopo/ftPp_SpecialN.h"
#include "ftPopo/ftPp_SpecialS.h"
#include "ftPopo/types.h"
#include "lb/lb_00B0.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <MSL/math.h>

void ftNn_Init_801238E4(Fighter_GObj* gobj);
void ftNn_Init_801232A4(Fighter_GObj* gobj);
void ftNn_Init_801233F8(Fighter_GObj* gobj);
void ftNn_Init_801237F8(Fighter_GObj* gobj);
void ftNn_Init_80123720(Fighter_GObj* gobj);
void ftNn_Init_8012378C(Fighter_GObj* gobj);
bool ftNn_Init_8012300C(Fighter_GObj* gobj);
bool ftNn_Init_8012309C(Fighter_GObj* gobj);
bool ftNn_Init_801230D0(Fighter_GObj* nana_gobj);
void fn_80123218(Fighter_GObj* nana_gobj);
void ftNn_Init_80123B3C(Fighter_GObj* nana_gobj);
void ftNn_Init_80123BF0(Fighter_GObj* gobj);

char ftNn_Init_803CD7F8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

ftCollisionBox ftNn_Unk_28 = { 12, 0, -6, 6, 6, 6 };

MotionState ftNn_Init_MotionStateTable[ftPp_MS_SelfCount] = {
    {
        // ftPp_MS_SpecialN = 341
        ftPp_SM_SpecialN,
        ftPp_MF_SpecialN,
        (FtMoveId_SpecialN << 24) | (1 << 23),
        ftPp_SpecialN_Anim,
        ftPp_SpecialN_IASA,
        ftPp_SpecialN_Phys,
        ftPp_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirN = 342
        ftPp_SM_SpecialAirN,
        ftPp_MF_SpecialAirN,
        (FtMoveId_SpecialN << 24) | (1 << 23),
        ftPp_SpecialAirN_Anim,
        ftPp_SpecialAirN_IASA,
        ftPp_SpecialAirN_Phys,
        ftPp_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS1 = 343
        ftPp_SM_SpecialS1,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS1_Anim,
        ftPp_SpecialS1_IASA,
        ftPp_SpecialS1_Phys,
        ftPp_SpecialS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS2 = 344
        ftPp_SM_SpecialS2,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS2_Anim,
        ftPp_SpecialS2_IASA,
        ftPp_SpecialS2_Phys,
        ftPp_SpecialS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirS1 = 345
        ftPp_SM_SpecialAirS1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS1_Anim,
        ftPp_SpecialAirS1_IASA,
        ftPp_SpecialAirS1_Phys,
        ftPp_SpecialAirS1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirS2 = 346
        ftPp_SM_SpecialAirS2,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS2_Anim,
        ftPp_SpecialAirS2_IASA,
        ftPp_SpecialAirS2_Phys,
        ftPp_SpecialAirS2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiStart_0 = 347
        ftPp_SM_SpecialHiStart_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_0_Anim,
        ftPp_SpecialHiStart_0_IASA,
        ftPp_SpecialHiStart_0_Phys,
        ftPp_SpecialHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow_0 = 348
        ftPp_SM_SpecialHiThrow_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow_0_Anim,
        ftPp_SpecialHiThrow_0_IASA,
        ftPp_SpecialHiThrow_0_Phys,
        ftPp_SpecialHiThrow_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow2 = 349
        ftPp_SM_SpecialHiThrow2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow2_Anim,
        ftPp_SpecialHiThrow2_IASA,
        ftPp_SpecialHiThrow2_Phys,
        ftPp_SpecialHiThrow2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiStart_1 = 350
        ftPp_SM_SpecialHiStart_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_1_Anim,
        ftPp_SpecialHiStart_1_IASA,
        ftPp_SpecialHiStart_1_Phys,
        ftPp_SpecialHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHiThrow_1 = 351
        ftPp_SM_SpecialHiThrow_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiThrow_1_Anim,
        ftPp_SpecialHiThrow_1_IASA,
        ftPp_SpecialHiThrow_1_Phys,
        ftPp_SpecialHiThrow_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiStart_0 = 352
        ftPp_SM_SpecialAirHiStart_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_0_Anim,
        ftPp_SpecialAirHiStart_0_IASA,
        ftPp_SpecialAirHiStart_0_Phys,
        ftPp_SpecialAirHiStart_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow_0 = 353
        ftPp_SM_SpecialAirHiThrow_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow_0_Anim,
        ftPp_SpecialAirHiThrow_0_IASA,
        ftPp_SpecialAirHiThrow_0_Phys,
        ftPp_SpecialAirHiThrow_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow2 = 354
        ftPp_SM_SpecialAirHiThrow2,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow2_Anim,
        ftPp_SpecialAirHiThrow2_IASA,
        ftPp_SpecialAirHiThrow2_Phys,
        ftPp_SpecialAirHiThrow2_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiStart_1 = 355
        ftPp_SM_SpecialAirHiStart_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_1_Anim,
        ftPp_SpecialAirHiStart_1_IASA,
        ftPp_SpecialAirHiStart_1_Phys,
        ftPp_SpecialAirHiStart_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirHiThrow_1 = 356
        ftPp_SM_SpecialAirHiThrow_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiThrow_1_Anim,
        ftPp_SpecialAirHiThrow_1_IASA,
        ftPp_SpecialAirHiThrow_1_Phys,
        ftPp_SpecialAirHiThrow_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialLw = 357
        ftPp_SM_SpecialLw,
        ftPp_MF_SpecialLw,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialLw_Anim,
        ftPp_SpecialLw_IASA,
        ftPp_SpecialLw_Phys,
        ftPp_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialAirLw = 358
        ftPp_SM_SpecialAirLw,
        ftPp_MF_MS_358,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialAirLw_Anim,
        ftPp_SpecialAirLw_IASA,
        ftPp_SpecialAirLw_Phys,
        ftPp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS_0 = 359
        ftPp_SM_SpecialS_0,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_0_Anim,
        ftPp_SpecialS_0_IASA,
        ftPp_SpecialS_0_Phys,
        ftPp_SpecialS_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialS_1 = 360
        ftPp_SM_SpecialS_1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_1_Anim,
        ftPp_SpecialS_1_IASA,
        ftPp_SpecialS_1_Phys,
        ftPp_SpecialS_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_0 = 361
        ftPp_SM_SpecialHi_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_0_Anim,
        ftPp_SpecialHi_0_IASA,
        ftPp_SpecialHi_0_Phys,
        ftPp_SpecialHi_0_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_1 = 362
        ftPp_SM_SpecialHi_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_1_Anim,
        ftPp_SpecialHi_1_IASA,
        ftPp_SpecialHi_1_Phys,
        ftPp_SpecialHi_1_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_2 = 363
        ftPp_SM_SpecialHi_2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_3 = 364
        ftPp_SM_SpecialHi_3,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_3_Anim,
        ftPp_SpecialHi_3_IASA,
        ftPp_SpecialHi_3_Phys,
        ftPp_SpecialHi_3_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_4 = 365
        ftPp_SM_SpecialHi_4,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_4_Anim,
        ftPp_SpecialHi_4_IASA,
        ftPp_SpecialHi_4_Phys,
        ftPp_SpecialHi_4_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftPp_MS_SpecialHi_5 = 366
        ftPp_SM_SpecialHi_5,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        ftCamera_UpdateCameraBox,
    },
};

char ftNn_Init_DatFilename[] = "PlNn.dat";
char ftNn_Init_DataName[] = "ftDataNana";
char ftNn_Init_803CDB90[] = "PlNnNr.dat";
char ftNn_Init_803CDB9C[] = "PlyNana5K_Share_joint";
char ftNn_Init_803CDBB4[] = "PlyNana5K_Share_matanim_joint";
char ftNn_Init_803CDBD4[] = "PlNnYe.dat";
char ftNn_Init_803CDBE0[] = "PlyNana5KYe_Share_joint";
char ftNn_Init_803CDBF8[] = "PlyNana5KYe_Share_matanim_joint";
char ftNn_Init_803CDC18[] = "PlNnAq.dat";
char ftNn_Init_803CDC24[] = "PlyNana5KAq_Share_joint";
char ftNn_Init_803CDC3C[] = "PlyNana5KAq_Share_matanim_joint";
char ftNn_Init_803CDC5C[] = "PlNnWh.dat";
char ftNn_Init_803CDC68[] = "PlyNana5KWh_Share_joint";
char ftNn_Init_803CDC80[] = "PlyNana5KWh_Share_matanim_joint";
char ftNn_Init_AnimDatFilename[] = "PlNnAJ.dat";
char ftNn_Init_803CDCAC[] = "ftDemoResultMotionFileNana";
char ftNn_Init_803CDCC8[] = "ftDemoIntroMotionFileNana";
char ftNn_Init_803CDCE4[] = "ftDemoEndingMotionFileNana";
char ftNn_Init_803CDD00[] = "ftDemoViWaitMotionFilePopo";

Fighter_DemoStrings ftNn_Init_DemoMotionFilenames = {
    ftNn_Init_803CDCAC,
    ftNn_Init_803CDCC8,
    ftNn_Init_803CDCE4,
    ftNn_Init_803CDD00,
};

Fighter_CostumeStrings ftNn_Init_CostumeStrings[] = {
    { ftNn_Init_803CDB90, ftNn_Init_803CDB9C, ftNn_Init_803CDBB4 },
    { ftNn_Init_803CDBD4, ftNn_Init_803CDBE0, ftNn_Init_803CDBF8 },
    { ftNn_Init_803CDC18, ftNn_Init_803CDC24, ftNn_Init_803CDC3C },
    { ftNn_Init_803CDC5C, ftNn_Init_803CDC68, ftNn_Init_803CDC80 },
};

extern ftCollisionBox ftNn_Unk2_803CDD60;

void ftNn_Init_OnLoad(Fighter_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2222_b4 = true;
    ftPp_Init_OnLoadForNana(fp);

    {
        ftIceClimberAttributes* da = fp->dat_attrs;
        fp->x40 = da->xC4;
    }
}

void ftNn_Init_OnDeath(Fighter_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    fp->dmg.armor0 = da->xC8;
    ftParts_80074A4C(gobj, 0U, 0);
    ftParts_80074A4C(gobj, 1U, 0);
    fp->fv.nn.x2234 = 0;
    fp->fv.nn.x222C = 0;
    fp->fv.nn.x2230_b0 = 0;
    fp->fv.nn.x2238 = 0;
    fp->fv.nn.x224C = 0;
    fp->fv.nn.x2250 = 0.0f;
}

void ftNn_Init_80122FAC(Fighter_GObj* gobj)
{
    ftNn_Init_801238E4(gobj);
}

void ftNn_Init_LoadSpecialAttrs(Fighter_GObj* gobj)
{
    COPY_ATTRS(gobj, ftIceClimberAttributes);
}

bool ftNn_Init_8012300C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int ret;
    if (!fp->x221F_b3 && !fp->x2219_b5) {
        switch (fp->x2070.x2071_b0_3) {
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
            ret = 1;
            break;
        case 2:
        case 9:
        default:
            ret = 0;
            break;
        }
        if (!ret) {
            ftNn_Init_801232A4(gobj);
            return true;
        }
    }
    return false;
}

bool ftNn_Init_8012309C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x221F_b3) {
        if (fp->motion_id >= 362 && fp->motion_id <= 366) {
            return true;
        }
    }
    return false;
}

bool ftNn_Init_801230D0(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Vec popo_vec;
    Vec nana_vec;
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        if (popo_fp->motion_id < 347 || popo_fp->motion_id > 352) {
            return false;
        }
        if (nana_fp->facing_dir != popo_fp->facing_dir) {
            nana_fp->facing_dir = popo_fp->facing_dir;
            ftParts_80075AF0(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
        }
        lb_8000B1CC(popo_fp->parts[FtPart_R4thNb].joint, NULL, &popo_vec);
        lb_8000B1CC(nana_fp->parts[FtPart_XRotN].joint, NULL, &nana_vec);
        nana_fp->cur_pos.x = popo_vec.x + (nana_fp->cur_pos.x - nana_vec.x);
        nana_fp->cur_pos.y = popo_vec.y + (nana_fp->cur_pos.y - nana_vec.y);
        nana_fp->cur_pos.z = popo_vec.z + (nana_fp->cur_pos.z - nana_vec.z);
        if (popo_fp->x2219_b6) {
            ftAnim_SetAnimRate(nana_gobj, 0.0f);
        } else {
            if (nana_fp->frame_speed_mul != popo_fp->frame_speed_mul) {
                ftAnim_SetAnimRate(nana_gobj, popo_fp->frame_speed_mul);
            }
        }
    }
    return true;
}

void fn_80123218(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        Vec nana_vec;
        PAD_STACK(8);
        nana_vec.x = nana_vec.y = nana_vec.z = 0;
        lb_8000B1CC(GET_FIGHTER(nana_gobj)->parts[FtPart_L4thNb].joint, NULL,
                    &nana_vec);
        popo_fp->fv.pp.x2240 = nana_vec;
    }
}

static inline void ftNn_Init_801232A4_inline(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    nana_fp->cmd_vars[0] = 0;
    nana_fp->x2222_b2 = 1;
}

void ftNn_Init_801232A4(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    ftCo_DatAttrs* attrs = getFtAttrs(nana_fp);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        nana_fp->facing_dir = popo_fp->facing_dir;
    }
    if (nana_fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(nana_fp);
    } else {
        nana_fp->x1968_jumpsUsed = attrs->max_jumps;
    }
    ftNn_Init_801233F8(nana_gobj);
    ftNn_Init_801232A4_inline(nana_gobj);
}

void ftPp_SpecialHi_0_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftNn_Init_801237F8(gobj);
    }
}

void ftPp_SpecialHi_3_Anim(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_0_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_3_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftNn_Init_801230D0(gobj)) {
        fp->cur_pos.x = -((8.0f * fp->facing_dir) - fp->cur_pos.x);
        ftCo_Fall_Enter(gobj);
    }
}

void ftPp_SpecialHi_3_Phys(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_0_Coll(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_3_Coll(Fighter_GObj* gobj)
{
    return;
}

void ftNn_Init_801233F8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_80123218;
}

void ftPp_SpecialHi_1_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftPp_SpecialHi_4_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attrs = fp->dat_attrs;
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCo_80096900(gobj, 0, 1, 0, attrs->x130, attrs->x134);
    }
}

void ftPp_SpecialHi_1_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_4_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialHi_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPp_SpecialHi_4_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attrs = fp->dat_attrs;
    ftCo_DatAttrs* co_attrs = getFtAttrs(fp);
    ftCommon_Fall(fp, attrs->x144, attrs->x148);
    if (ABS(fp->input.lstick.x) > attrs->x138) {
        ftCommon_8007D344(fp, 0.0f, co_attrs->air_drift_stick_mul * attrs->xB0,
                          co_attrs->air_drift_max * attrs->xB4);
    } else if (fp->self_vel.y < 0.0f) {
        ftCommon_8007CEF4(fp);
    }
}

void ftPp_SpecialHi_1_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftNn_Init_80123720(gobj);
    }
}

void ftPp_SpecialHi_4_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attrs = fp->dat_attrs;
    CollData* cd = &fp->coll_data;
    PAD_STACK(8);
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftNn_Init_8012378C(gobj);
        return;
    }
    if (cd->env_flags & Collide_LeftWallMask) {
        if (fp->self_vel.x > 0.0f) {
            fp->self_vel.x *= -1 * attrs->x14C;
            fp->facing_dir *= -1;
            ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            return;
        }
    }
    if (cd->env_flags & Collide_RightWallMask) {
        if (fp->self_vel.x < 0.0f) {
            fp->self_vel.x *= -1 * attrs->x14C;
            fp->facing_dir *= -1;
            ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            return;
        }
    }
    if (cd->env_flags & Collide_CeilingMask) {
        fp->self_vel.y = 0.0f;
    }
}

void ftNn_Init_80123720(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 365, 0x0C4C508A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    fp->accessory4_cb = fn_80123218;
}

void ftNn_Init_8012378C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 362, 0x0C4C508A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    fp->accessory4_cb = fn_80123218;
}

void ftNn_Init_801237F8(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    ftIceClimberAttributes* attrs = nana_fp->dat_attrs;
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    PAD_STACK(0x10);
    if (popo_gobj != NULL) {
        Fighter* popo_fp = GET_FIGHTER(popo_gobj);
        ft_800849EC(popo_fp, nana_fp);
    }
    nana_fp->self_vel.x =
        nana_fp->facing_dir * (attrs->x13C * cosf(attrs->x140));
    nana_fp->self_vel.y = attrs->x13C * sinf(attrs->x140);
    nana_fp->cur_pos.x += 4.0f * nana_fp->facing_dir * nana_fp->x34_scale.y;
    nana_fp->cur_pos.y += 7.0f * nana_fp->x34_scale.y;
    Fighter_ChangeMotionState(nana_gobj, 365, 0, 0.0f, 1.0f, 0.0f, NULL);
    nana_fp->accessory4_cb = fn_80123218;
}

void ftNn_Init_801238E4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_8007592C(fp, 0, 0.0f);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    if (fp->x1A5C != NULL) {
        Fighter* fp2 = GET_FIGHTER(fp->x1A5C);
        Fighter_UnkSetFlag_8006CFBC(fp->x1A5C);
        fp2->x1A5C = NULL;
    }
    fp->x1A5C = NULL;
}

bool ftNn_Init_80123954(Fighter_GObj* nana_gobj, GroundOrAir pp_ga)
{
    bool ret;
    if (nana_gobj != NULL) {
        Fighter* nana_fp = GET_FIGHTER(nana_gobj);
        Fighter* popo_fp =
            GET_FIGHTER(Player_GetEntityAtIndex(nana_fp->player_id, 0));
        switch (nana_fp->x2070.x2071_b0_3) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            nana_fp->x1A5C = NULL;
            ret = true;
            break;
        case 0:
        default: {
            ftIceClimberAttributes* attrs = nana_fp->dat_attrs;
            float dd = attrs->xD0;
            float dx = nana_fp->cur_pos.x - popo_fp->cur_pos.x;
            float dy = nana_fp->cur_pos.y - popo_fp->cur_pos.y;
            if (dx * dx + dy * dy < popo_fp->x34_scale.y * dd * dd) {
                ret = false;
                if (pp_ga == GA_Air) {
                    if (pp_ga != nana_fp->ground_or_air) {
                        ft_800849EC(nana_fp, popo_fp);
                        ftCommon_8007D7FC(popo_fp);
                    }
                    ftNn_Init_80123B3C(nana_gobj);
                }
                nana_fp->mv.pp.unk_80123954.x0 = 0;
                nana_fp->cur_pos = popo_fp->cur_pos;
                nana_fp->self_vel = popo_fp->self_vel;
                nana_fp->gr_vel = popo_fp->gr_vel;
                nana_fp->facing_dir = popo_fp->facing_dir;
                ftParts_80075AF0(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
                nana_fp->x1A5C =
                    Player_GetEntityAtIndex(nana_fp->player_id, 0);
            } else {
                nana_fp->x1A5C = NULL;
                ret = true;
            }
            break;
        }
        }
    } else {
        ret = true;
    }
    return ret;
}

bool ftNn_Init_80123B10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (fp->motion_id) {
    case 359:
    case 360:
        return false;
    default:
        return true;
    }
}

static inline void ftNn_Init_80123B3C_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftNn_Init_80122FAC;
    fp->death2_cb = ftNn_Init_80122FAC;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftNn_Init_80123B3C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(0x10);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    Fighter_ChangeMotionState(gobj, 359, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
    ftAnim_8006EBA4(gobj);
    fp->x74_anim_vel.y = 0.0f;
    fp->self_vel.y = 0.0f;
}

void ftNn_Init_80123BF0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(0x10);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    Fighter_ChangeMotionState(gobj, 360, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
    ftAnim_8006EBA4(gobj);
    fp->x74_anim_vel.y = 0.0f;
    fp->self_vel.y = 0.0f;
}

static inline void ftPp_SpecialS_0_Anim_inline(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    nana_fp->take_dmg_cb = NULL;
    nana_fp->death2_cb = NULL;
    nana_fp->pre_hitlag_cb = NULL;
    nana_fp->post_hitlag_cb = NULL;
    nana_fp->x1A5C = NULL;
}

void ftPp_SpecialS_0_Anim(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    if (!ftPp_SpecialS_8011F964(popo_gobj)) {
        nana_fp->cur_anim_frame = popo_fp->cur_anim_frame;
        return;
    }
    ftNn_Init_801238E4(nana_gobj); // inlined
    ftPp_SpecialS_0_Anim_inline(nana_gobj);
    ft_8008A2BC(nana_gobj);
}

void ftPp_SpecialS_1_Anim(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    ftIceClimberAttributes* attrs = nana_fp->dat_attrs;
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    PAD_STACK(8);
    if (!ftPp_SpecialS_8011F964(popo_gobj)) {
        nana_fp->cur_anim_frame = popo_fp->cur_anim_frame;
        return;
    }
    ftNn_Init_801238E4(nana_gobj); // inlined
    ftPp_SpecialS_0_Anim_inline(nana_gobj);
    if (0.0 == attrs->x12C) {
        ftCo_Fall_Enter(nana_gobj);
    } else {
        ftCommon_8007D60C(nana_fp);
        ftCo_80096900(nana_gobj, 1, 0, 1, 1.0f, attrs->x12C);
    }
}

void ftPp_SpecialS_0_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialS_1_IASA(Fighter_GObj* gobj)
{
    return;
}

void ftPp_SpecialS_0_Phys(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter* popo_fp =
        GET_FIGHTER(Player_GetEntityAtIndex(nana_fp->player_id, 0));
    PAD_STACK(8);
    nana_fp->self_vel = popo_fp->self_vel;
    nana_fp->x74_anim_vel = popo_fp->x74_anim_vel;
    nana_fp->gr_vel = popo_fp->gr_vel;
    nana_fp->xE4_ground_accel_1 = popo_fp->xE4_ground_accel_1;
    nana_fp->facing_dir = popo_fp->facing_dir;
    ftParts_80075AF0(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
}

void ftPp_SpecialS_1_Phys(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter* popo_fp =
        GET_FIGHTER(Player_GetEntityAtIndex(nana_fp->player_id, 0));
    PAD_STACK(8);
    nana_fp->self_vel = popo_fp->self_vel;
    nana_fp->x74_anim_vel = popo_fp->x74_anim_vel;
    nana_fp->gr_vel = popo_fp->gr_vel;
    nana_fp->xE4_ground_accel_1 = popo_fp->xE4_ground_accel_1;
    nana_fp->facing_dir = popo_fp->facing_dir;
    ftParts_80075AF0(nana_fp, 0, M_PI_2 * nana_fp->facing_dir);
}

static inline void ftPp_SpecialS_0_Coll_inline(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);

    ftParts_8007592C(nana_fp, 0, ftParts_80075E78(popo_fp, 0));
}

static inline void ftPp_SpecialS_0_Coll_inline2(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    nana_fp->take_dmg_cb = ftNn_Init_80122FAC;
    nana_fp->death2_cb = ftNn_Init_80122FAC;
    nana_fp->pre_hitlag_cb = efLib_PauseAll;
    nana_fp->post_hitlag_cb = efLib_ResumeAll;
}

static inline void ftPp_SpecialS_0_Coll_inline3(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 360, 0x0C4C528A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
}

void ftPp_SpecialS_0_Coll(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    if (!ftPp_SpecialS_8011F964(popo_gobj) &&
        !ftPp_SpecialS_8011F6FC(popo_gobj))
    {
        nana_fp->cur_pos = popo_fp->cur_pos;
        ft_800849EC(popo_fp, nana_fp);
        if (nana_fp->ground_or_air != popo_fp->ground_or_air) {
            Fighter_ChangeMotionState(nana_gobj, 360, 0x0C4C528A,
                                      nana_fp->cur_anim_frame, 1.0f, 0.0f,
                                      NULL);
        }
        nana_fp->ground_or_air = popo_fp->ground_or_air;
    } else {
        nana_fp->mv.pp.unk_80123954.x0 += 1;
        if (nana_fp->mv.pp.unk_80123954.x0 > 5) {
            nana_fp->mv.pp.unk_80123954.x0 = 5;
        }
        nana_fp->cur_pos.x =
            -((1.5f * (nana_fp->mv.pp.unk_80123954.x0 * nana_fp->facing_dir)) -
              popo_fp->cur_pos.x);
        if (!ft_80082888(nana_gobj, &ftNn_Unk2_803CDD60)) {
            ftPp_SpecialS_0_Coll_inline3(nana_gobj);
        }
    }
    ftPp_SpecialS_0_Coll_inline(nana_gobj);
    ftPp_SpecialS_0_Coll_inline2(nana_gobj);
}

static inline void ftPp_SpecialS_1_Coll_inline3(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftNn_Init_80123B3C_inline(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 359, 0x0C4C528A, fp->cur_anim_frame, 1.0f,
                              0.0f, NULL);
    ftNn_Init_80123B3C_inline(gobj);
}

void ftPp_SpecialS_1_Coll(Fighter_GObj* nana_gobj)
{
    Fighter* nana_fp = GET_FIGHTER(nana_gobj);
    Fighter_GObj* popo_gobj = Player_GetEntityAtIndex(nana_fp->player_id, 0);
    Fighter* popo_fp = GET_FIGHTER(popo_gobj);
    if (!ftPp_SpecialS_8011F964(popo_gobj) &&
        !ftPp_SpecialS_8011F6FC(popo_gobj))
    {
        nana_fp->cur_pos = popo_fp->cur_pos;
        ft_800849EC(popo_fp, nana_fp);
        if (nana_fp->ground_or_air != popo_fp->ground_or_air) {
            Fighter_ChangeMotionState(nana_gobj, 359, 0x0C4C528A,
                                      nana_fp->cur_anim_frame, 1.0f, 0.0f,
                                      NULL);
        }
        nana_fp->ground_or_air = popo_fp->ground_or_air;
    } else {
        nana_fp->mv.pp.unk_80123954.x0 += 1;
        if (nana_fp->mv.pp.unk_80123954.x0 > 5) {
            nana_fp->mv.pp.unk_80123954.x0 = 5;
        }
        nana_fp->cur_pos.x =
            -((1.5f * (nana_fp->mv.pp.unk_80123954.x0 * nana_fp->facing_dir)) -
              popo_fp->cur_pos.x);
        if (!ft_800824A0(nana_gobj, &ftNn_Unk2_803CDD60)) {
            ftPp_SpecialS_1_Coll_inline3(nana_gobj);
        }
    }
    ftPp_SpecialS_0_Coll_inline(nana_gobj);
    ftPp_SpecialS_0_Coll_inline2(nana_gobj);
}

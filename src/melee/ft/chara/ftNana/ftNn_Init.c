#include "ft/forward.h"
#include "ftPopo/forward.h"

#include "ftNn_Init.h"

#include "ft/fighter.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftPopo/ftPp_1211.h"
#include "ftPopo/ftPp_Init.h"
#include "ftPopo/ftPp_SpecialS.h"
#include "ftPopo/types.h"

#include <dolphin/mtx/types.h>

char ftNn_Init_803CD7F8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftNn_Init_803CD820[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

MotionState ftNn_Init_MotionStateTable[] = {
    {
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
        ftPp_SM_SpecialS1,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialS_Anim,
        ftPp_SpecialS_IASA,
        ftPp_SpecialS_Phys,
        ftPp_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialS2,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialSTogether_Anim,
        ftPp_SpecialSTogether_IASA,
        ftPp_SpecialSTogether_Phys,
        ftPp_SpecialSTogether_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirS1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirS_Anim,
        ftPp_SpecialAirS_IASA,
        ftPp_SpecialAirS_Phys,
        ftPp_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirS2,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftPp_SpecialAirSTogether_Anim,
        ftPp_SpecialAirSTogether_IASA,
        ftPp_SpecialAirSTogether_Phys,
        ftPp_SpecialAirSTogether_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHiStart_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiStart_Anim,
        ftPp_SpecialHiStart_IASA,
        ftPp_SpecialHiStart_Phys,
        ftPp_SpecialHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHiThrow_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHi_Anim,
        ftPp_SpecialHi_IASA,
        ftPp_SpecialHi_Phys,
        ftPp_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHiThrow2,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_MS_349_Anim,
        ftPp_MS_349_IASA,
        ftPp_MS_349_Phys,
        ftPp_MS_349_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHiStart_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiFail_Anim,
        ftPp_SpecialHiFail_IASA,
        ftPp_SpecialHiFail_Phys,
        ftPp_SpecialHiFail_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHiThrow_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialHiFailEnd_Anim,
        ftPp_SpecialHiFailEnd_IASA,
        ftPp_SpecialHiFailEnd_Phys,
        ftPp_SpecialHiFailEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirHiStart_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiStart_Anim,
        ftPp_SpecialAirHiStart_IASA,
        ftPp_SpecialAirHiStart_Phys,
        ftPp_SpecialAirHiStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirHiThrow_0,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHi_Anim,
        ftPp_SpecialAirHi_IASA,
        ftPp_SpecialAirHi_Phys,
        ftPp_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirHiThrow2,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiFail_Anim,
        ftPp_SpecialAirHiFail_IASA,
        ftPp_SpecialAirHiFail_Phys,
        ftPp_SpecialAirHiFail_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirHiStart_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialAirHiFailEnd_Anim,
        ftPp_SpecialAirHiFailEnd_IASA,
        ftPp_SpecialAirHiFailEnd_Phys,
        ftPp_SpecialAirHiFailEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        /// @todo Fix names, this is part of SpecialHi
        ftPp_SM_SpecialAirHiThrow_1,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftPp_SpecialLw_Anim,
        ftPp_SpecialLw_IASA,
        ftPp_SpecialLw_Phys,
        ftPp_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialLw,
        ftPp_MF_SpecialLw,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialAirLw_Anim,
        ftPp_SpecialAirLw_IASA,
        ftPp_SpecialAirLw_Phys,
        ftPp_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialAirLw,
        ftPp_MF_MS_358,
        (FtMoveId_SpecialLw << 24) | (1 << 23),
        ftPp_SpecialLw_80122A8C,
        ftPp_SpecialLw_80122B10,
        ftPp_SpecialLw_80122B34,
        ftPp_SpecialLw_80122D04,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialS_0,
        ftPp_MF_SpecialS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftNn_Init_80123CA4,
        ftNn_Init_80123E58,
        ftNn_Init_80123E60,
        ftNn_Init_80123F98,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialS_1,
        ftPp_MF_SpecialAirS,
        (FtMoveId_SpecialS << 24) | (1 << 23),
        ftNn_Init_80123D68,
        ftNn_Init_80123E5C,
        ftNn_Init_80123EFC,
        ftNn_Init_801241A0,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHi_0,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNn_Init_80123348,
        ftNn_Init_80123388,
        ftNn_Init_80123390,
        ftNn_Init_801233F0,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHi_1,
        ftPp_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftNn_Init_80123448,
        ftNn_Init_801234E4,
        ftNn_Init_801234EC,
        ftNn_Init_801235BC,
        ftCamera_UpdateCameraBox,
    },
    {
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
        ftPp_SM_SpecialHi_3,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftNn_Init_80123384,
        ftNn_Init_8012338C,
        ftNn_Init_801233EC,
        ftNn_Init_801233F4,
        ftCamera_UpdateCameraBox,
    },
    {
        ftPp_SM_SpecialHi_4,
        ftPp_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftNn_Init_80123484,
        ftNn_Init_801234E8,
        ftNn_Init_8012350C,
        ftNn_Init_801235F8,
        ftCamera_UpdateCameraBox,
    },
    {
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

extern f32 ftNn_Init_804D9898;

void ftNn_Init_OnLoad(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2222_flag.bits.b4 = true;
    ftPp_Init_OnLoadForNana(fp);

    {
        ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
        fp->x40 = attr->xC4;
    }
}

void ftNn_Init_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
    fp->dmg.x18B0 = attr->xC8;
    ftParts_80074A4C(gobj, 0U, 0);
    ftParts_80074A4C(gobj, 1U, 0);
    fp->fv.nn.x2234 = 0;
    fp->fv.nn.x222C = 0;
    fp->fv.nn.x2230.bits.b0 = 0;
    fp->fv.nn.x2238 = 0;
    fp->fv.nn.x224C = 0;
    fp->fv.nn.x2250 = ftNn_Init_804D9898;
}

/* static */ void ftNn_Init_801238E4(HSD_GObj* gobj);

void ftNn_Init_80122FAC(HSD_GObj* gobj)
{
    ftNn_Init_801238E4(gobj);
}

void ftNn_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftIceClimberAttributes);
}

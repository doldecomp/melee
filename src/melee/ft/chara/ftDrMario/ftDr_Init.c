#include "ftDr_Init.h"

#include "ftDr_AppealS.h"
#include "types.h"

#include "forward.h"

#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"

#include "ftMario/forward.h"

#include "ftMario/ftMr_Init.h"
#include "ftMario/ftMr_SpecialHi.h"
#include "ftMario/ftMr_SpecialLw.h"
#include "ftMario/ftMr_SpecialN.h"
#include "ftMario/ftMr_SpecialS.h"
#include "ftMario/types.h"
#include "it/it_26B1.h"
#include "it/items/itdrmariopill.h"

MotionState ftDr_Init_MotionStateTable[ftMr_MS_SelfCount] = {
    {
        // ftMr_MS_AppealSR = 341
        ftCo_SM_AppealSR,
        ftDr_MF_Appeal,
        FtMoveId_Default << 24,
        ftDr_AppealS_Anim,
        ftDr_AppealS_IASA,
        ftDr_AppealS_Phys,
        ftDr_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_AppealSL = 342
        ftCo_SM_AppealSL,
        ftDr_MF_Appeal,
        FtMoveId_Default << 24,
        ftDr_AppealS_Anim,
        ftDr_AppealS_IASA,
        ftDr_AppealS_Phys,
        ftDr_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialN = 343
        ftMr_SM_SpecialN,
        ftMr_MF_SpecialN,
        FtMoveId_SpecialN << 24,
        ftMr_SpecialN_Anim,
        ftMr_SpecialN_IASA,
        ftMr_SpecialN_Phys,
        ftMr_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialAirN = 344
        ftMr_SM_SpecialAirN,
        ftMr_MF_SpecialAirN,
        FtMoveId_SpecialN << 24,
        ftMr_SpecialAirN_Anim,
        ftMr_SpecialAirN_IASA,
        ftMr_SpecialAirN_Phys,
        ftMr_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialS = 345
        ftMr_SM_SpecialS,
        ftMr_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMr_SpecialS_Anim,
        ftMr_SpecialS_IASA,
        ftMr_SpecialS_Phys,
        ftMr_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialAirS = 346
        ftMr_SM_SpecialAirS,
        ftMr_MF_SpecialS,
        FtMoveId_SpecialS << 24,
        ftMr_SpecialAirS_Anim,
        ftMr_SpecialAirS_IASA,
        ftMr_SpecialAirS_Phys,
        ftMr_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialHi = 347
        ftMr_SM_SpecialHi,
        ftMr_MF_SpecialHi,
        FtMoveId_SpecialHi << 24,
        ftMr_SpecialHi_Anim,
        ftMr_SpecialHi_IASA,
        ftMr_SpecialHi_Phys,
        ftMr_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialAirHi = 348
        ftMr_SM_SpecialAirHi,
        ftMr_MF_SpecialAirHi,
        FtMoveId_SpecialHi << 24,
        ftMr_SpecialAirHi_Anim,
        ftMr_SpecialAirHi_IASA,
        ftMr_SpecialAirHi_Phys,
        ftMr_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialLw = 349
        ftMr_SM_SpecialLw,
        ftMr_MF_SpecialLw,
        FtMoveId_SpecialLw << 24,
        ftMr_SpecialLw_Anim,
        ftMr_SpecialLw_IASA,
        ftMr_SpecialLw_Phys,
        ftMr_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        // ftMr_MS_SpecialAirLw = 350
        ftMr_SM_SpecialAirLw,
        ftMr_MF_SpecialAirLw,
        FtMoveId_SpecialLw << 24,
        ftMr_SpecialAirLw_Anim,
        ftMr_SpecialAirLw_IASA,
        ftMr_SpecialAirLw_Phys,
        ftMr_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftDr_Init_DatFilename[] = "PlDr.dat";
char ftDr_Init_DataName[] = "ftDataDrmario";
char ftDr_Init_803D15F4[] = "PlDrNr.dat";
char ftDr_Init_803D1600[] = "PlyDrmario5K_Share_joint";
char ftDr_Init_803D161C[] = "PlyDrmario5K_Share_matanim_joint";
char ftDr_Init_803D1640[] = "PlDrRe.dat";
char ftDr_Init_803D164C[] = "PlyDrmario5KRe_Share_joint";
char ftDr_Init_803D1668[] = "PlyDrmario5KRe_Share_matanim_joint";
char ftDr_Init_803D168C[] = "PlDrBu.dat";
char ftDr_Init_803D1698[] = "PlyDrmario5KBu_Share_joint";
char ftDr_Init_803D16B4[] = "PlyDrmario5KBu_Share_matanim_joint";
char ftDr_Init_803D16D8[] = "PlDrGr.dat";
char ftDr_Init_803D16E4[] = "PlyDrmario5KGr_Share_joint";
char ftDr_Init_803D1700[] = "PlyDrmario5KGr_Share_matanim_joint";
char ftDr_Init_803D1724[] = "PlDrBk.dat";
char ftDr_Init_803D1730[] = "PlyDrmario5KBk_Share_joint";
char ftDr_Init_803D174C[] = "PlyDrmario5KBk_Share_matanim_joint";
char ftDr_Init_AnimDatFilename[] = "PlDrAJ.dat";

Fighter_DemoStrings ftDr_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileDrmario",
    "ftDemoIntroMotionFileDrmario",
    "ftDemoEndingMotionFileDrmario",
    "ftDemoViWaitMotionFileDrmario",
};

Fighter_CostumeStrings ftDr_Init_CostumeStrings[] = {
    { ftDr_Init_803D15F4, ftDr_Init_803D1600, ftDr_Init_803D161C },
    { ftDr_Init_803D1640, ftDr_Init_803D164C, ftDr_Init_803D1668 },
    { ftDr_Init_803D168C, ftDr_Init_803D1698, ftDr_Init_803D16B4 },
    { ftDr_Init_803D16D8, ftDr_Init_803D16E4, ftDr_Init_803D1700 },
    { ftDr_Init_803D1724, ftDr_Init_803D1730, ftDr_Init_803D174C },
};

void ftDr_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.mr.x2234_tornadoCharge = 0;
    fp->fv.mr.x2238_isCapeBoost = false;
    fp->fv.mr.x223C_capeGObj = NULL;
    fp->fv.mr.x2240 = 0;
}

void ftDr_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp;
    void** items;
    ftDrMarioAttributes* sa;

    u8 _[8];

    fp = gobj->user_data;
    items = fp->ft_data->x48_items;
    ftMr_Init_OnLoadForDrMario(fp);
    sa = fp->dat_attrs;
    it_8026B3F8(items[1], 0x31);
    it_8026B3F8(items[3], sa->x14);
}

void ftDr_Init_80149540(HSD_GObj* gobj)
{
    ftDr_Init_801497CC(gobj);
}

void ftDr_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftDr_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftDr_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftDr_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftDr_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMr_Init_LoadSpecialAttrs(gobj);
}

void ftDr_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftDr_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftDr_Init_801497CC(HSD_GObj* gobj)
{
    Fighter* fp;

    u8 _[8];

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->fv.mr.x2240 != 0) {
            itDrMarioPill_802C0DBC(fp->fv.mr.x2240);
            fp->fv.mr.x2240 = 0;
        }
    }

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            fp->take_dmg_cb = 0;
            fp->death2_cb = 0;
        }
    }
}

bool ftDr_Init_80149844(HSD_GObj* gobj)
{
    s32 tmp;
    Fighter* fp;

    if (gobj == NULL) {
        return true;
    }
    fp = gobj->user_data;
    if (fp == NULL) {
        return true;
    }
    tmp = fp->motion_id;
    if (tmp != 0x155 && tmp != 0x156) {
        return true;
    }
    if (fp->fv.mr.x2240 == 0) {
        return true;
    }
    return false;
}

void ftDr_Init_801498A0(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->fv.mr.x2240 != 0) {
            fp->fv.mr.x2240 = 0;
        }
    }
    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            fp->take_dmg_cb = 0;
            fp->death2_cb = 0;
        }
    }
}

u32 ftDr_Init_801498EC(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            return fp->cmd_vars[1];
        }
    }

    return 0;
}

void ftDr_Init_80149910(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCo_800DEAE8(gobj, ftMr_MS_AppealSR, ftMr_MS_AppealSL);
    fp->cmd_vars[0] = 1;
    fp->cmd_vars[1] = 0;
}

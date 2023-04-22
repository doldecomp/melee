#include "forward.h"
#include "ft/forward.h"

#include "ftFox/ftFx_Init.h"

#include "ftFx_Appeal.h"
#include "ftFx_SpecialHi.h"
#include "ftFx_SpecialLw.h"
#include "ftFx_SpecialN.h"
#include "ftFx_SpecialS.h"

#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

MotionState ftFx_Init_MotionStateTable[] = {
    {
        295,
        ftFx_MF_SpecialN,
        FtMoveId_SpecialN * (1 << 24),
        ftFx_SpecialNStart_Anim,
        ftFx_SpecialNStart_IASA,
        ftFx_SpecialNStart_Phys,
        ftFx_SpecialNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        ftFx_MF_SpecialNLoop,
        FtMoveId_SpecialN * (1 << 24),
        ftFx_SpecialNLoop_Anim,
        ftFx_SpecialNLoop_IASA,
        ftFx_SpecialNLoop_Phys,
        ftFx_SpecialNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        ftFx_MF_SpecialN,
        FtMoveId_SpecialN * (1 << 24),
        ftFx_SpecialNEnd_Anim,
        ftFx_SpecialNEnd_IASA,
        ftFx_SpecialNEnd_Phys,
        ftFx_SpecialNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        ftFx_MF_SpecialAirN,
        FtMoveId_SpecialN * (1 << 24),
        ftFx_SpecialAirNStart_Anim,
        ftFx_SpecialAirNStart_IASA,
        ftFx_SpecialAirNStart_Phys,
        ftFx_SpecialAirNStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        ftFx_MF_SpecialAirNLoop,
        FtMoveId_SpecialN * (1 << 24),
        ftFx_SpecialAirNLoop_Anim,
        ftFx_SpecialAirNLoop_IASA,
        ftFx_SpecialAirNLoop_Phys,
        ftFx_SpecialAirNLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        ftFx_MF_SpecialAirN,
        FtMoveId_SpecialN * (1 << 24),
        ftFx_SpecialAirNEnd_Anim,
        ftFx_SpecialAirNEnd_IASA,
        ftFx_SpecialAirNEnd_Phys,
        ftFx_SpecialAirNEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        ftFx_MF_SpecialS,
        FtMoveId_SpecialS * (1 << 24),
        ftFx_SpecialSStart_Anim,
        ftFx_SpecialSStart_IASA,
        ftFx_SpecialSStart_Phys,
        ftFx_SpecialSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        ftFx_MF_SpecialS,
        FtMoveId_SpecialS * (1 << 24),
        ftFx_SpecialS_Anim,
        ftFx_SpecialS_IASA,
        ftFx_SpecialS_Phys,
        ftFx_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        303,
        ftFx_MF_SpecialS,
        FtMoveId_SpecialS * (1 << 24),
        ftFx_SpecialSEnd_Anim,
        ftFx_SpecialSEnd_IASA,
        ftFx_SpecialSEnd_Phys,
        ftFx_SpecialSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        304,
        ftFx_MF_SpecialAirS,
        FtMoveId_SpecialS * (1 << 24),
        ftFx_SpecialAirSStart_Anim,
        ftFx_SpecialAirSStart_IASA,
        ftFx_SpecialAirSStart_Phys,
        ftFx_SpecialAirSStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        305,
        ftFx_MF_SpecialAirS,
        FtMoveId_SpecialS * (1 << 24),
        ftFx_SpecialAirS_Anim,
        ftFx_SpecialAirS_IASA,
        ftFx_SpecialAirS_Phys,
        ftFx_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        306,
        ftFx_MF_SpecialAirS,
        FtMoveId_SpecialS * (1 << 24),
        ftFx_SpecialAirSEnd_Anim,
        ftFx_SpecialAirSEnd_IASA,
        ftFx_SpecialAirSEnd_Phys,
        ftFx_SpecialAirSEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        307,
        ftFx_MF_SpecialHi,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialHiHold_Anim,
        ftFx_SpecialHiHold_IASA,
        ftFx_SpecialHiHold_Phys,
        ftFx_SpecialHiHold_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        308,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialHiHoldAir_Anim,
        ftFx_SpecialHiHoldAir_IASA,
        ftFx_SpecialHiHoldAir_Phys,
        ftFx_SpecialHiHoldAir_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        ftFx_MF_SpecialHi,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialHi_Anim,
        ftFx_SpecialHi_IASA,
        ftFx_SpecialHi_Phys,
        ftFx_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        309,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialAirHi_Anim,
        ftFx_SpecialAirHi_IASA,
        ftFx_SpecialAirHi_Phys,
        ftFx_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        310,
        ftFx_MF_SpecialHi,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialHiLanding_Anim,
        ftFx_SpecialHiLanding_IASA,
        ftFx_SpecialHiLanding_Phys,
        ftFx_SpecialHiLanding_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        311,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialHiFall_Anim,
        ftFx_SpecialHiFall_IASA,
        ftFx_SpecialHiFall_Phys,
        ftFx_SpecialHiFall_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        312,
        ftFx_MF_SpecialAirHiHold,
        FtMoveId_SpecialHi * (1 << 24),
        ftFx_SpecialHiBound_Anim,
        ftFx_SpecialHiBound_IASA,
        ftFx_SpecialHiBound_Phys,
        ftFx_SpecialHiBound_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        313,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialLwStart_Anim,
        ftFx_SpecialLwStart_IASA,
        ftFx_SpecialLwStart_Phys,
        ftFx_SpecialLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        ftFx_MF_SpecialLwLoop,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialLwLoop_Anim,
        ftFx_SpecialLwLoop_IASA,
        ftFx_SpecialLwLoop_Phys,
        ftFx_SpecialLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        315,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialLwHit_Anim,
        ftFx_SpecialLwHit_IASA,
        ftFx_SpecialLwHit_Phys,
        ftFx_SpecialLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        316,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialLwEnd_Anim,
        ftFx_SpecialLwEnd_IASA,
        ftFx_SpecialLwEnd_Phys,
        ftFx_SpecialLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        314,
        ftFx_MF_SpecialLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialLwTurn_Anim,
        ftFx_SpecialLwTurn_IASA,
        ftFx_SpecialLwTurn_Phys,
        ftFx_SpecialLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        317,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialAirLwStart_Anim,
        ftFx_SpecialAirLwStart_IASA,
        ftFx_SpecialAirLwStart_Phys,
        ftFx_SpecialAirLwStart_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        318,
        ftFx_MF_SpecialAirLwLoop,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialAirLwLoop_Anim,
        ftFx_SpecialAirLwLoop_IASA,
        ftFx_SpecialAirLwLoop_Phys,
        ftFx_SpecialAirLwLoop_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        319,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialAirLwHit_Anim,
        ftFx_SpecialAirLwHit_IASA,
        ftFx_SpecialAirLwHit_Phys,
        ftFx_SpecialAirLwHit_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        320,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialAirLwEnd_Anim,
        ftFx_SpecialAirLwEnd_IASA,
        ftFx_SpecialAirLwEnd_Phys,
        ftFx_SpecialAirLwEnd_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        318,
        ftFx_MF_SpecialAirLw,
        FtMoveId_SpecialLw * (1 << 24),
        ftFx_SpecialAirLwTurn_Anim,
        ftFx_SpecialAirLwTurn_IASA,
        ftFx_SpecialAirLwTurn_Phys,
        ftFx_SpecialAirLwTurn_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        321,
        ftFx_MF_Appeal,
        FtMoveId_Unk01 * (1 << 24),
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        322,
        ftFx_MF_Appeal,
        FtMoveId_Unk01 * (1 << 24),
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        323,
        ftFx_MF_Appeal,
        FtMoveId_Unk01 * (1 << 24),
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        324,
        ftFx_MF_Appeal,
        FtMoveId_Unk01 * (1 << 24),
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        325,
        ftFx_MF_Appeal,
        FtMoveId_Unk01 * (1 << 24),
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        326,
        ftFx_MF_Appeal,
        1 * (1 << 24),
        ftFx_AppealS_Anim,
        ftFx_AppealS_IASA,
        ftFx_AppealS_Phys,
        ftFx_AppealS_Coll,
        ftCamera_UpdateCameraBox,
    },
};

char ftFx_Init_DatFilename[] = "PlFx.dat";
char ftFx_Init_DataName[] = "ftDataFox";
char ftFx_Init_803C7C00[] = "PlFxNr.dat";
char ftFx_Init_803C7C0C[] = "PlyFox5K_Share_joint";
char ftFx_Init_803C7C24[] = "PlyFox5K_Share_matanim_joint";
char ftFx_Init_803C7C44[] = "PlFxOr.dat";
char ftFx_Init_803C7C50[] = "PlyFox5KOr_Share_joint";
char ftFx_Init_803C7C68[] = "PlyFox5KOr_Share_matanim_joint";
char ftFx_Init_803C7C88[] = "PlFxLa.dat";
char ftFx_Init_803C7C94[] = "PlyFox5KLa_Share_joint";
char ftFx_Init_803C7CAC[] = "PlyFox5KLa_Share_matanim_joint";
char ftFx_Init_803C7CCC[] = "PlFxGr.dat";
char ftFx_Init_803C7CD8[] = "PlyFox5KGr_Share_joint";
char ftFx_Init_803C7CF0[] = "PlyFox5KGr_Share_matanim_joint";
char ftFx_Init_AnimDatFilename[] = "PlFxAJ.dat";

Fighter_DemoStrings ftFx_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileFox",
    "ftDemoIntroMotionFileFox",
    "ftDemoEndingMotionFileFox",
    "ftDemoViWaitMotionFileFox",
};

Fighter_CostumeStrings ftFx_Init_CostumeStrings[] = {
    { ftFx_Init_803C7C00, ftFx_Init_803C7C0C, ftFx_Init_803C7C24 },
    { ftFx_Init_803C7C44, ftFx_Init_803C7C50, ftFx_Init_803C7C68 },
    { ftFx_Init_803C7C88, ftFx_Init_803C7C94, ftFx_Init_803C7CAC },
    { ftFx_Init_803C7CCC, ftFx_Init_803C7CD8, ftFx_Init_803C7CF0 },
};

bool ftFx_Init_800E5534(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;

    return fp->fv.fx.x222C_blasterGObj ? true : false;
}

void ftFx_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) gobj->user_data;

    fp->fv.fx.x222C_blasterGObj = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftFx_Init_800E5588(HSD_GObj* gobj)
{
    ftFx_SpecialN_RemoveBlaster(gobj);
}

void ftFx_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftFx_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftFx_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftFx_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftFx_Init_OnLoadForFalco(Fighter* fp)
{
    PUSH_ATTRS(fp, ftFoxAttributes);
}

void ftFx_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    void** item_list = fp->ft_data->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftFoxAttributes);

    {
        ftFoxAttributes* fox_attr = fp->x2D4_specialAttributes;
        it_8026B3F8(item_list[0], fox_attr->x1C_FOX_BLASTER_SHOT_ITKIND);
        it_8026B3F8(item_list[1], fox_attr->x20_FOX_BLASTER_GUN_ITKIND);
        it_8026B3F8(item_list[2], It_Kind_Fox_Illusion);
    }
}

void ftFx_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftFoxAttributes);
}

extern f32 lbl_804D9244; /// 0.0f

void ftFx_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 3, 0.0f);
}

void ftFx_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
    ftAnim_ApplyPartAnim(gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(gobj, 4, 2, 0.0f);
}

//// End of File

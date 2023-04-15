#include "ftnana.h"

#include "ft/fighter.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftPopo/fticeclimber.h"
#include "ftPopo/ftpopo_init.h"

#include <dolphin/mtx/types.h>

char ftNn_Init_803CD7F8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 ftNn_Init_803CD820[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

MotionState ftNn_Init_MotionStateTable[] = {
    { 295, 0x00340111, 0x12800000, ftPp_SpecialN_8011F318,
      ftPp_SpecialN_8011F390, ftPp_SpecialN_8011F398, ftPp_SpecialN_8011F3D8,
      ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12800000, ftPp_SpecialN_8011F354,
      ftPp_SpecialN_8011F394, ftPp_SpecialN_8011F3B8, ftPp_SpecialN_8011F454,
      ftCamera_UpdateCameraBox },
    { 297, 0x00340212, 0x13800000, ftPp_SpecialS_8011FC78,
      ftPp_SpecialS_8011FF40, ftPp_SpecialS_80120080, ftPp_SpecialS_80120660,
      ftCamera_UpdateCameraBox },
    { 298, 0x00340212, 0x13800000, ftPp_SpecialS_8011FCD0,
      ftPp_SpecialS_8011FF90, ftPp_SpecialS_80120230, ftPp_SpecialS_80120854,
      ftCamera_UpdateCameraBox },
    { 299, 0x00340612, 0x13800000, ftPp_SpecialS_8011FD9C,
      ftPp_SpecialS_8011FFE0, ftPp_SpecialS_801203E0, ftPp_SpecialS_80120A48,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340612, 0x13800000, ftPp_SpecialS_8011FE48,
      ftPp_SpecialS_80120030, ftPp_SpecialS_80120520, ftPp_SpecialS_80120C58,
      ftCamera_UpdateCameraBox },
    { 301, 0x00340213, 0x14000000, ftPp_SpecialHi_801212C4,
      ftPp_SpecialHi_801214D4, ftPp_SpecialHi_801215DC,
      ftPp_SpecialHi_80121740, ftCamera_UpdateCameraBox },
    { 302, 0x00340213, 0x14000000, ftPp_SpecialHi_80121944,
      ftPp_SpecialHi_80121AC8, ftPp_SpecialHi_80121AD0,
      ftPp_SpecialHi_80121C34, ftCamera_UpdateCameraBox },
    { 303, 0x00340213, 0x14000000, ftPp_SpecialHi_801223B8,
      ftPp_SpecialHi_8012248C, ftPp_SpecialHi_80122494,
      ftPp_SpecialHi_80122664, ftCamera_UpdateCameraBox },
    { 304, 0x00340213, 0x14000000, ftPp_SpecialHi_80121E10,
      ftPp_SpecialHi_80121EB0, ftPp_SpecialHi_80121EB8,
      ftPp_SpecialHi_80121F2C, ftCamera_UpdateCameraBox },
    { 305, 0x00340213, 0x14000000, ftPp_SpecialHi_80122110,
      ftPp_SpecialHi_801221AC, ftPp_SpecialHi_801221B4,
      ftPp_SpecialHi_80122228, ftCamera_UpdateCameraBox },
    { 306, 0x00340613, 0x14000000, ftPp_SpecialHi_801213CC,
      ftPp_SpecialHi_80121558, ftPp_SpecialHi_80121680,
      ftPp_SpecialHi_8012177C, ftCamera_UpdateCameraBox },
    { 307, 0x00340613, 0x14000000, ftPp_SpecialHi_801219F4,
      ftPp_SpecialHi_80121ACC, ftPp_SpecialHi_80121B74,
      ftPp_SpecialHi_80121C70, ftCamera_UpdateCameraBox },
    { 308, 0x00340613, 0x14000000, ftPp_SpecialHi_80122410,
      ftPp_SpecialHi_80122490, ftPp_SpecialHi_80122538,
      ftPp_SpecialHi_801226A0, ftCamera_UpdateCameraBox },
    { 309, 0x00340613, 0x14000000, ftPp_SpecialHi_80121E4C,
      ftPp_SpecialHi_80121EB4, ftPp_SpecialHi_80121ED8,
      ftPp_SpecialHi_80121F68, ftCamera_UpdateCameraBox },
    { 310, 0x00340613, 0x14000000, ftPp_SpecialHi_8012214C,
      ftPp_SpecialHi_801221B0, ftPp_SpecialHi_801221D4,
      ftPp_SpecialHi_80122264, ftCamera_UpdateCameraBox },
    { 311, 0x00340014, 0x15800000, ftPp_SpecialLw_80122A0C,
      ftPp_SpecialLw_80122B0C, ftPp_SpecialLw_80122B14,
      ftPp_SpecialLw_80122C18, ftCamera_UpdateCameraBox },
    { 312, 0x00340414, 0x15800000, ftPp_SpecialLw_80122A8C,
      ftPp_SpecialLw_80122B10, ftPp_SpecialLw_80122B34,
      ftPp_SpecialLw_80122D04, ftCamera_UpdateCameraBox },
    { 313, 0x00340212, 0x13800000, ftNn_Init_80123CA4, ftNn_Init_80123E58,
      ftNn_Init_80123E60, ftNn_Init_80123F98, ftCamera_UpdateCameraBox },
    { 314, 0x00340612, 0x13800000, ftNn_Init_80123D68, ftNn_Init_80123E5C,
      ftNn_Init_80123EFC, ftNn_Init_801241A0, ftCamera_UpdateCameraBox },
    { 315, 0x00340213, 0x14000000, ftNn_Init_80123348, ftNn_Init_80123388,
      ftNn_Init_80123390, ftNn_Init_801233F0, ftCamera_UpdateCameraBox },
    { 316, 0x00340213, 0x14000000, ftNn_Init_80123448, ftNn_Init_801234E4,
      ftNn_Init_801234EC, ftNn_Init_801235BC, ftCamera_UpdateCameraBox },
    { 317, 0x00340213, 0x14000000, NULL, NULL, NULL, NULL,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340613, 0x14000000, ftNn_Init_80123384, ftNn_Init_8012338C,
      ftNn_Init_801233EC, ftNn_Init_801233F4, ftCamera_UpdateCameraBox },
    { 319, 0x00340613, 0x14000000, ftNn_Init_80123484, ftNn_Init_801234E8,
      ftNn_Init_8012350C, ftNn_Init_801235F8, ftCamera_UpdateCameraBox },
    { 320, 0x00340613, 0x14000000, NULL, NULL, NULL, NULL,
      ftCamera_UpdateCameraBox },
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

extern f32 lbl_804D9898;

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
    fp->fv.nn.x2250 = lbl_804D9898;
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

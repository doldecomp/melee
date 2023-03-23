#include "ftnana.h"

#include "fticeclimber.h"

#include "ft/fighter.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <dolphin/mtx/types.h>

char lbl_803CD7F8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 lbl_803CD820[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

MotionState ftNana_MotionStateTable[] = {
    { 295, 0x00340111, 0x12800000, ftPopo_8011F318, ftPopo_8011F390,
      ftPopo_8011F398, ftPopo_8011F3D8, ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12800000, ftPopo_8011F354, ftPopo_8011F394,
      ftPopo_8011F3B8, ftPopo_8011F454, ftCamera_UpdateCameraBox },
    { 297, 0x00340212, 0x13800000, ftPopo_8011FC78, ftPopo_8011FF40,
      ftPopo_80120080, ftPopo_80120660, ftCamera_UpdateCameraBox },
    { 298, 0x00340212, 0x13800000, ftPopo_8011FCD0, ftPopo_8011FF90,
      ftPopo_80120230, ftPopo_80120854, ftCamera_UpdateCameraBox },
    { 299, 0x00340612, 0x13800000, ftPopo_8011FD9C, ftPopo_8011FFE0,
      ftPopo_801203E0, ftPopo_80120A48, ftCamera_UpdateCameraBox },
    { 300, 0x00340612, 0x13800000, ftPopo_8011FE48, ftPopo_80120030,
      ftPopo_80120520, ftPopo_80120C58, ftCamera_UpdateCameraBox },
    { 301, 0x00340213, 0x14000000, ftPopo_801212C4, ftPopo_801214D4,
      ftPopo_801215DC, ftPopo_80121740, ftCamera_UpdateCameraBox },
    { 302, 0x00340213, 0x14000000, ftPopo_80121944, ftPopo_80121AC8,
      ftPopo_80121AD0, ftPopo_80121C34, ftCamera_UpdateCameraBox },
    { 303, 0x00340213, 0x14000000, ftPopo_801223B8, ftPopo_8012248C,
      ftPopo_80122494, ftPopo_80122664, ftCamera_UpdateCameraBox },
    { 304, 0x00340213, 0x14000000, ftPopo_80121E10, ftPopo_80121EB0,
      ftPopo_80121EB8, ftPopo_80121F2C, ftCamera_UpdateCameraBox },
    { 305, 0x00340213, 0x14000000, ftPopo_80122110, ftPopo_801221AC,
      ftPopo_801221B4, ftPopo_80122228, ftCamera_UpdateCameraBox },
    { 306, 0x00340613, 0x14000000, ftPopo_801213CC, ftPopo_80121558,
      ftPopo_80121680, ftPopo_8012177C, ftCamera_UpdateCameraBox },
    { 307, 0x00340613, 0x14000000, ftPopo_801219F4, ftPopo_80121ACC,
      ftPopo_80121B74, ftPopo_80121C70, ftCamera_UpdateCameraBox },
    { 308, 0x00340613, 0x14000000, ftPopo_80122410, ftPopo_80122490,
      ftPopo_80122538, ftPopo_801226A0, ftCamera_UpdateCameraBox },
    { 309, 0x00340613, 0x14000000, ftPopo_80121E4C, ftPopo_80121EB4,
      ftPopo_80121ED8, ftPopo_80121F68, ftCamera_UpdateCameraBox },
    { 310, 0x00340613, 0x14000000, ftPopo_8012214C, ftPopo_801221B0,
      ftPopo_801221D4, ftPopo_80122264, ftCamera_UpdateCameraBox },
    { 311, 0x00340014, 0x15800000, ftPopo_80122A0C, ftPopo_80122B0C,
      ftPopo_80122B14, ftPopo_80122C18, ftCamera_UpdateCameraBox },
    { 312, 0x00340414, 0x15800000, ftPopo_80122A8C, ftPopo_80122B10,
      ftPopo_80122B34, ftPopo_80122D04, ftCamera_UpdateCameraBox },
    { 313, 0x00340212, 0x13800000, ftNana_80123CA4, ftNana_80123E58,
      ftNana_80123E60, ftNana_80123F98, ftCamera_UpdateCameraBox },
    { 314, 0x00340612, 0x13800000, ftNana_80123D68, ftNana_80123E5C,
      ftNana_80123EFC, ftNana_801241A0, ftCamera_UpdateCameraBox },
    { 315, 0x00340213, 0x14000000, ftNana_80123348, ftNana_80123388,
      ftNana_80123390, ftNana_801233F0, ftCamera_UpdateCameraBox },
    { 316, 0x00340213, 0x14000000, ftNana_80123448, ftNana_801234E4,
      ftNana_801234EC, ftNana_801235BC, ftCamera_UpdateCameraBox },
    { 317, 0x00340213, 0x14000000, NULL, NULL, NULL, NULL,
      ftCamera_UpdateCameraBox },
    { 318, 0x00340613, 0x14000000, ftNana_80123384, ftNana_8012338C,
      ftNana_801233EC, ftNana_801233F4, ftCamera_UpdateCameraBox },
    { 319, 0x00340613, 0x14000000, ftNana_80123484, ftNana_801234E8,
      ftNana_8012350C, ftNana_801235F8, ftCamera_UpdateCameraBox },
    { 320, 0x00340613, 0x14000000, NULL, NULL, NULL, NULL,
      ftCamera_UpdateCameraBox },
};

char lbl_803CDB78[] = "PlNn.dat";
char lbl_803CDB84[] = "ftDataNana";
char lbl_803CDB90[] = "PlNnNr.dat";
char lbl_803CDB9C[] = "PlyNana5K_Share_joint";
char lbl_803CDBB4[] = "PlyNana5K_Share_matanim_joint";
char lbl_803CDBD4[] = "PlNnYe.dat";
char lbl_803CDBE0[] = "PlyNana5KYe_Share_joint";
char lbl_803CDBF8[] = "PlyNana5KYe_Share_matanim_joint";
char lbl_803CDC18[] = "PlNnAq.dat";
char lbl_803CDC24[] = "PlyNana5KAq_Share_joint";
char lbl_803CDC3C[] = "PlyNana5KAq_Share_matanim_joint";
char lbl_803CDC5C[] = "PlNnWh.dat";
char lbl_803CDC68[] = "PlyNana5KWh_Share_joint";
char lbl_803CDC80[] = "PlyNana5KWh_Share_matanim_joint";
char lbl_803CDCA0[] = "PlNnAJ.dat";
char lbl_803CDCAC[] = "ftDemoResultMotionFileNana";
char lbl_803CDCC8[] = "ftDemoIntroMotionFileNana";
char lbl_803CDCE4[] = "ftDemoEndingMotionFileNana";
char lbl_803CDD00[] = "ftDemoViWaitMotionFilePopo";

Fighter_DemoStrings lbl_803CDD1C = {
    lbl_803CDCAC,
    lbl_803CDCC8,
    lbl_803CDCE4,
    lbl_803CDD00,
};

Fighter_CostumeStrings lbl_803CDD2C[] = {
    { lbl_803CDB90, lbl_803CDB9C, lbl_803CDBB4 },
    { lbl_803CDBD4, lbl_803CDBE0, lbl_803CDBF8 },
    { lbl_803CDC18, lbl_803CDC24, lbl_803CDC3C },
    { lbl_803CDC5C, lbl_803CDC68, lbl_803CDC80 },
};

extern f32 lbl_804D9898;

void ftNana_OnLoad(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2222_flag.bits.b4 = true;
    ftPopo_OnLoadForNana(fp);

    {
        ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
        fp->x40 = attr->xC4;
    }
}

void ftNana_OnDeath(HSD_GObj* gobj)
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

/* static */ void ftNana_801238E4(HSD_GObj* gobj);

void ftNana_80122FAC(HSD_GObj* gobj)
{
    ftNana_801238E4(gobj);
}

void ftNana_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftIceClimberAttributes);
}

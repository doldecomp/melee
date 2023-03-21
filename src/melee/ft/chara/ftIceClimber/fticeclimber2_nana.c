#include "fticeclimber2_nana.h"

#include "fticeclimber.h"

#include "ft/fighter.h"
#include "ft/forward.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include <dolphin/mtx/types.h>

char lbl_803CD7F8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 lbl_803CD820[] = {
    { 12, 0, -6 },
    { 6, 6, 6 },
};

ActionState as_table_nana[] = {
    { 295, 0x00340111, 0x12800000, lbl_8011F318, lbl_8011F390, lbl_8011F398,
      lbl_8011F3D8, func_800761C8 },
    { 296, 0x00340511, 0x12800000, lbl_8011F354, lbl_8011F394, lbl_8011F3B8,
      lbl_8011F454, func_800761C8 },
    { 297, 0x00340212, 0x13800000, lbl_8011FC78, lbl_8011FF40, lbl_80120080,
      lbl_80120660, func_800761C8 },
    { 298, 0x00340212, 0x13800000, lbl_8011FCD0, lbl_8011FF90, lbl_80120230,
      lbl_80120854, func_800761C8 },
    { 299, 0x00340612, 0x13800000, lbl_8011FD9C, lbl_8011FFE0, lbl_801203E0,
      lbl_80120A48, func_800761C8 },
    { 300, 0x00340612, 0x13800000, lbl_8011FE48, lbl_80120030, lbl_80120520,
      lbl_80120C58, func_800761C8 },
    { 301, 0x00340213, 0x14000000, lbl_801212C4, lbl_801214D4, lbl_801215DC,
      lbl_80121740, func_800761C8 },
    { 302, 0x00340213, 0x14000000, lbl_80121944, lbl_80121AC8, lbl_80121AD0,
      lbl_80121C34, func_800761C8 },
    { 303, 0x00340213, 0x14000000, lbl_801223B8, lbl_8012248C, lbl_80122494,
      lbl_80122664, func_800761C8 },
    { 304, 0x00340213, 0x14000000, lbl_80121E10, lbl_80121EB0, lbl_80121EB8,
      lbl_80121F2C, func_800761C8 },
    { 305, 0x00340213, 0x14000000, lbl_80122110, lbl_801221AC, lbl_801221B4,
      lbl_80122228, func_800761C8 },
    { 306, 0x00340613, 0x14000000, lbl_801213CC, lbl_80121558, lbl_80121680,
      lbl_8012177C, func_800761C8 },
    { 307, 0x00340613, 0x14000000, lbl_801219F4, lbl_80121ACC, lbl_80121B74,
      lbl_80121C70, func_800761C8 },
    { 308, 0x00340613, 0x14000000, lbl_80122410, lbl_80122490, lbl_80122538,
      lbl_801226A0, func_800761C8 },
    { 309, 0x00340613, 0x14000000, lbl_80121E4C, lbl_80121EB4, lbl_80121ED8,
      lbl_80121F68, func_800761C8 },
    { 310, 0x00340613, 0x14000000, lbl_8012214C, lbl_801221B0, lbl_801221D4,
      lbl_80122264, func_800761C8 },
    { 311, 0x00340014, 0x15800000, lbl_80122A0C, lbl_80122B0C, lbl_80122B14,
      lbl_80122C18, func_800761C8 },
    { 312, 0x00340414, 0x15800000, lbl_80122A8C, lbl_80122B10, lbl_80122B34,
      lbl_80122D04, func_800761C8 },
    { 313, 0x00340212, 0x13800000, lbl_80123CA4, lbl_80123E58, lbl_80123E60,
      lbl_80123F98, func_800761C8 },
    { 314, 0x00340612, 0x13800000, lbl_80123D68, lbl_80123E5C, lbl_80123EFC,
      lbl_801241A0, func_800761C8 },
    { 315, 0x00340213, 0x14000000, lbl_80123348, lbl_80123388, lbl_80123390,
      lbl_801233F0, func_800761C8 },
    { 316, 0x00340213, 0x14000000, lbl_80123448, lbl_801234E4, lbl_801234EC,
      lbl_801235BC, func_800761C8 },
    { 317, 0x00340213, 0x14000000, NULL, NULL, NULL, NULL, func_800761C8 },
    { 318, 0x00340613, 0x14000000, lbl_80123384, lbl_8012338C, lbl_801233EC,
      lbl_801233F4, func_800761C8 },
    { 319, 0x00340613, 0x14000000, lbl_80123484, lbl_801234E8, lbl_8012350C,
      lbl_801235F8, func_800761C8 },
    { 320, 0x00340613, 0x14000000, NULL, NULL, NULL, NULL, func_800761C8 },
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

void ftNana_OnLoad(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2222_flag.bits.b4 = true;
    ftIceClimber_OnLoadForNana(fp);

    {
        ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
        fp->x40 = attr->xC4;
    }
}

void ftNana_OnDeath(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
    fp->dmg.x18B0 = attr->xC8;
    func_80074A4C(fighter_gobj, 0U, 0);
    func_80074A4C(fighter_gobj, 1U, 0);
    fp->ev.nn.x2234 = 0;
    fp->ev.nn.x222C = 0;
    fp->ev.nn.x2230.bits.b0 = 0;
    fp->ev.nn.x2238 = 0;
    fp->ev.nn.x224C = 0;
    fp->ev.nn.x2250 = lbl_804D9898;
}

/* static */ void func_801238E4(HSD_GObj* fighter_gobj);

void ftNana_80122FAC(HSD_GObj* fighter_gobj)
{
    func_801238E4(fighter_gobj);
}

void ftNana_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftIceClimberAttributes);
}

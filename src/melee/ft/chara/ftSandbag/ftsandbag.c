#include "ftsandbag.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "lb/lb_00B0.h"

MotionState ftSb_Init_MotionStateTable[] = {
    { 295, 0, 0x01400000, ftSb_Init_8014FC20, ftSb_Init_8014FC24,
      ftSb_Init_8014FC28, ftSb_Init_8014FC48, ftCamera_UpdateCameraBox },
};

char ftSb_Init_DatFilename[] = "PlSb.dat";
char ftSb_Init_DataName[] = "ftDataSandbag";
char ftSb_Init_803D39D4[] = "PlSbNr.dat";
char ftSb_Init_803D39E0[] = "PlySandbag_Share_joint";
char ftSb_Init_803D39F8[] = "PlySandbag_Share_matanim_joint";
char ftSb_Init_AnimDatFilename[] = "PlSbAJ.dat";

Fighter_CostumeStrings ftSb_Init_CostumeStrings[] = {
    { ftSb_Init_803D39D4, ftSb_Init_803D39E0, ftSb_Init_803D39F8 },
};

typedef struct _ftSandbagAttributes {
    u32 x0_pair[2];
} ftSandbagAttributes;

void ftSb_Init_OnDeath(HSD_GObj* arg0) {}

void ftSb_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PUSH_ATTRS(fp, ftSandbagAttributes);

    fp->x2228_flag.bits.b2 = 1;
    fp->x2226_flag.bits.b0 = 1;

    ftSb_Init_8014FA30(fp);
}

void ftSb_Init_8014FA30(Fighter* fp)
{
    FighterBone* bones = fp->x5E8_fighterBones;
    lb_8000C1C0(bones[5].x0_jobj, bones[12].x0_jobj);
    bones = fp->x5E8_fighterBones;
    lb_8000C1C0(bones[5].x4_jobj2, bones[12].x4_jobj2);
    bones = fp->x5E8_fighterBones;
    lb_8000C1C0(bones[5].x0_jobj, bones[17].x0_jobj);
    bones = fp->x5E8_fighterBones;
    lb_8000C1C0(bones[5].x4_jobj2, bones[17].x4_jobj2);
    bones = fp->x5E8_fighterBones;
    lb_8000C228(bones[7].x0_jobj, bones[37].x0_jobj);
    bones = fp->x5E8_fighterBones;
    lb_8000C228(bones[7].x4_jobj2, bones[37].x4_jobj2);

    lb_8000C420(fp->x5E8_fighterBones[7].x0_jobj, 1, -1.57079637f);
    lb_8000C420(fp->x5E8_fighterBones[7].x0_jobj, 2, -1.57079637f);
    lb_8000C420(fp->x5E8_fighterBones[7].x4_jobj2, 1, -1.57079637f);
    lb_8000C420(fp->x5E8_fighterBones[7].x4_jobj2, 2, -1.57079637f);

    bones = fp->x5E8_fighterBones;
    lb_8000C228(bones[6].x0_jobj, bones[5].x0_jobj);
    bones = fp->x5E8_fighterBones;
    lb_8000C228(bones[6].x4_jobj2, bones[5].x4_jobj2);

    lb_8000C420(fp->x5E8_fighterBones[6].x0_jobj, 1, -1.50098311f);
    lb_8000C420(fp->x5E8_fighterBones[6].x0_jobj, 2, -1.50098311f);
    lb_8000C420(fp->x5E8_fighterBones[6].x4_jobj2, 1, -1.50098311f);
    lb_8000C420(fp->x5E8_fighterBones[6].x4_jobj2, 2, -1.50098311f);
}

void ftSb_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSandbagAttributes);
}

void ftSb_Init_OnKnockbackEnter(HSD_GObj* arg0) {}

void ftSb_Init_OnKnockbackExit(HSD_GObj* arg0) {}

void ftSb_Init_8014FBA4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->xE0_ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }

    Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
}

void ftSb_Init_8014FC20(HSD_GObj* arg0) {}

void ftSb_Init_8014FC24(HSD_GObj* arg0) {}

void ftSb_Init_8014FC28(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSb_Init_8014FC48(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

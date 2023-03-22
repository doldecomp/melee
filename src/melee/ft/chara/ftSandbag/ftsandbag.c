#include "ftsandbag.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "lb/lbunknown_001.h"

MotionState ftSandbag_MotionStateTable[] = {
    { 295, 0, 0x01400000, ftSandbag_8014FC20, ftSandbag_8014FC24,
      ftSandbag_8014FC28, ftSandbag_8014FC48, ftCamera_UpdateCameraBox },
};

char lbl_803D39B8[] = "PlSb.dat";
char lbl_803D39C4[] = "ftDataSandbag";
char lbl_803D39D4[] = "PlSbNr.dat";
char lbl_803D39E0[] = "PlySandbag_Share_joint";
char lbl_803D39F8[] = "PlySandbag_Share_matanim_joint";
char lbl_803D3A18[] = "PlSbAJ.dat";

Fighter_CostumeStrings lbl_803D3A24[] = {
    { lbl_803D39D4, lbl_803D39E0, lbl_803D39F8 },
};

typedef struct _ftSandbagAttributes {
    u32 x0_pair[2];
} ftSandbagAttributes;

void ftSandbag_OnDeath(HSD_GObj* arg0) {}

void ftSandbag_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    PUSH_ATTRS(fp, ftSandbagAttributes);

    fp->x2228_flag.bits.b2 = 1;
    fp->x2226_flag.bits.b0 = 1;

    ftSandbag_8014FA30(fp);
}

void ftSandbag_8014FA30(Fighter* fp)
{
    FighterBone* bones = fp->ft_bones;
    func_8000C1C0(bones[5].x0_jobj, bones[12].x0_jobj);
    bones = fp->ft_bones;
    func_8000C1C0(bones[5].x4_jobj2, bones[12].x4_jobj2);
    bones = fp->ft_bones;
    func_8000C1C0(bones[5].x0_jobj, bones[17].x0_jobj);
    bones = fp->ft_bones;
    func_8000C1C0(bones[5].x4_jobj2, bones[17].x4_jobj2);
    bones = fp->ft_bones;
    func_8000C228(bones[7].x0_jobj, bones[37].x0_jobj);
    bones = fp->ft_bones;
    func_8000C228(bones[7].x4_jobj2, bones[37].x4_jobj2);

    func_8000C420(fp->ft_bones[7].x0_jobj, 1, -1.57079637f);
    func_8000C420(fp->ft_bones[7].x0_jobj, 2, -1.57079637f);
    func_8000C420(fp->ft_bones[7].x4_jobj2, 1, -1.57079637f);
    func_8000C420(fp->ft_bones[7].x4_jobj2, 2, -1.57079637f);

    bones = fp->ft_bones;
    func_8000C228(bones[6].x0_jobj, bones[5].x0_jobj);
    bones = fp->ft_bones;
    func_8000C228(bones[6].x4_jobj2, bones[5].x4_jobj2);

    func_8000C420(fp->ft_bones[6].x0_jobj, 1, -1.50098311f);
    func_8000C420(fp->ft_bones[6].x0_jobj, 2, -1.50098311f);
    func_8000C420(fp->ft_bones[6].x4_jobj2, 1, -1.50098311f);
    func_8000C420(fp->ft_bones[6].x4_jobj2, 2, -1.50098311f);
}

void ftSandbag_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSandbagAttributes);
}

void ftSandbag_OnKnockbackEnter(HSD_GObj* arg0) {}

void ftSandbag_OnKnockbackExit(HSD_GObj* arg0) {}

void ftSandbag_8014FBA4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->ground_or_air == GA_Air)
        func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8007EFC0(fp, p_ftCommonData->x5F0);
}

void ftSandbag_8014FC20(HSD_GObj* arg0) {}

void ftSandbag_8014FC24(HSD_GObj* arg0) {}

void ftSandbag_8014FC28(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSandbag_8014FC48(HSD_GObj* gobj)
{
    func_80083F88(gobj);
}

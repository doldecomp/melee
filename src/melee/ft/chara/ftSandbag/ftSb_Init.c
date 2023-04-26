#include "forward.h"
#include "ft/forward.h"

#include "ftSb_Init.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "lb/lb_00B0.h"

MotionState ftSb_Init_MotionStateTable[ftSb_MS_SelfCount] = {
    {
        // ftSb_MS_WaitReverse = 341
        ftSb_SM_WaitReverse,
        Ft_MF_None,
        (FtMoveId_Default << 24) | (1 << 22),
        ftSb_MS_341_Anim,
        ftSb_MS_341_IASA,
        ftSb_MS_341_Phys,
        ftSb_MS_341_Coll,
        ftCamera_UpdateCameraBox,
    },
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

    fp->x2228_flag.bits.b2 = true;
    fp->x2226_flag.bits.b0 = true;

    ftSb_Init_8014FA30(fp);
}

void ftSb_Init_8014FA30(Fighter* fp)
{
    FighterBone* parts = fp->parts;
    lb_8000C1C0(parts[FtPart_WaistN].x0_jobj, parts[FtPart_RLegJ].x0_jobj);
    parts = fp->parts;
    lb_8000C1C0(parts[FtPart_WaistN].x4_jobj2, parts[FtPart_RLegJ].x4_jobj2);
    parts = fp->parts;
    lb_8000C1C0(parts[FtPart_WaistN].x0_jobj,
                parts[FtPart_LShoulderN].x0_jobj);
    parts = fp->parts;
    lb_8000C1C0(parts[FtPart_WaistN].x4_jobj2,
                parts[FtPart_LShoulderN].x4_jobj2);
    parts = fp->parts;
    lb_8000C228(parts[FtPart_LLegJ].x0_jobj, parts[FtPart_RShoulderJ].x0_jobj);
    parts = fp->parts;
    lb_8000C228(parts[FtPart_LLegJ].x4_jobj2,
                parts[FtPart_RShoulderJ].x4_jobj2);

    lb_8000C420(fp->parts[FtPart_LLegJ].x0_jobj, 1, -M_PI / 2);
    lb_8000C420(fp->parts[FtPart_LLegJ].x0_jobj, 2, -M_PI / 2);
    lb_8000C420(fp->parts[FtPart_LLegJ].x4_jobj2, 1, -M_PI / 2);
    lb_8000C420(fp->parts[FtPart_LLegJ].x4_jobj2, 2, -M_PI / 2);

    parts = fp->parts;
    lb_8000C228(parts[FtPart_LLegJA].x0_jobj, parts[FtPart_WaistN].x0_jobj);
    parts = fp->parts;
    lb_8000C228(parts[FtPart_LLegJA].x4_jobj2, parts[FtPart_WaistN].x4_jobj2);

    {
        float const angle = -86 * DEG_TO_RAD;
        lb_8000C420(fp->parts[FtPart_LLegJA].x0_jobj, 1, angle);
        lb_8000C420(fp->parts[FtPart_LLegJA].x0_jobj, 2, angle);
        lb_8000C420(fp->parts[FtPart_LLegJA].x4_jobj2, 1, angle);
        lb_8000C420(fp->parts[FtPart_LLegJA].x4_jobj2, 2, angle);
    }
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

    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }

    Fighter_ChangeMotionState(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    ftCommon_8007EFC0(fp, p_ftCommonData->x5F0);
}

void ftSb_MS_341_Anim(HSD_GObj* arg0) {}

void ftSb_MS_341_IASA(HSD_GObj* arg0) {}

void ftSb_MS_341_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSb_MS_341_Coll(HSD_GObj* gobj)
{
    ft_80083F88(gobj);
}

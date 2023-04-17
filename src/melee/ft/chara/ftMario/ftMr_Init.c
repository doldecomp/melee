#include <platform.h>

#include "ft/chara/ftMario/ftmario.h"
#include "ft/chara/ftMario/ftmario2.h"
#include "ft/chara/ftMario/ftMr_SpecialN.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include <baselib/random.h>

MotionState ftMr_Init_MotionStateTable[] = {
    {
        -1,
        0,
        0x01000000,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        -1,
        0,
        0x01000000,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        295,
        0x00340111,
        0x12000000,
        ftMr_SpecialN_Anim,
        ftMr_SpecialN_IASA,
        ftMr_SpecialN_Phys,
        ftMr_SpecialN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        296,
        0x00340511,
        0x12000000,
        ftMr_SpecialAirN_Anim,
        ftMr_SpecialAirN_IASA,
        ftMr_SpecialAirN_Phys,
        ftMr_SpecialAirN_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        297,
        0x00341012,
        0x13000000,
        ftMr_SpecialS_Anim,
        ftMr_SpecialS_IASA,
        ftMr_SpecialS_Phys,
        ftMr_SpecialS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        298,
        0x00341012,
        0x13000000,
        ftMr_SpecialAirS_Anim,
        ftMr_SpecialAirS_IASA,
        ftMr_SpecialAirS_Phys,
        ftMr_SpecialAirS_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        299,
        0x00340213,
        0x14000000,
        ftMr_SpecialHi_Anim,
        ftMr_SpecialHi_IASA,
        ftMr_SpecialHi_Phys,
        ftMr_SpecialHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        300,
        0x00340613,
        0x14000000,
        ftMr_SpecialAirHi_Anim,
        ftMr_SpecialAirHi_IASA,
        ftMr_SpecialAirHi_Phys,
        ftMr_SpecialAirHi_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        301,
        0x00340214,
        0x15000000,
        ftMr_SpecialLw_Anim,
        ftMr_SpecialLw_IASA,
        ftMr_SpecialLw_Phys,
        ftMr_SpecialLw_Coll,
        ftCamera_UpdateCameraBox,
    },
    {
        302,
        0x00340614,
        0x15000000,
        ftMr_SpecialAirLw_Anim,
        ftMr_SpecialAirLw_IASA,
        ftMr_SpecialAirLw_Phys,
        ftMr_SpecialAirLw_Coll,
        ftCamera_UpdateCameraBox,
    },
};

MotionState ftMr_Init_UnkMotionStates0[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C7158, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C7200, NULL, NULL },
};

void ftMr_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->ev.mr.x222C_vitaminCurr = 9;
    fp->ev.mr.x2230_vitaminPrev = 9;
    fp->ev.mr.x2234_tornadoCharge = false;
    fp->ev.mr.x2238_isCapeBoost = false;
    fp->ev.mr.x223C_capeGObj = NULL;
    fp->ev.mr.x2240 = 0;
}

void ftMr_Init_OnLoadForDrMario(Fighter* fp)
{
    PUSH_ATTRS(fp, ftMarioAttributes);
}

void ftMr_Init_OnLoad(HSD_GObj* gobj)
{
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes* sa;
    Fighter* fp = gobj->user_data;
    ftDataInfo = fp->x10C_ftData;
    items = ftDataInfo->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftMarioAttributes);

    sa = (ftMarioAttributes*) fp->x2D4_specialAttributes;

    it_8026B3F8(items[0], It_Kind_Mario_Fire);
    it_8026B3F8(items[2], sa->x14_MARIO_CAPE_IT_KIND);
}

// 0x800E0A00
void ftMr_Init_OnTakeDamage(HSD_GObj* gobj)
{
    ftMr_SpecialS_RemoveCape(gobj);
}

void ftMr_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftMr_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftMr_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftMr_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftMr_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMarioAttributes);
}

void ftMr_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftMr_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftMr_Init_UnkDemoCallbacks0(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 != 10) {
        if (arg0 >= 10) {
            return;
        }
        if (arg0 < 9) {
            return;
        }
        *arg2 = 0xe;
        *arg1 = 0xe;
    } else {
        *arg2 = 0xf;
        *arg1 = 0xf;
    }
}

unk_t ftMr_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 9:
        offset = 14;
        break;
    case 10:
        offset = 15;
    }

    return ftMr_Init_DemoViMotionFilenames[offset - 0xe];
}

#include "ftMr_Init.h"

#include "ftMr_SpecialHi.h"
#include "ftMr_SpecialLw.h"
#include "ftMr_SpecialN.h"
#include "ftMr_SpecialS.h"
#include "ftMr_Strings.h"
#include "types.h"

#include "ft/ft_0C31.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"
#include "it/forward.h"

#include "it/it_26B1.h"

MotionState ftMr_Init_MotionStateTable[ftMr_MS_SelfCount] = {
    {
        // ftMr_MS_AppealSR = 341
        ftCo_SM_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // ftMr_MS_AppealSL = 342
        ftCo_SM_None,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
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

MotionState ftMr_Init_UnkMotionStates0[aux_states_count] = {
    {
        ftCo_SM_RunBrake,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C7158,
        NULL,
        NULL,
    },
    {
        ftCo_SM_Kneebend,
        Ft_MF_None,
        FtMoveId_Default << 24,
        NULL,
        NULL,
        ftCo_800C7200,
        NULL,
        NULL,
    },
};

void ftMr_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.mr.x222C_vitaminCurr = 9;
    fp->fv.mr.x2230_vitaminPrev = 9;
    fp->fv.mr.x2234_tornadoCharge = false;
    fp->fv.mr.x2238_isCapeBoost = false;
    fp->fv.mr.x223C_capeGObj = NULL;
    fp->fv.mr.x2240 = 0;
}

void ftMr_Init_OnLoadForDrMario(Fighter* fp)
{
    PUSH_ATTRS(fp, ftMario_DatAttrs);
}

void ftMr_Init_OnLoad(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER is too much stack. Problem with #PUSH_ATTRS?
    Fighter* fp = gobj->user_data;
    ftData* ftDataInfo = fp->ft_data;
    void** items = ftDataInfo->x48_items;

    fp->x2224_b7 = true;

    PUSH_ATTRS(fp, ftMario_DatAttrs);

    {
        ftMario_DatAttrs* sa = fp->dat_attrs;

        it_8026B3F8(items[0], It_Kind_Mario_Fire);
        it_8026B3F8(items[2], sa->specials.cape_kind);
    }
}

void ftMr_Init_OnTakeDamage(HSD_GObj* gobj)
{
    ftMr_SpecialS_RemoveCape(gobj);
}

void ftMr_Init_OnItemPickup(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemPickup(gobj, flag, 1, 1);
}

void ftMr_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftMr_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftMr_Init_OnItemDrop(HSD_GObj* gobj, bool flag)
{
    Fighter_OnItemDrop(gobj, flag, 1, 1);
}

void ftMr_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMario_DatAttrs);
}

void ftMr_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftMr_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftMr_Init_UnkDemoCallbacks0(int arg0, int* arg1, int* arg2)
{
    if (arg0 != 10) {
        if (arg0 >= 10) {
            return;
        }
        if (arg0 < 9) {
            return;
        }
        *arg2 = 14;
        *arg1 = 14;
    } else {
        *arg2 = 15;
        *arg1 = 15;
    }
}

char* ftMr_Init_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 9:
        offset = 14;
        break;
    case 10:
        offset = 15;
    }

    return ftMr_Init_DemoViMotionFilenames[offset - 14];
}

#include "ftmewtwo.h"

// 0x80146CCC
// https://decomp.me/scratch/qxdYd
s32 ftMewtwo_SpecialN_GetChargeLevel(HSD_GObj* fighter_gobj, s32* chargeLevel, s32* chargeCycles)
{
    Fighter* fp;
    ftMewtwoAttributes* mewtwoAttrs;

    if (fighter_gobj != NULL)
    {
        fp = getFighter(fighter_gobj);
        mewtwoAttrs = getFtSpecialAttrsD(fp);

        if ((u32)fp->sa.mewtwo.x2230 == 0U)
        {
            return -1;
        }

        *chargeLevel = fp->sa.mewtwo.x2234_shadowBallCharge;
        *chargeCycles = mewtwoAttrs->x0_MEWTWO_SHADOWBALL_CHARGE_CYCLES;
        return 0;
    }
    return -1;
}

// 0x80146D24
// https://decomp.me/scratch/EKheK
BOOL func_80146D24(HSD_GObj* fighter_gobj)
{
    if (fighter_gobj != NULL)
    {
        Fighter* fp = getFighter(fighter_gobj);
        s32 ASID = fp->x10_action_state_index;

        switch (ASID)
        {
        case AS_MEWTWO_SPECIALN_START:
        case AS_MEWTWO_SPECIALN_LOOP:
        case AS_MEWTWO_SPECIALN_FULL:
        case AS_MEWTWO_SPECIALN_CANCEL:
        case AS_MEWTWO_SPECIALN_END:
        case AS_MEWTWO_SPECIALAIRN_START:
        case AS_MEWTWO_SPECIALAIRN_LOOP:
        case AS_MEWTWO_SPECIALAIRN_FULL:
        case AS_MEWTWO_SPECIALAIRN_CANCEL:
        case AS_MEWTWO_SPECIALAIRN_END:

            if (fp->x2071_b6 != FALSE)
            {
                return TRUE;
            }
            return FALSE;
        }
        return TRUE;
    }
    return TRUE;
}

// 0x80146D74
// https://decomp.me/scratch/s3eQH 
BOOL func_80146D74(HSD_GObj* fighter_gobj)
{
    s32 ASID;

    if (fighter_gobj != NULL)
    {
        ASID = getFighter(fighter_gobj)->x10_action_state_index;
        switch (ASID)
        {
        case AS_MEWTWO_SPECIALN_START:
        case AS_MEWTWO_SPECIALN_LOOP:
        case AS_MEWTWO_SPECIALN_FULL:
        case AS_MEWTWO_SPECIALN_END:
        case AS_MEWTWO_SPECIALAIRN_START:
        case AS_MEWTWO_SPECIALAIRN_LOOP:
        case AS_MEWTWO_SPECIALAIRN_FULL:
        case AS_MEWTWO_SPECIALAIRN_END:
            return FALSE;

        default:
        case AS_MEWTWO_SPECIALN_CANCEL:
        case AS_MEWTWO_SPECIALAIRN_CANCEL:
            return TRUE;
        }
    }
    else return TRUE;
}

extern void efLib_DestroyAll(HSD_GObj*);

inline void ftMewtwo_SpecialN_ClearGObj(HSD_GObj* fighter_gobj)
{
    if (fighter_gobj != NULL)
    {
        Fighter* fp = getFighter(fighter_gobj);
        if (fp->sa.mewtwo.x2238_shadowBallGObj != NULL)
        {
            efLib_DestroyAll(fighter_gobj);
            fp->sa.mewtwo.x2238_shadowBallGObj = NULL;
        }
    }
}

// 0x80146DC8
// https://decomp.me/scratch/gzSFm // Clear Shadow Ball GObj pointer and reset flag
void func_80146DC8(HSD_GObj* fighter_gobj)
{
    if (fighter_gobj != NULL)
    {
        Fighter* fp = getFighter(fighter_gobj);
        if ((u32)fp->sa.mewtwo.x2230 != 0U)
        {
            fp->sa.mewtwo.x2230 = 0U;
        }
        ftMewtwo_SpecialN_ClearGObj(fighter_gobj);
    }
}

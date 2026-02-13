#include "db.h"

#include <sysdolphin/baselib/particle.h>
#include <sysdolphin/baselib/psappsrt.h>
#include <melee/ef/eflib.h>

static UnkFlagStruct db_804D6BA0;

void fn_SetupObjAllocLimiter(void)
{
    db_804D6BA0.b0 = 0;
    db_804D6BA0.b1 = 0;
}

void fn_UpdateObjAllocLimiter(int player)
{
    int peak;

    if (g_debugLevel == 4) {
        if ((db_ButtonsDown(player) & HSD_PAD_B) &&
            (db_ButtonsPressed(player) & HSD_PAD_DPADUP))
        {
            if (db_804D6BA0.b0 == 0) {
                HSD_ObjAllocSetNumLimit(
                    &Effect_AllocData, HSD_ObjAllocGetPeak(&Effect_AllocData));
                HSD_ObjAllocEnableNumLimit(&Effect_AllocData);

                db_804D6BA0.b0 = 1;
            } else {
                HSD_ObjAllocDisableNumLimit(&Effect_AllocData);

                db_804D6BA0.b0 = 0;
            }
        }
        if ((db_ButtonsDown(player) & HSD_PAD_A) &&
            (db_ButtonsPressed(player) & HSD_PAD_DPADUP))
        {
            if (db_804D6BA0.b1 == 0) {
                HSD_ObjAllocSetNumLimit(
                    &hsd_804D0F90.alloc_data,
                    HSD_ObjAllocGetPeak(&hsd_804D0F90.alloc_data));
                HSD_ObjAllocEnableNumLimit(&hsd_804D0F90.alloc_data);
                HSD_ObjAllocSetNumLimit(
                    &hsd_804D0F60.alloc_data,
                    HSD_ObjAllocGetPeak(&hsd_804D0F60.alloc_data));
                HSD_ObjAllocEnableNumLimit(&hsd_804D0F60.alloc_data);
                HSD_ObjAllocSetNumLimit(
                    &HSD_PSAppSrt_804D10B0,
                    HSD_ObjAllocGetPeak(&HSD_PSAppSrt_804D10B0));
                HSD_ObjAllocEnableNumLimit(&HSD_PSAppSrt_804D10B0);

                db_804D6BA0.b1 = 1;
            } else {
                HSD_ObjAllocDisableNumLimit(&hsd_804D0F90.alloc_data);
                HSD_ObjAllocDisableNumLimit(&hsd_804D0F60.alloc_data);
                HSD_ObjAllocDisableNumLimit(&HSD_PSAppSrt_804D10B0);

                db_804D6BA0.b1 = 0;
            }
        }
    }
}

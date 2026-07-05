#include "crowdsfx.h"

#include "ft/ftlib.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"
#include "pl/plbonuslib.h"

#include <baselib/gobj.h>
#include <baselib/gobjproc.h>

void un_80321900(void)
{
    HSD_GObj* gobj = GObj_Create(0x16, 0x17, 0);
    HSD_GObj_SetupProc(gobj, fn_803219AC, 0x13);
    un_804D7050 = &un_804A2F08;
    un_80321950(un_804D7050);
}

void un_80321950(CrowdSFX_UnkStruct* s)
{
    s->x0 = 0;
    s->x4 = 0x10000;
    s->x8 = 0.0f;
    s->xC = 0;
    s->x10 = gCrowdConfig->cheer_limit;
    s->x14 = 0x83D60;
    s->x18 = gCrowdConfig->max_gasp_count;
    s->x1C = 0;
    s->x20 = 0;
    s->x24 = 0;
    s->x2C = -1;
    s->x28 = -1;
}

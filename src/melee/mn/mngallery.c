#include "mngallery.h"

#include <placeholder.h>
#include <platform.h>

#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/memory.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbmthp.h>

static void* mnGallery_804D6C8C;

void mnGallery_80258940(void)
{
    mnGallery_804D6C8C = HSD_MemAlloc(0x271000);
}

void mnGallery_80258D50(void* arg)
{
    struct {
        u8 unk0;
        u8 unk1;
        u8 pad[6];
        HSD_GObj* gobj;
    }* data = arg;
    s32 zero;

    if (data->unk0 != 0) {
        lbMthp_8001F800();
        lbAudioAx_800236DC();
        lbAudioAx_80023F28(gmMainLib_8015ECB0());

        zero = 0;
        data->unk0 = zero;
        data->unk1 = zero;

        if (data->gobj != NULL) {
            HSD_GObjPLink_80390228(data->gobj);
            data->gobj = NULL;
        }
    }
}

#include "mngallery.h"

#include <baselib/cobj.h>
#include <baselib/memory.h>

static void* mnGallery_804D6C8C;

void mnGallery_80258940(void)
{
    mnGallery_804D6C8C = HSD_MemAlloc(0x271000);
}

void lbMthp_8001F800(void);
void lbAudioAx_800236DC(void);
void gmMainLib_8015ECB0(void);
void lbAudioAx_80023F28(void);
void HSD_GObjPLink_80390228(void*);

void mnGallery_80258D50(u8* arg0) {
    void* gobj;
    if (arg0[0] != 0) {
        lbMthp_8001F800();
        lbAudioAx_800236DC();
        gmMainLib_8015ECB0();
        lbAudioAx_80023F28();
        arg0[0] = 0;
        arg0[1] = 0;
        gobj = *(void**)(arg0 + 0x8);
        if (gobj != NULL) {
            HSD_GObjPLink_80390228(gobj);
            *(void**)(arg0 + 0x8) = NULL;
        }
    }
}

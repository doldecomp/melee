/**
 * Card work area .bss/.sbss used by the card functions in hsd_3A94.c
 * (and the JPEG decoder in hsd_3B34.c). Kept in its own TU: the card
 * functions only match when this data is referenced as extern, so it
 * cannot be defined alongside them.
 */

#include <Runtime/platform.h>

#include "hsd_3A94.h"

/* 4D2348 */ CardRequest hsd_804D2348[32];
/* 4D1148 */ CardCmd hsd_804D1148[128];
/* 4D1138 */ CardActiveRequest hsd_804D1138;

/* 4D799C */ s32 hsd_804D799C;
/* 4D7998 */ s32 hsd_804D7998;
/* 4D7994 */ s32 hsd_804D7994;
/* 4D7990 */ s32 hsd_804D7990;
/* 4D798C */ s32 hsd_804D798C;
/* 4D7988 */ s32 hsd_804D7988;
/* 4D7984 */ volatile s32 hsd_804D7984;
/* 4D7980 */ volatile s32 hsd_804D7980;

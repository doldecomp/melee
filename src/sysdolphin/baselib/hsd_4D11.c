
#include "hsd_4D11.h"

#include <Runtime/platform.h>

/* 4D2348 */ __baselib_UnkType003 hsd_804D2348;
/* 4D1148 */ u32 hsd_804D1148[0x80][0x9];
/* 4D1138 */ u8 hsd_804D1138[0x10];
/* 4D799C */ s32 hsd_804D799C;
/* 4D7998 */ s32 hsd_804D7998;
/* 4D7994 */ s32 hsd_804D7994;
/* 4D7990 */ s32 hsd_804D7990;
/* 4D798C */ s32 hsd_804D798C;

/// Result of the request in progress: negative = CARD error, 1 = data
/// verified so the queued writes are skipped, 2 = verify mismatch.
/* 4D7988 */ s32 _card_error;

/* 4D7984 */ volatile s32 hsd_804D7984;
/* 4D7980 */ volatile s32 hsd_804D7980;

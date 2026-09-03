/**
 * Card work area .bss/.sbss used by the card functions in hsd_3A94.c
 * (and the JPEG decoder in hsd_3B34.c). Kept in its own TU: the card
 * functions only match when this data is referenced as extern, so it
 * cannot be defined alongside them.
 */

#include <platform.h>

/* 4D2E70 */ u8 hsd_804D2E70[2084];
/// @todo Declared as `__jmp_buf` (0xF8 bytes) by users, but the object is
/// 0x828 bytes: a JpegWork whose first member is the jmp_buf (see hsd_3B34.c).
/* 4D2648 */ u8 hsd_804D2648[0x828];
/* 4D2348 */ u8 hsd_804D2348[0x300];
/* 4D1148 */ u32 hsd_804D1148[0x80][0x9];
/* 4D1138 */ u8 hsd_804D1138[0x10];

/* 4D799C */ s32 hsd_804D799C;
/* 4D7998 */ s32 hsd_804D7998;
/* 4D7994 */ s32 hsd_804D7994;
/* 4D7990 */ s32 hsd_804D7990;
/* 4D798C */ s32 hsd_804D798C;
/* 4D7988 */ s32 hsd_804D7988;
/* 4D7984 */ volatile s32 hsd_804D7984;
/* 4D7980 */ volatile s32 hsd_804D7980;

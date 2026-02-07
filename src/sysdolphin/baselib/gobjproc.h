#ifndef SYSDOLPHIN_BASELIB_GOBJPROC_H
#define SYSDOLPHIN_BASELIB_GOBJPROC_H

#include <platform.h>

#include "baselib/forward.h" // IWYU pragma: export

struct HSD_GObjProc {
    /* 0x00 */ HSD_GObjProc* child;
    /* 0x04 */ HSD_GObjProc* next;
    /* 0x08 */ HSD_GObjProc* prev;
    /* 0x0C */ u8 s_link;
    /* 0x0D */ u8 flags_1 : 1;
    /* 0x0D */ u8 flags_2 : 1;
    /* 0x0D */ u8 flags_3 : 2;
    /* 0x0D */ u8 flags_4 : 2;
    /* 0x10 */ HSD_GObj* gobj; // owner
    /* 0x14 */ HSD_GObjEvent on_invoke;
};

/* 38FAA8 */ void HSD_GObjProc_8038FAA8(HSD_GObjProc* gproc);
/* 38FC18 */ void HSD_GObjProc_8038FC18(HSD_GObjProc* gproc);
/* 38FCE4 */ void HSD_GObjProc_8038FCE4(HSD_GObjProc* gproc);
/* 38FD54 */ HSD_GObjProc* HSD_GObjProc_8038FD54(HSD_GObj*, HSD_GObjEvent, u8);
/* 38FE24 */ void HSD_GObjProc_8038FE24(HSD_GObjProc* gproc);
/* 38FED4 */ void HSD_GObjProc_8038FED4(HSD_GObj* gobj);

#endif

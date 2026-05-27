#ifndef GALE01_ITMATERIAL
#define GALE01_ITMATERIAL

#include <platform.h>

#include "it/forward.h"

#include <baselib/forward.h>

#include <dolphin/gx.h>

struct it_MObjInfo;

/* 277D08 */ void it_80277D08(void);
/* 277D8C */ void fn_80277D8C(HSD_MObj*, u32, u32);
/* 277F90 */ HSD_TExp* it_80277F90(Item*, HSD_MObj*, HSD_TExp*);
/* 278108 */ void it_80278108(Item*, HSD_MObj*, HSD_TExp*);
/* 278574 */ void it_80278574(HSD_GObj*, GXColor*);
/* 3F1F90 */ extern struct it_MObjInfo it_803F1F90;

#endif

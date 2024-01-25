#include "psappsrt.h"

#include "objalloc.h"

/* 004D4538 */ extern u16 HSD_PSAppSrt_804D7958[4];
/* 004CDC90 */ extern HSD_ObjAllocData HSD_PSAppSrt_804D10B0;
extern u16 hsd_804D78DE;
extern u16 hsd_804D78D8;

bool psInitAppSRT(int num, int size)
{
    hsd_804D78DE = 0;
    hsd_804D78D8 = 0;
    HSD_PSAppSrt_804D7958[0] = (u16) size;
    HSD_ObjAllocInit(&HSD_PSAppSrt_804D10B0, size, 4U);
    return 0;
}

#ifndef _UTIL_H_
#define _UTIL_H_

#include <math.h>
#include <baselib/objalloc.h>

// functions
void HSD_MulColor(GXColor* arg0, GXColor* arg1, GXColor* dest);
u32 HSD_GetNbBits(u32 arg0);
s32 HSD_Index2PosNrmMtx(u32 arg0);

// variables
extern float HSD_identityMtx[];

#endif // _UTIL_H_

#ifndef _UTIL_H_
#define _UTIL_H_

#include <platform.h>
#include <dolphin/gx/forward.h>

// functions
void HSD_MulColor(GXColor* arg0, GXColor* arg1, GXColor* dest);
u32 HSD_GetNbBits(u32 arg0);
s32 HSD_Index2PosNrmMtx(u32 arg0);

// variables
extern float HSD_identityMtx[];

#endif // _UTIL_H_

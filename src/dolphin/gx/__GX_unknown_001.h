// header for shared declarations private to the gx module

#ifndef DOLPHIN_GX___GX_UNKNOWN_001_H
#define DOLPHIN_GX___GX_UNKNOWN_001_H

#include <dolphin/gx/__types.h>

/* 0033ED74 */ extern void GXClearGPMetric(void);
/* 0033E4DC */ extern void GXSetGPMetric(u32, u32);
/* 0033E458 */ extern void __GXSetMatrixIndex(s32);
/* 0033E430 */ extern void GXSetClipMode(s32);
/* 0033DBFC */ extern void GXSetFieldMask(s32, s8);
/* 0033C0F8 */ extern void __GXSetTmemConfig(s32);
/* 0033BE50 */ extern void GXInvalidateTexAll(GXContext*, s32, u8*);
/* 0033BE08 */ extern void GXInitTlutRegion(s32*, s32, s32);
/* 0033BCE8 */ extern void GXInitTexCacheRegion(unk_t, s8, u32, s32, u32, s32,
                                                s32);

#endif

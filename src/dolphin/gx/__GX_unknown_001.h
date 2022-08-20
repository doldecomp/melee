// header for shared declarations private to the gx module

#ifndef DOLPHIN_GX___GX_UNKNOWN_001_H
#define DOLPHIN_GX___GX_UNKNOWN_001_H

#include <dolphin/gx/__types.h>

/* 003FDE38 */ extern GXRenderModeObj GXPal528IntDf;
/* 003FDDFC */ extern GXRenderModeObj GXMpal480IntDf;
/* 0033ED74 */ extern void func_80342194();
/* 0033E4DC */ extern void func_803418FC(u32, u32);
/* 0033E458 */ extern s32 func_80341878(s32);
/* 0033E430 */ extern void func_80341850(s32);
/* 0033E3EC */ extern void func_8034180C(s32, s32);
/* 0033DBFC */ extern void GXSetFieldMask(s32, s8);
/* 0033C980 */ extern void __GXFlushTextureState(GXContext *, s32, u8 *);
/* 0033C980 */ extern void __GXFlushTextureState(GXContext *, s32, u8 *);
/* 0033C0F8 */ extern void __GXSetTmemConfig(s32);
/* 0033BEAC */ extern GXTexRegionCallback GXSetTlutRegionCallback(GXTexRegionCallback);
/* 0033BE98 */ extern GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback);
/* 0033BE50 */ extern void GXInvalidateTexAll(GXContext *, s32, u8 *);
/* 0033BE08 */ extern void GXInitTlutObj(s32 *, s32, s32);
/* 0033BCE8 */ extern void GXInitTexCacheRegion(unk_t, s8, u32, s32, u32, s32, s32);
/* 0033AA2C */ extern void GXClearBoundingBox();
/* 0033A31C */ extern void GXSetDispCopyFrame2Field(s32);



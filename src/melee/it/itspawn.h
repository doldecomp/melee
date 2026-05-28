#ifndef GALE01_ITSPAWN_H
#define GALE01_ITSPAWN_H

#include <platform.h>

#include "it/types.h"

#include <baselib/forward.h>
#include <dolphin/mtx.h>

/* 26C47C */ void it_8026C47C(struct it_8026C47C_arg0_t*);
/* 26C530 */ s32 it_8026C530(s32, ItemPickTable*, s32, s32);
/* 26C65C */ int it_8026C65C(ItemPickTable*);
/* 26C704 */ bool it_8026C704(void);
/* 26C75C */ ItemKind it_8026C75C(ItemPickTable*);
/* 26C88C */ void fn_8026C88C(HSD_GObj*);
/* 26CA4C */ void it_8026CA4C(ItemPickTable*, s32*, u64, s32, f32);
/* 26CB3C */ bool it_8026CB3C(Vec3*);
/* 26CB9C */ void it_8026CB9C(s32*, u64, f32);
/* 26CD50 */ void it_8026CD50(s32*, u64, f32);
/* 26CF04 */ void it_8026CF04(void);
/* 26D018 */ void it_8026D018(void);
/* 26D258 */ bool it_8026D258(Vec3*, ItemKind);
/* 26D324 */ bool it_8026D324(ItemKind);
/* 26D3CC */ bool it_8026D3CC(void);
#endif

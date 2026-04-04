#ifndef MELEE_PL_PLTRICK_H
#define MELEE_PL_PLTRICK_H

#include <placeholder.h>
#include <platform.h>

#include "ft/types.h"

struct plActionStats;
struct plAttackStats;

/* 037B2C */ int pl_80037B2C(struct plActionStats* arg0, int arg1, int arg2);
/* 037BC0 */ void pl_80037BC0(struct plAttackStats* stats,
                              union Struct2070* ev);
/* 037C60 */ void pl_80037C60(Fighter_GObj*, s32 prev2070_int);
/* 037DF4 */ void pl_80037DF4(HSD_GObj*, union Struct2070*);
/* 037ECC */ void pl_80037ECC(HSD_GObj*);
/* 038144 */ void pl_80038144(HSD_GObj*, HSD_GObj*, s32, ft_800898B4_t*,
                              u16, s32, s32);
/* 0384DC */ void pl_800384DC(HSD_GObj*, int, void*);
/* 038628 */ bool pl_80038628(HSD_GObj*, int);

#endif

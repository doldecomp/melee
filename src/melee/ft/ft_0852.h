#ifndef GALE01_08521C
#define GALE01_08521C

#include "ft/types.h"
#include "ft/forward.h"

ftData* gFtDataList[FTKIND_MAX];

struct ft_8045993C_t {
    u8 pad_x0[0x6];
    u16 x6_b0 : 1;
} ft_8045993C[6];

int ft_8045996C[FTKIND_MAX];

/* 08521C */ void ft_8008521C(Fighter_GObj* gobj);
/* 0852B0 */ void ft_800852B0(void);
/* 08549C */ void ft_8008549C(void);
/* 3C0EC0 */ extern struct UnkCostumeList
    CostumeListsForeachCharacter[FTKIND_MAX];

extern struct ftData_UnkCountStruct ftData_UnkIntPairs[FTKIND_MAX];

#endif

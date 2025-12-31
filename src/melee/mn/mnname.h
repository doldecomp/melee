#ifndef GALE01_23749C
#define GALE01_23749C

#include <placeholder.h>

#include <baselib/forward.h>

#include <stdbool.h>

/* 23749C */ void* mnName_8023749C(s32 arg0);
/* 23754C */ char* GetNameText(int slot);
/* 237594 */ int GetNameCount(void);
/* 2375EC */ bool IsNameListFull(void);
/* 237654 */ s32 CompareNameStrings(char* str1, char* str2);
/* 2377A4 */ void fn_802377A4(void);
/* 2377A8 */ bool IsNameUnique(char* name);
/* 237834 */ void DeleteName(u8 slot);
/* 2379BC */ bool IsNameValid(int slot);
/* 237A04 */ void CreateNameAtIndex(u8 slot);
/* 237A68 */ void mnName_SortNames(HSD_GObj* gobj);
/* 237D94 */ void mnName_80237D94(s32 arg0, u8 arg1);
/* 237F78 */ void mnName_ConfirmNameDeleteInput(void);
/* 23817C */ void mnName_MainInput(void);
/* 238540 */ void fn_80238540(void);
/* 2385A0 */ void mnName_802385A0(HSD_GObj* gobj);
/* 2385D4 */ s32 mnName_GetPageCount(void);
/* 238698 */ s32 mnName_GetColumnCount(void);
/* 238754 */ void mnName_80238754(HSD_GObj* gobj);
/* 2388D4 */ s32 mnName_802388D4(void* arg0, u8 arg1);
/* 238964 */ f32 mnName_80238964(void* arg0, u8 arg1, u8 arg2);
/* 238A04 */ void mnName_80238A04(s32 arg0, s32 arg1, s32 arg2);
/* 238AE0 */ void mnName_80238AE0(void* arg0, u8 arg1, s32 arg2);
/* 238C34 */ void mnName_80238C34(HSD_GObj* gobj, u8 arg1);
/* 239574 */ void fn_80239574(HSD_GObj* gobj);
/* 239878 */ void mnName_80239878(u8 arg0, s32 arg1);
/* 239A24 */ void mnName_80239A24(HSD_GObj* gobj);
/* 239EBC */ void mnName_80239EBC(void* arg0, f32 arg1);
/* 239F5C */ void mnName_80239F5C(void* arg0, f32 arg1);
/* 239FFC */ s32 mnName_80239FFC(void* arg0);
/* 23A058 */ void mnName_8023A058(HSD_GObj* gobj);
/* 23A0BC */ void fn_8023A0BC(HSD_GObj* gobj);
/* 23A290 */ void mnName_8023A290(void);
/* 23A59C */ void mnName_8023A59C(HSD_GObj* gobj);
/* 23A9B4 */ void mnName_8023A9B4(HSD_GObj* gobj);
/* 23AC40 */ void mnName_8023AC40(void);
/* 23B084 */ BOOL IsNameNotAllowed(char* name);

#endif

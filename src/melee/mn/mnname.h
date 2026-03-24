#ifndef GALE01_23749C
#define GALE01_23749C

#include <placeholder.h>

#include <baselib/forward.h>

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/sislib.h>

typedef struct MnName_GObj {
    /* +00 */ HSD_GObj gobj;
    /* +38 */ void* x38;
    /* +3C */ HSD_Text* text;
    /* +40 */ HSD_Text* text2;
} MnName_GObj;

/* 23749C */ char* mnName_8023749C(int slot);
/* 23754C */ char* GetNameText(int slot);
/* 237594 */ int GetNameCount(void);
/* 2375EC */ bool IsNameListFull(void);
/* 237654 */ s32 CompareNameStrings(char* str, s32 slot);
/* 2377A4 */ void fn_802377A4(void);
/* 2377A8 */ bool IsNameUnique(s32 slot);
/* 237834 */ s32 DeleteName(u8);
/* 2379BC */ bool IsNameValid(int slot);
/* 237A04 */ void CreateNameAtIndex(s32 slot);
/* 237A68 */ s32 mnName_SortNames(HSD_GObj*);
/* 237D94 */ u8 mnName_80237D94(s32, u8);
/* 237F78 */ UNK_RET mnName_ConfirmNameDeleteInput(HSD_GObj*);
/* 23817C */ UNK_RET mnName_MainInput(HSD_GObj*);
/* 238540 */ void fn_80238540(HSD_GObj* gobj);
/* 2385A0 */ void mnName_802385A0(HSD_GObj* gobj);
/* 2385D4 */ s32 mnName_GetPageCount(void);
/* 238698 */ s32 mnName_GetColumnCount(void);
/* 238754 */ void mnName_80238754(HSD_GObj* gobj);
/* 2388D4 */ HSD_JObj* mnName_802388D4(HSD_GObj* gobj, u8 index);
/* 238964 */ f32 mnName_80238964(u8 index, u8 target, u8 flag);
/* 238A04 */ void mnName_80238A04(HSD_GObj* gobj, u8 target, u8 flag);
/* 238AE0 */ void mnName_80238AE0(HSD_GObj* gobj, u8 index, u8 arg2);
/* 238C34 */ void mnName_80238C34(HSD_GObj*, u8, u8);
/* 239574 */ void fn_80239574(HSD_GObj*);
/* 239878 */ void mnName_80239878(u8, HSD_GObj*);
/* 239A24 */ void mnName_80239A24(HSD_GObj* gobj);
/* 239EBC */ void mnName_80239EBC(HSD_JObj* jobj, f32 y);
/* 239F5C */ void mnName_80239F5C(HSD_JObj* jobj, f32 x);
/* 239FFC */ void mnName_80239FFC(HSD_GObj* gobj);
/* 23A058 */ void mnName_8023A058(HSD_GObj* gobj);
/* 23A0BC */ void fn_8023A0BC(HSD_GObj*);
/* 23A290 */ void mnName_8023A290(void);
/* 23A59C */ HSD_GObj* mnName_8023A59C(u8);
/* 23A9B4 */ void mnName_8023A9B4(u8);
/* 23AC40 */ s32 mnName_8023AC40(void);
/* 23B084 */ bool IsNameNotAllowed(s32 name_idx);

#endif

#ifndef MELEE_MN_NAME_NEW_H
#define MELEE_MN_NAME_NEW_H

#include <placeholder.h>

#include <baselib/forward.h>

/* 23B0F8 */ void mnNameNew_8023B0F8(HSD_GObj* arg0, u8 arg1);
/* 23B224 */ void mnNameNew_8023B224(u8);
/* 23B314 */ void mnNameNew_8023B314(u8*, s32);
/* 23B3FC */ s32 mnNameNew_KeySetup(u8*, u8);
/* 23BAA8 */ s32 mnNameNew_8023BAA8(u8* arg0, s32 arg1, u8 arg2);
/* 23BD4C */ s32 PickAutoName(HSD_GObj* arg0);
/* 23BEE0 */ s32 NameContainsOnlySpaces(void);
/* 23BFE4 */ s32 WriteCharactersForNameAtIndex(u8 arg0, s32 arg1);
/* 23C148 */ s32 AddCharacterToName(u8* arg0, s32 arg1, u8 arg2, u8 arg3);
/* 23C290 */ void mnNameNew_GlyphVariantInput(void);
/* 23C54C */ UNK_RET mnNameNew_MainInput(HSD_GObj*);
/* 23CE4C */ void mnNameNew_8023CE4C(void);
/* 23CFC8 */ void fn_8023CFC8(HSD_GObj* arg0);
/* 23D0F8 */ void fn_8023D0F8(void*);
/* 23D130 */ s32 mnNameNew_8023D130(u8* arg0, u8 arg1, u8 arg2, s32 arg3);
/* 23D3E8 */ s32 mnNameNew_GlyphVariantSetup(u8* arg0, u8 arg1, u8 arg2);
/* 23DA08 */ s32 mnNameNew_8023DA08(u8*);
/* 23DAEC */ void fn_8023DAEC(HSD_GObj*);
/* 23DBE8 */ void fn_8023DBE8(HSD_GObj*);
/* 23E0D8 */ void mnNameNew_8023E0D8(u8* arg0);
/* 23E264 */ s32 InitNameEntryUIState(u8*, s32);
/* 23E32C */ void mnNameNew_8023E32C(s32);
/* 23E630 */ void mnNameNew_EnterFromMnName(UNK_T);
/* 23E6D0 */ void mnNameNew_EnterFromMnCharSel(HSD_Archive*, s32);
/* 23EA08 */ void mnNameNew_8023EA08(UNK_T);

#endif

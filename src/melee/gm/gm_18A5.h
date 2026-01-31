#ifndef MELEE_GM_18A5_H
#define MELEE_GM_18A5_H

#include <placeholder.h>

#include <melee/ft/forward.h>
#include <melee/gm/forward.h>
#include <melee/mn/forward.h>
#include <melee/sc/forward.h>
#include <sysdolphin/baselib/forward.h>

/* 18A514 */ UNK_RET fn_8018A514(UNK_PARAMS);
/* 18A970 */ void fn_8018A970(int);
/* 18AA74 */ UNK_RET fn_8018AA74(UNK_PARAMS);
/* 18B090 */ void fn_8018B090(HSD_GObj*);
/* 18C8D4 */ void fn_8018C8D4(void*, s32, s32, s32, s32, s32, s32, f32);
/* 18D50C */ void fn_8018D50C(void*, s32, s32, s32, s32, s32, s32, f32);
/* 18DC18 */ void fn_8018DC18(void*, s32, s32, s32, s32, s32, s32, f32);
/* 18DF68 */ void fn_8018DF68(void*, s32, s32, s32, s32, s32, s32, f32);
/* 18E46C */ void fn_8018E46C(HSD_GObj*, int);
/* 18E618 */ void fn_8018E618(int, int, float);
/* 18E85C */ void fn_8018E85C(int, u8);
/* 18EC48 */ UNK_RET fn_8018EC48(UNK_PARAMS);
/* 18EC7C */ UNK_RET fn_8018EC7C(UNK_PARAMS);
/* 18ECA8 */ UNK_RET fn_8018ECA8(UNK_PARAMS);
/* 18F00C */ void fn_8018F00C(char*, s32);
/* 18F1B0 */ s32 gm_8018F1B0(MatchEnd* me);
/* 17F294 */ int fn_8017F294(void);
/* 18F310 */ int fn_8018F310(int);
/* 18F3BC */ u8 fn_8018F3BC(s32 arg0);
/* 18F3D0 */ int fn_8018F3D0(int);
/* 18F410 */ int fn_8018F410(void);
/* 18F4A0 */ int fn_8018F4A0(void);
/* 18F508 */ s32 fn_8018F508(s32* arg0);
/* 18F5F0 */ char* fn_8018F5F0(void);
/* 18F62C */ u32 fn_8018F62C(HSD_GObj*);
/* 18F634 */ TmData* gm_8018F634(void);
/* 18F640 */ u32 fn_8018F640(int);
/* 18F674 */ u32 fn_8018F674(int);
/* 18F6A8 */ u32 fn_8018F6A8(int);
/* 18F6DC */ int fn_8018F6DC(int);
/* 18F6FC */ CharacterKind fn_8018F6FC(CSSIconHud);
/* 18F71C */ float
fn_8018F71C(int, int); ///< returns the frame for the tou css icon?
/* 18F74C */ int fn_8018F74C(void);
/* 18F808 */ int fn_8018F808(void);
/* 18F888 */ void fn_8018F888(void);
/* 18FA24 */ void fn_8018FA24(void);
/* 18FBD8 */ void fn_8018FBD8(UNK_T arg0, s32 arg1);
/* 18FBE0 */ void fn_8018FBE0(s32, s32, s32, s8, s8, s16, s8);
/* 18FDC4 */ void fn_8018FDC4(HSD_JObj*, float x, float y, float z);
/* 18FF9C */ void fn_8018FF9C(HSD_JObj*, float x, float y, float z);
/* 190174 */ HSD_GObj* fn_80190174(HSD_CObjDesc*);
/* 1901F8 */ HSD_GObj* fn_801901F8(HSD_CObjDesc*);
/* 19027C */ void fn_8019027C(UNK_T lights);
/* 1902F0 */ void fn_801902F0(int arg0);
/* 19035C */ HSD_GObj* fn_8019035C(bool, DynamicModelDesc*, int, int, int,
                                   bool, void (*)(HSD_GObj*), float);
/* 19044C */ void fn_8019044C(HSD_JObj*, float);
/* 190480 */ void fn_80190480(float);
/* 1904D0 */ UNK_RET fn_801904D0(UNK_PARAMS);
/* 190520 */ void fn_80190520(float x, float y, float z);
/* 1905F0 */ void gm_801905F0(StartMeleeData*);
/* 190ABC */ void fn_80190ABC(int);
/* 190EA4 */ void gm_80190EA4(void);
/* 190FE4 */ void gm_80190FE4(int);
/* 1910E0 */ void fn_801910E0(HSD_GObj*);
/* 191154 */ void fn_80191154(HSD_GObj*);
/* 191240 */ void fn_80191240(HSD_GObj*);
/* 1913BC */ UNK_RET fn_801913BC(UNK_PARAMS);
/* 191678 */ void fn_80191678(HSD_GObj*);
/* 19175C */ void fn_8019175C(void*);
/* 1918F0 */ void fn_801918F0(HSD_GObj*);
/* 191A54 */ void fn_80191A54(HSD_GObj*);
/* 191B5C */ void fn_80191B5C(void* arg0);
/* 191CA4 */ void fn_80191CA4(HSD_GObj*);
/* 191D38 */ void fn_80191D38(HSD_GObj*);
/* 191E9C */ void fn_80191E9C(HSD_GObj*);
/* 191FD4 */ UNK_RET fn_80191FD4(UNK_PARAMS);
/* 19237C */ void fn_8019237C(HSD_GObj*);
/* 19249C */ void fn_8019249C(HSD_GObj*);
/* 192690 */ void fn_80192690(HSD_GObj*);
/* 192758 */ void fn_80192758(HSD_GObj*);
/* 192938 */ UNK_RET fn_80192938(UNK_PARAMS);
/* 192BB0 */ UNK_RET fn_80192BB0(UNK_PARAMS);
/* 192E6C */ UNK_RET fn_80192E6C(UNK_PARAMS);
/* 193230 */ UNK_RET fn_80193230(UNK_PARAMS);
/* 193308 */ UNK_RET fn_80193308(UNK_PARAMS);
/* 1935B8 */ UNK_RET fn_801935B8(UNK_PARAMS);
/* 1937C4 */ void fn_801937C4(s32* arg, u32 arg0, u32 arg01);
/* 193B58 */ void fn_80193B58(s32* arg, u32 arg0, u32 arg01);
/* 193FCC */ void fn_80193FCC(s32* arg, u32 arg0, u32 arg01);
/* 194658 */ void fn_80194658(s32* arg, u32 arg0, u32 arg01);
/* 1949B4 */ void fn_801949B4(s32* arg, u32 arg0, u32 arg01);
/* 194BC4 */ void fn_80194BC4(s32* arg, u32 arg0, u32 arg01);
/* 194D84 */ void fn_80194D84(s32* arg, u32 arg0, u32 arg01);
/* 194F30 */ void fn_80194F30(s32* arg, u32 arg0, u32 arg01);
/* 1953C8 */ void fn_801953C8(s32* arg, u32 arg0, u32 arg01);
/* 195AF0 */ void fn_80195AF0(s32* arg, u32 arg0, u32 arg01);
/* 195CCC */ void fn_80195CCC(s32* arg, u32 arg0, u32 arg01);
/* 19610C */ void fn_8019610C(s32* arg, u32 arg0, u32 arg01);
/* 19628C */ void gm_8019628C_OnFrame(void);
/* 1963B4 */ void gm_801963B4_OnEnter(UNK_T);
/* 1964A4 */ void gm_801964A4_OnLeave(UNK_T);
/* 196510 */ void fn_80196510(void);
/* 19655C */ s32 fn_8019655C(void);
/* 196564 */ bool fn_80196564(TmData*);
/* 196594 */ bool fn_80196594(TmData*);
/* 1965C4 */ void fn_801965C4(void);
/* 196684 */ void fn_80196684(s32 arg0);
/* 1967E0 */ UNK_RET fn_801967E0(UNK_PARAMS);
/* 196CF8 */ s32 fn_80196CF8(void);
/* 196DBC */ void fn_80196DBC(HSD_GObj*);
/* 196E30 */ void fn_80196E30(HSD_GObj*);
/* 196EEC */ void fn_80196EEC(HSD_GObj*);
/* 196FFC */ UNK_RET fn_80196FFC(UNK_PARAMS);
/* 1973F8 */ void fn_801973F8(HSD_GObj*);
/* 1975C8 */ void fn_801975C8(HSD_GObj*);
/* 1976D4 */ void fn_801976D4(HSD_GObj*);
/* 1977AC */ UNK_RET fn_801977AC(UNK_PARAMS);
/* 197AF0 */ UNK_RET fn_80197AF0(UNK_PARAMS);
/* 197D4C */ void fn_80197D4C(HSD_GObj*);
/* 197E18 */ void fn_80197E18(HSD_GObj*);
/* 197FD8 */ void fn_80197FD8(HSD_GObj*);
/* 1981A0 */ void fn_801981A0(HSD_GObj*);
/* 1983E4 */ void fn_801983E4(HSD_GObj*);
/* 198584 */ void fn_80198584(ResultsData*);
/* 1985D4 */ UNK_RET fn_801985D4(UNK_PARAMS);
/* 198824 */ UNK_RET fn_80198824(UNK_PARAMS);
/* 198BA0 */ void fn_80198BA0(void);
/* 198C60 */ void fn_80198C60(void);
/* 198D18 */ void fn_80198D18(void);
/* 198EBC */ UNK_RET fn_80198EBC(UNK_PARAMS);
/* 199AF0 */ UNK_RET fn_80199AF0(UNK_PARAMS);
/* 19A158 */ UNK_RET fn_8019A158(UNK_PARAMS);
/* 19A71C */ void fn_8019A71C(s32* arg0);
/* 19A828 */ void gm_8019A828(void);
/* 19A86C */ void fn_8019A86C(s32*, u32, u32);
/* 19AF50 */ void fn_8019AF50(s32*, u32, u32);
/* 19B2DC */ void gm_8019B2DC_OnFrame(void);
/* 19B458 */ void fn_8019B458(s32* arg0);
/* 19B81C */ void fn_8019B81C(s32* arg0);
/* 19B860 */ void fn_8019B860(TmData*);

#endif

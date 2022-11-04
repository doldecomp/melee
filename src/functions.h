#ifndef _functions_h_
#define _functions_h_

#include <ctypes.h>

typedef struct _CameraBox CameraBox;
typedef struct _CollData CollData;
typedef struct _Hitbox Hitbox;
typedef struct _Fighter Fighter;
typedef struct _HSD_GObj HSD_GObj;
typedef struct _HSD_JObj HSD_JObj;
typedef struct _HSD_ImageDesc HSD_ImageDesc;

#pragma region "melee/ft/ft_unknown_006"
void func_800DE508(HSD_GObj*);
#pragma endregion

#pragma region "melee/ft/ftfox"
void ftFox_LoadSpecialAttrs(HSD_GObj*);
void ftFox_RemoveBlaster(HSD_GObj*);
#pragma endregion

#pragma region "melee/ft/ftlink"
void func_800EC06C();
void func_800ECD04(HSD_GObj*);
void func_800ECD58(HSD_GObj*);
#pragma endregion

#pragma region "melee/ft/ftkirby"
void func_800EED50(s32, s32);
void func_800F1D24();
void func_800F5BA4();
void func_800F5C34();
#pragma endregion

#pragma region "melee/gm/code_801601C4"
BOOL func_80164840(u8);
s32 func_8016AEDC(void);
s32 func_8016B1C4();
s32 func_8016B238(void);
s32 func_8016B3A0(void);
s32 func_8016B41C();
#pragma endregion

#pragma region "melee/gr/granime"
void func_801C8138();
#pragma endregion

#pragma region "melee/gr/ground"
void func_801C95C4(HSD_GObj*);
void func_801C5AA4();
void func_801C42AC();
s32 func_801C4210(void);
void func_801C3BB4();
void func_801C39C0();
BOOL func_801C2ED0(HSD_JObj*, s32);
BOOL func_801C2D24(s32, Vec*);
HSD_GObj* func_801C2BA4(s32);
BOOL func_801C28AC(s32, u32, s32*);
HSD_GObj* func_801C14D0(s32);
f32 func_801C0498(void);
#pragma endregion

#pragma region "melee/gr/stage"
s32 Stage_80225194(void);
void func_801C5A84();
#pragma endregion

#pragma region "melee/it/item"
void func_8026ABD8(HSD_GObj*, Vec*, f32);
#pragma endregion

#pragma region "melee/it/item2"
s32 func_8026B320(HSD_GObj*);
BOOL func_8026B2B4(HSD_GObj*);
s32 func_8026B30C(HSD_GObj*);
f32 func_8026B54C(HSD_GObj*);
f32 func_8026B560(HSD_GObj*);
f32 func_8026B574(HSD_GObj*);
s32 func_8026B588();
void func_8026B7F8();
#pragma endregion

#pragma region "melee/it/code_80266F3C"
void func_8027B4A4();
unk_t func_8027B5B0(s32, s32, HSD_JObj*, s32, s32);
#pragma endregion

#pragma region "melee/it/code_8027CF30"
void func_80294E78(HSD_GObj*, f32);
HSD_GObj* func_8029A748(HSD_GObj*, Vec*, u8, f32);
void func_8029A89C(HSD_GObj*, f32);
void func_8029A8F4(HSD_GObj*, Vec*, f32);
u32 func_802B1DF8(HSD_GObj*, Vec*, Vec*, s32, s32, s32);
s32 func_802B1FC8(u32);
void func_802B56E4(u32, Vec*, f32, f32, f32);
u32 func_802F0340(HSD_GObj*, Vec*, Vec*, u32, u32, f32);
void func_802F046C(s32);
void func_802F0AE0(HSD_GObj*, Vec*, Vec*, s32, s32, f32, f32, f32);
#pragma endregion

#pragma region "Runtime/runtime"
void __cvt_sll_flt(void);
void __cvt_dbl_usll(void);
#pragma endregion

#pragma region "MSL/string"
int __StringRead(unk_t, int, int);
char* strchr(const char*, int);
int strncmp(const char*, const char*, unsigned long);
int strcmp(const char*, const char*);
char* strncpy(char* __restrict, const char* __restrict, unsigned long);
char* strcpy(char* __restrict, const char* __restrict);
unsigned long strlen(const char*);
#pragma endregion

#pragma region "dolphin/mtx/mtxvec"
void PSMTXMUltiVec(Mtx, Vec*, Vec*);
#pragma endregion

#pragma region "dolphin/os/OSAlloc"
unk_t OSAllocFromHeap(int, u32);
#pragma endregion

#pragma region "dolphin/vi/vi"
void VIWaitForRetrace(void);
#pragma endregion

#pragma region "sysdolphin/baselib/tobj"
HSD_ImageDesc* HSD_ImageDescAlloc();
#pragma endregion

#pragma region "sysdolphin/baselib/aobj"
void HSD_ForeachAnim(unk_t, ...);
#pragma endregion

#endif

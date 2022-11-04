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

#pragma region "melee/cm/camera"
unk_t func_80030A50(void);
BOOL func_80030CFC(CameraBox*, f32);
f32 func_80031144();
#pragma endregion

#pragma region "melee/pl/player"
s32 Player_GetPlayerSlotType(s32);
#pragma endregion

#pragma region "melee/pl/pl_unknown_001"
void func_80037C60();
void func_8003E058(s32, s32, s32, s32);
void func_8003EC9C(s32, s32, f32, f32);
void func_8003FAA8(s32 slot, s32 index, Vec* pos, Vec* prevPos);
void func_8003FE1C();
void func_8003FFDC(u8, s32, u8, s32, s32);
void func_80040048(u8, s32);
void func_80040330();
void func_80040B8C();
void func_800411C4();
void func_80041280();
#pragma endregion

#pragma region "melee/mp/mpcoll"
void func_8004CBF4(CollData*);
#pragma endregion

#pragma region "melee/mp/mplib"
void func_80053DA4(u32, f32*);
void func_80053ECC(u32, f32*);
void func_80053FF4(s32, Vec*);
void func_80054158(s32, Vec*);
s32 func_800567C0(s32 wall_id, Vec* ecb_side_vertex, Vec* result);
#pragma endregion

#pragma region "melee/ef/efasync"
void func_8006737C(s8);
void func_80067624();
void func_80067688(unk_t);
void efAsync_Spawn(HSD_GObj*, unk_t, u32, u32, unk_t, ...);
#pragma endregion

#pragma region "melee/ft/fighter"
void Fighter_UnkProcessDeath_80068354(HSD_GObj*);
u32 Fighter_NewSpawn_80068E40();
void Fighter_ActionStateChange_800693AC(HSD_GObj* fighter_gobj, s32 newAction, s32 flags, HSD_GObj* otherObj, f32 animStart, f32 animSpeed, f32 animBlend);
#pragma endregion

#pragma region "melee/ft/ftanim"
void func_8006E9B4();
void func_8006EBA4(HSD_GObj*);
void func_8006EBE8(HSD_GObj* fighter_gobj, f32, f32, f32);
void func_8006F0FC(HSD_GObj* fighter_gobj, f32);
void ftAnim_SetAnimRate(HSD_GObj*, f32);
BOOL ftAnim_IsFramesRemaining(HSD_GObj*);
f32 func_8006F484(unk_t);
void func_8006FE48();
void func_80070308();
void func_800704F0(HSD_GObj*, s32, f32);
void func_80070654();
void func_80070758();
void func_8007077C();
void ftAnim_ApplyPartAnim(HSD_GObj*, s32, s32, f32);
void func_80070C48(HSD_GObj*, s32);
void func_80070CC4(HSD_GObj*, s32);
void func_80070E74();
void func_80070F28();
void func_80070FB4(HSD_GObj*, s32, s32);
s32 func_80070FD0(Fighter*);
#pragma endregion

#pragma region "melee/ft/ftaction"
void func_80073240();
void func_80073354();
void func_8007349C();
#pragma endregion

#pragma region "melee/ft/ftparts"
void func_80074B0C(HSD_GObj*, s32, s32);
void func_80074148();
void func_80073758();
void func_80074170();
void func_800743E0();
void func_800749CC();
void func_80074A4C(HSD_GObj*, u32, s32);
void func_80074A8C();
void func_80074E58();
s32 func_8007500C(Fighter*, s32);
void func_8007584C();
void func_8007592C(Fighter*, s32, f32);
void func_80075AF0(Fighter*, s32, f32);
void func_80075CB4(Fighter*, s32, f32);
#pragma endregion

#pragma region "melee/ft/ftcamera"
void func_80076064(Fighter*);
#pragma endregion

#pragma region "melee/ft/ftcoll"
void func_800764DC();
void func_80076528(HSD_GObj*);
void func_800765AC();
void func_800765E0();
void func_8007B760();
#pragma endregion

#pragma region "melee/ft/ftcommon"
void func_8007C930(Fighter*, f32);
void func_8007CB74(HSD_GObj*);
void func_8007CC78(Fighter*, f32);
void func_8007CCA0(Fighter*, f32);
f32 func_8007CD6C(f32 value, f32 decrement);
f32 func_8007CDA4(Fighter*);
f32 func_8007CDF8(Fighter*);
void func_8007CE4C(Fighter*, f32);
void func_8007CE94(Fighter*, f32);
BOOL func_8007CF58(Fighter*);
void func_8007D344(Fighter*, f32, f32, f32);
void func_8007D494(Fighter*, f32, f32);
void func_8007D4B8(Fighter*);
void func_8007D5BC();
void func_8007D5D4(Fighter*);
void func_8007D6A4(Fighter*);
void func_8007D780(Fighter*);
void func_8007D7FC(Fighter*);
void func_8007D92C(HSD_GObj*);
void func_8007D9FC(Fighter*);
f32 func_8007DA74(s32, u32, f32);
void func_8007DB24();
void func_8007E0E4();
void ftCommon_SetOnGrabCallbacks(Fighter*, s16, void (*)(HSD_GObj*), void (*)(HSD_GObj*), void (*)(HSD_GObj*, HSD_GObj*));
void func_8007E2F4(Fighter*, s16);
void func_8007E2FC(HSD_GObj*);
void func_8007E83C(HSD_GObj*, s32, f32 div);
s32 ftGetParasolStatus(HSD_GObj*);
void func_8007EA90(Fighter*, s32);
void func_8007EBAC(Fighter*, u32, u32);
void func_8007ECD4();
void func_8007ED50(Fighter*, s32);
void func_8007EE0C();
void func_8007EFC0(Fighter*, u32);
void func_8007F578();
f32 Fighter_GetModelScale(Fighter*);
void func_8007F8E8();
void func_8007F9B4();
void func_8007FC7C(HSD_GObj*, f32);
void func_8007FE84(HSD_GObj*, HSD_GObj*, s32, f32);
void func_8007FF74();
BOOL func_8007FFD8(Fighter*, f32);
void func_8008021C();
void func_8008031C();
f32 func_800804EC(Fighter*);
void func_800804FC();
#pragma endregion

#pragma region "melee/ft/code_80081938"
void func_800819A8();
#pragma endregion

#pragma region "melee/ft/ft_unknown_005"
void func_800852B0();
#pragma endregion

#pragma region "melee/ft/ftdata"
void func_800855C8();
void func_8008572C(u32);
void func_8008578C();
void func_800857E0(u32);
void func_80085820();
void func_800859A8();
void func_80085B10();
void func_80085CD8();
u32 func_80085E50(unk_t, u32);
#pragma endregion

#pragma region "melee/ft/ftlib"
HSD_GObj* func_8008627C(Vec*, HSD_GObj*);
void func_800866DC(HSD_GObj*, Vec*);
void func_800867E8();
void func_8008688C();
s32 func_80087120(HSD_GObj*);
s32 func_800872A4(HSD_GObj*);
#pragma endregion

#pragma region "melee/ft/ft_unknown_006"
void func_800880D8();
void func_80088148(Fighter*, u32, u32, u32);
void func_800C89A0(HSD_GObj*);
void func_800C8A64();
s32 func_800C8B2C();
void func_800C8C84();
void func_800C8D00();
void func_800C8F6C();
void func_800C8FC4(HSD_GObj*);
void func_800C9034();
void func_800C9840(HSD_GObj*, s32, s32, f32, f32, f32);
s32 func_800CAE80();
void func_800CB110(HSD_GObj*, s32, f32);
void func_800CC730(HSD_GObj*);
void func_800D105C(HSD_GObj*);
void func_800D14E4();
void func_800D1A8C();
void func_800D1E80();
void func_800D237C();
void func_800D3158(HSD_GObj* fighter_gobj);
void func_800D4F24(HSD_GObj*, s32);
void func_800D5AEC(HSD_GObj*, s32, s32, s32, Fighter*, f32, f32);
void func_800D5CB0(HSD_GObj*, s32, f32);
s32 func_800D67C4(Fighter*);
s32 func_800D688C(Fighter*);
s32 func_800D6928(Fighter*);
void func_800D71D8();
void func_800D94D8(HSD_GObj*);
void func_800DA824(Fighter*);
void func_800DB368(Fighter*, Fighter*);
void func_800DB464(HSD_GObj*);
void func_800DC750(HSD_GObj*);
void func_800DD168(HSD_GObj*);
void func_800DE2A8(HSD_GObj*, HSD_GObj*);
void func_800DE7C0(HSD_GObj*, s32, s32);
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

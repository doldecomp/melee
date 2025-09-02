#ifndef MELEE_MN_MAIN_H
#define MELEE_MN_MAIN_H

#include <placeholder.h>
#include <platform.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <baselib/object.h>

typedef struct _mn_unk1 {
    u8 x0;  // current menu
    u8 x1;  // previous menu
    u16 x2; // selected index
    s32 x4; // selected value
    u64 x8;
    u8 x10;
    u8 x11;
    u8 x12;
    u8 x13;
    GXColor* x14;
} mn_unk1;

typedef struct _mn_unk2 {
    u16 x0;
    u16 x2;
    s32 x4;
} mn_unk2;

/* 2295AC */ u8 mn_802295AC(void);
/* 229624 */ u32 mn_80229624(u32);
/* 229860 */ void mn_80229860(s8);
/* 229894 */ void mn_80229894(s32, u16, s32);
/* 229938 */ bool mn_80229938(s32 arg0, s32 arg1);
/* 229A04 */ int mn_80229A04(int, int);
/* 229B2C */ HSD_GObj* mn_80229B2C(void);
/* 229BF4 */ void fn_80229BF4(HSD_GObj*);
/* 229DC0 */ HSD_GObj* mn_80229DC0(void);
/* 229F60 */ void mn_80229F60(HSD_GObj*, HSD_JObj*, int);
/* 22A440 */ void mn_8022A440(HSD_GObj*, HSD_JObj*, s32);
/* 22A5D0 */ void mn_8022A5D0(HSD_GObj*, int);
/* 22ADD8 */ void mn_8022ADD8(HSD_GObj*, int);
/* 22AF10 */ void fn_8022AF10(HSD_GObj*);
/* 22AFEC */ void fn_8022AFEC(HSD_GObj*);
/* 22B3A0 */ HSD_GObj* mn_8022B3A0(u8);
/* 22BA1C */ void mn_8022BA1C(HSD_GObj*);
/* 22BCD4 */ void fn_8022BCD4(HSD_GObj*, int);
/* 22BCF8 */ HSD_GObj* mn_8022BCF8(void);
/* 22BD6C */ void mn_8022BD6C(void);
/* 22BD8C */ void mn_8022BD8C(void);
/* 22BDB4 */ void fn_8022BDB4(HSD_GObj*, int);
/* 22BE34 */ HSD_GObj* mn_8022BE34(void);
/* 22BEDC */ void mn_8022BEDC(HSD_GObj*);
/* 22BFBC */ GXColor* mn_8022BFBC(int);
/* 22C010 */ int mn_8022C010(int, int);
/* 22C068 */ void mn_8022C068(HSD_LObj*, int, int);
/* 22C128 */ void fn_8022C128(HSD_GObj*);
/* 22C304 */ void mn_8022C304(void);
/* 22C4F4 */ void mn_8022C4F4(HSD_GObj*);
/* 22C7CC */ void mn_8022C7CC(HSD_GObj*);
/* 22CA54 */ void mn_8022CA54(HSD_GObj*);
/* 22CC28 */ void mn_8022CC28(HSD_GObj*);
/* 22CE6C */ void mn_8022CE6C(HSD_GObj*);
/* 22D104 */ void mn_8022D104(HSD_GObj*);
/* 22D34C */ void mn_8022D34C(HSD_GObj*);
/* 22D594 */ void mn_8022D594(HSD_GObj*);
/* 22D7F4 */ void mn_8022D7F4(HSD_GObj*);
/* 22DB10 */ void mn_8022DB10(HSD_GObj*);
/* 22DD38 */ void mn_8022DD38_OnFrame(void);
/* 22DDA8 */ void mn_8022DDA8_OnEnter(void*);
/* 22E950 */ bool mn_8022E950(int);
/* 22E978 */ void mn_8022E978(u8 item_idx, u8 enable); ///< set/unset item mask bit
/* 22EA08 */ void mn_8022EA08(char* buf, u32 num);
/* 22EA78 */ void mn_8022EA78(char* buf, int buf_end, u32 num);
/* 22EAE0 */ void mn_8022EAE0(HSD_GObj*);
/* 22EB04 */ void mn_8022EB04(void* user_data);
/* 22EB24 */ s32 mn_8022EB24(s32, s32);
/* 22EB78 */ s32 mn_8022EB78(s32);
/* 22EBDC */ UNK_RET mn_8022EBDC(UNK_PARAMS);
/* 22EC18 */ float mn_8022EC18(HSD_JObj*, float*, HSD_TypeMask);
/* 22ED6C */ float mn_8022ED6C(HSD_JObj*, Vec3*);
/* 22EE84 */ float mn_8022EE84(HSD_JObj* arg0, Vec3* arg1, HSD_TypeMask arg2);
/* 22EFD8 */ float mn_8022EFD8(HSD_JObj*, Vec3*);
/* 22F0F0 */ void mn_8022F0F0(int);
/* 22F138 */ void mn_8022F138(u16, u16);
/* 22F1A8 */ void mn_8022F1A8(u16, u16);
/* 22F218 */ bool mn_8022F218(void);
/* 22F268 */ UNK_RET mn_8022F268(UNK_PARAMS);
/* 22F298 */ f32 mn_8022F298(HSD_JObj*);
/* 22F360 */ UNK_RET mn_8022F360(HSD_AObj*, void*, u32);
/* 22F3D8 */ void mn_8022F3D8(HSD_JObj*, u8, HSD_TypeMask);
/* 22F410 */ int mn_8022F410(float* x, float* target, float dx);
/* 22F470 */ int mn_8022F470(int* x, int* target, int dx);
/* 22F4CC */ UNK_RET mn_8022F4CC(UNK_PARAMS);

/* 4A04F0 */ extern mn_unk1 mn_804A04F0;
/* 4D6BB8 */ extern HSD_Archive* mn_804D6BB8;
/* 4D6BC8 */ extern mn_unk2 mn_804D6BC8;

#endif

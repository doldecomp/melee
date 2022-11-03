#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <sysdolphin/sysdolphin.h>

typedef struct _CameraBox CameraBox;
typedef struct _CollData CollData;
typedef struct _Hitbox Hitbox;
typedef struct _Fighter Fighter;

/* .text section */

void func_8001044C(unk_t, unk_t, s32, f32, s32, s32, s32, s32);

void func_800119DC(Vec *, s32, f32, f32, f32);

void func_80014574(u8, s32, s32, s32);
void func_800145C0(u8);

void func_80016C64(char*, unk_t*, char*, s32, ...); // from lbarchive.s, vararg may start earlier

f32 func_8001E8F8(u32);

s32 func_80021C48();

void func_800236B8(s32);

u32 func_800237A8(u32, u32, u32);

void func_80023F28();

void func_8002438C(s32);

void func_80024B1C(s32, s32);
void func_80024B58(s32, s32);

CameraBox *func_80029020();

void func_800290D4();

void func_8002A278(f32 x, f32 y);

void func_8002E6FC(u8);

void func_8002E948(u32 (*)(Vec *));

void func_8002EB5C(f32);
void func_8002EC7C(f32);
void func_8002ED9C(f32);
void func_8002EEC8(f32);
void func_8002EF14(void);
void func_8002F0E4(s32);
s32 func_8002F260(void);
void func_8002F274(void);

unk_t func_80030A50(void);

BOOL func_80030CFC(CameraBox *, f32);

f32 func_80031144();

s32 Player_GetPlayerSlotType(s32);

void func_80037C60();

void func_8003E058(s32, s32, s32, s32);

void func_8003EC9C(s32, s32, f32, f32);

void func_8003FAA8(s32 slot, s32 index, Vec *pos, Vec *prevPos);

void func_8003FE1C();

void func_8003FFDC(u8, s32, u8, s32, s32);
void func_80040048(u8, s32);

void func_80040330();

void func_80040B8C();

void func_800411C4();
void func_80041280();

void func_8004CBF4(CollData *);

void func_80053DA4(u32, f32 *);
void func_80053ECC(u32, f32 *);
void func_80053FF4(s32, Vec *);
void func_80054158(s32, Vec *);

s32 func_800567C0(s32 /*wallID?*/, Vec * /*ecb_side_vertex?*/, Vec *result);

void func_8006737C(s8);

void func_80067624();
void func_80067688(unk_t);
void efAsync_Spawn(HSD_GObj*, unk_t, u32, u32, unk_t, ...);

void Fighter_UnkProcessDeath_80068354(HSD_GObj *);

u32 Fighter_NewSpawn_80068E40();

void Fighter_ActionStateChange_800693AC(HSD_GObj *fighter_gobj, s32 newAction, s32 flags, HSD_GObj *otherObj, f32 animStart, f32 animSpeed, f32 animBlend);

void func_8006E9B4();
void func_8006EBA4(HSD_GObj *);
void func_8006EBE8(HSD_GObj *fighter_gobj, f32, f32, f32);

void func_8006F0FC(HSD_GObj *fighter_gobj, f32);
void ftAnim_SetAnimRate(HSD_GObj *, f32);
BOOL ftAnim_IsFramesRemaining(HSD_GObj *);

f32 func_8006F484(unk_t);

void func_8006FE48();

void func_80070308();

void func_80074B0C(HSD_GObj*, s32, s32);
void func_800704F0(HSD_GObj *, s32, f32);

void func_80070654();

void func_80070758();
void func_8007077C();

void ftAnim_ApplyPartAnim(HSD_GObj *, s32, s32, f32);
void func_80070C48(HSD_GObj *, s32);
void func_80070CC4(HSD_GObj *, s32);
void func_80070E74();
void func_80070F28();
void func_80070FB4(HSD_GObj *, s32, s32);
s32 func_80070FD0(Fighter *);

void func_80073240();
void func_80073354();
void func_8007349C();
void func_80073758();

void func_80074148();
void func_80074170();

void func_800743E0();

void func_800749CC();
void func_80074A4C(HSD_GObj *, u32, s32);

void func_80074A8C();

void func_80074E58();
s32 func_8007500C(Fighter *, s32);

void func_8007584C();
void func_8007592C(Fighter *, s32, f32);
void func_80075AF0(Fighter *, s32, f32);
void func_80075CB4(Fighter *, s32, f32);

void func_80076064(Fighter *);

void func_800764DC();
void func_80076528(HSD_GObj *);
void func_800765AC();
void func_800765E0();


void func_8007B760();


void func_8007C930(Fighter *, f32);

void func_8007CB74(HSD_GObj *);

void func_8007CC78(Fighter *, f32);
void func_8007CCA0(Fighter *, f32);

f32 func_8007CD6C(f32 value, f32 decrement);
f32 func_8007CDA4(Fighter *);
f32 func_8007CDF8(Fighter *);
void func_8007CE4C(Fighter *, f32);
void func_8007CE94(Fighter *, f32);

BOOL func_8007CF58(Fighter *);

void func_8007D344(Fighter *, f32, f32, f32);

void func_8007D494(Fighter *, f32, f32);
void func_8007D4B8(Fighter *);

void func_8007D5BC();
void func_8007D5D4(Fighter *);

void func_8007D6A4(Fighter *);
void func_8007D780(Fighter *);
void func_8007D7FC(Fighter *);
void func_8007D92C(HSD_GObj *);

void func_8007D9FC(Fighter *);

f32 func_8007DA74(s32, u32, f32);
void func_8007DB24();

void func_8007E0E4();
void ftCommon_SetOnGrabCallbacks(Fighter*, s16, void (*)(HSD_GObj*), void (*)(HSD_GObj*), void (*)(HSD_GObj*, HSD_GObj*));
void func_8007E2F4(Fighter *, s16);
void func_8007E2FC(HSD_GObj *);

void func_8007E83C(HSD_GObj *, s32, f32 div);
s32 ftGetParasolStatus(HSD_GObj *);
void func_8007EA90(Fighter *, s32);
void func_8007EBAC(Fighter *, u32, u32);

void func_8007ECD4();

void func_8007ED50(Fighter *, s32);
void func_8007EE0C();

void func_8007EFC0(Fighter *, u32);

void func_8007F578();

f32 Fighter_GetModelScale(Fighter *); // ftcommon.s

void func_8007F8E8();

void func_8007F9B4();

void func_8007FC7C(HSD_GObj *, f32);

void func_8007FE84(HSD_GObj *, HSD_GObj *, s32, f32);
void func_8007FF74();
BOOL func_8007FFD8(Fighter *, f32);

void func_8008021C();
void func_8008031C();

f32 func_800804EC(Fighter *); // DataOffset_PlayerScale_MultiplyBySomething, returns fp->x40*fp->x34
void func_800804FC();

void func_800819A8();

void func_800852B0();

void func_800855C8();
void func_8008572C(u32);
void func_8008578C();
void func_800857E0(u32);
void func_80085820();

void func_800859A8();
void func_80085B10();

void func_80085CD8();
u32 func_80085E50(unk_t, u32);

HSD_GObj *func_8008627C(Vec *, HSD_GObj *);

void func_800866DC(HSD_GObj *, Vec *);

void func_800867E8();

void func_8008688C();

s32 func_80087120(HSD_GObj *);

s32 func_800872A4(HSD_GObj *);

void func_800880D8();

void func_80088148(Fighter*, u32, u32, u32);

void func_800C89A0(HSD_GObj *);
void func_800C8A64();

s32 func_800C8B2C();

void func_800C8C84();
void func_800C8D00();

void func_800C8F6C();
void func_800C8FC4(HSD_GObj *);
void func_800C9034();

void func_800C9840(HSD_GObj *, s32, s32, f32, f32, f32);

s32 func_800CAE80();

void func_800CB110(HSD_GObj *, s32, f32);

void func_800CC730(HSD_GObj *);

void func_800D105C(HSD_GObj *);
void func_800D14E4();

void func_800D1A8C();

void func_800D1E80();

void func_800D237C();

void func_800D3158(HSD_GObj *fighter_gobj);

void func_800D4F24(HSD_GObj *, s32);

void func_800D5AEC(HSD_GObj *, s32, s32, s32, Fighter *, f32, f32);

void func_800D5CB0(HSD_GObj *, s32, f32);

s32 func_800D67C4(Fighter *);

s32 func_800D688C(Fighter *);

s32 func_800D6928(Fighter *);

void func_800D71D8();

void func_800D94D8(HSD_GObj *);

void func_800DA824(Fighter *);

void func_800DB368(Fighter *, Fighter *);
void func_800DB464(HSD_GObj *);

void func_800DC750(HSD_GObj *);

void func_800DD168(HSD_GObj *);

void func_800DE2A8(HSD_GObj *, HSD_GObj *);

void func_800DE508(HSD_GObj *);

void func_800DE7C0(HSD_GObj *, s32, s32);

void func_800DEEA8(HSD_GObj *fighter_gobj);

u32 func_800DEEE8(Fighter *, Vec2 *);
void func_800DEF38();
void func_800DF0D0();

void ftCaptain_OnLoadForGanon(Fighter *); // UnclePunch map file: FighterOnLoad_Ganondorf
void ftCFalcon_LoadSpecialAttrs(HSD_GObj *);

void ftFox_LoadSpecialAttrs(HSD_GObj *);

void ftFox_RemoveBlaster(HSD_GObj *);

void func_800EC06C();

void func_800ECD04(HSD_GObj *);
void func_800ECD58(HSD_GObj *);

void func_800EED50(s32, s32);

void func_800F1D24();

void func_800F5BA4();
void func_800F5C34();

void ftNess_ItemNessBatRemove(HSD_GObj *);

void ftNess_YoyoItemDespawn(HSD_GObj *);

void ftNess_ItemPKFlushSetNULL(HSD_GObj *);

void ftNess_SpecialHiTakeDamage(HSD_GObj *);

void ftPikachu_LoadSpecialAttrs(HSD_GObj *);

f32 ftSamus_80128AC8(HSD_GObj *fighter_gobj, f32 farg1, f32 farg2);
void ftSamus_80128B1C(HSD_GObj *, f32, f32, f32);

void ftMars_OnLoadForRoy(Fighter *);
void ftMars_LoadSpecialAttrs(HSD_GObj *);

void func_80149268(HSD_GObj *);

BOOL func_80164840(u8);

s32 func_8016AEDC(void);

s32 func_8016B0FC();

s32 func_8016B1C4();

s32 func_8016B238(void);

s32 func_8016B3A0(void);

s32 func_8016B41C();

s32 func_801A45E8(s32);

f32 func_801C0498(void);

HSD_GObj *func_801C14D0(s32);

BOOL func_801C28AC(s32, u32, s32 *);

HSD_GObj *func_801C2BA4(s32);

BOOL func_801C2D24(s32, Vec *);
BOOL func_801C2ED0(HSD_JObj *, s32);

void func_801C39C0();
void func_801C3BB4();

s32 func_801C4210(void);
void func_801C42AC();

void func_801C5A84();

void func_801C5AA4();

void func_801C8138();

void func_801C95C4(HSD_GObj *);

s32 Stage_80225194(void);

void func_8026ABD8(HSD_GObj *, Vec *, f32);

BOOL func_8026B2B4(HSD_GObj *);

s32 func_8026B30C(HSD_GObj *);
s32 func_8026B320(HSD_GObj *);

f32 func_8026B54C(HSD_GObj *);
f32 func_8026B560(HSD_GObj *);
f32 func_8026B574(HSD_GObj *);
s32 func_8026B588();
BOOL func_8026B594(HSD_GObj *);

void func_8026B7F8();

void func_8027B4A4();

unk_t func_8027B5B0(s32, s32, HSD_JObj*, s32, s32);

void func_80294E78(HSD_GObj *, f32);

HSD_GObj *func_8029A748(HSD_GObj *, Vec *, u8, f32);
void func_8029A89C(HSD_GObj *, f32);
void func_8029A8F4(HSD_GObj *, Vec *, f32);

s32 func_802B1DEC(u32);
u32 func_802B1DF8(HSD_GObj *, Vec *, Vec *, s32, s32, s32);
s32 func_802B1FC8(u32);
void func_802B1FE8(u32, Vec *);

void func_802B56E4(u32, Vec *, f32, f32, f32);

unk_t func_802C8B28(HSD_GObj*, Vec*, u32, f32);

u32 func_802F0340(HSD_GObj *, Vec *, Vec *, u32, u32, f32);
void func_802F046C(s32);

void func_802F0AE0(HSD_GObj *, Vec *, Vec *, s32, s32, f32, f32, f32);

s32 func_802FB6E8(u8);

s32 func_802FC998();

s32 func_80322258(f32 x);

void __cvt_sll_flt(void);
void __cvt_dbl_usll(void);

int __StringRead(unk_t, int, int);
char *strchr(const char *, int);
int strncmp(const char *, const char *, unsigned long);
int strcmp(const char *, const char *);
char *strncpy(char *__restrict, const char *__restrict, unsigned long);
char *strcpy(char *__restrict, const char *__restrict);
unsigned long strlen(const char *);

void PSMTXMUltiVec(Mtx, Vec *, Vec *);

unk_t OSAllocFromHeap(int, u32);

void VIWaitForRetrace(void);

HSD_ImageDesc *HSD_ImageDescAlloc();

void HSD_ForeachAnim(unk_t, ...);

void HSD_CObjSetScissorx4();

void HSD_CObjSetViewportfx4();

int HSD_GetHeap(void);

void HSD_VIInit(HSD_VIStatus* vi_status, unk_t xfb0, unk_t xfb1, unk_t xfb2);

void func_80378280(u8, int);

void func_80379310();
void HSD_MtxSRT();

unk_t func_8037ABC8(HSD_ObjAllocData* data);
void func_8037AD20(HSD_ObjAllocData *data, HSD_ObjAllocLink *obj);

#endif

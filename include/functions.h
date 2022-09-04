#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;
typedef struct _Item Item;
typedef struct _Article Article;

/* .init section */

/* .text section */

void *HSD_JObjUnkMtxPtr(); // asm/melee/lb/lbcollision.s

s32 func_80008248(s32, struct ftHurt *, void *, f32, f32, f32);

void func_8000B1CC(struct _HSD_JObj *, Vec *, Vec *);

f32 func_8000BDB4(struct _HSD_JObj *);

void func_8000C1C0(struct _HSD_JObj *, struct _HSD_JObj *);
void func_8000C228(struct _HSD_JObj *, struct _HSD_JObj *);

void func_8000C420(struct _HSD_JObj *, u32, f32);

s32 func_8000D148(f32, f32, f32, f32, f32, f32, f32);

void func_8000E9F0(Vec *, s32, f32);
void func_8000ED54();
void func_8000EE8C();

void func_8001044C(void *, void *, s32, f32, s32, s32, s32, s32);

void func_800119DC(Vec *, s32, f32, f32, f32);
void func_80011A50(Vec *, s32, f32, f32, f32, f32, f32, f32, f32);

void func_80014574(u8, s32, s32, s32);
void func_800145C0(u8);

struct _HSD_Archive *func_80015BD0(s32, s32);

void func_80016C64(char *, void **, char *, s32, ...); // from lbarchive.s, vararg may start earlier
void *func_80016DBC(void *, ...);

s32 func_800171CC(void *, ...);

f32 func_8001E8F8(u32);

s32 func_80021C48();

void func_800236B8(s32);

u32 func_800237A8(u32, u32, u32);

void func_80023F28();

void func_8002438C(s32);

void func_80024B1C(s32, s32);
void func_80024B58(s32, s32);

struct _CameraBox *func_80029020();

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

void func_8002F474(void);

void *func_80030A50(void);

BOOL func_80030CFC(struct _CameraBox *, f32);

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

void func_8004CBF4(struct _CollData *);

s32 func_80051EC8(Vec *, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);

void func_80053DA4(u32, f32 *);
void func_80053ECC(u32, f32 *);
void func_80053FF4(s32, Vec *);
void func_80054158(s32, Vec *);

s32 func_800567C0(s32 /*wallID?*/, Vec * /*ecb_side_vertex?*/, Vec *result);

void func_8006737C(s8);

void func_80067624();
void func_80067688(void *);
void efAsync_Spawn(struct _HSD_GObj *, void *, u32, u32, void *, ...);

void Fighter_UnkProcessDeath_80068354(struct _HSD_GObj *);

u32 Fighter_NewSpawn_80068E40();

void Fighter_ActionStateChange_800693AC(struct _HSD_GObj *fighter_gobj, s32 newAction, s32 flags, struct _HSD_GObj *otherObj, f32 animStart, f32 animSpeed, f32 animBlend);

void func_8006E9B4();
void func_8006EBA4(struct _HSD_GObj *);
void func_8006EBE8(struct _HSD_GObj *fighter_gobj, f32, f32, f32);

void func_8006F0FC(struct _HSD_GObj *fighter_gobj, f32);
void ftAnim_SetAnimRate(struct _HSD_GObj *, f32);
BOOL ftAnim_IsFramesRemaining(struct _HSD_GObj *);

f32 func_8006F484(void *);

void func_8006FE48();

void func_80070308();

void func_800704F0(struct _HSD_GObj *, s32, f32);

void func_80070654();

void func_80070758();
void func_8007077C();

void ftAnim_ApplyPartAnim(struct _HSD_GObj *, s32, s32, f32);
void func_80070C48(struct _HSD_GObj *, s32);
void func_80070CC4(struct _HSD_GObj *, s32);
void func_80070E74();
void func_80070F28();
void func_80070FB4(struct _HSD_GObj *, s32, s32);
s32 func_80070FD0(struct _Fighter *);

void func_80073240();
void func_80073354();
void func_8007349C();
void func_80073758();

void func_80074148();
void func_80074170();

void func_800743E0();

void func_800749CC();
void func_80074A4C(struct _HSD_GObj *, u32, s32);

void func_80074A8C();

void func_80074E58();
s32 func_8007500C(struct _Fighter *, s32);

void func_8007584C();
void func_8007592C(struct _Fighter *, s32, f32);
void func_80075AF0(struct _Fighter *, s32, f32);
void func_80075CB4(struct _Fighter *, s32, f32);

void func_80076064(struct _Fighter *);

void func_800764DC();
void func_80076528(struct _HSD_GObj *);
void func_800765AC();
void func_800765E0();

void func_80078754();

void func_80078A2C();
void func_80078C70();
void func_8007925C();

void func_8007AB48();
void func_8007AB80();
void func_8007ABD0(struct _Hitbox *, u32 damageAmount, struct _HSD_GObj *);

void func_8007AE80();
void func_8007AEE0(struct _HSD_GObj *);

void func_8007AF28(struct _HSD_GObj *fighter_gobj);

void func_8007AFF8(struct _HSD_GObj *);

void func_8007B0C0(struct _HSD_GObj *, s32);

void func_8007B1B8(struct _HSD_GObj *, f32 *, void (*)(struct _HSD_GObj *));

void func_8007B320();
void func_8007B4E0();

void func_8007B62C();

void func_8007B6EC();
void func_8007B760();

void func_8007B8CC();
void func_8007B8E8();
void func_getWindOffsetVec_8007B924(struct _HSD_GObj *, Vec *out_wind);
void func_8007BA0C();
void func_8007BAC0();
f32 func_8007BBCC(struct _HSD_GObj *);
void func_8007BC90();
void func_8007BE3C(struct _HSD_GObj *);

void func_8007C930(struct _Fighter *, f32);

void func_8007CB74(struct _HSD_GObj *);

void func_8007CC78(struct _Fighter *, f32);
void func_8007CCA0(struct _Fighter *, f32);

f32 func_8007CD6C(f32 value, f32 decrement);
f32 func_8007CDA4(struct _Fighter *);
f32 func_8007CDF8(struct _Fighter *);
void func_8007CE4C(struct _Fighter *, f32);
void func_8007CE94(struct _Fighter *, f32);

BOOL func_8007CF58(struct _Fighter *);

void func_8007D344(struct _Fighter *, f32, f32, f32);

void func_8007D494(struct _Fighter *, f32, f32);
void func_8007D4B8(struct _Fighter *);

void func_8007D5BC();
void func_8007D5D4(struct _Fighter *);

void func_8007D6A4(struct _Fighter *);
void func_8007D780(struct _Fighter *);
void func_8007D7FC(struct _Fighter *);
void func_8007D92C(struct _HSD_GObj *);

void func_8007D9FC(struct _Fighter *);

f32 func_8007DA74(s32, u32, f32);
void func_8007DB24();
void func_8007DB58();
// void func_8007DBCC(Fighter*, s32);

void func_8007E0E4();
void func_8007E2D0(struct _Fighter *, s16, void (*)(struct _HSD_GObj *), void (*)(struct _HSD_GObj *), void (*)(struct _HSD_GObj *, struct _HSD_GObj *));
void func_8007E2F4(struct _Fighter *, s16);
void func_8007E2FC(struct _HSD_GObj *);

void func_8007E83C(struct _HSD_GObj *, s32, f32 div);
s32 ftGetParasolStatus(struct _HSD_GObj *);
void func_8007EA90(struct _Fighter *, s32);
void func_8007EBAC(struct _Fighter *, u32, u32);

void func_8007ECD4();

void func_8007ED50(struct _Fighter *, s32);
void func_8007EE0C();

void func_8007EFC0(struct _Fighter *, u32);

void func_8007F578();

f32 Fighter_GetModelScale(struct _Fighter *); // ftcommon.s

void func_8007F8E8();

void func_8007F9B4();

void func_8007FC7C(struct _HSD_GObj *, f32);

void func_8007FE84(struct _HSD_GObj *, struct _HSD_GObj *, s32, f32);
void func_8007FF74();
BOOL func_8007FFD8(struct _Fighter *, f32);

void func_8008021C();
void func_8008031C();

f32 func_800804EC(struct _Fighter *); // DataOffset_PlayerScale_MultiplyBySomething, returns fp->x40*fp->x34
void func_800804FC();

void func_800819A8();

void func_800852B0();
void func_8008549C();

void func_800855C8();
void func_8008572C(u32);
void func_8008578C();
void func_800857E0(u32);
void func_80085820();

void func_800859A8();
void func_80085A14(u32);
void func_80085B10();

void func_80085CD8();
u32 func_80085E50(void *, u32);

struct _HSD_GObj *func_8008627C(Vec *, struct _HSD_GObj *);

void func_800866DC(struct _HSD_GObj *, Vec *);

void func_800867E8();

void func_8008688C();

s32 func_80087120(struct _HSD_GObj *);

s32 func_800872A4(struct _HSD_GObj *);

void func_800880D8();

void func_80088148(struct _Fighter *, u32, u32, u32);
void func_800881D8(struct _Fighter *, u32, u32, u32);

void func_80088640();

void func_800887CC();

void func_80088884();
void func_800888E0();

void func_80088A50(struct _Fighter *);
void func_80088C5C();
void func_800890BC(struct _Fighter *);
void func_800890D0();

void func_800892A0(struct _HSD_GObj *);
void func_800892D4(struct _Fighter *);

void func_800895E0();

void func_80089824(struct _HSD_GObj *);

void func_80089B08(struct _HSD_GObj *pPlayerEntityStruct);

void func_8008A2BC(struct _HSD_GObj *gobj);

// s32 func_8008A9F8(HSD_GObj*);

f32 func_8008D7F0(struct _Fighter *);
f32 scaleBy154_8008D8D8(f32);
s32 func_8008D8E8(f32);
void func_8008D930();

void func_8008DCE0(HSD_GObj *, s32, f32);

void func_8008E908(struct _HSD_GObj *, f32);
s32 func_8008E984(struct _Fighter *);
void func_8008E9D0();
void func_8008EB58();
void func_8008EC90();

void func_80090594();
u32 func_80090690(struct _Fighter *, struct _Vec2 *);
void func_80090718();

f32 func_80092ED8(s32, void *, f32);

void func_80095744();

s32 func_800964FC(struct _Fighter *);

void func_800968C8();
void func_80096900(struct _HSD_GObj *, s32, s32, s32, f32, f32);

void func_8009750C(HSD_GObj *);

void func_80098B20();
void func_80098C9C();

void func_80099D9C();

void func_8009A804(struct _HSD_GObj *);

void func_8009CF84();

void func_8009E0A8();
void func_8009E0D4();

void func_8009E7B4();

s32 func_8009EF68(struct _HSD_GObj *);

void func_8009F4A4();
void func_8009F578();

void func_800A0DA4();

void func_800A101C(struct _Fighter *, s8, s8, s32);
f32 func_800A17E4(struct _Fighter *);
f32 func_800A1874(struct _Fighter *);
f32 func_800A1904(struct _Fighter *);
f32 func_800A1948(struct _Fighter *);
s32 func_800A198C(struct _Fighter *);
f32 func_800A1994(struct _Fighter *);
f32 func_800A1A24(struct _Fighter *);

s32 func_800A2040();

void func_800B3900();

void func_800BFD04();

void func_800BFFAC(struct _Fighter *);
void func_800BFFD0(struct _Fighter *, s32, s32);
void func_800C0074(struct _Fighter *);

void func_800C0134();
void func_800C0200();

void func_800C0408();

s32 func_800C0694();

void func_800C09B4(struct _HSD_GObj *);

void func_800C0A98(struct _HSD_GObj *fighter_gobj);

void func_800C1E64(struct _HSD_GObj *pPlayerEntityStruct, s32, s32, u8, f32); // UnclePunch Map file: AS_203_PassiveWalljump_Walljump

void func_800C2FD8();

void func_800C37A0();

void func_800C511C();

void func_800C61B0();

void func_800C8064();

void func_800C8348(struct _HSD_GObj *, s32, s32);
void func_800C8438(struct _HSD_GObj *);
void func_800C8540();

void func_800C884C();
void func_800C88A0(struct _Fighter *);

void func_800C89A0(struct _HSD_GObj *);
void func_800C8A64();

s32 func_800C8B2C();

void func_800C8C84();
void func_800C8D00();

void func_800C8F6C();
void func_800C8FC4(struct _HSD_GObj *);
void func_800C9034();

void func_800C9840(HSD_GObj *, s32, s32, f32, f32, f32);

s32 func_800CAE80();

void func_800CB110(HSD_GObj *, s32, f32);

void func_800CC730(struct _HSD_GObj *);

void func_800D0FA0();
void func_800D105C(struct _HSD_GObj *);
void func_800D14E4();

void func_800D1A8C();

void func_800D1E80();

void func_800D237C();

void func_800D3158(struct _HSD_GObj *fighter_gobj);

void func_800D4F24(struct _HSD_GObj *, s32);

void func_800D5AEC(HSD_GObj *, s32, s32, s32, Fighter *, f32, f32);

void func_800D5CB0(struct _HSD_GObj *, s32, f32);

s32 func_800D67C4(struct _Fighter *);

s32 func_800D688C(struct _Fighter *);

s32 func_800D6928(struct _Fighter *);

void func_800D71D8();

void func_800D94D8(HSD_GObj *);

void func_800DA824(Fighter *);

void func_800DB368(Fighter *, Fighter *);
void func_800DB464(HSD_GObj *);

void func_800DC750(HSD_GObj *);

void func_800DD168(HSD_GObj *);

void func_800DE2A8(HSD_GObj *, HSD_GObj *);

void func_800DE508(HSD_GObj *);

void func_800DE7C0(struct _HSD_GObj *, s32, s32);

void func_800DEEA8(struct _HSD_GObj *fighter_gobj);

u32 func_800DEEE8(struct _Fighter *, struct _Vec2 *);
void func_800DEF38();
void func_800DF0D0();

void ftCaptain_OnLoadForGanon(struct _Fighter *); // UnclePunch map file: FighterOnLoad_Ganondorf
void ftCFalcon_LoadSpecialAttrs(struct _HSD_GObj *);

void ftFox_LoadSpecialAttrs(struct _HSD_GObj *);

void ftFox_RemoveBlaster(struct _HSD_GObj *);

void func_800EC06C();

void func_800ECD04(HSD_GObj *);
void func_800ECD58(HSD_GObj *);

void func_800EED50(s32, s32);

void func_800F1D24();

void func_800F5BA4();
void func_800F5C34();

void ftNess_ItemNessBatRemove(struct _HSD_GObj *);

void ftNess_YoyoItemDespawn(struct _HSD_GObj *);

void ftNess_ItemPKFlushSetNULL(struct _HSD_GObj *);

void ftNess_SpecialHiTakeDamage(struct _HSD_GObj *);

void ftPikachu_LoadSpecialAttrs(struct _HSD_GObj *);

f32 ftSamus_80128AC8(HSD_GObj *fighter_gobj, f32 farg1, f32 farg2);
void ftSamus_80128B1C(HSD_GObj *, f32, f32, f32);

void ftMars_OnLoadForRoy(struct _Fighter *);
void ftMars_LoadSpecialAttrs(struct _HSD_GObj *);

void func_80149268(HSD_GObj *);

void func_8014FE10();
void func_8014FE58();

void func_80150144(struct _HSD_GObj *);

void func_80150C8C(struct _HSD_GObj *);
void func_80150D28(struct _HSD_GObj *);
void func_80150DC4(struct _HSD_GObj *, void *, Vec *);
void func_80151018(struct _HSD_GObj *gobj);
void func_801510B0(struct _HSD_GObj *);

void func_80151918(struct _HSD_GObj *);
void func_80151AC8(struct _HSD_GObj *);
void func_80151CA8(struct _HSD_GObj *);
void func_80151EB4(struct _HSD_GObj *);
void func_801520D8(struct _HSD_GObj *);
void func_8015247C(struct _HSD_GObj *);
void func_801525E0(struct _HSD_GObj *);
void func_80152880(struct _HSD_GObj *);
void func_80152CD8(struct _HSD_GObj *);
void func_80152F80(struct _HSD_GObj *);
void func_801530A4(struct _HSD_GObj *);
void func_801533CC(struct _HSD_GObj *);
void func_8015364C(struct _HSD_GObj *, struct _HSD_JObj *, f32, f32);
void func_80153730(struct _HSD_GObj *);
void func_80153820(struct _HSD_GObj *);
void func_80153910(struct _HSD_GObj *);
void func_80153A64(struct _HSD_GObj *);
void func_801541C8(struct _HSD_GObj *, void *);
void func_801542E0(struct _HSD_GObj *);
void func_801545A0(struct _HSD_GObj *);
void func_801546D8(HSD_GObj *);

void func_80154A78(HSD_GObj *);
void func_80154C78(struct _HSD_GObj *);
void func_80154CF8(struct _HSD_GObj *, struct _Fighter *);
void func_80154E78(struct _HSD_GObj *);
void func_80155014(struct _HSD_GObj *);
void func_80155818(HSD_GObj *);
void func_80155B80(struct _HSD_GObj *);

void func_80155D1C(struct _HSD_GObj *);
void func_80155D6C(HSD_GObj *, s32);
void func_80155FCC();
void func_80156014();

void func_8015A2B0(HSD_GObj *);
void func_8015A3F4(HSD_GObj *);

void func_8015BD20(struct _HSD_GObj *);
void func_8015BD24(s32, f32 *, f32, s32, s32, s32);
void func_8015BDB4(struct _HSD_GObj *);
void func_8015BE40(struct _HSD_GObj *gobj, Vec *, f32 *, f32, f32);
void func_8015BF74(struct _HSD_GObj *, f32);
void func_8015C010(struct _HSD_GObj *, f32);
void func_8015C09C(struct _HSD_GObj *, f32);
void func_8015C190(struct _HSD_GObj *);
void func_8015C208(struct _HSD_GObj *, Vec *);
struct _HSD_GObj *func_8015C244(struct _HSD_GObj *, Vec *);

BOOL func_8015C31C(void);

BOOL func_8015C3A0(void);
struct _HSD_GObj *func_8015C3E8(s32);
s32 func_8015C44C(s32);
s32 func_8015C4C4(void);

void func_8015C5F8(struct _HSD_GObj *);

s8 *func_8015CE44(s32, s32);

void func_8015D888(u32);

void func_8015D8FC(u32);

s32 func_8015D94C(u32);

BOOL func_80164840(u8);

s32 func_8016AEDC(void);

s32 func_8016B0FC();

s32 func_8016B1C4();

s32 func_8016B238(void);

s32 func_8016B3A0(void);

s32 func_8016B41C();

s32 func_801A45E8(s32);

f32 func_801C0498(void);

struct _HSD_GObj *func_801C14D0(s32);

BOOL func_801C28AC(s32, u32, s32 *);

struct _HSD_GObj *func_801C2BA4(s32);

struct _HSD_JObj *func_801C2CF4(s32);

BOOL func_801C2D24(s32, Vec *);
BOOL func_801C2ED0(struct _HSD_JObj *, s32);

void func_801C39C0();
void func_801C3BB4();

struct _HSD_JObj *func_801C3FA4(struct _HSD_GObj *, s32);

s32 func_801C4210(void);
void func_801C42AC();

void *func_801C49F8(void); // get stage's "yakumono" ("about"?) param

void func_801C5A84();

void func_801C5AA4();

void func_801C5DB0(struct _HSD_GObj *, s32);

void func_801C7FF8(struct _HSD_GObj *, s32, s32, s32, f32, f32);

void func_801C8138();

void func_801C95C4(struct _HSD_GObj *);

s32 Stage_80225194(void);

void func_8026ABD8(struct _HSD_GObj *, Vec *, f32);

BOOL func_8026B2B4(struct _HSD_GObj *);

s32 itGetKind(struct _HSD_GObj *); // itGetKind
s32 func_8026B30C(struct _HSD_GObj *);
s32 func_8026B320(struct _HSD_GObj *);

void func_8026B3F8(struct _Article *, s32);

f32 func_8026B54C(struct _HSD_GObj *);
f32 func_8026B560(struct _HSD_GObj *);
f32 func_8026B574(struct _HSD_GObj *);
s32 func_8026B588();
BOOL func_8026B594(struct _HSD_GObj *);

void func_8026B7F8();

void func_8027B4A4();

void *func_8027B5B0(s32, s32, struct _HSD_JObj *, s32, s32);

void func_80294E78(struct _HSD_GObj *, f32);

struct _HSD_GObj *func_8029A748(struct _HSD_GObj *, Vec *, u8, f32);
void func_8029A89C(struct _HSD_GObj *, f32);
void func_8029A8F4(struct _HSD_GObj *, Vec *, f32);

s32 func_802B1DEC(u32);
u32 func_802B1DF8(HSD_GObj *, Vec *, Vec *, s32, s32, s32);
s32 func_802B1FC8(u32);
void func_802B1FE8(u32, Vec *);

void func_802B56E4(u32, Vec *, f32, f32, f32);

void *func_802C8B28(struct _HSD_GObj *, Vec *, u32, f32);

void func_802D8618(s32, Vec *, s32, s32);

u32 func_802F0340(struct _HSD_GObj *, Vec *, Vec *, u32, u32, f32);
void func_802F046C(s32);

void func_802F0AE0(struct _HSD_GObj *, Vec *, Vec *, s32, s32, f32, f32, f32);

s32 func_802FB6E8(u8);

s32 func_802FC998();

s32 func_80322258(f32 x);

void __cvt_sll_flt(void);
void __cvt_dbl_usll(void);

int __StringRead(void *, int, int);
char *strchr(const char *, int);
int strncmp(const char *, const char *, unsigned long);
int strcmp(const char *, const char *);
char *strncpy(char *__restrict, const char *__restrict, unsigned long);
char *strcpy(char *__restrict, const char *__restrict);
unsigned long strlen(const char *);

f32 tanf(f32);

f32 cosf(f32);
f32 sinf(f32);

#pragma region "asm/dolphin/mtx/mtx.s"
void PSMTXIdentity(Mtx m);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXRotAxisRad(Mtx m, const Vec *axis, f32 rad);
void PSMTXTrans(Mtx m, f32 x_trans, f32 y_trans, f32 z_trans);
void PSMTXScale(Mtx m, f32 x_scale, f32 y_scale, f32 z_scale);
void PSMTXQuat(Mtx m, const Quaternion *q);
#pragma endregion

void PSMTXMUltiVec(Mtx, Vec *, Vec *);

#pragma region "asm/dolphin/mtx/vec.s"
void PSVECAdd(Vec *a, Vec *b, Vec *result);
void PSVECScale(Vec *src, Vec *dst, f32 scale);
f32 PSVECMag(Vec *v);
f32 PSVECDotProduct(Vec *a, Vec *b);
#pragma endregion

void *OSAllocFromHeap(int, u32);

void OSReport(char *, ...);

u32 OSGetConsoleSimulatedMemSize();

void VIWaitForRetrace(void);

struct _HSD_DObj *HSD_DObjLoadDesc(struct _HSD_DObjDesc *);

struct _HSD_TObj *allocShadowTObj();

struct _HSD_ImageDesc *HSD_ImageDescAlloc();

struct _HSD_MObj *HSD_MObjLoadDesc(struct _HSD_MObjDesc *);

void HSD_AObjRemove(struct _HSD_AObj *aobj);

void HSD_ForeachAnim(void *, ...);

struct _HSD_WObj *HSD_LObjGetPositionWObj(struct _HSD_LObj *);
struct _HSD_WObj *HSD_LObjGetInterestWObj(struct _HSD_LObj *);

f32 HSD_CObjGetNear(struct _HSD_CObj *);

f32 HSD_CObjGetFar(struct _HSD_CObj *);

void HSD_CObjSetScissorx4();

void HSD_CObjSetViewportfx4();
u32 HSD_CObjGetProjectionType(struct _HSD_CObj *);

struct _HSD_PObj *HSD_PObjLoadDesc(struct _HSD_PObjDesc *);

void HSD_EraseRect();
void HSD_GXInit(void);
void HSD_OSInit(void);
int HSD_GetHeap(void);

void HSD_ObjInit(void);

void HSD_VIInit(struct _HSD_VIStatus *vi_status, void *xfb0, void *xfb1, void *xfb2);

void func_80378280(u8, int);

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);

void splArcLengthPoint(Vec *, struct _HSD_Spline *, f32);
void func_80379310();
void HSD_MtxSRT();

void *func_8037ABC8(struct _HSD_ObjAllocData *data);
void func_8037AD20(struct _HSD_ObjAllocData *data, struct _HSD_ObjAllocLink *obj);

void HSD_RObjRemoveAnimAll(struct _HSD_RObj *robj);

void HSD_RObjReqAnimAll(struct _HSD_RObj *robj, f32 frame);

void HSD_IDSetup(void);

void *func_8037CF98(struct _HSD_IDTable *table, u32 id, u8 *success);

void func_8037EE0C(Vec *, Quaternion *);
void func_8037EF28(Quaternion *, Quaternion *, Quaternion *, f32);

void func_803881E4(void);
void HSD_Panic(char *, u32, char *);

void func_8038FD54(struct _HSD_GObj *, void (*)(struct _HSD_GObj *), s32);

struct _HSD_GObj *func_803901F0(s32, s32, s32);
void func_80390228(struct _HSD_GObj *);

void efLib_PauseAll(struct _HSD_GObj *);
void efLib_ResumeAll(struct _HSD_GObj *);
s32 func_80096CC8(struct _HSD_GObj *);
void ef_Spawn(s32, ...);
f32 HSD_Randf(void);
s32 HSD_Randi(s32);

#endif

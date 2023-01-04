#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;
typedef struct _Item Item;
typedef struct _Article Article;

/// @addtogroup ftlib ftLib
/// @{
struct _HSD_GObj* func_8008627C(Vec*, struct _HSD_GObj*);
void func_800866DC(struct _HSD_GObj*, Vec*);
void func_800867E8();
void func_8008688C();
s32 func_80087120(struct _HSD_GObj*);
s32 func_800872A4(struct _HSD_GObj*);
/// @}

/// @addtogroup ft_unknown_006 ftUnk6
/// @{
void func_800880D8();
void func_80088148(struct _Fighter*, u32, u32, u32);
void func_800881D8(struct _Fighter*, u32, u32, u32);
void func_80088640();
void func_800887CC();
void func_80088884();
void func_800888E0();
void func_80088A50(struct _Fighter*);
void func_80088C5C();
void func_800890BC(struct _Fighter*);
void func_800890D0();
void func_800892A0(struct _HSD_GObj*);
void func_800892D4(struct _Fighter*);
void func_800895E0();
void func_80089824(struct _HSD_GObj*);
void func_80089B08(struct _HSD_GObj* pPlayerEntityStruct);
void func_8008A2BC(struct _HSD_GObj* gobj);
f32 func_8008D7F0(struct _Fighter*);
f32 scaleBy154_8008D8D8(f32);
s32 func_8008D8E8(f32);
void func_8008D930();
void func_8008DCE0(HSD_GObj*, s32, f32);
void func_8008E908(struct _HSD_GObj*, f32);
s32 func_8008E984(struct _Fighter*);
void func_8008E9D0();
void func_8008EB58();
void func_8008EC90();
void func_80090594();
u32 func_80090690(struct _Fighter*, struct _Vec2*);
void func_80090718();
f32 func_80092ED8(s32, void*, f32);
s32 func_80093694();
s32 func_8009515C(s32);
void func_80095744();
s32 func_800964FC(struct _Fighter*);
void func_800968C8();
void func_80096900(struct _HSD_GObj*, s32, s32, s32, f32, f32);
void func_8009750C(HSD_GObj*);
void func_80098B20();
void func_80098C9C();
void func_80099D9C();
s32 func_8009A080(s32);
void func_8009A804(struct _HSD_GObj*);
void func_8009CF84();
void func_8009E0A8();
void func_8009E0D4();
void func_8009E7B4();
s32 func_8009EF68(struct _HSD_GObj*);
void func_8009F4A4();
void func_8009F578();
void func_800A0DA4();
void func_800A101C(struct _Fighter*, s8, s8, s32);
f32 func_800A17E4(struct _Fighter*);
f32 func_800A1874(struct _Fighter*);
f32 func_800A1904(struct _Fighter*);
f32 func_800A1948(struct _Fighter*);
s32 func_800A198C(struct _Fighter*);
f32 func_800A1994(struct _Fighter*);
f32 func_800A1A24(struct _Fighter*);
s32 func_800A2040();
void func_800B3900();
void func_800BFD04();
void func_800BFFAC(struct _Fighter*);
void func_800BFFD0(struct _Fighter*, s32, s32);
void func_800C0074(struct _Fighter*);
void func_800C0134();
void func_800C0200();
void func_800C0408();
s32 func_800C0694();
void func_800C09B4(struct _HSD_GObj*);
void func_800C0A98(struct _HSD_GObj* fighter_gobj);

/// @todo UnclePunch Map file: AS_203_PassiveWalljump_Walljump
void func_800C1E64(struct _HSD_GObj* pPlayerEntityStruct, s32, s32, u8, f32);

void func_800C2FD8();
void func_800C37A0();
void func_800C511C();
void func_800C61B0();
void func_800C8064();
void func_800C8348(struct _HSD_GObj*, s32, s32);
void func_800C8438(struct _HSD_GObj*);
void func_800C8540();
void func_800C884C();
void func_800C88A0(struct _Fighter*);
void func_800C89A0(struct _HSD_GObj*);
void func_800C8A64();
s32 func_800C8B2C();
void func_800C8C84();
void func_800C8D00();
void func_800C8F6C();
void func_800C8FC4(struct _HSD_GObj*);
void func_800C9034();
void func_800C9840(HSD_GObj*, s32, s32, f32, f32, f32);
s32 func_800CAE80();
void func_800CB110(HSD_GObj*, s32, f32);
void func_800CC730(struct _HSD_GObj*);
void func_800D0FA0();
void func_800D105C(struct _HSD_GObj*);
void func_800D14E4();
void func_800D1A8C();
void func_800D1E80();
void func_800D237C();
void func_800D3158(struct _HSD_GObj* fighter_gobj);
void func_800D4F24(struct _HSD_GObj*, s32);
void func_800D5AEC(HSD_GObj*, s32, s32, s32, Fighter*, f32, f32);
void func_800D5CB0(struct _HSD_GObj*, s32, f32);
s32 func_800D67C4(struct _Fighter*);
s32 func_800D688C(struct _Fighter*);
s32 func_800D6928(struct _Fighter*);
void func_800D71D8();
void func_800D94D8(HSD_GObj*);
void func_800DA824(Fighter*);
void func_800DB368(Fighter*, Fighter*);
void func_800DB464(HSD_GObj*);
void func_800DC750(HSD_GObj*);
void func_800DD168(HSD_GObj*);
void func_800DE2A8(HSD_GObj*, HSD_GObj*);
void func_800DE508(HSD_GObj*);
void func_800DE7C0(struct _HSD_GObj*, s32, s32);
void func_800DEEA8(struct _HSD_GObj* fighter_gobj);
u32 func_800DEEE8(struct _Fighter*, struct _Vec2*);
void func_800DEF38();
void func_800DF0D0();
s32 func_80096CC8(struct _HSD_GObj*);
/// @}

/// @addtogroup ftcaptain ftCaptain
/// @{
void ftCaptain_OnLoadForGanon(struct _Fighter*);

/// @todo @c ftCaptain prefix
void ftCFalcon_LoadSpecialAttrs(struct _HSD_GObj*);
/// @}

/// @addtogroup ftfox ftFox
/// @{
void ftFox_LoadSpecialAttrs(struct _HSD_GObj*);
/// @}

/// @addtogroup ftfox_specialn ftFox_SpecialN
/// @{
void ftFox_RemoveBlaster(struct _HSD_GObj*);
/// @}

/// @addtogroup ftlink ftLink
/// @{
void func_800EC06C();
void func_800ECD04(HSD_GObj*);
void func_800ECD58(HSD_GObj*);
/// @}

/// @addtogroup ftkirby ftKirby
/// @{
void func_800EED50(s32, s32);
void func_800F1D24();
void func_800F5BA4();
void func_800F5C34();
/// @}

/// @addtogroup ftness_attacks4 ftNess_AttackS4
/// @{
void ftNess_ItemNessBatRemove(struct _HSD_GObj*);
/// @}

/// @addtogroup ftness_attackhi4 ftNess_AttackHi4
/// @{
void ftNess_YoyoItemDespawn(struct _HSD_GObj*);
/// @}

/// @addtogroup ftness_specialn ftNess_SpecialN
/// @{
void ftNess_ItemPKFlushSetNULL(struct _HSD_GObj*);
/// @}

/// @addtogroup ftness_specialhi ftNess_SpecialHi
/// @{
void ftNess_SpecialHiTakeDamage(struct _HSD_GObj*);
/// @}

/// @addtogroup ftpikachu1 ftPikachu1
/// @{
void ftPikachu_LoadSpecialAttrs(struct _HSD_GObj*);
/// @}

/// @addtogroup ftsamus2 ftSamus2
/// @{
f32 ftSamus_80128AC8(HSD_GObj* fighter_gobj, f32 farg1, f32 farg2);
void ftSamus_80128B1C(HSD_GObj*, f32, f32, f32);
/// @}

/// @addtogroup ftmars ftMars
/// @{
void ftMars_OnLoadForRoy(struct _Fighter*);
void ftMars_LoadSpecialAttrs(struct _HSD_GObj*);
/// @}

/// @addtogroup ftclink ftCLink
/// @{
void func_80149268(HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_2 ftMasterHand_02
/// @{
void func_8014FE10();
void func_8014FE58();
void func_80150144(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_3 ftMasterHand_03
/// @{
void func_80150C8C(struct _HSD_GObj*);
void func_80150D28(struct _HSD_GObj*);
void func_80150DC4(struct _HSD_GObj*, void*, Vec*);
void func_80151018(struct _HSD_GObj* gobj);
/// @}

/// @addtogroup ftmasterhand_4 ftMasterHand_04
/// @{
void func_801510B0(struct _HSD_GObj*);

/// @}
///
/// @addtogroup ftmasterhand_6 ftMasterHand_06
/// @{
void func_80151918(struct _HSD_GObj*);
void func_80151AC8(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_8 ftMasterHand_08
/// @{
void func_80151CA8(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_9 ftMasterHand_09
/// @{
void func_80151EB4(struct _HSD_GObj*);
void func_801520D8(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_11 ftMasterHand_11
/// @{
void func_8015247C(struct _HSD_GObj*);
void func_801525E0(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_13 ftMasterHand_13
/// @{
void func_80152880(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_14 ftMasterHand_14
/// @{
void func_80152CD8(struct _HSD_GObj*);
void func_80152F80(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_15 ftMasterHand_15
/// @{
void func_801530A4(struct _HSD_GObj*);
void func_801533CC(struct _HSD_GObj*);
void func_80153730(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_16 ftMasterHand_16
/// @{
void func_80153820(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_17 ftMasterHand_17
/// @{
void func_80153910(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_18 ftMasterHand_18
/// @{
void func_80153A64(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_21 ftMasterHand_21
/// @{
void func_801541C8(struct _HSD_GObj*, void*);
/// @}

/// @addtogroup ftmasterhand_22 ftMasterHand_22
/// @{
void func_801542E0(struct _HSD_GObj*);
void func_801545A0(struct _HSD_GObj*);
void func_801546D8(HSD_GObj*);
/// @}
/// @addtogroup ftmasterhand_23 ftMasterHand_23
/// @{
void func_80154A78(HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_24 ftMasterHand_24
/// @{
void func_80154C78(struct _HSD_GObj*);
void func_80154CF8(struct _HSD_GObj*, struct _Fighter*);
/// @}

/// @addtogroup ftmasterhand_25 ftMasterHand_25
/// @{
void func_80154E78(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_26 ftMasterHand_26
/// @{
void func_80155014(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_30 ftMasterHand_30
/// @{
void func_80155818(HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_32 ftMasterHand_32
/// @{
void func_80155B80(struct _HSD_GObj*);
/// @}

/// @addtogroup ftmasterhand_34 ftMasterHand_34
/// @{
void func_80155D1C(struct _HSD_GObj*);
void func_80155D6C(HSD_GObj*, s32);
/// @}

/// @addtogroup ftcrazyhand ftCrazyHand
/// @{
void func_80155FCC();
void func_80156014();
void func_8015A2B0(HSD_GObj*);
void func_8015A3F4(HSD_GObj*);
/// @}

/// @addtogroup ftbosslib ftBossLib
/// @{
void func_8015BD20(struct _HSD_GObj*);
void func_8015BD24(s32, f32*, f32, s32, s32, s32);
void func_8015BDB4(struct _HSD_GObj*);
void func_8015BE40(struct _HSD_GObj* gobj, Vec*, f32*, f32, f32);
void func_8015BF74(struct _HSD_GObj*, f32);
void func_8015C010(struct _HSD_GObj*, f32);
void func_8015C09C(struct _HSD_GObj*, f32);
void func_8015C190(struct _HSD_GObj*);
void func_8015C208(struct _HSD_GObj*, Vec*);
struct _HSD_GObj* func_8015C244(struct _HSD_GObj*, Vec*);
BOOL func_8015C31C(void);
BOOL func_8015C3A0(void);
struct _HSD_GObj* func_8015C3E8(s32);
s32 func_8015C44C(s32);
s32 func_8015C4C4(void);
void func_8015C5F8(struct _HSD_GObj*);
/// @}

/// @addtogroup gmmain_lib gmMainLib
/// @{
s8* func_8015CE44(s32, s32);

/// @todo static
void func_8015D888(u32);

void func_8015D8FC(u32);
s32 func_8015D94C(u32);
/// @}

/// @addtogroup code_801601C4 gmUnk1
/// @{
BOOL func_80164840(u8);
s32 func_8016AEDC(void);
s32 func_8016B0FC();
s32 func_8016B1C4();
s32 func_8016B238(void);
s32 func_8016B3A0(void);
s32 func_8016B41C();
/// @}

/// @addtogroup text_2 unkUnk2
/// @{
s32 func_801A45E8(s32);
/// @}

/// @addtogroup grground grGround
/// @{
f32 func_801C0498(void);
struct _HSD_GObj* func_801C14D0(s32);
BOOL func_801C28AC(s32, u32, s32*);
struct _HSD_GObj* func_801C2BA4(s32);
struct _HSD_JObj* func_801C2CF4(s32);
BOOL func_801C2D24(s32, Vec*);
BOOL func_801C2ED0(struct _HSD_JObj*, s32);
void func_801C39C0();
void func_801C3BB4();
struct _HSD_JObj* func_801C3FA4(struct _HSD_GObj*, s32);
s32 func_801C4210(void);
void func_801C42AC();

/// @brief Get stage's "yakumono" ("about"?) param
void* func_801C49F8(void);

void func_801C5A84();
void func_801C5AA4();
/// @}

/// @addtogroup grdisplay grDisplay
/// @{
void func_801C5DB0(struct _HSD_GObj*, s32);
/// @}

/// @addtogroup granime grAnime
/// @{
void func_801C7FF8(struct _HSD_GObj*, s32, s32, s32, f32, f32);
void func_801C8138();
/// @}

/// @addtogroup grmaterial grMaterial
/// @{
void func_801C95C4(struct _HSD_GObj*);
/// @}

/// @addtogroup grstage grStage
/// @{
s32 Stage_80225194(void);
/// @}

/// @addtogroup item itUnk1
/// @{
void func_8026ABD8(struct _HSD_GObj*, Vec*, f32);
/// @}

/// @addtogroup item2 itUnk2
/// @{
BOOL func_8026B2B4(struct _HSD_GObj*);
s32 itGetKind(struct _HSD_GObj*);
s32 func_8026B30C(struct _HSD_GObj*);
s32 func_8026B320(struct _HSD_GObj*);
void func_8026B3F8(struct _Article*, s32);
f32 func_8026B54C(struct _HSD_GObj*);
f32 func_8026B560(struct _HSD_GObj*);
f32 func_8026B574(struct _HSD_GObj*);
s32 func_8026B588();
BOOL func_8026B594(struct _HSD_GObj*);
void func_8026B7F8();
/// @}

/// @addtogroup code_80266F3C itUnk3
/// @{
void func_8027B4A4();
void* func_8027B5B0(s32, s32, struct _HSD_JObj*, s32, s32);
/// @}

/// @addtogroup code_8027CF30 itUnk4
/// @{
void func_80294E78(struct _HSD_GObj*, f32);
struct _HSD_GObj* func_8029A748(struct _HSD_GObj*, Vec*, u8, f32);
void func_8029A89C(struct _HSD_GObj*, f32);
void func_8029A8F4(struct _HSD_GObj*, Vec*, f32);
s32 func_802B1DEC(u32);
u32 func_802B1DF8(HSD_GObj*, Vec*, Vec*, s32, s32, s32);
s32 func_802B1FC8(u32);
void func_802B1FE8(u32, Vec*);
void func_802B56E4(u32, Vec*, f32, f32, f32);
void* func_802C8B28(struct _HSD_GObj*, Vec*, u32, f32);
void func_802D8618(s32, Vec*, s32, s32);
u32 func_802F0340(struct _HSD_GObj*, Vec*, Vec*, u32, u32, f32);
void func_802F046C(s32);
void func_802F0AE0(struct _HSD_GObj*, Vec*, Vec*, s32, s32, f32, f32, f32);
/// @}

/// @addtogroup ifmagnify ifMagnify
/// @{
s32 func_802FB6E8(u8);
s32 func_802FC998();
/// @}

/// @addtogroup text_4 unkUnk4
/// @{
s32 func_80322258(f32 x);
/// @}

/// @addtogroup runtime_runtime runtimeRuntime
/// @{
void __cvt_sll_flt(void);
void __cvt_dbl_usll(void);
/// @}

/// @addtogroup msl_string mslString
/// @{
int __StringRead(void*, int, int);
char* strchr(const char*, int);
int strncmp(const char*, const char*, unsigned long);
int strcmp(const char*, const char*);
char* strncpy(char* __restrict, const char* __restrict, unsigned long);
char* strcpy(char* __restrict, const char* __restrict);
unsigned long strlen(const char*);
/// @}

/// @addtogroup msl_trigf mslTrigF
/// @{
f32 tanf(f32);
f32 cosf(f32);
f32 sinf(f32);
/// @}

/// @addtogroup dolphin_mtx PSMTX
/// @{
void PSMTXIdentity(Mtx m);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void PSMTXTrans(Mtx m, f32 x_trans, f32 y_trans, f32 z_trans);
void PSMTXScale(Mtx m, f32 x_scale, f32 y_scale, f32 z_scale);
void PSMTXQuat(Mtx m, const Quaternion* q);
/// @}

/// @addtogroup dolphin_mtx_mtxvec PSMTXVec
/// @{
void PSMTXMUltiVec(Mtx, Vec*, Vec*);
/// @}

/// @addtogroup dolphin_mtx_vec PSVEC
/// @{
void PSVECAdd(Vec* a, Vec* b, Vec* result);
void PSVECScale(Vec* src, Vec* dst, f32 scale);
f32 PSVECMag(Vec* v);
f32 PSVECDotProduct(Vec* a, Vec* b);
/// @}

/// @addtogroup dolphin_vi VI
/// @{
void VIWaitForRetrace(void);
/// @}

/// @addtogroup todo_unk NOT FOUND
/// @{

/// @todo This doesn't exist???
void* func_8037ABC8(struct _HSD_ObjAllocData* data);

/// @todo This doesn't exist???
void func_8037AD20(struct _HSD_ObjAllocData* data,
                   struct _HSD_ObjAllocLink* obj);

/// @todo This doesn't exist???
void* func_8037CF98(struct _HSD_IDTable* table, u32 id, u8* success);
/// @}

/// @addtogroup eflib efLib
/// @{
void efLib_PauseAll(struct _HSD_GObj*);
void efLib_ResumeAll(struct _HSD_GObj*);
/// @}

/// @addtogroup efsync efSync
/// @{
void ef_Spawn(s32, ...);
/// @}

#endif

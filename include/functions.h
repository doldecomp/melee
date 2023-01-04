#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;
typedef struct _Item Item;
typedef struct _Article Article;

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

#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;
typedef struct _Item Item;
typedef struct _Article Article;

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

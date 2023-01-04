#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;
typedef struct _Item Item;
typedef struct _Article Article;

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

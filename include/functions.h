#ifndef _functions_h_
#define _functions_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

typedef struct _HSD_GObj HSD_GObj;
typedef struct _Fighter Fighter;
typedef struct _Item Item;
typedef struct _Article Article;

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

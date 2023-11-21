#ifndef GALE01_0679B0
#define GALE01_0679B0

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ftanim.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "lb/lbcollision.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx/types.h>
#include <baselib/archive.h>
#include <baselib/controller.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

/// @todo #Fighter_804D64FC..#Fighter_804D6550 are initialized to 0 in
///       #Fighter_LoadCommonData, probably all pointers
extern UNK_T Fighter_804D64FC;
extern UNK_T Fighter_804D6500;
extern UNK_T Fighter_804D6504;
extern UNK_T Fighter_804D6508;
extern int* Fighter_804D650C;
extern UNK_T Fighter_804D6510;
extern UNK_T Fighter_804D6514;
extern UNK_T Fighter_804D6518;
extern UNK_T Fighter_804D651C;
extern float* Fighter_804D6524;
extern UNK_T Fighter_804D6528;
extern Vec2** Fighter_804D6530;
extern UNK_T Fighter_804D6534;
extern UNK_T Fighter_804D6538;
extern UNK_T Fighter_804D653C;
extern int** Fighter_804D6540;
extern UNK_T Fighter_804D6548;
extern UNK_T Fighter_804D654C;
extern int** Fighter_804D6550;

extern unk_t Fighter_804D6520;
extern ftCommonData* p_ftCommonData;
extern FighterPartsTable** ftPartsTable;

extern HSD_ObjAllocData fighter_alloc_data;
extern HSD_ObjAllocData Fighter_80458FFC;
extern HSD_ObjAllocData fighter_bones_alloc_data;
extern HSD_ObjAllocData Fighter_80459054;
extern HSD_ObjAllocData Fighter_80459080;
extern HSD_ObjAllocData Fighter_804590AC;

// functions in fighter.c
void Fighter_800679B0(void);
void Fighter_FirstInitialize_80067A84(void);
void Fighter_LoadCommonData(void);
void Fighter_UpdateModelScale(Fighter_GObj* gobj);
void Fighter_UnkInitReset_80067C98(Fighter*);
void Fighter_UnkProcessDeath_80068354(Fighter_GObj* gobj);
void Fighter_UnkUpdateCostumeJoint_800686E4(Fighter_GObj* gobj);
void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fp);
void Fighter_ResetInputData_80068854(Fighter_GObj* gobj);
void Fighter_UnkInitLoad_80068914(Fighter_GObj* gobj, struct S_TEMP1* argdata);
u32 Fighter_NewSpawn_80068E40(void);
void Fighter_80068E64(Fighter_GObj* gobj);
Fighter_GObj* Fighter_Create(struct S_TEMP1* input);
void Fighter_ChangeMotionState(Fighter_GObj* gobj, FtMotionId msid,
                               MotionFlags flags, float anim_start,
                               float anim_speed, float anim_blend,
                               Fighter_GObj* arg3);
void Fighter_8006A1BC(Fighter_GObj* gobj);
void Fighter_8006A360(Fighter_GObj* gobj);
void Fighter_8006ABA0(Fighter_GObj* gobj);
void Fighter_UnkIncrementCounters_8006ABEC(Fighter_GObj* gobj);
void Fighter_Spaghetti_8006AD10(Fighter_GObj* gobj);
void Fighter_procUpdate(Fighter_GObj* gobj);
void Fighter_UnkApplyTransformation_8006C0F0(Fighter_GObj* gobj);
void Fighter_8006C27C(Fighter_GObj* gobj);
void Fighter_8006C5F4(Fighter_GObj* gobj);
void Fighter_CallAcessoryCallbacks_8006C624(Fighter_GObj* gobj);
void Fighter_8006C80C(Fighter_GObj* gobj);
void Fighter_UnkProcessGrab_8006CA5C(Fighter_GObj* gobj);
void Fighter_8006CB94(Fighter_GObj* gobj);
void Fighter_UnkTakeDamage_8006CC30(Fighter* fp, f32 damage_amount);
void Fighter_TakeDamage_8006CC7C(Fighter*, f32);
void Fighter_8006CDA4(Fighter* fp, s32 arg1, s32 arg2);
void Fighter_8006CF5C(Fighter* fp, s32 arg1);
void Fighter_UnkSetFlag_8006CFBC(Fighter_GObj* gobj);
void Fighter_8006CFE0(Fighter_GObj* gobj);
void Fighter_UnkRecursiveFunc_8006D044(Fighter_GObj* gobj);
void Fighter_8006D10C(Fighter_GObj* gobj);
void Fighter_UnkProcessShieldHit_8006D1EC(Fighter_GObj* gobj);
void Fighter_8006D9AC(Fighter_GObj* gobj);
void Fighter_UnkCallCameraCallback_8006D9EC(Fighter_GObj* gobj);
void Fighter_8006DA4C(Fighter_GObj* gobj);
void Fighter_Unload_8006DABC(void* user_data);

#endif

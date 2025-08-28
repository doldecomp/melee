#ifndef GALE01_0679B0
#define GALE01_0679B0

#include <placeholder.h>
#include <platform.h>

#include "ft/inlines.h" // IWYU pragma: export
#include "ft/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <baselib/objalloc.h>

extern struct Fighter_804D64FC_t {
    u8** cmdscripts;
}* Fighter_804D64FC;

/* 0679B0 */ void Fighter_800679B0(void);
/* 067A84 */ void Fighter_FirstInitialize_80067A84(void);
/* 067ABC */ void Fighter_LoadCommonData(void);
/* 067BB4 */ void Fighter_UpdateModelScale(Fighter_GObj* gobj);
/* 067C98 */ void Fighter_UnkInitReset_80067C98(Fighter*);
/* 068354 */ void Fighter_UnkProcessDeath_80068354(Fighter_GObj* gobj);
/* 0686E4 */ void Fighter_UnkUpdateCostumeJoint_800686E4(Fighter_GObj* gobj);
/* 06876C */ void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fp);
/* 068854 */ void Fighter_ResetInputData_80068854(Fighter_GObj* gobj);
/* 068914 */ void Fighter_UnkInitLoad_80068914(Fighter_GObj* gobj,
                                               struct S_TEMP1* argdata);
/* 068E40 */ u32 Fighter_NewSpawn_80068E40(void);
/* 068E64 */ void Fighter_80068E64(Fighter_GObj* gobj);
/* 068E98 */ Fighter_GObj* Fighter_Create(struct S_TEMP1* input);
/* 0693AC */ void Fighter_ChangeMotionState(Fighter_GObj* gobj,
                                            FtMotionId msid, MotionFlags flags,
                                            f32 anim_start, f32 anim_speed,
                                            f32 anim_blend,
                                            Fighter_GObj* arg3);
/* 06A1BC */ void Fighter_8006A1BC(Fighter_GObj* gobj);
/* 06A360 */ void Fighter_8006A360(Fighter_GObj* gobj);
/* 06ABA0 */ void Fighter_8006ABA0(Fighter_GObj* gobj);
/* 06ABEC */ void Fighter_UnkIncrementCounters_8006ABEC(Fighter_GObj* gobj);
/* 06AD10 */ void Fighter_Spaghetti_8006AD10(Fighter_GObj* gobj);
/* 06B82C */ void Fighter_procUpdate(Fighter_GObj* gobj);
/* 06C0F0 */ void Fighter_UnkApplyTransformation_8006C0F0(Fighter_GObj* gobj);
/* 06C27C */ void Fighter_8006C27C(Fighter_GObj* gobj);
/* 06C5F4 */ void Fighter_8006C5F4(Fighter_GObj* gobj);
/* 06C624 */ void Fighter_CallAcessoryCallbacks_8006C624(Fighter_GObj* gobj);
/* 06C80C */ void Fighter_8006C80C(Fighter_GObj* gobj);
/* 06CA5C */ void Fighter_UnkProcessGrab_8006CA5C(Fighter_GObj* gobj);
/* 06CB94 */ void Fighter_8006CB94(Fighter_GObj* gobj);
/* 06CC30 */ void Fighter_UnkTakeDamage_8006CC30(Fighter* fp,
                                                 float damage_amount);
/* 06CC7C */ void Fighter_TakeDamage_8006CC7C(Fighter*, float);
/* 06CDA4 */ void Fighter_8006CDA4(Fighter* fp, s32 arg1, s32 arg2);
/* 06CF5C */ void Fighter_8006CF5C(Fighter* fp, s32 arg1);
/* 06CFBC */ void Fighter_UnkSetFlag_8006CFBC(Fighter_GObj* gobj);
/* 06CFE0 */ void Fighter_8006CFE0(Fighter_GObj* gobj);
/* 06D044 */ void Fighter_UnkRecursiveFunc_8006D044(Fighter_GObj* gobj);
/* 06D10C */ void Fighter_8006D10C(Fighter_GObj* gobj);
/* 06D1EC */ void Fighter_ProcessHit_8006D1EC(Fighter_GObj* gobj);
/* 06D9AC */ void Fighter_8006D9AC(Fighter_GObj* gobj);
/* 06D9EC */ void Fighter_UnkCallCameraCallback_8006D9EC(Fighter_GObj* gobj);
/* 06DA4C */ void Fighter_8006DA4C(Fighter_GObj* gobj);
/* 06DABC */ void Fighter_Unload_8006DABC(void* user_data);
/* 458FD0 */ extern HSD_ObjAllocData fighter_alloc_data;
/* 458FFC */ extern HSD_ObjAllocData fighter_dat_attrs_alloc_data;
/* 459028 */ extern HSD_ObjAllocData fighter_parts_alloc_data;
/* 459054 */ extern HSD_ObjAllocData fighter_dobj_list_alloc_data;
/* 459080 */ extern HSD_ObjAllocData fighter_x2040_alloc_data;
/* 4590AC */ extern HSD_ObjAllocData fighter_x59C_alloc_data;
/* 4598B8 */ extern ftData* gFtDataList[FTKIND_MAX];
/* 4D6500 */ extern UNK_T Fighter_804D6500;
/* 4D6504 */ extern HSD_Joint* Fighter_804D6504;
/* 4D6508 */ extern u8* Fighter_804D6508;
/* 4D650C */ extern u8* Fighter_804D650C;
/* 4D6510 */ extern UNK_T Fighter_804D6510;
/* 4D6514 */ extern UNK_T Fighter_804D6514;
/* 4D6518 */ extern UNK_T Fighter_804D6518;
/* 4D651C */ extern float* Fighter_804D651C;
/* 4D6520 */ extern float* Fighter_804D6520;
/* 4D6524 */ extern float* Fighter_804D6524;

/* 4D6528 */ extern struct Fighter_804D6528_t {
    Vec2* x0;
    int x4;
}* Fighter_804D6528;

/* 4D6530 */ extern Vec2** Fighter_804D6530;
/* 4D6534 */ extern UNK_T Fighter_804D6534;
/* 4D6538 */ extern struct Fighter_804D653C_t* Fighter_804D6538;
/* 4D653C */ extern struct Fighter_804D653C_t* Fighter_804D653C;
/* 4D6540 */ extern struct Fighter_804D6540_t {
    struct Fighter_804D6540_x0_t {
        u8 x0;
        u8 x1;
        u8 x2;
        u8 x3;
    }* x0;
    int x4;
}** Fighter_804D6540;
/* 4D6544 */ extern FighterPartsTable** ftPartsTable;
/* 4D6548 */ extern UNK_T Fighter_804D6548;
/* 4D654C */ extern UNK_T Fighter_804D654C;
/* 4D6550 */ extern int** Fighter_804D6550;
/* 4D6554 */ extern ftCommonData* p_ftCommonData;

#endif

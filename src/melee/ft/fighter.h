#ifndef _fighter_h_
#define _fighter_h_

#include <common_structs.h>
#include <dolphin/mtx/mtxtypes.h>
#include <math.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftstatevars.h>
#include <melee/ft/types.h>
#include <melee/gr/stage.h>
#include <melee/it/item2.h>
#include <melee/lb/lbcollision.h>
#include <melee/lb/lbrefract.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/random.h>

/// @todo #lbl_804D64FC..#lbl_804D6550 are initialized to 0 in
///       #Fighter_LoadCommonData, probably all pointers
extern void* lbl_804D64FC;
extern void* lbl_804D6500;
extern void* lbl_804D6504;
extern void* lbl_804D6508;
extern void* lbl_804D650C;
extern void* lbl_804D6510;
extern void* lbl_804D6514;
extern void* lbl_804D6518;
extern void* lbl_804D651C;
extern void* lbl_804D6524;
extern void* lbl_804D6528;
extern void* lbl_804D6530;
extern void* lbl_804D6534;
extern void* lbl_804D6538;
extern void* lbl_804D653C;
extern s32** lbl_804D6540;
extern void* lbl_804D6548;
extern void* lbl_804D654C;
extern void* lbl_804D6550;

// Ternary macro for fcmpo-based facing direction check

#define CLIFFCATCH_O(fp)                                                       \
    ((fp)->x2C_facing_direction < 0.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT

// Ternary macro for fcmpu-based facing direction check

#define CLIFFCATCH_U(fp)                                                       \
    ((fp)->x2C_facing_direction != 1.0f) ? CLIFFCATCH_LEFT : CLIFFCATCH_RIGHT

static inline Fighter* getFighter(HSD_GObj* fighter_gobj)
{
    return fighter_gobj->user_data;
}

static inline Fighter*
getFighterPlus(HSD_GObj* fighter_gobj) // Uses more stack space //
{
    Fighter* fp = fighter_gobj->user_data;
    return fp;
}

static inline void* getFtSpecialAttrs(Fighter* fp)
{
    void* fighter_attr = fp->x2D4_specialAttributes;
    return fighter_attr;
}

static inline void* getFtSpecialAttrsD(Fighter* fp) // Direct
{
    return fp->x2D4_specialAttributes;
}

static inline s32 ftGetKind(Fighter* fp)
{
    return fp->x4_fighterKind;
}

static inline s32 ftGetAction(Fighter* fp)
{
    return fp->x10_action_state_index;
}

static inline void* getFtSpecialAttrs2CC(Fighter* fp)
{
    void* fighter_attr = fp->x2CC;
    return fighter_attr;
}

static inline attr* getFtAttrs(Fighter* fp)
{
    return &fp->x110_attr;
}

static inline CollData* getFtColl(Fighter* fp)
{
    return &fp->x6F0_collData;
}

static inline BOOL ftGetGroundAir(Fighter* fp)
{
    return fp->xE0_ground_or_air;
}

static inline f32 stickGetDir(f32 x1, f32 x2)
{
    if (x1 < x2) {
        return -x1;
    } else
        return x1;
}

// functions in fighter.c
void Fighter_800679B0();
void Fighter_FirstInitialize_80067A84();
void Fighter_LoadCommonData();
void Fighter_UpdateModelScale(HSD_GObj* fighter_gobj);
void Fighter_UnkInitReset_80067C98(Fighter*);
void Fighter_UnkProcessDeath_80068354(HSD_GObj* fighter_gobj);
void Fighter_UnkUpdateCostumeJoint_800686E4(HSD_GObj* fighter_gobj);
void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fp);
void Fighter_ResetInputData_80068854(HSD_GObj* fighter_gobj);
void Fighter_UnkInitLoad_80068914(HSD_GObj* fighter_gobj,
                                  struct S_TEMP1* argdata);
u32 Fighter_NewSpawn_80068E40();
void Fighter_80068E64(HSD_GObj* fighter_gobj);
HSD_GObj* Fighter_Create(struct S_TEMP1* input);
void Fighter_ActionStateChange_800693AC(HSD_GObj* fighter_gobj,
                                        s32 new_action_state_index, s32 flags,
                                        HSD_GObj* otherObj, f32 animStart,
                                        f32 animSpeed, f32 animBlend);
void Fighter_8006A1BC(HSD_GObj* fighter_gobj);
void Fighter_8006A360(HSD_GObj* fighter_gobj);
void Fighter_8006ABA0(HSD_GObj* fighter_gobj);
void Fighter_UnkIncrementCounters_8006ABEC(HSD_GObj* fighter_gobj);
void Fighter_Spaghetti_8006AD10(HSD_GObj* fighter_gobj);
void Fighter_procUpdate(HSD_GObj* fighter_gobj);
void Fighter_UnkApplyTransformation_8006C0F0(HSD_GObj* fighter_gobj);
void Fighter_8006C27C(HSD_GObj* fighter_gobj);
void Fighter_8006C5F4(HSD_GObj* fighter_gobj);
void Fighter_CallAcessoryCallbacks_8006C624(HSD_GObj* fighter_gobj);
void Fighter_8006C80C(HSD_GObj* fighter_gobj);
void Fighter_UnkProcessGrab_8006CA5C(HSD_GObj* fighter_gobj);
void Fighter_8006CB94(HSD_GObj* fighter_gobj);
void Fighter_UnkTakeDamage_8006CC30(Fighter* fp, f32 damage_amount);
void Fighter_TakeDamage_8006CC7C(Fighter*, f32);
void Fighter_8006CDA4(Fighter* fp, s32 arg1, s32 arg2, s32 arg3);
void Fighter_8006CF5C(Fighter* fp, s32 arg1);
void Fighter_UnkSetFlag_8006CFBC(HSD_GObj* fighter_gobj);
void Fighter_8006CFE0(HSD_GObj* fighter_gobj);
void Fighter_UnkRecursiveFunc_8006D044(HSD_GObj* fighter_gobj);
void Fighter_8006D10C(HSD_GObj* fighter_gobj);
void Fighter_UnkProcessShieldHit_8006D1EC(HSD_GObj* fighter_gobj);
void Fighter_8006D9AC(HSD_GObj* fighter_gobj);
void Fighter_UnkCallCameraCallback_8006D9EC(HSD_GObj* fighter_gobj);
void Fighter_8006DA4C(HSD_GObj* fighter_gobj);
void Fighter_Unload_8006DABC(void* user_data);

///// Shared Fighter Code

#define PUSH_ATTRS(fp, attributeName)                                          \
    do {                                                                       \
        void* backup = (fp)->x2D8_specialAttributes2;                          \
        attributeName* src = (attributeName*) (fp)->x10C_ftData->ext_attr;     \
        void** attr = &(fp)->x2D4_specialAttributes;                           \
        *(attributeName*) (fp)->x2D8_specialAttributes2 = *src;                \
        *attr = backup;                                                        \
    } while (0)

#define COPY_ATTRS(gobj, attributeName)                                        \
    Fighter* fp = gobj->user_data;                                             \
    attributeName* sA2 = (attributeName*) fp->x2D4_specialAttributes;          \
    attributeName* ext_attr = (attributeName*) fp->x10C_ftData->ext_attr;      \
    *sA2 = *ext_attr;

#define SCALE_HEIGHT_ATTRS(num_attrs)                                          \
    {                                                                          \
        int i;                                                                 \
        for (i = 0; i < num_attrs; i++) {                                      \
            sA2->height_attributes[i] *= fp->x34_scale.y;                      \
        }                                                                      \
    }

// Works but unused decided to go with inline instead
#define MACRO_ft_OnItemPickup(FTNAME, param1, param2)                          \
    void FTNAME##_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool)              \
    {                                                                          \
        Fighter* fp = getFighter(fighter_gobj);                                \
        if (!func_8026B2B4(fp->x1974_heldItem)) {                              \
            switch (func_8026B320(fp->x1974_heldItem)) {                       \
            case 1:                                                            \
                func_80070FB4(fighter_gobj, param1, 1);                        \
                break;                                                         \
            case 2:                                                            \
                func_80070FB4(fighter_gobj, param1, 0);                        \
                break;                                                         \
            case 3:                                                            \
                func_80070FB4(fighter_gobj, param1, 2);                        \
                break;                                                         \
            case 4:                                                            \
                func_80070FB4(fighter_gobj, param1, 3);                        \
                break;                                                         \
            }                                                                  \
            if (bool) {                                                        \
                func_80070C48(fighter_gobj, param2);                           \
            }                                                                  \
        }                                                                      \
    }

/// used for all fighters except Kirby and Purin
static inline void Fighter_OnItemPickup(HSD_GObj* fighter_gobj,
                                        BOOL catchItemFlag, BOOL bool2,
                                        BOOL bool3)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        switch (func_8026B320(fp->x1974_heldItem)) {
        case 1:
            func_80070FB4(fighter_gobj, bool2, 1);
            break;
        case 2:
            func_80070FB4(fighter_gobj, bool2, 0);
            break;
        case 3:
            func_80070FB4(fighter_gobj, bool2, 2);
            break;
        case 4:
            func_80070FB4(fighter_gobj, bool2, 3);
            break;
        }
        if (catchItemFlag) {
            func_80070C48(fighter_gobj, bool3);
        }
    }
}

static inline void Fighter_OnItemInvisible(HSD_GObj* gobj, BOOL bool)
{
    Fighter* fp = getFighter(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        func_80070CC4(gobj, bool);
    }
}

static inline void Fighter_OnItemVisible(HSD_GObj* gobj, BOOL bool)
{
    Fighter* fp = getFighter(gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        func_80070C48(gobj, bool);
    }
}

static inline void Fighter_OnItemDrop(HSD_GObj* gobj, BOOL dropItemFlag,
                                      BOOL bool2, BOOL bool3)
{
    func_80070FB4(gobj, bool2, -1);
    if (dropItemFlag) {
        func_80070CC4(gobj, bool3);
    }
}

static inline void Fighter_OnKnockbackEnter(HSD_GObj* gobj, s32 arg1)
{
    func_800704F0(gobj, arg1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

static inline void Fighter_OnKnockbackExit(HSD_GObj* gobj, s32 arg1)
{
    func_800704F0(gobj, arg1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

static inline void Fighter_UnsetCmdVar0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
}

extern unk_t lbl_804D6520;
extern ftCommonData* p_ftCommonData;
extern FighterPartsTable** ftPartsTable;
void Fighter_UnkProcessDeath_80068354(struct _HSD_GObj*);
u32 Fighter_NewSpawn_80068E40();

void Fighter_ActionStateChange_800693AC(struct _HSD_GObj* fighter_gobj,
                                        s32 newAction, s32 flags,
                                        struct _HSD_GObj* otherObj,
                                        f32 animStart, f32 animSpeed,
                                        f32 animBlend);

extern HSD_ObjAllocData fighter_alloc_data;
extern HSD_ObjAllocData lbl_80458FFC;
extern HSD_ObjAllocData fighter_bones_alloc_data;
extern HSD_ObjAllocData lbl_80459054;
extern HSD_ObjAllocData lbl_80459080;
extern HSD_ObjAllocData lbl_804590AC;

#endif

#ifndef MELEE_SC_TYPES_H
#define MELEE_SC_TYPES_H

#include <melee/sc/forward.h> // IWYU pragma: export
#include <sysdolphin/baselib/forward.h>

#include <dat_macros.h>

/// Model with a single animation or no animation
struct StaticModelDesc {
    HSD_Joint* joint;
    HSD_AnimJoint* animjoint;
    HSD_MatAnimJoint* matanim_joint;
    HSD_ShapeAnimJoint* shapeanim_joint;
};

/// Model with multiple animations
struct DynamicModelDesc {
    HSD_Joint* joint;
    HSD_AnimJoint** anims DAT_NULLTERM;
    HSD_MatAnimJoint** matanims DAT_NULLTERM;
    HSD_ShapeAnimJoint** shapeanims DAT_NULLTERM;
};

typedef struct SceneCameraDesc {
    HSD_CObjDesc* desc;
    HSD_CameraAnim** anims DAT_NULLTERM;
} SceneCameraDesc;
typedef struct LightList {
    HSD_LightDesc* desc;
    HSD_LightAnim** anims DAT_NULLTERM;
} LightList;
typedef struct SceneFogDesc {
    HSD_FogDesc* desc;
    HSD_CameraAnim** anims DAT_NULLTERM;
} SceneFogDesc;

/// The basis of a rendered scene, like a stage, menu, or HUD overlay
struct SceneDesc {
    DynamicModelDesc** models DAT_NULLTERM;
    SceneCameraDesc* cameras;
    LightList** lights DAT_NULLTERM;
    SceneFogDesc* fogs;
};

#endif

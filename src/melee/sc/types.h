#ifndef MELEE_SC_TYPES_H
#define MELEE_SC_TYPES_H

#include <melee/sc/forward.h> // IWYU pragma: export
#include <sysdolphin/baselib/forward.h>

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
    HSD_AnimJoint** anims;
    HSD_MatAnimJoint** matanims;
    HSD_ShapeAnimJoint** shapeanims;
};

typedef struct SceneCameraDesc {
    HSD_CObjDesc* desc;
    HSD_CameraAnim** anims;
} SceneCameraDesc;
typedef struct LightList {
    HSD_LightDesc* desc;
    HSD_LightAnim** anims;
} LightList;
typedef struct SceneFogDesc {
    HSD_FogDesc* desc;
    HSD_CameraAnim** anims;
} SceneFogDesc;

/// The basis of a rendered scene, like a stage, menu, or HUD overlay
struct SceneDesc {
    DynamicModelDesc** models;
    SceneCameraDesc* cameras;
    LightList** lights;
    SceneFogDesc* fogs;
};

#endif

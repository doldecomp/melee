#ifndef MELEE_SC_TYPES_H
#define MELEE_SC_TYPES_H

#include <melee/sc/forward.h> // IWYU pragma: export
#include <sysdolphin/baselib/forward.h>

#include <dat_macros.h>
#include <placeholder.h>

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
    HSD_AnimJoint** anims DAT_TERMINATED(0);
    HSD_MatAnimJoint** matanims DAT_TERMINATED(0);
    HSD_ShapeAnimJoint** shapeanims DAT_TERMINATED(0);
};

typedef struct SceneCameraDesc {
    HSD_CObjDesc* desc;
    HSD_CameraAnim** anims DAT_TERMINATED(0);
} SceneCameraDesc;
typedef struct LightList {
    HSD_LightDesc* desc;
    HSD_LightAnim** anims DAT_TERMINATED(0);
} LightList;
/// Two words, unlike #HSD_CameraAnim: the archives' lists of these start
/// right after them.
typedef struct SceneFogAnim {
    HSD_AObjDesc* aobjdesc;
    UNK_T x4;
} SceneFogAnim;
typedef struct SceneFogDesc {
    HSD_FogDesc* desc;
    SceneFogAnim** anims DAT_TERMINATED(0);
} SceneFogDesc;

/// The basis of a rendered scene, like a stage, menu, or HUD overlay
struct SceneDesc {
    DynamicModelDesc** models DAT_TERMINATED(0);
    SceneCameraDesc* cameras;
    LightList** lights DAT_TERMINATED(0);
    SceneFogDesc* fogs;
};

#endif

#ifndef MELEE_SC_TYPES_H
#define MELEE_SC_TYPES_H

#include <placeholder.h>

#include "sc/forward.h" // IWYU pragma: export
#include <baselib/forward.h>

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

// The basis of a rendered scene, like a stage, menu, or HUD overlay
struct SceneDesc {
    DynamicModelDesc** models;
    struct {
        HSD_CObjDesc* desc;
        HSD_CameraAnim** anims;
    }* cameras;
    struct {
        HSD_LightDesc* desc;
        UNK_T anims;
    }** lights;
    struct {
        HSD_FogDesc* desc;
        HSD_CameraAnim** anims;
    }* fogs;
};

#endif

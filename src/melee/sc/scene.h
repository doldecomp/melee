#ifndef MELEE_SC_SCENE_H
#define MELEE_SC_SCENE_H

// Model with a single animation or no animation
typedef struct _StaticModelDesc {
    struct _HSD_Joint* joint;
    struct _HSD_AnimJoint* animjoint;
    struct _HSD_MatAnimJoint* matanim_joint;
    struct _HSD_ShapeAnimJoint* shapeanim_joint;
} StaticModelDesc;

// Model with multiple animations
typedef struct _DynamicModelDesc {
    struct _HSD_Joint* joint;
    struct _HSD_AnimJoint** anims;
    struct _HSD_MatAnimJoint** matanims;
    struct _HSD_ShapeAnimJoint** shapeanims;
} DynamicModelDesc;

// The basis of a rendered scene, like a stage, menu, or HUD overlay
typedef struct _SceneDesc {
    DynamicModelDesc** models;
    struct _HSD_CObjDesc** cameras;
    struct _HSD_LObjDesc** lights;
    struct _HSD_FogDesc** fogs;
} SceneDesc;

#endif

#ifndef MELEE_LB_FORWARD_H
#define MELEE_LB_FORWARD_H

#include <platform.h>

typedef struct AbsorbDesc AbsorbDesc;
typedef struct CollData CollData;
typedef struct DynamicsDesc DynamicsDesc;
typedef struct FigaTrack FigaTrack;
typedef struct FigaTree FigaTree;
typedef struct HSD_AllocEntry HSD_AllocEntry;
typedef struct HitCapsule HitCapsule;
typedef struct HitResult HitResult;
typedef struct HitVictim HitVictim;
typedef struct HurtCapsule HurtCapsule;
typedef struct FighterHurtCapsule FighterHurtCapsule;
typedef struct PreloadCache PreloadCache;
typedef struct PreloadCacheScene PreloadCacheScene;
typedef struct PreloadCacheSceneEntry PreloadCacheSceneEntry;
typedef struct PreloadEntry PreloadEntry;
typedef struct ReflectDesc ReflectDesc;
typedef struct ShieldDesc ShieldDesc;
typedef struct Unk80433380_48 Unk80433380_48;
typedef struct lbRefract_CallbackData lbRefract_CallbackData;

typedef enum HurtCapsuleState {
    HurtCapsule_Enabled,
    HurtCapsule_Disabled,
    Intangible
} HurtCapsuleState;

typedef enum HitElement {
    HitElement_Normal,
    HitElement_Fire,
    HitElement_Electric,
    HitElement_Slash,
    HitElement_Coin,
    HitElement_Ice,

    /// Sleep for 103 frames
    HitElement_Nap,

    /// Sleep for 412 frames
    HitElement_Sleep,

    HitElement_Catch,
    HitElement_Ground,
    HitElement_Cape,
    HitElement_Inert,
    HitElement_Disable,
    HitElement_Dark,

    /// Screw Attack
    HitElement_Scball,

    HitElement_Lipstick,

    /// Formerly presumed empty, this hitbox element is used by
    ///  ReDead grab attacks
    HitElement_Leadead,
} HitElement;

typedef enum HitCapsuleState {
    HitCapsule_Disabled,
    HitCapsule_Enabled,
    HitCapsule_Unk2,
    HitCapsule_Unk3,
    HitCapsule_Max = HitCapsule_Unk3,
} HitCapsuleState;

STATIC_ASSERT(HitCapsule_Max == 3);

typedef enum HurtHeight {
    HurtHeight_Low,
    HurtHeight_Mid,
    HurtHeight_High,
} HurtHeight;

typedef void (*RefractCallbackTypeA)(struct lbRefract_CallbackData*, s32, u32,
                                     s8, s8);
typedef void (*RefractCallbackTypeB)(struct lbRefract_CallbackData*, s32, u32,
                                     s8, s8, s8, s8);
typedef void (*RefractCallbackTypeC)(struct lbRefract_CallbackData*, s32, u32,
                                     s32*, s32*, s32*, s32*);

#endif

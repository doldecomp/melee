#ifndef MELEE_LB_FORWARD_H
#define MELEE_LB_FORWARD_H

typedef struct HurtCapsule HurtCapsule;
typedef struct HitCapsule HitCapsule;
typedef struct HitVictim HitVictim;
typedef struct HitResult HitResult;

typedef enum Tangibility {
    Vulnerable,
    Invincible,
    Intangible
} Tangibility;

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

#endif

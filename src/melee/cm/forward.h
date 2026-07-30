#ifndef MELEE_CM_FORWARD_H
#define MELEE_CM_FORWARD_H

#include <placeholder.h>

typedef enum CameraType {
    CAMERA_STANDARD = 0,      ///< mode used during normal gameplay
    CAMERA_PAUSE = 1,         ///< mode used during pause menu
    CAMERA_TRAINING_MENU = 2, ///< mode used when the training menu is open
    CAMERA_CLEAR = 3,         ///< camera zooms in on the target. gets set when
                              // clearing a stage 1p modes
    CAMERA_FIXED = 4,
    CAMERA_FREE =
        5, ///< used in training mode, and special melee "Camera Mode"
    CAMERA_BOSS_INTRO =
        6, ///< used during master/crazy hand match spawn. rotates
           // around the player then the boss
    CAMERA_DEBUG_FOLLOW =
        7, ///< follows the player, but can change pos/rotation offset
    CAMERA_DEBUG_FREE = 8,
} CameraType;

#define CAM_BOUNDS_INSIDE 0
#define CAM_BOUNDS_OUTSIDE_TOP (1 << 0)    ///< 0x1
#define CAM_BOUNDS_OUTSIDE_BOTTOM (1 << 1) ///< 0x2
#define CAM_BOUNDS_OUTSIDE_LEFT (1 << 2)   ///< 0x4
#define CAM_BOUNDS_OUTSIDE_RIGHT (1 << 3)  ///< 0x8

typedef struct Camera Camera;
typedef struct CameraBounds CameraBounds;
typedef struct Camera_x2D0 Camera_x2D0;
typedef struct CameraQuake CameraQuake;
typedef struct CmSubject CmSubject;
typedef struct CameraTransformState CameraTransformState;
typedef struct CameraUnkGlobals CameraUnkGlobals;
typedef struct CameraDebugMode CameraDebugMode;
typedef struct CameraModeCallbacks CameraModeCallbacks;
typedef struct CameraInputs CameraInputs;

/// @remarks @c CmSnapStatus_Sleep is named by an assert in
/// #cmSnap_800315C8.
typedef enum CmSnapStatus {
    /* 0x0 */ CmSnapStatus_Sleep,
    /* 0x1 */ CmSnapStatus_Unk1,
    /* 0x2 */ CmSnapStatus_Unk2,
    /* 0x3 */ CmSnapStatus_Unk3,
    /* 0x4 */ CmSnapStatus_Unk4,
    /* 0x5 */ CmSnapStatus_Unk5,
} CmSnapStatus;

#endif

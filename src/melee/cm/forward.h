#ifndef MELEE_CM_FORWARD_H
#define MELEE_CM_FORWARD_H

#include <placeholder.h>

#define TOP_BOUND (1 << 0)    ///< 0x1
#define BOTTOM_BOUND (1 << 1) ///< 0x2
#define LEFT_BOUND (1 << 2)   ///< 0x4
#define RIGHT_BOUND (1 << 3)  ///< 0x8

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

typedef struct Camera Camera;
typedef struct CameraBounds CameraBounds;
typedef struct CameraQuake CameraQuake;
typedef struct CmSubject CmSubject;
typedef struct CameraTransformState CameraTransformState;
typedef struct CameraUnkGlobals CameraUnkGlobals;
typedef struct CameraDebugMode CameraDebugMode;
typedef struct CameraModeCallbacks CameraModeCallbacks;
typedef struct CameraInputs CameraInputs;

#endif

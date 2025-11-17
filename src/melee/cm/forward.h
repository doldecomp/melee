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
    CAMERA_FREE = 5,        ///< used in training mode, and special melee "Camera Mode"
    CAMERA_BOSS_INTRO = 6,  ///< used during master/crazy hand match spawn. rotates
                            // around the player then the boss
    CAMERA_DEBUG_FOLLOW = 7, ///< follows the player, but can change pos/rotation offset
    CAMERA_DEBUG_FREE = 8,
} CameraType;

typedef struct Camera Camera;
typedef struct CameraBounds CameraBounds;
typedef struct CameraQuake CameraQuake;
typedef struct CameraBox CameraBox;
typedef struct CameraTransformState CameraTransformState;
typedef struct CameraUnkGlobals CameraUnkGlobals;
typedef struct CameraDebugMode CameraDebugMode;
typedef struct CameraModeCallbacks CameraModeCallbacks;
typedef struct CameraInputs CameraInputs;

#endif

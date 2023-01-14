#ifndef DOLPHIN_MTX_TYPES_H
#define DOLPHIN_MTX_TYPES_H

#include <Runtime/platform.h>

/// @sz{C}
typedef struct Vec3 {
    /// @at{0} @sz{4}
    /// @brief The @e x component.
    f32 x;

    /// @at{4} @sz{4}
    /// @brief The @e y component.
    f32 y;

    /// @at{8} @sz{4}
    /// @brief The @e z component.
    f32 z;
} Vec3;

/// @sz{10}
typedef struct Vec4 {
    /// @at{0} @sz{4}
    /// @brief The @e x component.
    f32 x;

    /// @at{4} @sz{4}
    /// @brief The @e y component.
    f32 y;

    /// @at{8} @sz{4}
    /// @brief The @e z component.
    f32 z;

    /// @at{C} @sz{4}
    /// @brief The @e w component.
    f32 w;

} Quaternion, Vec4;
// Don't change the order of the typedefs; it affects Doxygen.

/// @sz{3}
typedef struct S8Vec3 {
    /// @at{0} @sz1
    /// @brief The @e x component.
    s8 x;

    /// @at{1} @sz1
    /// @brief The @e y component.
    s8 y;

    /// @at{2} @sz1
    /// @brief The @e z component.
    s8 z;
} S8Vec3;

typedef struct S16Vec3 {
    /// @at{0} @sz{2}
    /// @brief The @e x component.
    s16 x;

    /// @at{2} @sz{2}
    /// @brief The @e y component.
    s16 y;

    /// @at{4} @sz{2}
    /// @brief The @e z component.
    s16 z;
} S16Vec3;

/// @sz{8}
typedef struct S32Vec2 {
    /// @at{0} @sz{4}
    /// @brief The @e x component.
    s32 x;

    /// @at{1} @sz{4}
    /// @brief The @e y component.
    s32 y;
} S32Vec2;

/// @sz{C}
typedef struct S32Vec3 {
    /// @at{0} @sz{4}
    /// @brief The @e x component.
    s32 x;

    /// @at{1} @sz{4}
    /// @brief The @e y component.
    s32 y;

    /// @at{2} @sz{4}
    /// @brief The @e z component.
    s32 z;
} S32Vec3;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

typedef f32 Mtx44[4][4];
typedef f32 (*Mtx44Ptr)[4];

#endif

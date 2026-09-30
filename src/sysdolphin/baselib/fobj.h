/**
 * @file fobj.h
 * @brief Frame Object (FObj) keyframe animation track declarations.
 * @details Implements individual property animation tracks within AObj (Animation Object).
 * Each FObj stores a compressed variable-length byte stream of keyframes for a single
 * animated property (e.g. bone translations, rotations, scale, material color, texture scroll)
 * and supports step/constant, linear, and cubic Hermite spline interpolation.
 * Module prefix: HSD (Sysdolphin)
 */

#ifndef _fobj_h_
#define _fobj_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/objalloc.h>

/// No interpolation operation
#define HSD_A_OP_NONE 0

/// Constant / Step interpolation: holds previous keyframe value until duration expires
#define HSD_A_OP_CON 1

/// Linear interpolation: linearly interpolates between start and target values over duration
#define HSD_A_OP_LIN 2

/// Hermite cubic spline interpolation with zero end tangent (d1 = 0)
#define HSD_A_OP_SPL0 3

/// Hermite cubic spline interpolation with explicit end tangent/slope decoded from stream
#define HSD_A_OP_SPL 4

/// Slope update: updates tangent derivative without emitting a new position value
#define HSD_A_OP_SLP 5

/// Keyframe trigger / event: emits instantaneous event value
#define HSD_A_OP_KEY 6

/// Uncompressed 32-bit IEEE-754 floating point format
#define HSD_A_FRAC_FLOAT (0 << 5)

/// Signed 16-bit fixed-point format with variable fractional shift
#define HSD_A_FRAC_S16 (1 << 5)

/// Unsigned 16-bit fixed-point format with variable fractional shift
#define HSD_A_FRAC_U16 (2 << 5)

/// Signed 8-bit fixed-point format with variable fractional shift
#define HSD_A_FRAC_S8 (3 << 5)

/// Unsigned 8-bit fixed-point format with variable fractional shift
#define HSD_A_FRAC_U8 (4 << 5)

/// Initial state: loading initial keyframe data packet
#define FOBJ_LOAD_DATA0 1

/// State: loading subsequent keyframe data packet
#define FOBJ_LOAD_DATA 2

/// State: parsing wait duration until next keyframe
#define FOBJ_LOAD_WAIT 3

#define TYPE_ROBJ 1
#define TYPE_JOBJ 12

/**
 * @brief Frame Object (FObj) animation track runtime instance.
 * @details Represents a single animated property track inside an AObj. Contains
 * state variables for reading a compressed byte stream, interpolating keyframe data
 * (step, linear, cubic Hermite spline), and emitting property updates to target objects.
 */
struct HSD_FObj {
    struct HSD_FObj* next; ///< Next sibling animation track in AObj chain (offset 0x00)
    u8* ad;                ///< Current reading pointer in animation byte stream (offset 0x04)
    u8* ad_head;           ///< Base pointer to start of animation byte stream (offset 0x08)
    u32 length;            ///< Total length of animation stream in bytes (offset 0x0C)
    u8 flags;              ///< State and control flags (lower 4 bits: state; bit 5: lin recalc; bit 6: key loaded; bit 7: key pending) (offset 0x10)
    u8 op;                 ///< Current animation opcode (HSD_A_OP_*) (offset 0x11)
    u8 op_intrp;           ///< Active interpolation mode for current segment (offset 0x12)
    u8 obj_type;           ///< Target property/attribute ID being animated (e.g. JOBJ_TRAX, MOBJ_ALPHA) (offset 0x13)
    u8 frac_value;         ///< Fixed-point quantization format for keyframe values (offset 0x14)
    u8 frac_slope;         ///< Fixed-point quantization format for tangents/slopes (offset 0x15)
    u16 nb_pack;           ///< Remaining keyframe packets under current opcode (offset 0x16)
    s16 startframe;        ///< Starting frame offset for this animation track (offset 0x18)
    u16 fterm;             ///< Duration in frames of current keyframe interval (offset 0x1A)
    f32 time;              ///< Elapsed time in frames within current interval (offset 0x1C)
    f32 p0;                ///< Initial value at start of interval (offset 0x20)
    f32 p1;                ///< Target value at end of interval (offset 0x24)
    f32 d0;                ///< Starting slope/tangent derivative of interval (offset 0x28)
    f32 d1;                ///< Ending slope/tangent derivative of interval (offset 0x2C)
};

/**
 * @brief Static descriptor for loading an FObj animation track from archive data (DAT files).
 */
typedef struct _HSD_FObjDesc {
    struct _HSD_FObjDesc* next; ///< Pointer to next FObj descriptor in archive (offset 0x00)
    u32 length;                 ///< Byte length of raw animation data stream (offset 0x04)
    f32 startframe;             ///< Initial start frame offset (offset 0x08)
    u8 type;                    ///< Target property/attribute type ID (offset 0x0C)
    u8 frac_value;              ///< Fixed-point quantization format for values (offset 0x0D)
    u8 frac_slope;              ///< Fixed-point quantization format for slopes (offset 0x0E)
    u8 dummy0;                  ///< Unused alignment padding (offset 0x0F)
    u8* ad;                     ///< Pointer to raw compressed animation byte stream (offset 0x10)
} HSD_FObjDesc;

/**
 * @brief Polymorphic container for passing interpolated animation values to target objects.
 */
union HSD_ObjData {
    f32 fv;  ///< Scalar floating-point property value (e.g. translation, rotation, scale, alpha)
    s32 iv;  ///< Integer property value
    Vec3 p;  ///< 3D vector property value
};

/**
 * @brief Returns the allocator data structure for HSD_FObj instances.
 * @return Pointer to global HSD_ObjAllocData for FObj
 */
HSD_ObjAllocData* HSD_FObjGetAllocData(void);

/**
 * @brief Initializes the memory pool allocator for HSD_FObj structures.
 */
void HSD_FObjInitAllocData(void);

/**
 * @brief Frees a single HSD_FObj back to the memory pool.
 * @param fobj Pointer to HSD_FObj to remove
 */
void HSD_FObjRemove(HSD_FObj* fobj);

/**
 * @brief Recursively frees an entire linked list of HSD_FObj tracks.
 * @param fobj Head of HSD_FObj linked list to remove
 */
void HSD_FObjRemoveAll(HSD_FObj* fobj);

/**
 * @brief Sets the state machine state on an FObj.
 * @param fobj Pointer to HSD_FObj
 * @param state State ID to set in lower 4 bits of flags
 * @return The state ID passed in
 */
u32 HSD_FObjSetState(HSD_FObj* fobj, u32 state);

/**
 * @brief Retrieves the current state machine state of an FObj.
 * @param fobj Pointer to HSD_FObj
 * @return Current state ID from lower 4 bits of flags, or 0 if fobj is NULL
 */
u32 HSD_FObjGetState(HSD_FObj* fobj);

/**
 * @brief Resets playback to a start frame across an entire linked list of FObj tracks.
 * @param fobj Head of HSD_FObj linked list
 * @param startframe Starting frame offset to apply
 */
void HSD_FObjReqAnimAll(HSD_FObj* fobj, f32 startframe);

/**
 * @brief Stops animation on a single FObj track, flushing any pending keyframe event.
 * @param fobj Pointer to HSD_FObj
 * @param obj Target object to receive property update
 * @param obj_update Callback to apply property updates to target object
 * @param rate Animation playback rate
 */
void HSD_FObjStopAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update,
                      f32 rate);

/**
 * @brief Stops animation across an entire linked list of FObj tracks.
 * @param fobj Head of HSD_FObj linked list
 * @param obj Target object to receive property updates
 * @param obj_update Callback to apply property updates
 * @param rate Animation playback rate
 */
void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj,
                         HSD_ObjUpdateFunc obj_update, f32 rate);

/**
 * @brief Evaluates interpolation and applies the current value to the target object.
 * @details Evaluates constant, linear, or cubic Hermite spline interpolation for the
 * current track frame and invokes obj_update with the result.
 * @param fobj Pointer to HSD_FObj track
 * @param obj Target object (JObj, MObj, Camera, etc.)
 * @param update_func Callback that writes the animated property to the object
 */
void FObjUpdateAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc update_func);

/**
 * @brief Advances and interprets animation playback on a single FObj track by rate frames.
 * @details Advances track time by rate, decodes new keyframes from the compressed byte stream
 * as intervals expire, evaluates interpolation, and pushes updates to the target object.
 * @param fobj Pointer to HSD_FObj track
 * @param obj Target object
 * @param obj_update Callback to apply updates
 * @param rate Playback rate (typically 1.0 for normal speed)
 */
void HSD_FObjInterpretAnim(HSD_FObj* fobj, void* obj,
                           HSD_ObjUpdateFunc obj_update, f32 rate);

/**
 * @brief Advances and interprets animation across an entire linked list of FObj tracks.
 * @param fobj Head of HSD_FObj linked list (passed as void*)
 * @param obj Target object
 * @param obj_update Callback to apply updates
 * @param rate Playback rate
 */
void HSD_FObjInterpretAnimAll(void* fobj, void* obj,
                              HSD_ObjUpdateFunc obj_update, f32 rate);

/**
 * @brief Instantiates and initializes an FObj track chain from archive descriptors.
 * @param desc Pointer to HSD_FObjDesc descriptor
 * @return Head of newly allocated HSD_FObj chain, or NULL if desc is NULL
 */
HSD_FObj* HSD_FObjLoadDesc(HSD_FObjDesc* desc);

/**
 * @brief Allocates and zero-initializes a new HSD_FObj from the memory pool.
 * @return Pointer to newly allocated HSD_FObj
 */
HSD_FObj* HSD_FObjAlloc(void);

/**
 * @brief Frees an HSD_FObj back to the memory pool.
 * @param fobj Pointer to HSD_FObj to free
 */
void HSD_FObjFree(HSD_FObj* fobj);

#endif

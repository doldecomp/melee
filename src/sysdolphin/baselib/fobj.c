/**
 * @file fobj.c
 * @brief Frame Object (FObj) keyframe animation track implementation.
 * @details Implements decoding, decompression, variable-length integer parsing,
 * and keyframe interpolation (step, linear, and cubic Hermite spline) for individual
 * animation tracks in the Sysdolphin animation engine.
 * Module prefix: HSD (Sysdolphin)
 */

#include "fobj.h"

#include <string.h>

#include "debug.h"
#include "spline.h"

/// Global memory pool allocator data for HSD_FObj instances
HSD_ObjAllocData fobj_alloc_data;

/**
 * @brief Returns the allocator data structure for HSD_FObj instances.
 * @return Pointer to global HSD_ObjAllocData for FObj
 */
HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &fobj_alloc_data;
}

/**
 * @brief Initializes the memory pool allocator for HSD_FObj structures.
 */
void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_FObjGetAllocData(), sizeof(HSD_FObj), 4);
}

/**
 * @brief Frees a single HSD_FObj back to the memory pool.
 * @param fobj Pointer to HSD_FObj to remove
 */
void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (!fobj) {
        return;
    }

    HSD_FObjFree(fobj);
}

/**
 * @brief Recursively frees an entire linked list of HSD_FObj tracks.
 * @param fobj Head of HSD_FObj linked list to remove
 */
void HSD_FObjRemoveAll(HSD_FObj* fobj)
{
    if (fobj == NULL) {
        return;
    }
    HSD_FObjRemoveAll(fobj->next);
    HSD_FObjRemove(fobj);
}

/**
 * @brief Sets the state machine state on an FObj.
 * @param fobj Pointer to HSD_FObj
 * @param state State ID to set in lower 4 bits of flags
 * @return The state ID passed in
 */
u32 HSD_FObjSetState(HSD_FObj* fobj, u32 state)
{
    if (fobj) {
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    }
    return state;
}

/**
 * @brief Retrieves the current state machine state of an FObj.
 * @param fobj Pointer to HSD_FObj
 * @return Current state ID from lower 4 bits of flags, or 0 if fobj is NULL
 */
u32 HSD_FObjGetState(HSD_FObj* fobj)
{
    if (!fobj) {
        return 0;
    }
    return fobj->flags & 0xF;
}

/**
 * @brief Inlined helper to reset playback state on a single FObj track.
 * @param fobj Pointer to HSD_FObj
 * @param startframe Starting frame offset to apply
 */
static inline void HSD_FObjReqAnim(HSD_FObj* fobj, f32 startframe)
{
    if (fobj == NULL) {
        return;
    }

    fobj->ad = fobj->ad_head;
    fobj->time = (f32) fobj->startframe + startframe;
    fobj->op = 0;
    fobj->op_intrp = 0;
    fobj->flags &= ~0x40;
    fobj->nb_pack = 0;
    fobj->fterm = 0;
    fobj->p0 = 0.f;
    fobj->p1 = 0.f;
    fobj->d0 = 0.f;
    fobj->d1 = 0.f;
    HSD_FObjSetState(fobj, 1);
}

/**
 * @brief Resets playback to a start frame across an entire linked list of FObj tracks.
 * @param fobj Head of HSD_FObj linked list
 * @param startframe Starting frame offset to apply
 */
void HSD_FObjReqAnimAll(HSD_FObj* fobj, f32 startframe)
{
    HSD_FObj* cur;

    if (fobj == NULL) {
        return;
    }

    for (cur = fobj; cur != NULL; cur = cur->next) {
        HSD_FObjReqAnim(cur, startframe);
    }
}

/**
 * @brief Inlined helper to flush pending keyframe trigger event when stopping animation.
 * @param fobj Pointer to HSD_FObj
 * @param obj Target object
 * @param obj_update Callback to apply property updates
 * @param rate Playback rate
 */
static inline void FObj_FlushKeyData(HSD_FObj* fobj, void* obj,
                                     HSD_ObjUpdateFunc obj_update, f32 rate)
{
    if (fobj->op_intrp == HSD_A_OP_KEY) {
        HSD_FObjInterpretAnim(fobj, obj, obj_update, rate);
    }
}

/**
 * @brief Stops animation on a single FObj track, flushing any pending keyframe event.
 * @param fobj Pointer to HSD_FObj
 * @param obj Target object to receive property update
 * @param obj_update Callback to apply property updates to target object
 * @param rate Animation playback rate
 */
void HSD_FObjStopAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update,
                      f32 rate)
{
    if (fobj == NULL) {
        return;
    }

    FObj_FlushKeyData(fobj, obj, obj_update, rate);
    HSD_FObjSetState(fobj, 0);
}

/**
 * @brief Stops animation across an entire linked list of FObj tracks.
 * @param fobj Head of HSD_FObj linked list
 * @param obj Target object to receive property updates
 * @param obj_update Callback to apply property updates
 * @param rate Animation playback rate
 */
void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj,
                         HSD_ObjUpdateFunc obj_update, f32 rate)
{
    for (; fobj != NULL; fobj = fobj->next) {
        HSD_FObjStopAnim(fobj, obj, obj_update, rate);
    }
}

/// Union for type-punning 32-bit float values from raw byte streams
union parseFloat_u {
    f32 f;
    u32 d;
};

/**
 * @brief Decodes a compressed fixed-point or IEEE-754 float from the animation stream.
 * @details Reads fixed-point quantized values (8-bit or 16-bit, signed or unsigned)
 * and divides by 2^(frac & 0x1F), or reads 4 raw bytes as a standard IEEE float.
 * @param[in,out] pos Pointer to current byte stream position (advanced past decoded bytes)
 * @param frac Format specification byte (HSD_A_FRAC_*)
 * @return Decoded floating point value
 */
static f32 parseFloat(u8** pos, u8 frac)
{
    union parseFloat_u val_union;
    f32 numer;
    s32 denom;

    if (frac == HSD_A_FRAC_FLOAT) {
        val_union.d = (s32) ((*pos)++)[0];
        val_union.d |= ((*pos)++)[0] << 8;
        val_union.d |= ((*pos)++)[0] << 16;
        val_union.d |= ((*pos)++)[0] << 24;
        return val_union.f;
    }

    denom = (1 << (frac & 0x1F));
    switch (frac & 0xE0) {
    case HSD_A_FRAC_S8:
        numer = (s8) (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_U8:
        numer = (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_S16:
        numer = ((s8) (*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    case HSD_A_FRAC_U16:
        numer = ((*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    default:
        return 0.0f;
    }
    return numer / denom;
}

/**
 * @brief Reads the lower 4-bit opcode from the current stream position without advancing.
 * @param pos Pointer to current stream pointer
 * @return Opcode identifier (HSD_A_OP_*)
 */
static u8 parseOpCode(u8** pos)
{
    return (**pos) & 0xF;
}

/**
 * @brief Decodes a variable-length packet count from the animation stream.
 * @details Extracts initial 3-bit count from bits 4-6 (+ 1). If MSB (bit 7) is set,
 * decodes 7-bit continuation chunks until a byte with MSB 0 is encountered.
 * @param[in,out] adp Pointer to stream position (advanced past packet info)
 * @return Total number of keyframe packets in this opcode run
 */
static u32 parsePackInfo(u8** adp)
{
    u8 byte_val;
    u32 packet_count;
    s32 shift;

    byte_val = *(*adp)++;
    packet_count = ((byte_val >> 4) & 7) + 1;
    shift = 3;
    if (!(byte_val & 0x80)) {
        return packet_count;
    }
    do {
        byte_val = *(*adp)++;
        packet_count += (byte_val & 0x7F) << shift;
        shift += 7;
    } while (byte_val & 0x80);
    return packet_count;
}

/**
 * @brief Transitions a keyframe trigger event from loaded (bit 0x40) to pending (bit 0x80).
 * @param fobj Pointer to HSD_FObj
 */
static void FObjLaunchKeyData(HSD_FObj* fobj)
{
    if ((fobj->flags & 0x40) != 0) {
        fobj->op_intrp = fobj->op;
        fobj->flags &= ~0x40;
        fobj->flags |= 0x80;
        fobj->p0 = fobj->p1;
    }
}

/**
 * @brief Decodes a variable-length integer representing wait duration / frame interval.
 * @details Encoded in 7-bit chunks with bit 7 serving as a continuation flag.
 * @param[in,out] adp Pointer to stream position
 * @return Number of frames to wait until next keyframe
 */
static s32 parseWait(u8** adp)
{
    u8 byte_val;
    s32 wait = 0;
    s32 shift = 0;

    do {
        byte_val = *(*adp)++;
        wait |= (byte_val & 0x7f) << shift;
        shift += 7;
    } while (byte_val & 0x80);

    return wait;
}

/**
 * @brief Parses wait duration until next keyframe from stream and transitions state.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (6 if end of stream reached, 2 otherwise)
 */
static u32 FObjLoadWait(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x16C, st == FOBJ_LOAD_WAIT);

    if ((unsigned) (fobj->ad - fobj->ad_head) >= fobj->length) {
        return 6;
    } else {
        fobj->fterm = parseWait(&fobj->ad);
        fobj->flags |= 0x20;
        return HSD_FObjSetState(fobj, 2);
    }
}

/**
 * @brief Decodes keyframe packet for constant / step interpolation.
 * @details Moves p1 to p0, reads new p1 value from stream, and resets slope d1.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (3 if first keyframe, 4 for subsequent)
 */
static u32 FObjAnimCON(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x17F, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    if (fobj->op_intrp != 5) {
        fobj->d0 = fobj->d1;
        fobj->d1 = 0.0F;
    }

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

/**
 * @brief Decodes keyframe packet for linear interpolation.
 * @details Moves p1 to p0, reads new target value p1, and prepares for slope calculation.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (3 if first keyframe, 4 for subsequent)
 */
static u32 FObjAnimLinear(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x193, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    if (fobj->op_intrp != 5) {
        fobj->d0 = fobj->d1;
        fobj->d1 = 0.0F;
    }

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

/**
 * @brief Decodes keyframe packet for cubic Hermite spline with zero destination tangent.
 * @details Moves p1 to p0, advances tangent d1 to d0, reads new p1 value, and sets d1 = 0.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (3 if first keyframe, 4 for subsequent)
 */
static u32 FObjAnimSPL0(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1A7, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->d0 = fobj->d1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    fobj->d1 = 0.0F;

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

/**
 * @brief Decodes keyframe packet for cubic Hermite spline with explicit tangent.
 * @details Reads target value p1 and destination slope/tangent d1 from stream.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (3 if first keyframe, 4 for subsequent)
 */
static u32 FObjAnimSPL(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1B9, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    fobj->d0 = fobj->d1;
    fobj->d1 = parseFloat(&fobj->ad, fobj->frac_slope);

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

/**
 * @brief Decodes standalone tangent/slope update packet without generating a new position.
 * @param fobj Pointer to HSD_FObj
 * @return Current state ID
 */
static u32 FObjAnimSLP(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1CC, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->d0 = fobj->d1;
    fobj->d1 = parseFloat(&fobj->ad, fobj->frac_slope);

    return HSD_FObjGetState(fobj);
}

/**
 * @brief Decodes keyframe trigger event packet.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (3 if first keyframe, 4 for subsequent)
 */
static u32 FObjAnimKey(HSD_FObj* fobj)
{
    u32 st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1E9, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    FObjLaunchKeyData(fobj);
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    fobj->flags |= 0x40;

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

/**
 * @brief Inlined helper to parse next opcode/packet header and dispatch keyframe decoding.
 * @param fobj Pointer to HSD_FObj
 * @return Next state ID (6 if end of stream reached, otherwise dispatched decoder state)
 */
static inline u32 FObjLoadData(HSD_FObj* fobj)
{
    if ((unsigned) (fobj->ad - fobj->ad_head) >= fobj->length) {
        return 6;
    } else {
        fobj->op_intrp = fobj->op;
        if (fobj->nb_pack == 0) {
            fobj->op = parseOpCode(&fobj->ad);
            fobj->nb_pack = parsePackInfo(&fobj->ad);
        }

        fobj->nb_pack -= 1;

        switch (fobj->op) {
        case HSD_A_OP_CON:
            return FObjAnimCON(fobj);

        case HSD_A_OP_LIN:
            return FObjAnimLinear(fobj);

        case HSD_A_OP_SPL0:
            return FObjAnimSPL0(fobj);

        case HSD_A_OP_SPL:
            return FObjAnimSPL(fobj);

        case HSD_A_OP_SLP:
            return FObjAnimSLP(fobj);

        case HSD_A_OP_KEY:
            return FObjAnimKey(fobj);

        default:
            return 0;
        }
    }
}

/**
 * @brief Evaluates interpolation and applies the current value to the target object.
 * @details Evaluates constant, linear, or cubic Hermite spline interpolation for the
 * current track frame and invokes obj_update with the result.
 * @param fobj Pointer to HSD_FObj track
 * @param obj Target object (JObj, MObj, Camera, etc.)
 * @param obj_update Callback that writes the animated property to the object
 */
void FObjUpdateAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update)
{
    f32 interp_val;
    HSD_ObjData obj_data;

    if (obj_update == NULL) {
        return;
    }
    switch (fobj->op_intrp) {
    case HSD_A_OP_KEY:
        if (fobj->flags & 0x80) {
            obj_data.fv = fobj->p0;
            fobj->flags &= 0xFFFFFF7F;
        } else {
            return;
        }
        break;
    case HSD_A_OP_CON:
        if (fobj->time >= fobj->fterm) {
            interp_val = fobj->p1;
        } else {
            interp_val = fobj->p0;
        }
        obj_data.fv = interp_val;
        break;
    case HSD_A_OP_LIN:
        if (fobj->flags & 0x20) {
            fobj->flags = fobj->flags & 0xFFFFFFDF;
            if (fobj->fterm != 0) {
                fobj->d0 = (fobj->p1 - fobj->p0) / fobj->fterm;
            } else {
                fobj->d0 = 0;
                fobj->p0 = fobj->p1;
            }
        }
        obj_data.fv = fobj->d0 * fobj->time + fobj->p0;
        break;
    case HSD_A_OP_SPL0:
    case HSD_A_OP_SPL:
    case HSD_A_OP_SLP:
        if (fobj->fterm != 0) {
            obj_data.fv =
                splGetHelmite(1.0 / fobj->fterm, fobj->time, fobj->p0,
                              fobj->p1, fobj->d0, fobj->d1);
        } else {
            obj_data.fv = fobj->p1;
        }
        break;
    default:
        break;
    }
    obj_update(obj, fobj->obj_type, &obj_data);
}

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
                           HSD_ObjUpdateFunc obj_update, f32 rate)
{
    f32 prev_fterm;
    u32 state;

    prev_fterm = 0.0F;
    state = fobj != NULL ? HSD_FObjGetState(fobj) : 0;
    if (state != 0 && !(fobj->time += rate, (fobj->time < 0.0))) {
        for (;;) {
            switch (state) {
            case 6: {
                /* End of stream reached */
                fobj->time += prev_fterm;
                FObjLaunchKeyData(fobj);
                FObjUpdateAnim(fobj, obj, obj_update);
                return;
            }
            case 1:
            case 2: {
                /* Load next keyframe packet */
                state = FObjLoadData(fobj);
                break;
            }
            case 3: {
                /* Load wait duration */
                if ((fobj->flags & 0x80) != 0) {
                    FObjUpdateAnim(fobj, obj, obj_update);
                }
                state = FObjLoadWait(fobj);
                break;
            }
            case 4: {
                /* Active interpolation interval */
                if (fobj->fterm <= fobj->time) {
                    u8 _[8];
                    state =
#ifdef MUST_MATCH
                        state =
#endif
                            3;

                    prev_fterm = fobj->fterm;
                    fobj->time -= fobj->fterm;
                    HSD_FObjSetState(fobj, state);
                    break;
                }
                FObjUpdateAnim(fobj, obj, obj_update);
                state =
#ifdef MUST_MATCH
                    state =
#endif
                        5;
                HSD_FObjSetState(fobj, state);
                return;
            }
            case 5: {
                /* Transition back to active interpolation state */
                state =
#ifdef MUST_MATCH
                    state =
#endif
                        4;
                HSD_FObjSetState(fobj, state);
                break;
            }
            case 0:
                /* Inactive / stopped track */
                return;
            }
        }
    }
}

/**
 * @brief Advances and interprets animation across an entire linked list of FObj tracks.
 * @param fobj Head of HSD_FObj linked list (passed as void*)
 * @param obj Target object
 * @param obj_update Callback to apply updates
 * @param rate Playback rate
 */
void HSD_FObjInterpretAnimAll(void* fobj, void* obj,
                              HSD_ObjUpdateFunc obj_update, f32 rate)
{
    HSD_FObj* cur = (HSD_FObj*) fobj;
    while (cur != NULL) {
        HSD_FObjInterpretAnim(cur, obj, obj_update, rate);
        cur = cur->next;
    }
}

/**
 * @brief Instantiates and initializes an FObj track chain from archive descriptors.
 * @param desc Pointer to HSD_FObjDesc descriptor
 * @return Head of newly allocated HSD_FObj chain, or NULL if desc is NULL
 */
HSD_FObj* HSD_FObjLoadDesc(HSD_FObjDesc* desc)
{
    if (desc != NULL) {
        HSD_FObj* fobj = HSD_FObjAlloc();
        fobj->next = HSD_FObjLoadDesc(desc->next);
        fobj->startframe = desc->startframe;
        fobj->obj_type = desc->type;
        fobj->frac_value = desc->frac_value;
        fobj->frac_slope = desc->frac_slope;
        fobj->ad_head = desc->ad;
        fobj->length = desc->length;
        fobj->flags = 0;
        return fobj;
    }
    return NULL;
}

/**
 * @brief Allocates and zero-initializes a new HSD_FObj from the memory pool.
 * @return Pointer to newly allocated HSD_FObj
 */
HSD_FObj* HSD_FObjAlloc(void)
{
    HSD_FObj* new = HSD_ObjAlloc(HSD_FObjGetAllocData());
    HSD_ASSERT(0x2F3, new);
    memset(new, 0, sizeof(HSD_FObj));
    return new;
}

/**
 * @brief Frees an HSD_FObj back to the memory pool.
 * @param fobj Pointer to HSD_FObj to free
 */
void HSD_FObjFree(HSD_FObj* fobj)
{
    HSD_ObjFree(HSD_FObjGetAllocData(), fobj);
}

/**
 * @file lobj.h
 * @brief Light Object (LObj) subsystem for SysDolphin
 * @details Manages lighting calculations including point, directional, spot, and ambient lights.
 * Handles hardware light mapping, attenuation, and color properties.
 */
#ifndef SYSDOLPHIN_BASELIB_LOBJ_H
#define SYSDOLPHIN_BASELIB_LOBJ_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dat_macros.h>

#include <dolphin/gx.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/object.h>

#define MAX_GXLIGHT 9

struct HSD_LightPoint {
    f32 cutoff;
    u32 point_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightPointDesc {
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightSpot {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightSpotDesc {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightAttn {
    f32 a0;
    f32 a1;
    f32 a2;
    f32 k0;
    f32 k1;
    f32 k2;
};

struct HSD_LObj {
    /* 0x00 - 0x04 */ HSD_Obj parent;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 priority;
    /* 0x0C */ HSD_LObj* next;
    /* 0x10 */ GXColor color;
    /* 0x14 */ GXColor hw_color;
    /* 0x18 */ HSD_WObj* position;
    /* 0x1C */ HSD_WObj* interest;
    /* 0x20 - 0x34 */ union HSD_LObj_u {
        HSD_LightPoint point;
        HSD_LightSpot spot;
        HSD_LightAttn attn;
    } u;
    /* 0x38 */ f32 shininess;
    /* 0x3C - 0x44 */ Vec3 lvec;
    /* 0x48 */ HSD_AObj* aobj;
    /* 0x4C */ GXLightID id;
    /* 0x50 */ GXLightObj lightobj;
    /* 0x90 */ GXLightID spec_id;
    /* 0x94 */ GXLightObj spec_lightobj;
};

struct HSD_LightDesc {
    /* 0x00 */ char* class_name;
    /* 0x04 */ HSD_LightDesc* next;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 attnflags;
    /* 0x0C */ GXColor color;
    /* 0x10 */ HSD_WObjDesc* position;
    /* 0x14 */ HSD_WObjDesc* interest;
    union HSD_LightDesc_u {
        void* p DAT_IF(false);
        f32* shininess DAT_IF(false);
        HSD_LightPointDesc* point DAT_IF((flags & LOBJ_TYPE_MASK) ==
                                             LOBJ_POINT &&
                                         !(attnflags & LOBJ_LIGHT_ATTN));
        HSD_LightSpotDesc* spot DAT_IF((flags & LOBJ_TYPE_MASK) == LOBJ_SPOT &&
                                       attnflags == 0);
        HSD_LightAttn* attn DAT_IF(((flags & LOBJ_TYPE_MASK) == LOBJ_POINT &&
                                    (attnflags & LOBJ_LIGHT_ATTN)) ||
                                   ((flags & LOBJ_TYPE_MASK) == LOBJ_SPOT &&
                                    attnflags != 0));
    } u;
};

struct HSD_LightAnim {
    HSD_LightAnim* next;
    HSD_AObjDesc* aobjdesc;
    HSD_WObjAnim* position_anim;
    HSD_WObjAnim* interest_anim;
};

struct HSD_LObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_LObj* lobj, HSD_LightDesc* ldesc);
};

#define HSD_LOBJ(o) ((HSD_LObj*) (o))
#define HSD_LOBJ_INFO(i) ((HSD_LObjInfo*) (i))
#define HSD_LOBJ_METHOD(o) HSD_LOBJ_INFO(HSD_OBJECT_METHOD((o)))

/**
 * @brief Retrieves the priority of the light object
 * @param lobj Light object
 * @return Priority level
 */
static inline u8 HSD_LObjGetPriority(HSD_LObj* lobj)
{
    HSD_ASSERT(367, lobj);
    return lobj->priority;
}

extern HSD_LObjInfo hsdLobj;

/** @brief Retrieves the flags of the light object */
u32 HSD_LObjGetFlags(HSD_LObj* lobj);
/** @brief Sets flags on the light object */
void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags);
/** @brief Clears flags on the light object */
void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags);

/** @brief Retrieves the active diffuse light mask */
GXLightID HSD_LObjGetLightMaskDiffuse(void);
/** @brief Retrieves the active attenuation function light mask */
s32 HSD_LObjGetLightMaskAttnFunc(void);
/** @brief Retrieves the active alpha light mask */
s32 HSD_LObjGetLightMaskAlpha(void);
/** @brief Retrieves the active specular light mask */
s32 HSD_LObjGetLightMaskSpecular(void);

/** @brief Sets a light object as active in the current GX rendering context */
void HSD_LObjSetActive(HSD_LObj* lobj);
/** @brief Retrieves the total number of currently active lights */
s32 HSD_LObjGetNbActive(void);
/** @brief Retrieves an active light object by its GXLightID */
HSD_LObj* HSD_LObjGetActiveByID(GXLightID id);
/** @brief Retrieves an active light object by its internal array index */
HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx);
/** @brief Clears all active light objects */
void HSD_LObjClearActive(void);

/** @brief Updates properties for a light object based on an animation value */
void LObjUpdateFunc(void* lobj_ptr, enum_t anim_type, HSD_ObjData* val);

/** @brief Adds a single animation to a light object */
void HSD_LObjAddAnim(HSD_LObj* lobj, HSD_LightAnim* lanim);
/** @brief Adds animations to a linked list of light objects */
void HSD_LObjAddAnimAll(HSD_LObj* lobj, HSD_LightAnim* lanim);
/** @brief Processes animation evaluation for a single light object */
void HSD_LObjAnim(HSD_LObj* lobj);
/** @brief Processes animation evaluation for a linked list of light objects */
void HSD_LObjAnimAll(HSD_LObj* lobj);
/** @brief Requests animation playback starting from a specific frame for a light */
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
/** @brief Requests animation playback starting from a specific frame for a list of lights */
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);

/** @brief Calculates the normalized directional light vector (from position to interest) */
void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir);
/** @brief Configures light GX parameters such as color and shininess */
void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess);

/** @brief Safely retrieves the position vector of the light */
bool HSD_LObjGetPosition(HSD_LObj*, Vec3*);
/** @brief Safely retrieves the interest (look-at) vector of the light */
bool HSD_LObjGetInterest(HSD_LObj*, Vec3*);

/** @brief Retrieves the underlying position WObj of the light */
HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj);
/** @brief Retrieves the underlying interest (look-at) WObj of the light */
HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj);
/** @brief Assigns a new WObj as the light's position */
void HSD_LObjSetPositionWObj(HSD_LObj* lobj, HSD_WObj* wobj);
/** @brief Assigns a new WObj as the light's interest (look-at) */
void HSD_LObjSetInterestWObj(HSD_LObj* lobj, HSD_WObj* wobj);

/** @brief Converts a GXLightID into an internal light array index */
u32 HSD_LightID2Index(GXLightID);
/** @brief Converts an internal light array index into a GXLightID */
s32 HSD_Index2LightID(u32);

/** @brief Deletes a light object from the current active list */
void HSD_LObjDeleteCurrent(HSD_LObj* lobj);
/** @brief Recursively removes and destroys a list of light objects */
void HSD_LObjRemoveAll(HSD_LObj* lobj);

/** @brief Sets the absolute position vector of the light */
void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position);
/** @brief Sets the absolute interest (look-at) vector of the light */
void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest);

/** @brief Replaces all currently active lights with a new light list */
void HSD_LObj_803668EC(HSD_LObj* lobj);

/** @brief Performs core initialization of active lights relative to a camera view */
void HSD_LObjSetupInit(HSD_CObj* arg0);

/** @brief Sets the primary color of the light object */
void HSD_LObjSetColor(HSD_LObj* lobj, GXColor color);
/** @brief Retrieves the primary color of the light object */
void HSD_LObjGetColor(HSD_LObj* lobj, GXColor* color);

/** @brief Configures spot light parameters (cutoff angle and spot function) */
void HSD_LObjSetSpot(HSD_LObj* lobj, f32 cutoff, s32 point_func);
/** @brief Configures distance attenuation function parameters for point/spot lights */
void HSD_LObjSetDistAttn(HSD_LObj* lobj, f32 ref_dist, f32 ref_br,
                         s32 dist_func);

/** @brief Sets the angular attenuation terms */
void HSD_LObjSetAttnA(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2);
/** @brief Sets the distance attenuation terms */
void HSD_LObjSetAttnK(HSD_LObj* lobj, f32 k0, f32 k1, f32 k2);
/** @brief Sets all attenuation terms simultaneously */
void HSD_LObjSetAttn(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                     f32 k2);

/** @brief Initializes the half-angle vectors required for specular lighting computations */
void HSD_LObjSetupSpecularInit(Mtx pmtx);

/** @brief Retrieves the lighting type (point, spot, infinite, ambient) */
u32 HSD_LObjGetType(HSD_LObj* lobj);

/** @brief Appends a light to the current global light list */
void HSD_LObjAddCurrent(HSD_LObj* lobj);
/** @brief Decrements the reference count of a light object, freeing it if zero */
void HSD_LObjUnrefThis(HSD_LObj* lobj);

/** @brief Deletes a linked list of light objects from the current active list */
void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj);
/** @brief Clears existing active lights and adds all lights from the given list */
void HSD_LObjSetCurrentAll(HSD_LObj* lobj);

/** @brief Locates the first active light object that matches a specific type flag */
HSD_LObj* HSD_LObjGetCurrentByType(u16 type);

void HSD_LObjSetDefaultClass(HSD_LObjInfo* info);
HSD_LObjInfo* HSD_LObjGetDefaultClass(void);
HSD_LObj* HSD_LObjAlloc(void);
HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc);

static inline HSD_LObj* HSD_LObjGetNext(HSD_LObj* lobj)
{
    if (lobj == NULL) {
        return NULL;
    } else {
        return lobj->next;
    }
}

static inline void HSD_LObjSetNext(HSD_LObj* lobj, HSD_LObj* next)
{
    HSD_ASSERT(0x136, lobj);
    lobj->next = next;
}

#endif

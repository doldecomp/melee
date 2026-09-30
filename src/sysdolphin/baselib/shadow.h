/**
 * @file shadow.h
 * @brief Circular shadow rendering system
 * @details Handles the projection of circular shadows beneath characters and items onto the ground.
 */

#ifndef _shadow_h_
#define _shadow_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/tobj.h>

struct HSD_Shadow {
    HSD_SList* objects; // 0x0
    HSD_CObj* camera;   // 0x4
    HSD_TObj* texture;  // 0x8
    f32 scaleS;         // 0xC
    f32 scaleT;         // 0x10
    f32 transS;         // 0x14
    f32 transT;         // 0x18
    bool active;        // 0x1C
    u8 intensity;       // 0x20
    void* user_data;    // 0x24
};

struct HSD_ViewingRect {
    Vec3 origin;
    Vec3 up_v;
    Vec3 right_v;
    Vec3 eye_v;
    Vec3 eye_vn;
    f32 distance;
    f32 top;
    f32 bottom;
    f32 left;
    f32 right;
    int perspective;
};

/**
 * @brief Retrieves the shadow allocation data object
 * @return Pointer to the shadow HSD_ObjAllocData
 */
HSD_ObjAllocData* HSD_ShadowGetAllocData(void);

/**
 * @brief Initializes the shadow memory allocator
 */
void HSD_ShadowInitAllocData(void);

/**
 * @brief Allocates and initializes a new HSD_Shadow instance
 * @return A new shadow instance
 */
HSD_Shadow* HSD_ShadowAlloc(void);

/**
 * @brief Adds a JObj (joint object) to the list of objects receiving this shadow
 * @param shadow The shadow instance
 * @param jobj The JObj to cast the shadow on
 */
void HSD_ShadowAddObject(HSD_Shadow* shadow, HSD_JObj* jobj);

/**
 * @brief Removes a JObj from the list of objects receiving this shadow
 * @param shadow The shadow instance
 * @param jobj The JObj to remove, or NULL to clear all
 */
void HSD_ShadowDeleteObject(HSD_Shadow* shadow, HSD_JObj* jobj);

/**
 * @brief Begins the shadow rendering pass, configuring the TEV and rendering objects
 * @param shadow The shadow instance
 */
void HSD_ShadowStartRender(HSD_Shadow* shadow);

/**
 * @brief Ends the shadow rendering pass, syncing GX pixels and copying to the texture
 * @param shadow The shadow instance
 */
void HSD_ShadowEndRender(HSD_Shadow* shadow);

/**
 * @brief Toggles the active state of a shadow
 * @param shadow The shadow instance
 * @param active Non-zero to activate, zero to deactivate
 */
void HSD_ShadowSetActive(HSD_Shadow* shadow, int active);

/**
 * @brief Internal helper to allocate a generic texture object for shadows
 * @return A new HSD_TObj for the shadow
 */
HSD_TObj* makeShadowTObj(void);

/**
 * @brief Frees a shadow instance and cleans up its camera and textures
 * @param shadow The shadow instance
 */
void HSD_ShadowRemove(HSD_Shadow* shadow);

/**
 * @brief Configures GX hardware copying state for the shadow texture
 * @param shadow The shadow instance
 */
void HSD_ShadowInit(HSD_Shadow* shadow);

/**
 * @brief Updates the shadow texture resolution
 * @param shadow The shadow instance
 * @param width New width
 * @param height New height
 */
void HSD_ShadowSetSize(HSD_Shadow* shadow, u16 width, u16 height);

/**
 * @brief Adjusts the shadow camera viewing volume (frustum/ortho/perspective)
 * @param shadow The shadow instance
 * @param top Top bound
 * @param bottom Bottom bound
 * @param left Left bound
 * @param right Right bound
 */
void HSD_ShadowSetViewingRect(HSD_Shadow* shadow, float top, float bottom,
                              float left, float right);

/**
 * @brief Initializes a viewing rect structure based on camera properties
 * @param rect Pointer to the viewing rect to initialize
 * @param position Camera position
 * @param interest Camera interest/look-at point
 * @param upvector Camera up vector
 * @param perspective Perspective mode indicator
 */
void HSD_ViewingRectInit(HSD_ViewingRect* rect, Vec3* position, Vec3* interest,
                         Vec3* upvector, int perspective);

/**
 * @brief Checks if a viewing rect is valid (top > bottom and right > left)
 * @param rect Pointer to the viewing rect
 * @return Non-zero if valid, zero if invalid
 */
int HSD_ViewingRectCheck(HSD_ViewingRect* rect);

/**
 * @brief Expands the viewing rect boundaries to encompass the provided rectangle
 * @param rect Pointer to the viewing rect
 * @param position Local origin of the sub-rect
 * @param top Local top
 * @param bottom Local bottom
 * @param left Local left
 * @param right Local right
 */
void HSD_ViewingRectAddRect(HSD_ViewingRect* rect, Vec3* position, float top,
                            float bottom, float left, float right);

#endif

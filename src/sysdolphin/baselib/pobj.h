/**
 * @file pobj.h
 * @brief Polygon Object (PObj) management
 * @details PObjs contain vertex geometry data such as display lists, skin weights, and shape blending info.
 * Module prefix: HSD_PObj
 */
#ifndef _pobj_h_
#define _pobj_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dat_macros.h>

#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/list.h>

#define HSD_MTX_RIGID 1
#define HSD_MTX_ENVELOPE 2

struct HSD_PObj {
    HSD_Class parent;
    HSD_PObj* next;
    HSD_VtxDescList* verts;
    u16 flags;
    u16 n_display;
    /// #u8 primitive, #u16 vtxcnt, #u16* indices
    u8* display;
    union HSD_PObjUnion {
        HSD_JObj* jobj;
        HSD_ShapeSet* shape_set;
        HSD_SList* envelope_list;
    } u;
};

/// Envelopes of one vertex matrix, up to one with a null joint.
typedef HSD_EnvelopeDesc* HSD_EnvelopeList DAT_NULLTERM;

struct HSD_PObjDesc {
    char* class_name;
    HSD_PObjDesc* next;
    HSD_VtxDescList* verts;
    u16 flags;
    u16 n_display;
    u8* display;
    union HSD_PObjDesc_u {
        HSD_Joint* joint DAT_IF((flags & 0x3000) == POBJ_SKIN);
        HSD_ShapeSetDesc* shape_set DAT_IF((flags & 0x3000) == POBJ_SHAPEANIM);
        HSD_EnvelopeList* envelope_p DAT_NULLTERM DAT_IF((flags & 0x3000) ==
                                                         POBJ_ENVELOPE);
    } u;
};

struct HSD_VtxDescList {
    GXAttr attr;
    GXAttrType attr_type;
    GXCompCnt comp_cnt;
    GXCompType comp_type;
    u8 frac;
    u16 stride;
    void* vertex;
};

struct HSD_Envelope {
    HSD_Envelope* next;
    HSD_JObj* jobj;
    f32 weight;
};

struct HSD_EnvelopeDesc {
    HSD_Joint* joint;
    f32 weight;
};

struct HSD_ShapeSet {
    u16 flags;
    u16 nb_shape;
    int nb_vertex_index;
    HSD_VtxDescList* vertex_desc;
    u8** vertex_idx_list;
    s32 nb_normal_index;
    HSD_VtxDescList* normal_desc;
    u8** normal_idx_list;
    union HSD_ShapeSet_blend {
        f32* bp;
        f32 bl;
    } blend;
    HSD_AObj* aobj;
};

struct HSD_ShapeSetDesc {
    u16 flags;
    u16 nb_shape;
    s32 nb_vertex_index;
    HSD_VtxDescList* vertex_desc;
    u8** vertex_idx_list;
    s32 nb_normal_index;
    HSD_VtxDescList* normal_desc;
    u8** normal_idx_list;
};

struct HSD_ShapeAnim {
    HSD_ShapeAnim* next;
    HSD_AObjDesc* aobjdesc;
};

struct HSD_ShapeAnimJoint {
    HSD_ShapeAnimJoint* child;
    HSD_ShapeAnimJoint* next;
    HSD_ShapeAnimDObj* shapeanimdobj;
};

struct HSD_PObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
    void (*setup_mtx)(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
    s32 (*load)(HSD_PObj* pobj, HSD_PObjDesc* desc);
};

extern HSD_PObjInfo hsdPObj;

#define HSD_POBJ(o) ((HSD_PObj*) (o))
#define HSD_POBJ_INFO(i) ((HSD_PObjInfo*) (i))
#define HSD_POBJ_METHOD(o) HSD_POBJ_INFO(HSD_CLASS_METHOD(o))

/**
 * @brief Gets the default PObj class info.
 */
HSD_PObjInfo* HSD_PObjGetDefaultClass(void);
/**
 * @brief Sets the default PObj class info.
 * @param info The PObj class info to set as default
 */
void HSD_PObjSetDefaultClass(HSD_PObjInfo* info);
/**
 * @brief Allocates a new PObj.
 * @return Pointer to the allocated PObj
 */
HSD_PObj* HSD_PObjAlloc(void);
/**
 * @brief Frees a given PObj.
 * @param pobj The PObj to free
 */
void HSD_PObjFree(HSD_PObj*);

/**
 * @brief Gets the flags of a PObj.
 * @param pobj The PObj
 * @return The flags
 */
u32 HSD_PObjGetFlags(HSD_PObj* pobj);
/**
 * @brief Removes animations from a list of PObjs matching the given flags.
 * @param pobj The head of the PObj list
 * @param flags The flags to match
 */
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, u32 flags);
/**
 * @brief Requests an animation on a PObj matching the given flags.
 * @param pobj The PObj
 * @param startframe The start frame
 * @param flags The flags to match
 */
void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
/**
 * @brief Requests an animation on a list of PObjs matching the given flags.
 * @param pobj The head of the PObj list
 * @param startframe The start frame
 * @param flags The flags to match
 */
void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
/**
 * @brief Clears the GX vertex descriptor cache.
 */
void HSD_ClearVtxDesc(void);
/**
 * @brief Loads a PObj from a descriptor.
 * @param desc The PObj descriptor
 * @return The loaded PObj
 */
HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc*);

/**
 * @brief Clears the matrix mark for an object.
 * @param obj The object
 * @param mark The mark to clear
 */
void HSD_PObjClearMtxMark(void* obj, u32 mark);
/**
 * @brief Sets the matrix mark for an object at a specific index.
 * @param idx The index
 * @param obj The object
 * @param mark The mark to set
 */
void HSD_PObjSetMtxMark(int idx, void* obj, u32 mark);
/**
 * @brief Gets the matrix mark for an object at a specific index.
 * @param idx The index
 * @param obj Output pointer for the object
 * @param mark Output pointer for the mark
 */
void HSD_PObjGetMtxMark(int idx, void** obj, u32* mark);
/**
 * @brief Adds a shape animation to a PObj.
 * @param pobj The PObj
 * @param anim The shape animation
 */
void HSD_PObjAddAnim(HSD_PObj*, HSD_ShapeAnim*);
/**
 * @brief Adds shape animations to a list of PObjs.
 * @param pobj The head of the PObj list
 * @param anim The shape animation
 */
void HSD_PObjAddAnimAll(HSD_PObj*, HSD_ShapeAnim*);
/**
 * @brief Processes the animation for a PObj.
 * @param pobj The PObj
 */
void HSD_PObjAnim(HSD_PObj* pobj);
/**
 * @brief Processes the animation for a list of PObjs.
 * @param pobj The head of the PObj list
 */
void HSD_PObjAnimAll(HSD_PObj*);
/**
 * @brief Resolves JObj references in a PObj using its descriptor.
 * @param pobj The PObj
 * @param desc The PObj descriptor
 */
void HSD_PObjResolveRefs(HSD_PObj*, HSD_PObjDesc*);
/**
 * @brief Resolves JObj references in a list of PObjs using a descriptor list.
 * @param pobj The head of the PObj list
 * @param desc The head of the PObj descriptor list
 */
void HSD_PObjResolveRefsAll(HSD_PObj*, HSD_PObjDesc*);
/**
 * @brief Removes (deletes) a PObj.
 * @param pobj The PObj
 */
void HSD_PObjRemove(HSD_PObj*);
/**
 * @brief Removes (deletes) a list of PObjs.
 * @param pobj The head of the PObj list
 */
void HSD_PObjRemoveAll(HSD_PObj*);

/**
 * @brief Removes an animation from a PObj matching the given flags.
 * @param pobj The PObj
 * @param flags The flags to match
 */
void HSD_PObjRemoveAnimByFlags(HSD_PObj* pobj, u32 flags);

/**
 * @brief Displays (renders) a PObj.
 * @param pobj The PObj
 * @param vmtx The view matrix
 * @param pmtx The projection matrix
 * @param rendermode Rendering mode flags
 */
void HSD_PObjDisp(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);

#endif

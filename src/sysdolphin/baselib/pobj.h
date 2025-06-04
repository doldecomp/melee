#ifndef _pobj_h_
#define _pobj_h_

#include <platform.h>

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/aobj.h"
#include "baselib/class.h"
#include "baselib/list.h"

#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>

#define HSD_MTX_RIGID 1
#define HSD_MTX_ENVELOPE 2

struct _unk_struct_pobj {
    u32 data[8];
    HSD_AObj* aobj;
};

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
        struct _unk_struct_pobj* unk;
    } u;
};

struct HSD_PObjDesc {
    char* class_name;
    HSD_PObjDesc* next;
    HSD_VtxDescList* verts;
    u16 flags;
    u16 n_display;
    u8* display;
    union {
        HSD_Joint* joint;
        HSD_ShapeSetDesc* shape_set;
        HSD_EnvelopeDesc** envelope_p;
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
    union {
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

HSD_PObjInfo* HSD_PObjGetDefaultClass(void);
void HSD_PObjSetDefaultClass(HSD_PObjInfo* info);
HSD_PObj* HSD_PObjAlloc(void);
void HSD_PObjFree(HSD_PObj*);

u32 HSD_PObjGetFlags(HSD_PObj* pobj);
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, u32 flags);
void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, f32 startframe, u32 flags);
void HSD_ClearVtxDesc(void);
HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc*);

void HSD_PObjClearMtxMark(void* obj, u32 mark);
void HSD_PObjSetMtxMark(int idx, void* obj, u32 mark);
void HSD_PObjGetMtxMark(int idx, void** obj, u32* mark);
void HSD_PObjAddAnim(HSD_PObj*, HSD_ShapeAnim*);
void HSD_PObjAddAnimAll(HSD_PObj*, HSD_ShapeAnim*);
void HSD_PObjAnim(HSD_PObj* pobj);
void HSD_PObjAnimAll(HSD_PObj*);
void HSD_PObjResolveRefs(HSD_PObj*, HSD_PObjDesc*);
void HSD_PObjResolveRefsAll(HSD_PObj*, HSD_PObjDesc*);
void HSD_PObjRemove(HSD_PObj*);
void HSD_PObjRemoveAll(HSD_PObj*);

void HSD_PObjRemoveAnimByFlags(HSD_PObj* pobj, u32 flags);

void HSD_PObjDisp(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);

#endif

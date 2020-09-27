#ifndef _pobj_h_
#define _pobj_h_

#include "include/dolphin/types.h"

#include "object.h"

#include "aobj.h"
#include "fobj.h"

#define HSD_A_S_W0 8
#define HSD_DEFAULT_MAX_SHAPE_VERTICES 2000
#define HSD_DEFAULT_MAX_SHAPE_NORMALS 2000

#define POBJ_ANIM (1 << 3)
#define POBJ_SKIN (0 << 12)
#define POBJ_SHAPEANIM (1 << 12)
#define POBJ_ENVELOPE (2 << 12)

#define pobj_type(o) (o->flags & 0x3000)

#define POBJ_CULLFRONT (1 << 14)
#define POBJ_CULLBACK (1 << 15)

#define SHAPESET_AVERAGE 1
#define SHAPESET_ADDITIVE 1 << 1

#define GX_NOP 0
#define GX_VAT_MASK 0x7
#define GX_OPCODE_MASK 0xF8

typedef enum _PObjSetupFlag {
    SETUP_NORMAL = 1,
    SETUP_REFLECTION = 2,
    SETUP_HIGHLIGHT = 4,
    SETUP_NORMAL_PROJECTION = 6,
    SETUP_JOINT0 = 1,
    SETUP_JOINT1 = 2,
    SETUP_NONE = 0
} PObjSetupFlag;

//Polygon Object
typedef struct _HSD_PObj {
    HSD_Class parent;
    struct _HSD_PObj* next;
    struct _HSD_VtxDescList* verts;
    u16 flags;
    u16 n_display;
    u8* display; //u8 primitive, u8 vtxcnt, u16* indices
    union {
        struct _HSD_JObj* jobj;
        struct _HSD_ShapeSet* shape_set;
        HSD_SList* envelope_list;
    } u;
    struct _HSD_AObj* aobj;
} HSD_PObj;

typedef struct _HSD_PObjDesc {
    char* class_name;
    struct _HSD_PObjDesc* next;
    struct _HSD_VtxDescList* verts;
    u16 flags;
    u16 n_display;
    u8* display;
    union {
        struct _HSD_JObjDesc* joint;
        struct _HSD_ShapeSetDesc* shape_set;
        struct _HSD_EnvelopeDesc** envelope_p;
    } u;
} HSD_PObjDesc;

typedef struct _HSD_VtxDescList {
    u32 attr;
    u32 attr_type;
    u32 comp_cnt;
    u32 comp_type;
    u8 frac;
    u16 stride;
    void* vertex;
} HSD_VtxDescList;

typedef struct _HSD_Envelope {
    struct _HSD_Envelope* next;
    struct _HSD_JObj* jobj;
    f32 weight;
} HSD_Envelope;

typedef struct _HSD_EnvelopeDesc {
    struct _HSD_JObjDesc* joint;
    f32 weight;
} HSD_EnvelopeDesc;

typedef struct _HSD_ShapeSet {
    u16 flags;
    u16 nb_shape;
    u32 nb_vertex_index;
    struct _HSD_VtxDescList* vertex_desc;
    u8** vertex_idx_list;
    u32 nb_normal_index;
    struct _HSD_VtxDescList* normal_desc;
    u8** normal_idx_list;
    struct {
        f32* bp;
        f32 bl;
    } blend;
} HSD_ShapeSet;

typedef struct _HSD_ShapeSetDesc {
    u16 flags;
    u16 nb_shape;
    u32 nb_vertex_index;
    struct _HSD_VtxDescList* vertex_desc;
    u8** vertex_idx_list;
    u32 nb_normal_index;
    struct _HSD_VtxDescList* normal_desc;
    u8** normal_idx_list;
} HSD_ShapeSetDesc;

typedef struct _HSD_ShapeAnim {
    struct _HSD_ShapeAnim* next;
    HSD_AObjDesc* aobjdesc;
} HSD_ShapeAnim;

typedef struct _HSD_ShapeAnimJoint {
    struct _HSD_ShapeAnimJoint* child;
    struct _HSD_ShapeAnimJoint* next;
    struct _HSD_ShapeAnimDObj* shapeanimdobj;
} HSD_ShapeAnimJoint;

typedef struct _HSD_PObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
    void (*setup_mtx)(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
    s32 (*load)(HSD_PObj* pobj, HSD_PObjDesc* desc);
    void (*update)(void* obj, u32 type, FObjData* val);
} HSD_PObjInfo;

extern HSD_PObjInfo hsdPObj;

#define HSD_POBJ(o) ((HSD_PObj*)(o))
#define HSD_POBJ_INFO(i) ((HSD_PObjInfo*)(i))
#define HSD_POBJ_METHOD(o) HSD_POBJ_INFO(HSD_CLASS_METHOD(o))

u16 HSD_PObjGetFlags(HSD_PObj* pobj);

#endif

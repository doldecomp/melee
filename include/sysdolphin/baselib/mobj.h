#ifndef _mobj_h_
#define _mobj_h_

#include <global.h>

#include <dolphin/types.h>

#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/texp.h>
#include <sysdolphin/baselib/tobj.h>

#define MOBJ_ANIM 0x4
#define TOBJ_ANIM 0x10
#define ALL_ANIM 0x7FF

#define HSD_A_M_AMBIENT_R 1
#define HSD_A_M_AMBIENT_G 2
#define HSD_A_M_AMBIENT_B 3
#define HSD_A_M_DIFFUSE_R 4
#define HSD_A_M_DIFFUSE_G 5
#define HSD_A_M_DIFFUSE_B 6
#define HSD_A_M_SPECULAR_R 7
#define HSD_A_M_SPECULAR_G 8
#define HSD_A_M_SPECULAR_B 9
#define HSD_A_M_ALPHA 10
#define HSD_A_M_PE_REF0 11
#define HSD_A_M_PE_REF1 12
#define HSD_A_M_PE_DSTALPHA 13

#define RENDER_DIFFUSE_SHIFT 0
#define RENDER_DIFFUSE_BITS (3 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_MAT0 (0 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_MAT (1 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_VTX (2 << RENDER_DIFFUSE_SHIFT)
#define RENDER_DIFFUSE_BOTH (3 << RENDER_DIFFUSE_SHIFT)

#define RENDER_CONSTANT (1 << 0)
#define RENDER_VERTEX (1 << 1)
#define RENDER_DIFFUSE (1 << 2)
#define RENDER_SPECULAR (1 << 3)
#define CHANNEL_FIELD (RENDER_CONSTANT | RENDER_VERTEX | RENDER_DIFFUSE | RENDER_SPECULAR)
#define RENDER_TEX0 (1 << 4)
#define RENDER_TEX1 (1 << 5)
#define RENDER_TEX2 (1 << 6)
#define RENDER_TEX3 (1 << 7)
#define RENDER_TEX4 (1 << 8)
#define RENDER_TEX5 (1 << 9)
#define RENDER_TEX6 (1 << 10)
#define RENDER_TEX7 (1 << 11)
#define RENDER_TEXTURES (RENDER_TEX0 | RENDER_TEX1 | RENDER_TEX2 | RENDER_TEX3 | RENDER_TEX4 | RENDER_TEX5 | RENDER_TEX6 | RENDER_TEX7)
#define RENDER_TOON (1 << 12)

#define RENDER_ALPHA_SHIFT 13
#define RENDER_ALPHA_BITS (3 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_COMPAT (0 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_MAT (1 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_VTX (2 << RENDER_ALPHA_SHIFT)
#define RENDER_ALPHA_BOTH (3 << RENDER_ALPHA_SHIFT)

#define RENDER_SHADOW (1 << 26)
#define RENDER_ZMODE_ALWAYS (1 << 27)
#define RENDER_NO_ZUPDATE (1 << 29)
#define RENDER_XLU (1 << 30)

typedef struct _HSD_MObj {
    HSD_Class parent;
    u32 rendermode;
    struct _HSD_TObj* tobj;
    struct _HSD_Material* mat;
    struct _HSD_PEDesc* pe;
    struct _HSD_AObj* aobj;
    struct _HSD_TExpTevDesc* tevdesc;
    union _HSD_TExp* texp;

    struct _HSD_TObj* tobj_toon;
    struct _HSD_TObj* tobj_gradation;
    struct _HSD_TObj* tobj_backlight;
    f32 z_offset;
} HSD_MObj;

typedef struct _HSD_Material {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    f32 alpha;
    f32 shininess;
} HSD_Material;

typedef struct _HSD_PEDesc {
    u8 flags;
    u8 ref0;
    u8 ref1;
    u8 dst_alpha;
    u8 type;
    u8 src_factor;
    u8 dst_factor;
    u8 logic_op;
    u8 z_comp;
    u8 alpha_comp0;
    u8 alpha_op;
    u8 alpha_comp1;
} HSD_PEDesc;

typedef struct _HSD_MObjDesc {
    char* class_name;
    u32 rendermode;
    struct _HSD_TObjDesc* texdesc;
    struct _HSD_Material* mat;
    void* renderdesc;
    struct _HSD_PEDesc* pedesc;
} HSD_MObjDesc;

typedef struct _HSD_ChanAnim {
    struct _HSD_ChanAnim* next;
    struct _HSD_AObjDesc* aobjdesc;
} HSD_ChanAnim;

typedef struct _HSD_TevRegAnim {
    struct _HSD_TevRegAnim* next;
    struct _HSD_AObjDesc* aobjdesc;
} HSD_TevRegAnim;

typedef struct _HSD_RenderAnim {
    struct _HSD_ChanAnim* chananim;
    struct _HSD_TevRegAnim* reganim;
} HSD_RenderAnim;

typedef struct _HSD_MatAnim {
    struct _HSD_MatAnim* next;
    struct _HSD_AObjDesc* aobjdesc;
    struct _HSD_TexAnim* texanim;
    struct _HSD_RenderAnim* renderanim;
} HSD_MatAnim;

typedef struct _HSD_MatAnimJoint {
    struct _HSD_MatAnimJoint* child;
    struct _HSD_MatAnimJoint* next;
    struct _HSD_MatAnim* matanim;
} HSD_MatAnimJoint;

typedef struct _HSD_MObjInfo {
    HSD_ClassInfo parent;
    void (*setup)(HSD_MObj* mobj, u32 rendermode);
    int (*load)(HSD_MObj* mobj, HSD_MObjDesc* desc);
    HSD_TExp* (*make_texp)(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list);
    void (*setup_tev)(HSD_MObj* mobj, HSD_TObj* tobj, u32 rendermode);
    void (*unset)(HSD_MObj* mobj, u32 rendermode);
} HSD_MObjInfo;

#define HSD_MOBJ(o) ((HSD_MObj*)(o))
#define HSD_MOBJ_INFO(i) ((HSD_MObjInfo*)(i))
#define HSD_MOBJ_METHOD(o) HSD_MOBJ_INFO(HSD_CLASS_METHOD(o))

extern HSD_MObjInfo hsdMObj;

void HSD_MObjSetCurrent(HSD_MObj* mobj);
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim);
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags);
void HSD_MObjReqAnim(HSD_MObj *mobj, f32 startframe);

void MObjUpdateFunc(void* obj, u32 type, FObjData* val);

void HSD_MObjAnim(HSD_MObj* mobj);

int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc);
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc);

HSD_MObj* HSD_MObjAlloc();
HSD_Material* HSD_MaterialAlloc();

void HSD_MObjCompileTev(HSD_MObj *mobj);

#endif

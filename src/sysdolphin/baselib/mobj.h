#ifndef _mobj_h_
#define _mobj_h_

#include <platform.h>

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/class.h"
#include "baselib/texp.h"
#include "baselib/tobj.h"

#include <dolphin/gx/types.h>

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
#define CHANNEL_FIELD                                                         \
    (RENDER_CONSTANT | RENDER_VERTEX | RENDER_DIFFUSE | RENDER_SPECULAR)
#define RENDER_TEX0 (1 << 4)
#define RENDER_TEX1 (1 << 5)
#define RENDER_TEX2 (1 << 6)
#define RENDER_TEX3 (1 << 7)
#define RENDER_TEX4 (1 << 8)
#define RENDER_TEX5 (1 << 9)
#define RENDER_TEX6 (1 << 10)
#define RENDER_TEX7 (1 << 11)
#define RENDER_TEXTURES                                                       \
    (RENDER_TEX0 | RENDER_TEX1 | RENDER_TEX2 | RENDER_TEX3 | RENDER_TEX4 |    \
     RENDER_TEX5 | RENDER_TEX6 | RENDER_TEX7)
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

struct HSD_MObj {
    HSD_Class parent;
    u32 rendermode;
    HSD_TObj* tobj;
    HSD_Material* mat;
    HSD_PEDesc* pe;
    HSD_AObj* aobj;
    struct _HSD_TExpTevDesc* tevdesc;
    HSD_TExp* texp;
};

struct HSD_Material {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    f32 alpha;
    f32 shininess;
};

struct HSD_PEDesc {
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
};

typedef struct _HSD_MObjDesc {
    char* class_name;
    u32 rendermode;
    struct _HSD_TObjDesc* texdesc;
    HSD_Material* mat;
    void* renderdesc;
    HSD_PEDesc* pedesc;
} HSD_MObjDesc;

typedef struct _HSD_ChanAnim {
    struct _HSD_ChanAnim* next;
    HSD_AObjDesc* aobjdesc;
} HSD_ChanAnim;

typedef struct _HSD_TevRegAnim {
    struct _HSD_TevRegAnim* next;
    HSD_AObjDesc* aobjdesc;
} HSD_TevRegAnim;

typedef struct _HSD_RenderAnim {
    struct _HSD_ChanAnim* chananim;
    struct _HSD_TevRegAnim* reganim;
} HSD_RenderAnim;

typedef struct _HSD_MatAnim {
    struct _HSD_MatAnim* next;
    HSD_AObjDesc* aobjdesc;
    struct _HSD_TexAnim* texanim;
    struct _HSD_RenderAnim* renderanim;
} HSD_MatAnim;

struct HSD_MatAnimJoint {
    HSD_MatAnimJoint* child;
    HSD_MatAnimJoint* next;
    HSD_MatAnim* matanim;
};

struct HSD_MObjInfo {
    /*  +0 */ HSD_ClassInfo parent;
    /* +3C */ HSD_MObjSetupFunc setup;
    /* +40 */ int (*load)(HSD_MObj* mobj, HSD_MObjDesc* desc);
    /* +44 */ HSD_TExp* (*make_texp)(HSD_MObj* mobj, HSD_TObj* tobj_top,
                                     HSD_TExp** list);
    /* +48 */ void (*setup_tev)(HSD_MObj* mobj, HSD_TObj* tobj,
                                u32 rendermode);
    /* +4C */ void (*unset)(HSD_MObj* mobj, u32 rendermode);
};

#define HSD_MOBJ(o) ((HSD_MObj*) (o))
#define HSD_MOBJ_INFO(i) ((HSD_MObjInfo*) (i))
#define HSD_MOBJ_METHOD(o) HSD_MOBJ_INFO(HSD_CLASS_METHOD(o))

extern HSD_MObjInfo hsdMObj;

void HSD_MObjSetCurrent(HSD_MObj* mobj);
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim);
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags);
void HSD_MObjReqAnim(HSD_MObj* mobj, f32 startframe);
void HSD_MObjAnim(HSD_MObj* mobj);
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc);
HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj);
void HSD_MObjRemove(HSD_MObj* mobj);
HSD_MObj* HSD_MObjAlloc(void);
HSD_Material* HSD_MaterialAlloc(void);
void HSD_MObjCompileTev(HSD_MObj* mobj);
void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj);
HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list);
void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2);

void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode);
void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode);
void HSD_MObjSetToonTextureImage(HSD_ImageDesc* imagedesc);
void HSD_MObjSetDiffuseColor(HSD_MObj* mobj, u8 r, u8 g, u8 b);
void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha);
void HSD_MObjAddShadowTexture(HSD_TObj* tobj);
extern HSD_TObj* tobj_shadows;
extern HSD_TObj* tobj_toon;

#endif

#ifndef _cobj_h_
#define _cobj_h_

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/wobj.h>

#define PROJ_PERSPECTIVE 1
#define PROJ_FRUSTRUM 2
#define PROJ_ORTHO 3

struct HSD_CObj {
    HSD_Obj parent;
    u32 flags;              // 0x08
    f32 viewport_left;      // 0x0C
    f32 viewport_right;     // 0x10
    f32 viewport_top;       // 0x14
    f32 viewport_bottom;    // 0x18
    u16 scissor_left;       // 0x1C
    u16 scissor_right;      // 0x1E
    u16 scissor_top;        // 0x20
    u16 scissor_bottom;     // 0x22
    HSD_WObj* eye_position; // 0x24
    HSD_WObj* interest;     // 0x28
    union {
        f32 roll; // 0x2C
        Vec3 up;  // 0x2C - 0x34
    } u;
    f32 near; // 0x38
    f32 far;  // 0x3C
    union {
        struct {
            f32 fov;
            f32 aspect;
        } perspective;

        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustrum;

        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
    u8 projection_type; // 0x50
    Mtx view_mtx;       // 0x54
    HSD_AObj* aobj;     // 0x84
    Mtx* proj_mtx;      // 0x88
};

struct HSD_CObjDesc {
    char* class_name;            // 0x00
    u16 flags;                   // 0x04
    u16 projection_type;         // 0x06
    u16 viewport_left;           // 0x08
    u16 viewport_right;          // 0x0A
    u16 viewport_top;            // 0x0C
    u16 viewport_bottom;         // 0x0E
    u32 scissor_lr;              // 0x10
    u32 scissor_tb;              // 0x14
    HSD_WObjDesc* eye_desc;      // 0x18
    HSD_WObjDesc* interest_desc; // 0x1C
    f32 roll;                    // 0x20
    Vec3* vector;                // 0x24
    f32 near;                    // 0x28
    f32 far;                     // 0x2C
    union {
        struct {
            f32 fov;
            f32 aspect;
        } perspective;

        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustrum;

        struct {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
};

struct HSD_CObjInfo {
    HSD_ObjInfo parent;
    int (*load)(HSD_CObj* cobj, HSD_CObjDesc* desc);
};

struct HSD_CameraAnim {
    HSD_AObjDesc* aobjdesc;
    HSD_WObjAnim* eye_anim;
    HSD_WObjAnim* interest_anim;
};

typedef struct _cobj_Unk1 cobj_Unk1;

typedef void (*cobj_UnkCallback1)(void);

void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha,
                         s32 enable_depth);
void HSD_CObjRemoveAnim(HSD_CObj* cobj);
HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj);
HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj);
void HSD_CObjSetOrtho(HSD_CObj* cobj, f32, f32, f32, f32);
unk_t HSD_CObjLoadDesc(cobj_Unk1*);
void HSD_CObjSetInterest(HSD_CObj* cobj, s32*);
void HSD_CObjSetEyePosition(HSD_CObj* cobj, s32*);
void HSD_CObjSetRoll(HSD_CObj* cobj, f32);
void HSD_CObjSetNear(HSD_CObj* cobj, f32);
void HSD_CObjSetFar(HSD_CObj* cobj, f32);
void HSD_CObjSetScissor(HSD_CObj* cobj, s16*);
void HSD_CObjSetViewport(HSD_CObj* cobj, s16*);
void HSD_CObjSetProjectionType(u32);
bool HSD_CObjSetCurrent(HSD_Obj*, cobj_UnkCallback1);
HSD_CObj* HSD_CObjGetCurrent(void);
void HSD_CObjEndCurrent(void);
void HSD_CObjGetViewingMtx(unk_t);
MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj*);
f32 HSD_CObjGetNear(HSD_CObj*);
f32 HSD_CObjGetFar(HSD_CObj*);
void HSD_CObjSetScissorx4(HSD_CObj*, s32, s32, s32, s32);
void HSD_CObjSetViewportfx4(HSD_CObj*, f32, f32, f32, f32);
u32 HSD_CObjGetProjectionType(HSD_CObj*);
void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* cam_pos);
void HSD_CObjGetEyeVector(void);
void HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up);
void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest);
HSD_CObj* HSD_CObjAlloc(void);

void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags);

#endif

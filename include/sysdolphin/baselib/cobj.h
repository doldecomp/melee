#ifndef _cobj_h_
#define _cobj_h_

#include <global.h>

#include <dolphin/types.h>

#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/wobj.h>

#define PROJ_PERSPECTIVE 1
#define PROJ_FRUSTRUM 2
#define PROJ_ORTHO 3

typedef struct _HSD_CObj
{
    HSD_Obj parent;
    u32 flags;                      // 0x08
    f32 viewport_left;              // 0x0C
    f32 viewport_right;             // 0x10
    f32 viewport_top;               // 0x14
    f32 viewport_bottom;            // 0x18
    u16 scissor_left;               // 0x1C
    u16 scissor_right;              // 0x1E
    u16 scissor_top;                // 0x20
    u16 scissor_bottom;             // 0x22
    struct _HSD_WObj *eye_position; // 0x24
    struct _HSD_WObj *interest;     // 0x28
    union
    {
        f32 roll; // 0x2C
        Vec up;   // 0x2C - 0x34
    } u;
    f32 near; // 0x38
    f32 far;  // 0x3C
    union
    {
        struct
        {
            f32 fov;
            f32 aspect;
        } perspective;

        struct
        {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustrum;

        struct
        {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
    u8 projection_type;     // 0x50
    Mtx view_mtx;           // 0x54
    struct _HSD_AObj *aobj; // 0x84
    Mtx *proj_mtx;          // 0x88
} HSD_CObj;

typedef struct _HSD_CObjDesc
{
    char *class_name;                    // 0x00
    u16 flags;                           // 0x04
    u16 projection_type;                 // 0x06
    u16 viewport_left;                   // 0x08
    u16 viewport_right;                  // 0x0A
    u16 viewport_top;                    // 0x0C
    u16 viewport_bottom;                 // 0x0E
    u32 scissor_lr;                      // 0x10
    u32 scissor_tb;                      // 0x14
    struct _HSD_WObjDesc *eye_desc;      // 0x18
    struct _HSD_WObjDesc *interest_desc; // 0x1C
    f32 roll;                            // 0x20
    Vec *vector;                         // 0x24
    f32 near;                            // 0x28
    f32 far;                             // 0x2C
    union
    {
        struct
        {
            f32 fov;
            f32 aspect;
        } perspective;

        struct
        {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } frustrum;

        struct
        {
            f32 top;
            f32 bottom;
            f32 left;
            f32 right;
        } ortho;
    } projection_param;
} HSD_CObjDesc;

typedef struct _HSD_CObjInfo
{
    HSD_ObjInfo parent;
    int (*load)(HSD_CObj *cobj, HSD_CObjDesc *desc);
} HSD_CObjInfo;

typedef struct _HSD_CameraAnim
{
    struct _HSD_AObjDesc *aobjdesc;
    struct _HSD_WObjAnim *eye_anim;
    struct _HSD_WObjAnim *interest_anim;
} HSD_CameraAnim;

STRUCT_PLACEHOLDER(cobj, 1)
CALLBACK_PLACEHOLDER(cobj, 1)

void HSD_CObjEraseScreen(HSD_CObj *cobj, s32 enable_color, s32 enable_alpha, s32 enable_depth);
void HSD_CObjRemoveAnim(HSD_CObj *cobj);
HSD_WObj *HSD_CObjGetEyePositionWObj(HSD_CObj *cobj);
HSD_WObj *HSD_CObjGetInterestWObj(HSD_CObj *cobj);
void func_8036A194(HSD_CObj *cobj, f32, f32, f32, f32);
unk_t func_8036A590(cobj_Unk1 *);
HSD_CObj *HSD_CObjAlloc();
void func_80368718(HSD_CObj *cobj, s32 *);
void func_803687F0(HSD_CObj *cobj, s32 *);
void func_803699C0(HSD_CObj *cobj, f32);
void func_80369FA0(HSD_CObj *cobj, f32);
void func_80369FC8(HSD_CObj *cobj, f32);
void func_80369FF4(HSD_CObj *cobj, s16 *);
void func_8036A058(HSD_CObj *cobj, s16 *);
void func_8036A144(u32);
BOOL func_80368458(HSD_Obj *, cobj_UnkCallback1);
void func_80368608();
void func_803695F0(unk_t);

#endif

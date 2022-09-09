#ifndef SYSDOLPHIN_BASELIB_FOG_H
#define SYSDOLPHIN_BASELIB_FOG_H

#include <dolphin/types.h>

#include <sysdolphin/baselib/object.h>

typedef struct _HSD_FogAdj {
    HSD_Obj parent;
    s16 center; // 0x08
    u16 width; // 0xA
    Mtx44 mtx; // 0x0C
    struct _HSD_AObj* aobj;
} HSD_FogAdj;

typedef struct _HSD_Fog {
    HSD_Obj parent;
    u32 type; // 0x08
    struct _HSD_FogAdj* fog_adj; // 0x0C
    f32 start; // 0x10
    f32 end; // 0x14
    GXColor color; // 0x18
    struct _HSD_AObj* aobj; // 0x1C
} HSD_Fog;

typedef struct _HSD_FogAdjDesc {
    u16 center; // 0x00
    u16 width; // 0x02
    Mtx44 mtx; // 0x04
} HSD_FogAdjDesc;

typedef struct _HSD_FogInfo {
    HSD_ObjInfo parent;
} HSD_FogInfo;

typedef struct _HSD_FogAdjInfo {
    HSD_ObjInfo parent;
} HSD_FogAdjInfo;

typedef struct _HSD_FogDesc {
    u32 type;
    struct _HSD_FogAdjDesc* fogadjdesc; // 0x04
    f32 start;
    f32 end;
    GXColor color;
} HSD_FogDesc;

void HSD_FogSet(HSD_Fog*);
HSD_FogAdj* HSD_FogAdjLoadDesc(HSD_FogAdjDesc*);
void HSD_FogInit(HSD_Fog*, HSD_FogDesc*);
void HSD_FogAdjInit(HSD_FogAdj*, HSD_FogAdjDesc*);
void HSD_FogReqAnimByFlags(HSD_Fog*, u32 flags, f32 frame);
void FogUpdateFunc();

#endif

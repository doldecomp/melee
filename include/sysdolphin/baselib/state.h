#ifndef SYSDOLPHIN_BASELIB_STATE_H
#define SYSDOLPHIN_BASELIB_STATE_H

#include <sysdolphin/baselib/mobj.h>

void HSD_StateSetZMode(u32, u32, u32);
void HSD_StateInvalidate(s32);
void func_80361E8C(s32);
HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe);
HSD_SetMaterialShininess(HSD_Material* mat, f32 shininess);
HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular, HSD_Material* mat, f32 alpha);

#endif

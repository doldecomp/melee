#ifndef SYSDOLPHIN_BASELIB_S
#define SYSDOLPHIN_BASELIB_S

#include <dolphin/gx/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <Runtime/platform.h>

void HSD_StateSetZMode(u32, u32, u32);
void HSD_StateInvalidate(s32);
void func_80361E8C(s32);
void HSD_SetupRenderMode(u32);
void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular,
                          HSD_Material* mat, f32 alpha);
void HSD_SetMaterialShininess(HSD_Material* mat, f32 shininess);
void HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe);

#endif

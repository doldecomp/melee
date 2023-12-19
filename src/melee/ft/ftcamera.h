#ifndef MELEE_FT_FTCAMERA_H
#define MELEE_FT_FTCAMERA_H

#include "ft/forward.h"

#include "ft/fighter.h"

void ftCamera_UpdateCameraBox(HSD_GObj* gobj);
void ftCamera_80076018(UnkFloat6_Camera* in, UnkFloat6_Camera* out, f32 mul);
void ftCamera_80076064(Fighter*);
void ftCamera_800762F4(HSD_GObj* gobj);
void ftCamera_80076320(HSD_GObj* gobj);

#endif

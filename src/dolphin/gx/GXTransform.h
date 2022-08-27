#ifndef DOLPHIN_GX_GXTRANSFORM_H
#define DOLPHIN_GX_GXTRANSFORM_H

#include <dolphin/types.h>

void GXProject(
	f32 x, // model coordinates
	f32 y,
	f32 z,
	f32 mtx[3][4], // model-view matrix
	f32 *pm,	   // projection matrix, as returned by GXGetProjectionv
	f32 *vp,	   // viewport, as returned by GXGetViewportv
	f32 *sx,	   // screen coordinates
	f32 *sy,
	f32 *sz);

#endif

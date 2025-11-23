#ifndef __GALE01_04D164
#define __GALE01_04D164

#include "mplib.h" // IWYU pragma: export

#include <placeholder.h>

#include "mp/forward.h"

static struct {
    float top;
    float bottom;
    float left;
    float right;
} mpLib_80458868[2];

/* 04E97C */ static bool mpLineIntersection(float a0x, float a0y, float a1x,
                                            float a1y, float b0x, float b0y,
                                            float b1x, float b1y, float* int_x,
                                            float* int_y);
/* 4D64B0 */ static bool didCheckBounding;
/* 4D64B4 */ static MapCollData* mpLib_804D64B4;
/* 4D64B8 */ static CollVtx* groundCollVtx;
/* 4D64BC */ static CollLine* groundCollLine;
/* 4D64C0 */ static CollJoint* groundCollJoint;
/* 4D64C4 */ static CollJoint* jointListStart;
/* 4D64C8 */ static CollJoint* jointListEnd;
/* 4D64CC */ static s32 mpLib_804D64CC;
/* 4D64D0 */ static s32 mpLib_804D64D0;
/* 4D64D4 */ static s32 mpLib_804D64D4;
/* 4D64D8 */ static s32 mpLib_804D64D8;
/* 4D64DC */ static s32 mpLib_804D64DC;
/* 4D64E0 */ static s32 mpLib_804D64E0;
/* 4D64E4 */ static s32 mpLib_804D64E4;
/* 458888 */ static Vec3 mpLib_80458888[0x200];

#endif

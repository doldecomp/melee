#ifndef MELEE_MP_FORWARD_H
#define MELEE_MP_FORWARD_H

#include <platform.h>
#include "ft/forward.h"

typedef void (*mpLib_Callback)(s32, s32, CollData*, s32, s32, f32);
typedef bool (*mpColl_Callback)(CollData*, u32);

#endif

#ifndef _item_h_
#define _item_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include <functions.h>
#include <melee/pl/player.h>
#include <melee/gr/stage.h>
#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include "sysdolphin/baselib/controller.h"

typedef struct {
	void* x0_common_attr;
	void* x4_ext_attr;
} ItemData;

typedef struct {
	u8 padding_x0[0xC4];
	ItemData* xC4_data;
} Item;

#endif
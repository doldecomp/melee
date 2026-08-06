// IWYU pragma: begin_exports
#include "grdisplay.h"
#include "ground.h"
#include "grpura.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "stage.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"
#include "cm/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbspdisplay.h"
#include "mp/mplib.h"

#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <baselib/tobj.h>

struct GrPuModelDesc {
    /* 0x0 */ s32 x0;
    /* 0x4 */ f32 x4;
    /* 0x8 */ s32 x8;
};

struct GrPuVtxMapEntry {
    /* 0x00 */ s16 x00;
    /* 0x02 */ s16 x02;
    /* 0x04 */ s16 x04;
    /* 0x06 */ s16 x06;
    /* 0x08 */ HSD_JObj* x08;
};

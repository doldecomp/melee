// IWYU pragma: begin_keep
#include <placeholder.h>
#include <platform.h>

#include "baselib/debug.h"

#include "baselib/forward.h"

#include "baselib/gobjproc.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"

#include "gr/forward.h"

#include "gr/grdatfiles.h"
#include "gr/gricemt.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 1F9338 */ static void fn_801F9338(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);
/* 1F9448 */ static void fn_801F9448(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);
/* 1F9558 */ static void fn_801F9558(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);
/* 1F8C64 */ static void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2,
                                     HSD_GObj* u3, f32 u4);
/* 1F91EC */ static void
grIceMt_801F91EC(HSD_GObj* param_1, s16* param_2, int param_3, int param_4,
                 int param_5, int param_6, int param_7,
                 mpLib_JointCollisionCallback param_8);
/* 1FA7F0 */ static void grIceMt_801FA7F0(void* user_data, int joint_id,
                                          CollData* coll, int coll_x50,
                                          mpLib_GroundEnum ground_kind,
                                          float delta_y);

static const Vec3 grIm_803B8220[] = {
    { 0.0, 0.0, 0.0 },    { -8.0, 15.0, 0.0 }, { 8.0, 15.0, 0.0 },
    { -24.0, 15.0, 0.0 }, { 24.0, 15.0, 0.0 },
};

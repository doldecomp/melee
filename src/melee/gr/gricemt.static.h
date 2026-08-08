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

/* 1F8C64 */ static void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2,
                                     HSD_GObj* u3, f32 u4);
/* 1F91EC */ static void
grIceMt_801F91EC(HSD_GObj* param_1, s16* param_2, int param_3, int param_4,
                 int param_5, int param_6, int param_7,
                 mpLib_JointCollisionCallback param_8);
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
/* 1F96E0 */ static float grIceMt_801F96E0(struct grIceMt_GObj9_GObj10_x0*,
                                           float);
/* 1FA7F0 */ static void grIceMt_801FA7F0(void* user_data, int joint_id,
                                          CollData* coll, int coll_x50,
                                          mpLib_GroundEnum ground_kind,
                                          float delta_y);

struct grIceMt_YakumonoParam {
    s16 x0;
    s16 x2;
    s16 x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    s16 x34;
    s16 x36;
    s16 x38;
    u16 x3A;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    float x50;
    float x54;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    float x6C;
    float x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90;
    float x94;
    s16 ft_max_y;
    s16 x9E;
    float x9C;
    float xA0;
    s16 xA4;
    s16 xA6;
    s16 xA8;
    s16* xAC;
    s16* xB0;
    s16* xB4;
    s16 xB8;
    s16 pad;
    grZakoGenerator_SpawnDesc xBC;
    float xC0;
    float xC4;
    float xC8;
    float xCC;
};

static const Vec3 grIm_803B8220[] = {
    { 0.0f, 0.0f, 0.0f },    { -8.0f, 15.0f, 0.0f }, { 8.0f, 15.0f, 0.0f },
    { -24.0f, 15.0f, 0.0f }, { 24.0f, 15.0f, 0.0f },
};

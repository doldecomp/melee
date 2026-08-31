#ifndef LBSPDISPLAY_1_H
#define LBSPDISPLAY_1_H

#include <placeholder.h>
#include <platform.h>

#include "ft/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx.h>

/* 00F9F8 */ void lb_8000F9F8(HSD_JObj* jobj);
/* 00FA94 */ void lb_8000FA94(void);
/* 00FCDC */ void lb_8000FCDC(void);
/* 00FD18 */ void lb_8000FD18(DynamicsDesc*);
/* 00FD48 */ void lb_8000FD48(HSD_JObj*, DynamicsDesc*, size_t);
/* 0100B0 */ struct lb_80011A50_t* lb_800100B0(struct lb_80011A50_t*, float);
/* 0101C8 */ float lb_800101C8(Vec3*, Vec3*);
/* 0103B8 */ float lb_800103B8(Vec3*, Vec3*);
/* 01044C */ void lb_8001044C(DynamicsDesc*, UNK_T, int, float pos_y, bool,
                              Fighter_Part part, int, bool);
/* 0115F4 */ void lb_800115F4(void);
/* 011710 */ void lb_80011710(DynamicsDesc*, DynamicsDesc*);
/* 0117F4 */ bool lb_800117F4(DynamicsDesc*, GXColor*, GXColor*, int, u32);
/* 0119DC */ void lb_800119DC(Vec3*, int, float, float, float);
/* 011A50 */ struct lb_80011A50_t* lb_80011A50(Vec3*, int, float, float, float,
                                               float, float, float, float);
/* 011ABC */ enum_t lb_80011ABC(void);
/* 013BB0 */ bool lb_80013BB0(ColorOverlay* arg);

#endif

#ifndef GALE01_00F9F8
#define GALE01_00F9F8

#include <platform.h>

#include "dolphin/gx.h"

#include <baselib/forward.h>
#include <melee/sc/forward.h>

/* 011AC4 */ HSD_LObj* lb_80011AC4(LightList**);
/* 011B74 */ void lb_80011B74(HSD_DObj* dobj, u32 flags);
/* 011C18 */ void lb_80011C18(HSD_JObj* jobj, u32 flags);
/* 011E24 */ int lb_80011E24(HSD_JObj*, HSD_JObj**, ...);
/* 01204C */ int lb_8001204C(HSD_JObj*, HSD_JObj**, u16*, int);
/* 0121FC */ HSD_ImageDesc* lb_800121FC(HSD_ImageDesc* image_desc, int width,
                                        int height, GXTexFmt format,
                                        s16 entry_num);
/* 0122C8 */ void lb_800122C8(HSD_ImageDesc* image_desc, u16 origx, u16 origy,
                              bool clear);
/* 0122F0 */ void lb_800122F0(HSD_ImageDesc*, GXTexObj*, f32);
/* 01271C */ void lb_8001271C(GXTexObj*, float, float, float, float, float,
                              float);
/* 01285C */ void lb_8001285C(HSD_ImageDesc*, GXTexObj*);
/* 012994 */ void lb_80012994(HSD_ImageDesc*, u8, u8, float, float, float,
                              float, float);
/* 013614 */ void fn_80013614(HSD_GObj*);
/* 0138AC */ void fn_800138AC(void* ptr);
/* 0138CC */ void lb_800138CC(HSD_GObj* gobj, HSD_GObjEvent arg1);
/* 0138D8 */ void lb_800138D8(HSD_GObj* gobj, s8 arg1);
/* 0138EC */ void lb_800138EC(s32 arg0, GObj_RenderFunc render_func, u32 arg2,
                              s8 arg3, f32 x, f32 y, f32 w, f32 h);
/* 013B14 */ HSD_CObj* lb_80013B14(HSD_CameraDescPerspective*);

#endif

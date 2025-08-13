#ifndef GALE01_00F9F8
#define GALE01_00F9F8

#include <placeholder.h>
#include <platform.h>

#include "dolphin/gx.h"

#include "ft/forward.h"
#include "lb/forward.h"

#include "lb/types.h"

#include <baselib/forward.h>
#include <melee/sc/forward.h>

#include <dolphin/mtx.h>

/* 00F9F8 */ void lb_8000F9F8(HSD_JObj* jobj);
/* 00FA94 */ UNK_RET lb_8000FA94(UNK_PARAMS);
/* 00FCDC */ void lb_8000FCDC(void);
/* 00FD18 */ void lb_8000FD18(DynamicsDesc*);
/* 00FD48 */ void lb_8000FD48(HSD_JObj*, DynamicsDesc*, size_t);
/* 0100B0 */ struct lb_80011A50_t* lb_800100B0(struct lb_80011A50_t*, float);
/* 0101C8 */ UNK_RET lb_800101C8(UNK_PARAMS);
/* 0103B8 */ UNK_RET lb_800103B8(UNK_PARAMS);
/* 01044C */ void lb_8001044C(DynamicsDesc*, UNK_T, int, float pos_y, bool,
                              Fighter_Part part, int, bool);
/* 0115F4 */ void lb_800115F4(void);
/* 011710 */ void lb_80011710(DynamicsDesc*, DynamicsDesc*);
/* 0117F4 */ bool lb_800117F4(UNK_T, float*, float*, u32, int);
/* 0119DC */ void lb_800119DC(Vec3*, int, float, float, float);
/* 011A50 */ void lb_80011A50(Vec3*, int, float, float, float, float, float,
                              float, float);
/* 011ABC */ enum_t lb_80011ABC(void);
/* 011AC4 */ HSD_LObj* lb_80011AC4(LightList**);
/* 011C18 */ void lb_80011C18(HSD_JObj* jobj, u32 flags);
/* 011E24 */ int lb_80011E24(HSD_JObj*, HSD_JObj**, ...);
/* 01204C */ void lb_8001204C(HSD_JObj*, HSD_JObj**, u16*, int);
/* 0121FC */ HSD_ImageDesc* lb_800121FC(HSD_ImageDesc* image_desc, int width,
                                        int height, GXTexFmt format,
                                        s16 entry_num);
/* 0122C8 */ void lb_800122C8(HSD_ImageDesc*, u16, u16,
                              int); ///< #HSD_ImageDescCopyFromEFB wrapper
/* 0122F0 */ UNK_RET lb_800122F0(UNK_PARAMS);
/* 01271C */ UNK_RET lb_8001271C(UNK_PARAMS);
/* 01285C */ UNK_RET lb_8001285C(UNK_PARAMS);
/* 012994 */ UNK_RET lb_80012994(UNK_PARAMS);
/* 013614 */ UNK_RET fn_80013614(UNK_PARAMS);
/* 0138AC */ void fn_800138AC(void* ptr); ///< #HSD_Free wrapper
/* 0138CC */ void lb_800138CC(HSD_GObj* gobj, int arg1);
/* 0138D8 */ void lb_800138D8(HSD_GObj* gobj, s8 arg1);
/* 0138EC */ UNK_RET lb_800138EC(UNK_PARAMS);
/* 013B14 */ HSD_CObj* lb_80013B14(HSD_CameraDescPerspective*);
/* 013C18 */ UNK_RET lb_80013C18(UNK_PARAMS);
/* 013D68 */ int lb_80013D68(ColorOverlay*);
/* 013E3C */ UNK_RET lb_80013E3C(UNK_PARAMS);
/* 013F78 */ int lb_80013F78(
    ColorOverlay*); ///< Copy light rotation from #ColorOverlay::x8_ptr1
/* 014014 */ int lb_80014014(ColorOverlay*);
/* 0140F8 */ UNK_RET lb_800140F8(UNK_PARAMS);
/* 014258 */ bool lb_80014258(HSD_GObj* gobj, void* arg1, FtCmd cmd);
/* 014498 */ void lb_80014498(ColorOverlay*);
/* 0144C8 */ bool lb_800144C8(ColorOverlay*, struct Fighter_804D653C_t*, int,
                              int);
/* 014534 */ UNK_RET lb_80014534(UNK_PARAMS);
/* 014574 */ void lb_80014574(u8, int, int, int);
/* 0145C0 */ void lb_800145C0(u8 slot); ///< Reset pad rumble
/* 0145F4 */ void lb_800145F4(void);
/* 014638 */ bool lb_80014638(Vec3*, UNK_T);
/* 014770 */ bool lb_80014770(Vec3*, int);
/* 0149E0 */ bool lb_800149E0(Mtx, u32);

#endif

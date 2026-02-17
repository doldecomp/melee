#ifndef MELEE_MN_SNAP_H
#define MELEE_MN_SNAP_H

#include <placeholder.h>
#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/gx.h>

/* 253184 */ void mnSnap_80253184(void);
/* 253640 */ void mnSnap_80253640(s32 page);
/* 253964 */ void mnSnap_80253964(void);
/* 253AE4 */ void mnSnap_80253AE4(s32 mode);
/* 253BE0 */ s32 mnSnap_80253BE0(u64 buttons, s32* cursor, s32 count);
/* 253DB4 */ void fn_80253DB4(HSD_GObj* gobj, s32 rendermode);
/* 253DE8 */ void fn_80253DE8(HSD_GObj* gobj, s32 rendermode);
/* 253E1C */ void fn_80253E1C(HSD_GObj* gobj, s32 rendermode);
/* 253E5C */ void fn_80253E5C(HSD_GObj* gobj, s32 rendermode);
/* 253E90 */ void mnSnap_80253E90(s32 idx);
/* 253F60 */ void mnSnap_80253F60(void);
/* 254014 */ void mnSnap_80254014(void);
/* 25409C */ void mnSnap_8025409C(HSD_JObj* jobj_flag);
/* 254298 */ void mnSnap_80254298(void);
/* 25441C */ s32 mnSnap_8025441C(u64 buttons);
/* 2545C4 */ void fn_802545C4(void);
/* 257D7C */ void fn_80257D7C(void);
/* 257F24 */ void mnSnap_80257F24(void);

#endif

#ifndef GALE01_1F6868
#define GALE01_1F6868

#include <platform.h>
#include <placeholder.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include "mp/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

typedef struct IceMountainParams {
    float x0;
    int x4;
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
    float x34;
    u16 x38;
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
    float x98;
    float x9C;
    float xA0;
    float xA4;
    float xA8;
    HSD_GObj* xAC;
    float xB0;
    float xB4;
    s16 xB8;
    bool xBC;
    float xC0;
    float xC4;
    float xC8;
    float xCC;
} IceMountainParams;

/* 1F6868 */ void grIceMt_801F6868(int id);
/* 1F686C */ void grIceMt_801F686C(void);
/* 1F7080 */ void grIceMt_801F7080(void);
/* 1F71DC */ void grIceMt_801F71DC(void);
/* 1F71E0 */ bool grIceMt_801F71E0(void);
/* 1F71E8 */ HSD_GObj* grIceMt_801F71E8(int gobj_id);
/* 1F72D4 */ void grIceMt_801F72D4(Ground_GObj*);
/* 1F75DC */ bool grIceMt_801F75DC(Ground_GObj*);
/* 1F75E4 */ void grIceMt_801F75E4(Ground_GObj*);
/* 1F75E8 */ void grIceMt_801F75E8(Ground_GObj*);
/* 1F75EC */ void fn_801F75EC(Ground_GObj*);
/* 1F75FC */ void grIceMt_801F75FC(Ground_GObj*);
/* 1F7720 */ bool grIceMt_801F7720(Ground_GObj*);
/* 1F7728 */ void grIceMt_801F7728(Ground_GObj*);
/* 1F77AC */ void grIceMt_801F77AC(Ground_GObj*);
/* 1F77B0 */ void fn_801F77B0(Ground_GObj*);
/* 1F785C */ void grIceMt_801F785C(Ground_GObj*);
/* 1F796C */ bool grIceMt_801F796C(Ground_GObj*);
/* 1F7A2C */ void grIceMt_801F7A2C(Ground_GObj*);
/* 1F7D90 */ void grIceMt_801F7D90(Ground_GObj*);
/* 1F7D94 */ void grIceMt_801F7D94(Ground_GObj*);
/* 1F7EE0 */ bool grIceMt_801F7EE0(Ground_GObj*);
/* 1F7EE8 */ void grIceMt_801F7EE8(Ground_GObj*);
/* 1F7F1C */ void grIceMt_801F7F1C(Ground_GObj*);
/* 1F7F70 */ void grIceMt_801F7F70(Ground_GObj*);
/* 1F8154 */ bool grIceMt_801F8154(Ground_GObj*);
/* 1F815C */ void grIceMt_801F815C(Ground_GObj*);
/* 1F81B4 */ void grIceMt_801F81B4(Ground_GObj*);
/* 1F8208 */ void grIceMt_801F8208(Ground_GObj*);
/* 1F835C */ bool grIceMt_801F835C(Ground_GObj*);
/* 1F8364 */ void grIceMt_801F8364(Ground_GObj*);
/* 1F8398 */ void grIceMt_801F8398(Ground_GObj*);
/* 1F83EC */ void grIceMt_801F83EC(Ground_GObj*);
/* 1F85BC */ bool grIceMt_801F85BC(HSD_GObj* param1);
/* 1F85C4 */ void grIceMt_801F85C4(Ground_GObj*);
/* 1F8608 */ void grIceMt_801F8608(Ground_GObj*);
/* 1F865C */ void grIceMt_801F865C(Ground_GObj*);
/* 1F87C0 */ bool grIceMt_801F87C0(Ground_GObj*);
/* 1F87C8 */ void grIceMt_801F87C8(Ground_GObj*);
/* 1F87FC */ void grIceMt_801F87FC(Ground_GObj*);
/* 1F8850 */ void grIceMt_801F8850(Ground_GObj*);
/* 1F89A4 */ bool grIceMt_801F89A4(Ground_GObj*);
/* 1F89AC */ void grIceMt_801F89AC(Ground_GObj*);
/* 1F89E0 */ void grIceMt_801F89E0(Ground_GObj*);
/* 1F8A34 */ void grIceMt_801F8A34(Ground_GObj*);
/* 1F8B08 */ bool grIceMt_801F8B08(Ground_GObj*);
/* 1F8B10 */ void grIceMt_801F8B10(Ground_GObj*);
/* 1F8C60 */ void grIceMt_801F8C60(Ground_GObj*);
/* 1F8C64 */ // void fn_801F8C64(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32);
/* 1F8CDC */ UNK_RET grIceMt_801F8CDC(Ground_GObj*);
/* 1F8E58 */ UNK_RET fn_801F8E58(Ground_GObj*);
/* 1F9038 */ UNK_RET fn_801F9038(Ground_GObj*);
/* 1F9150 */ IceMountainParams* fn_801F9150(HSD_GObj*);
/* 1F91A4 */ void fn_801F91A4(UNK_PARAMS);
/* 1F91A8 */ HSD_GObj* fn_801F91A8(HSD_GObj*);
/* 1F91EC */ UNK_RET grIceMt_801F91EC(HSD_GObj*);
/* 1F929C */ UNK_RET grIceMt_801F929C(HSD_GObj* arg0);
/* 1F9338 */ UNK_RET fn_801F9338(Ground*, UNK_T, UNK_T, UNK_T,
                                 mpLib_GroundEnum);
/* 1F9448 */ UNK_RET fn_801F9448(Ground*, UNK_T, UNK_T, UNK_T,
                                 mpLib_GroundEnum);
/* 1F9558 */ UNK_RET fn_801F9558(Ground*, UNK_T, UNK_T, UNK_T,
                                 mpLib_GroundEnum);
/* 1F9668 */ void grIceMt_801F9668(float);
/* 1F96E0 */ float grIceMt_801F96E0(float);
/* 1F98A8 */ bool grIceMt_801F98A8(HSD_GObj* param1);
/* 1F993C */ UNK_RET grIceMt_801F993C(UNK_PARAMS);
/* 1F9ACC */ UNK_RET grIceMt_801F9ACC(float);
/* 1FA0BC */ UNK_RET grIceMt_801FA0BC(int);
/* 1FA364 */ void grIceMt_801FA364(UNK_T, float*, HSD_GObjEvent, Ground_GObj*);
/* 1FA4CC */ int fn_801FA4CC(int num);
/* 1FA500 */ int grIceMt_801FA500(HSD_GObj*);
/* 1FA6D8 */ UNK_RET grIceMt_801FA6D8(Ground_GObj*);
/* 1FA728 */ void grIceMt_801FA728(Vec3*);
/* 1FA7F0 */ UNK_RET grIceMt_801FA7F0(Ground*, UNK_T, UNK_T, UNK_T,
                                      mpLib_GroundEnum);
/* 1FA854 */ UNK_RET grIceMt_801FA854(void);
/* 1FA8F8 */ DynamicsDesc* grIceMt_801FA8F8(int id);
/* 1FA900 */ bool grIceMt_801FA900(Vec3* a, int id, HSD_JObj* jobj);

#endif

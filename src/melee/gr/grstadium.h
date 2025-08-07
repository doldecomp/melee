#ifndef MELEE_GR_STADIUM_H
#define MELEE_GR_STADIUM_H

#include <placeholder.h>

#include <dolphin/mtx.h>
#include <melee/gr/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

typedef enum {
    PsType_Display = 1,
} StadiumGrType;

/* 1D1018 */ void grStadium_801D1018(bool);
/* 1D101C */ void grStadium_801D101C(void);
/* 1D10C8 */ void grStadium_801D10C8(void);
/* 1D10CC */ void grStadium_801D10CC(void);
/* 1D10F0 */ bool grStadium_801D10F0(void);
/* 1D10F8 */ Ground_GObj* grStadium_801D10F8(StadiumGrType);
/* 1D11E4 */ void fn_801D11E4(Ground_GObj*);
/* 1D1290 */ void grStadium_801D1290(Ground_GObj*);
/* 1D1388 */ bool grStadium_801D1388(Ground_GObj* gobj);
/* 1D1390 */ void grStadium_801D1390(Ground_GObj*);
/* 1D13C4 */ void grStadium_801D13C4(Ground_GObj*);
/* 1D13C8 */ void fn_801D13C8(Ground_GObj*);
/* 1D13E0 */ void grStadium_801D13E0(Ground_GObj*);
/* 1D1518 */ bool grStadium_801D1518(Ground_GObj*);
/* 1D1520 */ void grStadium_801D1520(Ground_GObj*);
/* 1D156C */ void grStadium_801D156C(Ground_GObj*);
/* 1D1570 */ void grStadium_801D1570(Ground_GObj*);
/* 1D15FC */ bool grStadium_801D15FC(Ground_GObj*);
/* 1D1604 */ void grStadium_801D1604(Ground_GObj*);
/* 1D1624 */ void grStadium_801D1624(Ground_GObj*);
/* 1D1648 */ void grStadium_801D1648(Ground_GObj*);
/* 1D16D4 */ bool grStadium_801D16D4(Ground_GObj*);
/* 1D16DC */ void grStadium_801D16DC(Ground_GObj*);
/* 1D16FC */ void grStadium_801D16FC(Ground_GObj*);
/* 1D1720 */ void grStadium_801D1720(Ground_GObj*);
/* 1D17E0 */ bool grStadium_801D17E0(Ground_GObj*);
/* 1D17E8 */ void grStadium_801D17E8(Ground_GObj*);
/* 1D1808 */ void grStadium_801D1808(Ground_GObj*);
/* 1D1840 */ void grStadium_801D1840(Ground_GObj*);
/* 1D19D0 */ bool grStadium_801D19D0(Ground_GObj*);
/* 1D19D8 */ void grStadium_801D19D8(Ground_GObj*);
/* 1D19F8 */ void grStadium_801D19F8(Ground_GObj*);
/* 1D1A38 */ void grStadium_801D1A38(Ground_GObj*);
/* 1D1B40 */ bool grStadium_801D1B40(Ground_GObj*);
/* 1D1B48 */ void grStadium_801D1B48(Ground_GObj*);
/* 1D1D84 */ void grStadium_801D1D84(Ground_GObj*);
/* 1D1DE4 */ void grStadium_801D1DE4(Ground_GObj*);
/* 1D1E10 */ bool grStadium_801D1E10(Ground_GObj*);
/* 1D1E18 */ void grStadium_801D1E18(Ground_GObj*);
/* 1D1E1C */ void grStadium_801D1E1C(Ground_GObj*);
/* 1D1E20 */ void grStadium_801D1E20(void);
/* 1D1EF8 */ void grStadium_801D1EF8(Ground_GObj*);
/* 1D21E4 */ void grStadium_801D21E4(Ground_GObj*, bool);
/* 1D2278 */ void grStadium_801D2278(Ground_GObj*);
/* 1D2344 */ void grStadium_801D2344(Ground_GObj*);
/* 1D2528 */ void grStadium_801D2528(Ground_GObj*, int, int);
/* 1D2A60 */ void grStadium_801D2A60(Ground_GObj*);
/* 1D2BEC */ HSD_GObj* grStadium_801D2BEC(void);
/* 1D2D78 */ HSD_GObj* grStadium_801D2D78(void);
/* 1D2E24 */ HSD_GObj* grStadium_801D2E24(void);
/* 1D2ED0 */ void fn_801D2ED0(HSD_GObj*, int);
/* 1D2FD0 */ void fn_801D2FD0(HSD_GObj*, int);
/* 1D3084 */ void fn_801D3084(HSD_GObj*, int);
/* 1D3138 */ HSD_TObj* grStadium_801D3138(Ground_GObj*, HSD_ImageDesc*, HSD_MObj**);
/* 1D32D0 */ bool grStadium_801D32D0(Ground_GObj*);
/* 1D3460 */ void grStadium_801D3460(Ground_GObj*);
/* 1D384C */ void grStadium_801D384C(Ground_GObj*);
/* 1D39A0 */ void grStadium_801D39A0(Ground_GObj*);
/* 1D3A0C */ void grStadium_801D3A0C(Ground_GObj*);
/* 1D3B4C */ void grStadium_801D3B4C(int, int);
/* 1D3BBC */ void grStadium_801D3BBC(Ground_GObj*);
/* 1D3F40 */ void grStadium_801D3F40(Ground_GObj*, int);
/* 1D4040 */ UNK_RET grStadium_801D4040(UNK_PARAMS);
/* 1D4084 */ UNK_RET grStadium_801D4084(UNK_PARAMS);
/* 1D40C8 */ UNK_RET grStadium_801D40C8(UNK_PARAMS);
/* 1D410C */ UNK_RET grStadium_801D410C(UNK_PARAMS);
/* 1D4150 */ UNK_RET grStadium_801D4150(UNK_PARAMS);
/* 1D4194 */ void grStadium_801D4194(Ground_GObj*);
/* 1D4220 */ void fn_801D4220(UNK_T, int, UNK_T, bool);
/* 1D42B8 */ bool grStadium_801D42B8(void);
/* 1D4354 */ Ground* grStadium_801D4354(Ground_GObj*);
/* 1D435C */ void grStadium_801D435C(Ground_GObj*);
/* 1D4548 */ void grStadium_801D4548(Ground_GObj*);
/* 1D4FF8 */ bool grStadium_801D4FF8(int pl_slot);
/* 1D5074 */ void fn_801D5074(Ground_GObj*, int);
/* 1D50B8 */ DynamicsDesc* grStadium_801D50B8(enum_t);
/* 1D50C0 */ bool grStadium_801D50C0(Vec3*, int, HSD_JObj*);
/* 1D511C */ void grStadium_801D511C(void);

#endif

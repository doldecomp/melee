#include "sc/forward.h"

#include <baselib/gobj.h>

struct IfStockUserData {
    unsigned char player;
    unsigned char mode;
};
#define GET_IFSTOCK(gobj) ((struct IfStockUserData*) HSD_GObjGetUserData(gobj))

struct ifStock_804A1378_per_player {
    HSD_GObj* x0;
    HSD_JObj*(x4[8]);
    HSD_JObj* x24;
    HSD_JObj* x28;
    HSD_JObj* x2C;
    HSD_JObj* x30;
    HSD_JObj* x34;
    HSD_JObj* x38;
    HSD_JObj* x3C;
    HSD_JObj* x40;
    HSD_JObj* x44;
    int coins;
    int stocks;
};

/// @todo merge with IfStockUserData
struct ifStock_804A1378_x204 {
    unsigned char x0[0x54];
};

struct ifStock_804A1378 {
    DynamicModelDesc** x0;
    DynamicModelDesc* x4;
    struct ifStock_804A1378_per_player player[6];
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    char pad1F0[0x1F4 - 0x1F0];
    HSD_JObj* jobj_a;
    HSD_JObj* jobj_b;
    HSD_JObj* jobj_c;
    HSD_JObj* jobj_d;
    struct ifStock_804A1378_x204 x204[6];
};

struct ifStock_804A1774 {
    char x0;
    signed char x1[130];
    signed char x83[133];
    int x108;
    HSD_GObj* x10C[131];
};

struct ifStock_804A1ACC {
    char x0;
    signed char x1[130];
    signed char x83[133];
    int x108;
    HSD_GObj* x10C[130];
};

/// .bss
struct ifStock_804A1378 ifStock_804A1378;
struct ifStock_804A1774 ifStock_804A1774;
HSD_GObj* ifStock_804A1A8C[16];
struct ifStock_804A1ACC ifStock_804A1ACC;

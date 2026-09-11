#ifndef GALE01_1D5238
#define GALE01_1D5238

#include <Runtime/platform.h>

#include <melee/gr/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <melee/gr/types.h>

extern GrJoint grKg_803E16E0[6];
extern StageCallbacks grKg_StageCallbacks[12];

/// A dat file index and the index of a spline within that file's
/// spline table, as taken by #Ground_801C247C.
typedef struct grKg_SplineChoice {
    s32 file;
    s32 spline;
} grKg_SplineChoice;

typedef struct grKg_SplineChoiceList {
    grKg_SplineChoice pairs[3];
    s32 terminator;
} grKg_SplineChoiceList;

struct grKongo_YakumonoParam {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    s32 unk64;
    s32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    void* unk84;
    f32 unk88;
    f32 unk8C;
    f32 unk90;
    f32 unk94;
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    f32 unkA4;
    f32 unkA8;
    f32 unkAC;
    f32 unkB0;
    f32 unkB4;
    f32 unkB8;
};

extern const grKg_SplineChoiceList grKg_803B7FD4;

static struct grKongo_YakumonoParam* yakumono_param;

/* 1D5238 */ void grKongo_801D5238(bool);
/* 1D523C */ void grKongo_801D523C(void);
/* 1D52F8 */ void grKongo_801D52F8(void);
/* 1D52FC */ void grKongo_801D52FC(void);
/* 1D5338 */ bool grKongo_801D5338(void);
/* 1D5340 */ Ground_GObj* grKongo_801D5340(int gobj_id);
/* 1D542C */ void fn_801D542C(HSD_GObj*);
/* 1D5490 */ void grKongo_801D5490(Ground_GObj*);
/* 1D5574 */ bool grKongo_801D5574(Ground_GObj*);
/* 1D557C */ void grKongo_801D557C(Ground_GObj*);
/* 1D55D4 */ void grKongo_801D55D4(Ground_GObj*);
/* 1D55D8 */ void grKongo_801D55D8(Ground_GObj*);
/* 1D5774 */ bool grKongo_801D5774(Ground_GObj*);
/* 1D577C */ void grKongo_801D577C(Ground_GObj*);
/* 1D5FA4 */ void grKongo_801D5FA4(Ground_GObj*);
/* 1D5FA8 */ void grKongo_801D5FA8(Ground_GObj*);
/* 1D5FD4 */ bool grKongo_801D5FD4(Ground_GObj*);
/* 1D5FDC */ void grKongo_801D5FDC(Ground_GObj*);
/* 1D5FE0 */ void grKongo_801D5FE0(Ground_GObj*);
/* 1D5FE4 */ void grKongo_801D5FE4(Ground_GObj*);
/* 1D6028 */ bool grKongo_801D6028(Ground_GObj*);
/* 1D6030 */ void grKongo_801D6030(Ground_GObj*);
/* 1D6034 */ void grKongo_801D6034(Ground_GObj*);
/* 1D6038 */ void grKongo_801D6038(Ground_GObj*);
/* 1D6064 */ bool grKongo_801D6064(Ground_GObj*);
/* 1D606C */ void grKongo_801D606C(Ground_GObj*);
/* 1D6070 */ void grKongo_801D6070(Ground_GObj*);
/* 1D6074 */ void grKongo_801D6074(Ground_GObj*);
/* 1D6190 */ bool grKongo_801D6190(Ground_GObj*);
/* 1D6198 */ void grKongo_801D6198(Ground_GObj*);
/* 1D6378 */ void grKongo_801D6378(Ground_GObj*);
/* 1D637C */ void grKongo_801D637C(Ground_GObj*);
/* 1D64B4 */ bool grKongo_801D64B4(Ground_GObj*);
/* 1D64BC */ void grKongo_801D64BC(Ground_GObj*);
/* 1D6518 */ void grKongo_801D6518(Ground_GObj*);
/* 1D651C */ void grKongo_801D651C(Ground_GObj*);
/* 1D6660 */ bool grKongo_801D6660(Ground_GObj*);
/* 1D6668 */ void grKongo_801D6668(Ground_GObj*);
/* 1D69AC */ void grKongo_801D69AC(Ground_GObj*);
/* 1D69B0 */ void grKongo_801D69B0(HSD_GObj*);
/* 1D6AFC */ void grKongo_801D6AFC(void);
/* 1D7134 */ void grKongo_801D7134(HSD_GObj*, s32);
/* 1D77E0 */ void grKongo_801D77E0(HSD_GObj*, s32);
/* 1D7BBC */ void grKongo_801D7BBC(HSD_GObj*);
/* 1D7E78 */ Vec3* grKongo_801D7E78(HSD_GObj*, Vec3*);
/* 1D7F78 */ bool grKongo_801D7F78(HSD_GObj*);
/* 1D8058 */ void grKongo_801D8058(Ground_GObj*);
/* 1D8078 */ HSD_GObj* grKongo_801D8078(HSD_GObj*);
/* 1D8270 */ void grKongo_801D8270(Ground_GObj*);
/* 1D828C */ void grKongo_801D828C(HSD_GObj*);
/* 1D8314 */ f32 grKongo_801D8314(void);
/* 1D844C */ bool grKongo_801D844C(Vec3*, int arg, HSD_JObj* jobj);
/* 3E1800 */ extern StageData grKg_StageData;

#endif

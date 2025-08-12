#ifndef GALE01_26B1D4
#define GALE01_26B1D4

#include <platform.h>

#include "ft/types.h"

#include "it/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 26B1D4 */ float it_8026B1D4(Item_GObj* gobj, HitCapsule* itemHitboxUnk);
/* 26B294 */ void it_8026B294(Item_GObj* gobj, Vec3* pos);
/* 26B2B4 */ enum_t it_8026B2B4(Item_GObj* gobj);
/* 26B2D8 */ bool it_8026B2D8(Item_GObj* gobj);
/* 26B300 */ s32 itGetKind(Item_GObj* gobj);
/* 26B30C */ enum_t it_8026B30C(Item_GObj* gobj);
/* 26B320 */ enum_t it_8026B320(Item_GObj* gobj);
/* 26B334 */ float it_8026B334(Item_GObj* gobj);
/* 26B344 */ void it_8026B344(Item_GObj* gobj, Vec3* pos);
/* 26B378 */ float it_8026B378(Item_GObj* gobj);
/* 26B384 */ float it_8026B384(Item_GObj* gobj);
/* 26B390 */ void it_8026B390(Item_GObj* gobj);
/* 26B3A8 */ void it_8026B3A8(Item_GObj* gobj);
/* 26B3C0 */ int it_8026B3C0(ItemKind kind);
/* 26B3F8 */ void it_8026B3F8(Article* article, s32 kind);
/* 26B40C */ void it_8026B40C(Article* article, s32 kind);
/* 26B424 */ float it_8026B424(s32 damage);
/* 26B47C */ s32 it_8026B47C(Item_GObj* gobj);
/* 26B4F0 */ bool it_8026B4F0(Item_GObj* gobj);
/* 26B54C */ float it_8026B54C(Item_GObj* gobj);
/* 26B560 */ float it_8026B560(Item_GObj* gobj);
/* 26B574 */ float it_8026B574(Item_GObj* gobj);
/* 26B588 */ s32 it_8026B588(void);
/* 26B594 */ bool it_8026B594(Item_GObj* gobj);
/* 26B5E4 */ HSD_GObj* it_8026B5E4(Vec3* vector, Vec3* vector2,
                                   Item_GObj* gobj);
/* 26B634 */ HSD_GObj* it_8026B634(Vec3* vector, Vec3* vector2,
                                   Item_GObj* gobj);
/* 26B684 */ float it_8026B684(Vec3* pos);
/* 26B6A8 */ float it_8026B6A8(Vec3* pos, HSD_GObj* arg);
/* 26B6C8 */ bool it_8026B6C8(Item_GObj* gobj);
/* 26B718 */ void it_8026B718(Item_GObj* gobj, float hitlagFrames);
/* 26B724 */ void it_8026B724(Item_GObj* gobj);
/* 26B73C */ void it_8026B73C(Item_GObj* gobj);
/* 26B774 */ bool it_8026B774(Item_GObj* gobj, u8 arg1);
/* 26B7A4 */ s32 it_8026B7A4(Item_GObj* gobj);
/* 26B7B0 */ u8 it_8026B7B0(Item_GObj* gobj);
/* 26B7BC */ s32 it_8026B7BC(Item_GObj* gobj);
/* 26B7CC */ s32 it_8026B7CC(Item_GObj* gobj);
/* 26B7D8 */ s32 it_8026B7D8(void);
/* 26B7E0 */ s32 it_8026B7E0(void);
/* 26B7E8 */ s32 it_8026B7E8(Item_GObj* gobj);
/* 26B7F8 */ void it_8026B7F8(Item_GObj* gobj);
/* 26B894 */ bool it_8026B894(Item_GObj* gobj, HSD_GObj* referenced_gobj);
/* 26B924 */ s32 it_8026B924(Item_GObj* gobj);
/* 26B960 */ float it_8026B960(Item_GObj* gobj);
/* 26B9A8 */ void it_8026B9A8(Item_GObj* gobj, HSD_GObj* arg1,
                              Fighter_Part arg2);
/* 26BAE8 */ void it_8026BAE8(Item_GObj* gobj, float scale_mul);
/* 26BB20 */ void it_8026BB20(Item_GObj* gobj);
/* 26BB44 */ void it_8026BB44(Item_GObj* gobj);
/* 26BB68 */ void it_8026BB68(Item_GObj* gobj, Vec3* pos);
/* 26BB88 */ void it_8026BB88(Item_GObj* gobj, Vec3* pos);
/* 26BBCC */ void it_8026BBCC(Item_GObj* gobj, Vec3* pos);
/* 26BC14 */ void it_8026BC14(Item_GObj* gobj);
/* 26BC68 */ bool it_8026BC68(Item_GObj* gobj);
/* 26BC78 */ HSD_GObj* it_8026BC78(Item_GObj* gobj);
/* 26BC84 */ bool it_8026BC84(Item_GObj* gobj);
/* 26BC90 */ void it_8026BC90(Item_GObj* gobj, Vec3* pos);
/* 26BCF4 */ void it_8026BCF4(Item_GObj* gobj);
/* 26BD0C */ void it_8026BD0C(Item_GObj* gobj);
/* 26BD24 */ void it_8026BD24(Item_GObj* gobj);
/* 26BD3C */ void it_8026BD3C(Item_GObj* gobj);
/* 26BD54 */ void it_8026BD54(Item_GObj* gobj);
/* 26BD6C */ void it_8026BD6C(Item_GObj* gobj);
/* 26BD84 */ void it_8026BD84(Item_GObj* gobj);
/* 26BD9C */ void it_8026BD9C(Item_GObj* gobj);
/* 26BDB4 */ void it_8026BDB4(Item_GObj* gobj);
/* 26BDCC */ void it_8026BDCC(Item_GObj* gobj);
/* 26BE28 */ void it_8026BE28(Item_GObj* gobj);
/* 26BE84 */ HSD_GObj* it_8026BE84(BobOmbRain* bobOmbRain);
/* 26C100 */ CollData* it_8026C100(Item_GObj* gobj);
/* 26C16C */ void it_8026C16C(Item_GObj* gobj, bool isHeadless);
/* 26C1B4 */ bool it_8026C1B4(Item_GObj* gobj);
/* 26C1D4 */ u32 it_8026C1D4(void);
/* 26C1E8 */ bool it_8026C1E8(Item_GObj* gobj);
/* 26C220 */ void it_8026C220(Item_GObj* gobj, HSD_GObj* arg1);
/* 26C258 */ HSD_GObj* it_8026C258(Vec3* vector, float facingDir);
/* 26C334 */ void it_8026C334(Item_GObj* gobj, Vec3* pos);
/* 26C368 */ void it_8026C368(Item_GObj* gobj);
/* 26C3FC */ void it_8026C3FC(void);
/* 26C42C */ void it_8026C42C(void);

#endif

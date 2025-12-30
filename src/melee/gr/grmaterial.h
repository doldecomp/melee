#ifndef GALE01_1C87D0
#define GALE01_1C87D0

#include <placeholder.h>
#include <platform.h>

#include "gr/forward.h"
#include <baselib/forward.h>
#include <melee/it/forward.h>

#include <baselib/gobj.h>

/* 1C8858 */ void grMaterial_801C8858(HSD_JObj*, u32 flags);
/* 1C8A04 */ void grMaterial_801C8A04(HSD_JObj*, u32 flags);
/* 1C8B28 */ HSD_JObj* grMaterial_801C8B28(HSD_JObj*);
/* 1C8B68 */ void grMaterial_801C8B68(HSD_JObj*, int);
/* 1C8CDC */ UNK_RET grMaterial_801C8CDC(HSD_GObj*);
/* 1C8CFC */ Item_GObj*
grMaterial_801C8CFC(int, int, Ground*, HSD_JObj*,
                    void (*arg4)(Item_GObj*, Ground*),
                    void (*arg5)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32),
                    void (*arg6)(Item_GObj*, Ground*, HSD_GObj*));
/* 1C8D98 */ void grMaterial_801C8D98(HSD_GObj* gobj, int id);
/* 1C8DE0 */ void grMaterial_801C8DE0(Item_GObj* gobj, float arg8, float arg9,
                                      float argA, float argB, float argC,
                                      float argD, float argE);
/* 1C8E08 */ void grMaterial_801C8E08(Item_GObj*);
/* 1C8E28 */ void grMaterial_801C8E28(HSD_GObj*);
/* 1C8E68 */ void grMaterial_801C8E68(HSD_GObj*, GroundOrAir);
/* 1C92C0 */ void grMaterial_801C92C0(HSD_JObj*);
/* 1C94D8 */ void grMaterial_801C94D8(UNK_T hsd_obj);
/* 1C95C4 */ void grMaterial_801C95C4(HSD_GObj*);
/* 1C9604 */ void grMaterial_801C9604(HSD_GObj* bg, int, bool);
/* 1C9698 */ void grMaterial_801C9698(HSD_GObj*);

#endif

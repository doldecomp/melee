#ifndef GALE01_1C87D0
#define GALE01_1C87D0

#include <placeholder.h>
#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>
#include <melee/it/forward.h>

#include <baselib/gobj.h>

/* 1C897C */ static void grMaterial_801C897C(HSD_JObj* jobj, u32 flags);
/* 1C8D44 */ Item_GObj*
grMaterial_801C8D44(int arg0, int arg1, Ground* arg2, Vec3* arg3, int arg4,
                    void (*arg5)(Item_GObj*, Ground*),
                    void (*arg6)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32),
                    void (*arg7)(Item_GObj*, Ground*, HSD_GObj*));
/* 1C8E48 */ static bool grMaterial_801C8E48(HSD_GObj* gobj);
/* 1C8E74 */ static void grMaterial_801C8E74(void);
/* 1C8EF8 */ static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode);
/* 1C9490 */ void grMaterial_801C9490(Item_GObj* gobj, CommandInfo* cmd);


/* 1C87D0 */ void grMaterial_801C87D0(HSD_JObj*, u32 flags);
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
/* 1C8D44 */ Item_GObj*
grMaterial_801C8D44(int, int, Ground*, Vec3*, int,
                    void (*)(Item_GObj*, Ground*),
                    void (*)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32),
                    void (*)(Item_GObj*, Ground*, HSD_GObj*));
/* 1C8D98 */ void grMaterial_801C8D98(HSD_GObj* gobj, int id);
/* 1C8DE0 */ void grMaterial_801C8DE0(Item_GObj* gobj, float arg8, float arg9,
                                      float argA, float argB, float argC,
                                      float argD, float argE);
/* 1C8E08 */ void grMaterial_801C8E08(Item_GObj*);
/* 1C8E28 */ void grMaterial_801C8E28(HSD_GObj*);
/* 1C8E68 */ void grMaterial_801C8E68(HSD_GObj*, GroundOrAir);
/* 1C92C0 */ void grMaterial_801C92C0(HSD_JObj*);
/* 1C9470 */ void grMaterial_801C9470(Item_GObj*, CommandInfo*);
/* 1C94D8 */ void grMaterial_801C94D8(void*);
/* 1C95C4 */ void grMaterial_801C95C4(HSD_GObj*);
/* 1C9604 */ void grMaterial_801C9604(HSD_GObj* bg, int, bool);
/* 1C9664 */ void fn_801C9664(Item_GObj* gobj, CommandInfo* cmd, int arg2);
/* 1C9698 */ void grMaterial_801C9698(HSD_GObj*);

#endif

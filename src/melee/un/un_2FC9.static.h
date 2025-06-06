#ifndef __GALE01_2FC9B4
#define __GALE01_2FC9B4

#include "platform.h"
#include "types.h"
#include "un_2FC9.h" // IWYU pragma: export

#include "baselib/objalloc.h"
#include "sc/types.h"

#include <dolphin/mtx.h>
#include <baselib/cobj.h>

struct un_80304138_objalloc_t {
    char pad_0[0x20];
};
STATIC_ASSERT(sizeof(struct un_80304138_objalloc_t) == 0x20);

/* 2FCAA4 */ static void fn_802FCAA4(HSD_GObj* gobj, int code);
/* 3FDC48 */ static HSD_CObjDesc devtext_CObjDesc;
/* 4A1ED0 */ static StaticModelDesc un_804A1ED0;
/* 4A1FD8 */ static DevText devtext_pool[32];
/* 4A2688 */ static HSD_ObjAllocData un_804A2688;
/* 4D6D6C */ static s8 un_804D6D6C;
/* 4D6D78 */ static HSD_Text* un_804D6D78;
/* 4D6D88 */ static s32 un_804D6D88;
/* 4D6D8C */ static s32 un_804D6D8C;
/* 4D6D90 */ static IntVec2 un_804D6D90;
/* 4D6E18 */ static DevText* devtext_drawlist;
/* 4D6E1C */ static HSD_GObj* devtext_gobj;
/* 4D6E20 */ static HSD_CObj* devtext_cobj;
/* 4D6E24 */ static int devtext_setup_classifier;
/* 4D6E28 */ static int devtext_setup_p_link;
/* 4D6E2C */ static int devtext_setup_priority;
/* 4D6E30 */ static int devtext_setup_gx_link;
/* 4D6E34 */ static int devtext_setup_render_priority;
/* 4D6E38 */ static DevText* devtext_poolhead;
/* 4D6E44 */ static UNK_T un_804D6E44;

#endif

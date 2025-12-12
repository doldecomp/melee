#ifndef GALE01_2F23AC
#define GALE01_2F23AC

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

/* 2F23AC */ double it_802F23AC(int* obj, float* pos);
/* 2F23EC */ void it_802F23EC(Item_GObj* gobj, Fighter_GObj* owner_gobj,
                              float facing_dir);
/* 2F2578 */ bool itKirby_2F23_UnkMotion0_Anim(Item_GObj*);
/* 2F2580 */ void itKirby_2F23_UnkMotion0_Phys(Item_GObj*);
/* 2F2584 */ bool itKirby_2F23_UnkMotion0_Coll(Item_GObj*);
/* 2F258C */ UNK_RET it_802F258C(UNK_PARAMS);
/* 2F2810 */ UNK_RET it_802F2810(UNK_PARAMS);
/* 2F2888 */ bool itKirby_2F23_UnkMotion1_Anim(Item_GObj*);
/* 2F2890 */ void itKirby_2F23_UnkMotion1_Phys(Item_GObj*);
/* 2F2894 */ bool itKirby_2F23_UnkMotion1_Coll(Item_GObj*);
/* 2F289C */ void it_802F289C(Item_GObj*);
/* 3F9450 */ extern ItemStateTable it_803F9450[];

#endif

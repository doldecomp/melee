#ifndef GALE01_2E6AEC
#define GALE01_2E6AEC

#include <platform.h>

#include "gr/forward.h"
#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2E6AEC */ Item_GObj* it_802E6AEC(Ground*, int, int, HSD_JObj*, Vec3*, int,
                                    void (*)(Item_GObj*, Ground*),
                                    void (*)(Item_GObj*, Ground*, Vec3*,
                                             HSD_GObj*, f32),
                                    void (*)(Item_GObj*, Ground*, HSD_GObj*));
/* 2E6F7C */ bool it_2E6A_Logic117_DmgDealt(Item_GObj*);
/* 2E6FC0 */ bool it_2E6A_Logic117_DmgReceived(Item_GObj*);
/* 2E709C */ void it_2E6A_Logic117_EvtUnk(Item_GObj*, HSD_GObj*);
/* 3F8C8C */ extern ItemStateTable it_803F8C8C[];

#endif

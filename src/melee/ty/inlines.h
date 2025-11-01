#ifndef MELEE_TY_INLINES_H
#define MELEE_TY_INLINES_H

#include <placeholder.h>

#include "ty/forward.h"

#ifdef M2C
#define GET_TOY(gobj) ((Toy*) HSD_GObjGetUserData((HSD_GObj*) gobj))
#else
#define GET_TOY(gobj) ((Toy*) HSD_GObjGetUserData(gobj))
#endif

#endif

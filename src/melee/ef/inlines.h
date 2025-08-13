#ifndef MELEE_EF_INLINES_H
#define MELEE_EF_INLINES_H

#include <platform.h>

#include <baselib/forward.h>

#include <baselib/gobj.h>

#ifdef M2CTX_DUAL
#define GET_EFFECT(gobj) ((Effect*) HSD_GObjGetUserData((HSD_GObj*) gobj))
#else
#define GET_EFFECT(gobj) ((Effect*) HSD_GObjGetUserData(gobj))
#endif

#endif

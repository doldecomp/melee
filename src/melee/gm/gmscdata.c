#include "gmscdata.h"

#include <melee/gm/types.h>

/* 3DA920 */ extern MinorSceneHandler gm_803DA920[];
/* 3DACA4 */ extern MajorScene gm_803DACA4;

MinorSceneHandler* gm_801A50A0(void)
{
    return gm_803DA920;
}

MajorScene* gm_801A50AC(void)
{
    return &gm_803DACA4;
}


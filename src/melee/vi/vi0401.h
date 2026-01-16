#ifndef MELEE_VI_0401_H
#define MELEE_VI_0401_H

#include <placeholder.h>

#include "ft/forward.h"
#include <baselib/forward.h>

typedef struct vi0401_SceneData {
    u8 char_id;
    u8 costume_id;
} vi0401_SceneData;

/* 31D030 */ void un_8031D030(CharacterKind, int);
/* 31D288 */ void un_8031D288_OnEnter(vi0401_SceneData*);
/* 31D698 */ void un_8031D698_OnFrame(void);

#endif

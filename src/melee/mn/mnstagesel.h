#ifndef GALE01_2599EC
#define GALE01_2599EC

#include <sysdolphin/baselib/forward.h>

#include <placeholder.h>

#include <melee/sc/types.h>

/* 2599EC */ int mnStageSel_802599EC(void);
/* 259C28 */ void mnStageSel_80259C28(void);
/* 259D84 */ void fn_80259D84(HSD_GObj*);
/* 259ED8 */ void mnStageSel_80259ED8(int);
/* 25A090 */ void fn_8025A090(HSD_GObj*);
/* 25A310 */ void fn_8025A310(HSD_GObj*);
/* 25A560 */ void fn_8025A560(HSD_GObj*);
/* 25A91C */ void fn_8025A91C(HSD_GObj*);
/* 25A974 */ void fn_8025A974(HSD_GObj*, intptr_t);
/* 25A998 */ void mnStageSel_Scene_OnEnter(UNK_T);
/* 25B850 */ void mnStageSel_Scene_OnFrame(void);
/* 25BB5C */ void mnStageSel_Scene_OnExit(UNK_T);
/* 25BBD4 */ int mnSelStageRandom(void);
/* 25BC08 */ int mnStageSel_8025BC08(int);

typedef struct MnSelectStageModels {
    /* +00 */ StaticModelDesc icon_large;
    /* +10 */ StaticModelDesc icon_random;
    /* +20 */ StaticModelDesc icon_special;
    /* +30 */ StaticModelDesc stage_name;
    /* +40 */ StaticModelDesc icon_stacked;
    /* +50 */ StaticModelDesc menu_border;
    /* +60 */ StaticModelDesc stage_preview;
    /* +70 */ StaticModelDesc icon_hover;
    /* +80 */ StaticModelDesc cursor;
    /* +90 */ StaticModelDesc layout;
    /* +A0 */ StaticModelDesc background;
    /* +B0 */ StaticModelDesc now_loading;
} MnSelectStageModels;

struct MnSelectStageDataTable {
    /* 0x00 */ HSD_CObjDesc* cam;
    /* 0x04 */ HSD_LightDesc* light0;
    /* 0x08 */ HSD_LightDesc* light1;
    /* 0x0C */ HSD_FogDesc* fog;
    /* 0x10 */ MnSelectStageModels models;
};

#endif

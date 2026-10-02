#ifndef GALE01_25BC20
#define GALE01_25BC20

#include <sysdolphin/baselib/forward.h>

#include <melee/sc/types.h>

/* 25BC20 */ u8* mnCharSel_8025BC20(u8* dst, u32 value);
/* 25BD30 */ void mnCharSel_8025BD30(void);
/* 25C020 */ void mnCharSel_8025C020(int);
/* 25D1C4 */ void mnCharSel_8025D1C4(int, int);
/* 25D5AC */ void mnCharSel_8025D5AC(int door, int frame, bool hidden);
/* 25DAA0 */ bool mnCharSel_8025DAA0(int door);
/* 25DB34 */ void mnCharSel_8025DB34(u8);
/* 25EE8C */ void mnCharSel_8025EE8C(u8 idx);
/* 25F0E0 */ void fn_8025F0E0(HSD_GObj*);
/* 25FAC0 */ void fn_8025FAC0(HSD_GObj*);
/* 25FB2C */ void fn_8025FB2C(HSD_GObj*);
/* 25FB50 */ void mnCharSel_8025FB50(u8 door, s32 arg1);
/* 25FDEC */ s32 mnCharSel_8025FDEC(u8 door);
/* 260094 */ void mnCharSel_CostumeChange(int door, u32 input);
/* 2602A0 */ void mnCharSel_CursorThink(HSD_GObj* gobj);
/* 262648 */ void fn_80262648(HSD_GObj*);
/* 262F44 */ void fn_80262F44(HSD_GObj*);
/* 263354 */ void fn_80263354(HSD_GObj*);
/* 2633B0 */ void fn_802633B0(HSD_GObj*);
/* 264070 */ void mnCharSel_80264070(void);
/* 26407C */ void fn_8026407C(HSD_GObj*);
/* 2640A0 */ s32 mnCharSel_802640A0(void);
/* 26688C */ void mnCharSel_Scene_OnEnter(void*);
/* 2669F4 */ void mnCharSel_Scene_OnFrame(void);
/* 266D70 */ void mnCharSel_Scene_OnExit(void*);

typedef struct MnSelectChrModels {
    /* 0x0 */ StaticModelDesc background;
    /* 0x10 */ StaticModelDesc hand;
    /* 0x20 */ StaticModelDesc token;
    /* 0x30 */ StaticModelDesc menu;
    /* 0x40 */ StaticModelDesc press_start;
    /* 0x50 */ StaticModelDesc debug_camera;
    /* 0x60 */ StaticModelDesc regend_menu;
    /* 0x70 */ StaticModelDesc regend_options;
    /* 0x80 */ StaticModelDesc door;
} MnSelectChrModels;

struct MnSelectChrDataTable {
    /* 0x00 */ HSD_CObjDesc* cam;
    /* 0x04 */ HSD_LightDesc* light0;
    /* 0x08 */ HSD_LightDesc* light1;
    /* 0x0C */ HSD_FogDesc* fog;
    /* 0x10 */ MnSelectChrModels models;
};

#endif

#ifndef MELEE_MN_EVENT_H
#define MELEE_MN_EVENT_H

#include <placeholder.h>

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/sislib.h>

typedef struct MnEventData {
    /* 0x00 */ u8 page;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ s32 first_event;
    /* 0x08 */ HSD_GObj* gobjs[9];
    /* 0x2C */ HSD_Text* texts[9];
    /* 0x50 */ HSD_Text* icons[9];
    /* 0x74 */ HSD_Text* name_text;
    /* 0x78 */ HSD_Text* desc_text;
} MnEventData;

/* 24CE74 */ s32 mnEvent_8024CE74(void);
/* 24D014 */ void mnEvent_8024D014(HSD_GObj*);
/* 24D0CC */ void mnEvent_8024D0CC(HSD_GObj*, s32);
/* 24D15C */ void mnEvent_8024D15C(s32, s32);
/* 24D4E0 */ void mnEvent_8024D4E0(HSD_JObj*, Vec3*);
/* 24D5B0 */ void mnEvent_8024D5B0(HSD_GObj*, u8);
/* 24D7E0 */ void mnEvent_8024D7E0(HSD_GObj*, s32);
/* 24D864 */ void fn_8024D864(HSD_GObj*);
/* 24E1B4 */ void fn_8024E1B4(HSD_GObj*);
/* 24E2A0 */ void fn_8024E2A0(HSD_GObj*);
/* 24E34C */ void fn_8024E34C(HSD_GObj*);
/* 24E420 */ void mnEvent_8024E420(MnEventData*, s32);
/* 24E524 */ void mnEvent_8024E524(s32);
/* 24E838 */ void mnEvent_8024E838(int, int);

extern void* mnEvent_804A08F8[];
extern void* mnEvent_804A0908;
extern HSD_GObj* mnEvent_804D6C60;
extern u8 mnEvent_804D6C64;
extern u8 mnEvent_804D6C65;

#endif

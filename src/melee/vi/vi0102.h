#ifndef GALE01_31CB00
#define GALE01_31CB00

#include <placeholder.h>

#include <baselib/gobj.h>

typedef struct un_804D6F60_t {
    /* 0x0 */ u8 unk_0; /* inferred */
    /* 0x1 */ u8 unk_1; /* inferred */
    /* 0x2 */ u8 unk_2; /* inferred */
    /* 0x3 */ u8 unk_3; /* inferred */
    /* 0x4 */ char pad_2[4];
} un_804D6F60_t; /* size = 0x8 */
STATIC_ASSERT(sizeof(un_804D6F60_t) == 0x8);

/* 31CB00 */ void vi0102_8031CB00(int, int);
/* 31CC68 */ void vi0102_JObjCallback(HSD_GObj*);
/* 31CC8C */ void vi0102_CameraCallback(HSD_GObj* gobj, int unused);
/* 31CD20 */ void vi0102_8031CD20(HSD_GObj*);
/* 31CD94 */ void vi0102_Initialize_OnEnter(un_804D6F60_t*);
/* 31D000 */ void vi0102_8031D000_OnFrame(void);
/* 31D020 */ void vi0102_8031D020(int, int);

#endif

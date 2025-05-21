#ifndef GALE01_31CB00
#define GALE01_31CB00

#include <placeholder.h>

#include <baselib/gobj.h>

struct un_804D6F60_t {
    /* 0x0 */ s8 unk_0;      /* inferred */
    /* 0x1 */ s8 unk_1;      /* inferred */
    /* 0x2 */ char pad_2[6]; /* maybe part of unk_1[7]? */
}; /* size = 0x8 */
STATIC_ASSERT(sizeof(struct un_804D6F60_t) == 0x8);

/* 31CB00 */ UNK_RET vi_8031CB00(UNK_PARAMS);
/* 31CC68 */ void vi_8031CC68(HSD_GObj*);
/* 31CC8C */ void vi_8031CC8C(HSD_GObj*);
/* 31CD20 */ void vi_8031CD20(HSD_GObj*);
/* 31CD94 */ UNK_RET vi_8031CD94(UNK_PARAMS);
/* 31D000 */ void vi_8031D000(void);
/* 31D020 */ void vi_8031D020(s8 arg0, s8 arg1);

#endif

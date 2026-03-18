#ifndef MELEE_MN_MNCOUNT_H
#define MELEE_MN_MNCOUNT_H

#include <placeholder.h>
#include <platform.h>

#include "mn/forward.h"
#include <baselib/forward.h>
#include <baselib/sislib.h>

typedef struct MnCountData {
    /* 0x00 */ u8 cursor;
    /* 0x01 */ u8 pad_01[3];
    /* 0x04 */ s32 page_size;
    /* 0x08 */ HSD_Text* labels[10];
    /* 0x30 */ HSD_Text* values[10];
    /* 0x58 */ HSD_Text* title;
} MnCountData; // size 0x5C

/* 2502CC */ s32 mnCount_802502CC(s32);
/* 2502F0 */ s32 fn_802502F0(u8);
/* 250314 */ s32 fn_80250314(u8);
/* 250338 */ s32 fn_80250338(s32);
/* 25035C */ int mnCount_8025035C(s32 skip_count, u32 (*get_val_func)(s8));
/* 25069C */ s32 fn_8025069C(s32);
/* 2506C0 */ s32 fn_802506C0(s32);
/* 2506E4 */ s32 fn_802506E4(s32);
/* 250708 */ s32 fn_80250708(s32);
/* 25072C */ s32 mnCount_8025072C(CountEntry* entries, s32 start_idx,
                                  s32 mode);
/* 25092C */ UNK_RET mnCount_8025092C(UNK_PARAMS);
/* 250C7C */ UNK_RET mnCount_80250C7C(UNK_PARAMS);
/* 250DE4 */ UNK_RET mnCount_80250DE4(UNK_PARAMS);
/* 250FF8 */ UNK_RET mnCount_80250FF8(UNK_PARAMS);
/* 251278 */ UNK_RET fn_80251278(UNK_PARAMS);
/* 2513F4 */ void mnCount_802513F4(HSD_GObj*);
/* 2514B8 */ void fn_802514B8(HSD_GObj* gobj);
/* 2514D8 */ UNK_RET fn_802514D8(UNK_PARAMS);
/* 251640 */ UNK_RET fn_80251640(UNK_PARAMS);
/* 2517E0 */ void mnCount_802517E0(MnCountData*);
/* 25186C */ void mnCount_8025186C(void);

#endif

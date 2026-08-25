#ifndef SYSDOLPHIN_GENERATOR_H
#define SYSDOLPHIN_GENERATOR_H

#include <placeholder.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/objalloc.h>

struct hsd_804D0F60_t {
    HSD_ObjAllocData alloc_data;
    UNK_T pad;
};

/* 39D0A0 */ void hsd_8039D0A0(HSD_Generator*);
/* 39D1E4 */ void hsd_8039D1E4(HSD_Generator*, void*);
/* 39D1EC */ u16 hsd_8039D1EC(void);
/* 39D214 */ void hsd_8039D214(HSD_Generator*);
/* 39D354 */ void hsd_8039D354(u32);
/* 39D3AC */ HSD_Generator* hsd_8039D3AC(HSD_Generator*, HSD_Generator*);
/* 39D4DC */ void hsd_8039D4DC(HSD_Generator*);
/* 39D580 */ void hsd_8039D580(HSD_JObj*);
/* 39D5DC */ void hsd_8039D5DC(HSD_JObj*);
/* 39D688 */ void hsd_8039D688(HSD_JObj*, f32**, s32);
/* 39D71C */ void hsd_8039D71C(HSD_Generator*);
/* 39D9C8 */ HSD_Generator* hsd_8039D9C8(void);
/* 39DAD4 */ f32 hsd_8039DAD4(HSD_Generator*);
/* 39EE24 */ void hsd_8039EE24(u32);
/* 39EFAC */ HSD_Generator* hsd_8039EFAC(s32 linkNo, s32 bank, s32 gfx_id,
                                         HSD_JObj*);
/* 39F05C */ HSD_Generator* hsd_8039F05C(s32 linkNo, s32 bank, s32 idx);
/* 39F6CC */ HSD_Generator* hsd_8039F6CC(s32 linkNo, s32 bank, s32 gfx_id,
                                         HSD_JObj*);

/* 4D0F60 */ extern struct hsd_804D0F60_t hsd_804D0F60;
/* 4D0F90 */ extern struct hsd_804D0F60_t hsd_804D0F90;

#endif

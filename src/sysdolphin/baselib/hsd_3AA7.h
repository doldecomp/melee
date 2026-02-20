#ifndef GALE01_3AA790
#define GALE01_3AA790

#include <placeholder.h>

struct hsd_803AC3E0_arg0_t {
    /*  +0 */ u8 _pad0[0x8];
    /* +08 */ u32 x8;
    /* +0C */ u8 _pad1[0x18];
    /* +24 */ u32 x24;
    /* +28 */ int x28[9];
    /* +4C */ int x4C[9];
    /* +70 */ int x70[9];
};

/* 3AA790 */ UNK_RET fn_803AA790(UNK_PARAMS);
/* 3AAA48 */ UNK_RET hsd_803AAA48(UNK_PARAMS);
/* 3AC168 */ s32 fn_803AC168(s32* cmd_buf);
/* 3AC258 */ void fn_803AC258(s32 card_state, s32 block_idx);
/* 3AC2A4 */ void fn_803AC2A4(s32 card_state);
/* 3AC2D4 */ UNK_RET fn_803AC2D4(UNK_PARAMS);
/* 3AC2E0 */ void fn_803AC2E0(void);
/* 3AC334 */ UNK_RET fn_803AC334(UNK_PARAMS);
/* 3AC340 */ int hsd_803AC340(void* header);
/* 3AC3E0 */ void hsd_803AC3E0(struct hsd_803AC3E0_arg0_t* file_desc,
                               int file_idx, int file_size, int file_offset,
                               int file_flags);
/* 3AC3F8 */ void fn_803AC3F8(void*, u8*, s32);
/* 3AC558 */ void hsd_803AC558(struct hsd_803AC3E0_arg0_t*, u8*);
/* 3AC634 */ u32 fn_803AC634(struct hsd_803AC3E0_arg0_t* file_desc,
                             s32 file_idx);
/* 3AC6B8 */ UNK_RET fn_803AC6B8(UNK_PARAMS);
typedef struct CardState {
    /* 0x00 */ u8* x0;
    /* 0x04 */ u8 _pad0[0x4];
    /* 0x08 */ u32 x8;
    /* 0x0C */ u8 _pad1[0x18];
    /* 0x24 */ u32 x24;
} CardState;
/* 3AC7DC */ s32 fn_803AC7DC(CardState*);
/* 3ACB74 */ s32 fn_803ACB74(s32 seq_a, s32 seq_b);
/* 3ACBE8 */ s32 fn_803ACBE8(CardState* state, s32 block_idx);
/* 3ACC0C */ s32 fn_803ACC0C(CardState* state, s32 block_idx, s32 file_id,
                             s32 seq_num, void* expected_data, s32 data_size);
/* 3ACD58 */ s32 fn_803ACD58(CardState* state, void* icon_data,
                             void* file_data);
/* 3ACF30 */ s32 fn_803ACF30(CardState* state, s32 file_id, s32 seq_num,
                             s32 version);
/* 3ACFC0 */ s32 fn_803ACFC0(CardState* state, s32 block_idx, s32 file_id,
                             s32 seq_num, void* payload, s32 payload_size,
                             s32 version);
/* 3AD16C */ UNK_RET fn_803AD16C(UNK_PARAMS);
/* 3ADE4C */ s32 fn_803ADE4C(s32 card_state, s32 channel, s32 callback);
/* 3ADF90 */ UNK_RET fn_803ADF90(UNK_PARAMS);
/* 3AE7F8 */ UNK_RET fn_803AE7F8(UNK_PARAMS);
/* 3AF3F0 */ UNK_RET fn_803AF3F0(UNK_PARAMS);
/* 3B0120 */ UNK_RET fn_803B0120(UNK_PARAMS);
/* 3B0E9C */ s32 fn_803B0E9C(s32, s32, s32, s32, s32);
/* 3B1338 */ s32 fn_803B1338(s32, s32);
/* 3B1F78 */ s32 fn_803B1F78(CardState* state, s32 channel, s32 file_id,
                             s32 seq_num, s32 callback);
/* 3B21E8 */ s32 fn_803B21E8(s32 card_state, s32 file_id, s32 seq_num,
                             s32 callback);
/* 3B2374 */ void hsd_803B2374(void);
/* 3B24E4 */ void hsd_803B24E4(s32* ctx, int channel, int file_no,
                               void* work_buf);
/* 3B2550 */ int hsd_803B2550(s32*, const char*, void (*)(int, int));
/* 3B2674 */ s32 hsd_803B2674(CardState* state);
/* 3B26CC */ s32 fn_803B26CC(CardState* state, s32 file_id, s32 seq_num,
                             s32 version, s32 callback);

#endif

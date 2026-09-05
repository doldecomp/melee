#ifndef GALE01_0A0148
#define GALE01_0A0148

#include <placeholder.h>

#include <melee/ft/forward.h>

#include <melee/ft/types.h>
#include <Runtime/platform.h>

struct _m2c_stack_ftCo_800A3554 {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ f32 f;
    /* 0x14 */ Vec3 vec;
    /* 0x20 */ char pad_20[0x18];
}; /* size = 0x38 */

/* 09D4F0 */ void ftCo_800A05F4(Fighter* fp);
/* 09D694 */ void ftCo_800A0798(Fighter* fp);
/* 09DB88 */ void ftCo_800A0C8C(Fighter* fp);
/* 09DCA0 */ void ftCo_800A0DA4(Fighter* fp);
/* 09DEAC */ bool ftCo_800A0FB0(Vec3* vec_out, int* line_id_out,
                                u32* flags_out, Vec3* normal_out, int arg4,
                                int arg5, int arg6, float arg7, float arg8,
                                float arg9, float arg10, float arg11);
/* 09DF18 */ void ftCo_800A101C(Fighter*, int, int, int);
/* 09E6E0 */ float ftCo_800A17E4(Fighter* fp);
/* 09E770 */ float ftCo_800A1874(Fighter* fp);
/* 09E800 */ float ftCo_800A1904(Fighter* fp);
/* 09E844 */ float ftCo_800A1948(Fighter* fp);
/* 09E888 */ HSD_Pad ftCo_800A198C(Fighter* fp);
/* 09E890 */ float ftCo_800A1994(Fighter* fp);
/* 09E920 */ float ftCo_800A1A24(Fighter* fp);
/* 09F06C */ bool ftCo_800A2170(Fighter* fp0, Fighter* fp1);
/* 09F7CC */ bool ftCo_800A28D0(Fighter* fp, float arg1);
/* 09F894 */ bool ftCo_800A2998(Fighter* fp, float arg1);
/* 09F96C */ float ftCo_800A2A70(Fighter* fp, bool);
/* 09FAD0 */ bool ftCo_800A2BD4(Fighter* fp);
/* 09FB04 */ bool ftCo_800A2C08(Fighter* fp);
/* 0A0030 */ enum_t ftCo_800A3134(Fighter* fp);
/* 0A007C */ bool ftCo_IsGrabbing(Fighter* fp);
/* 0A00FC */ bool ftCo_800A3200(Fighter* fp);
/* 0A0740 */ bool ftCo_IsAlly(Fighter* fp0, Fighter* fp1);
/* 0A193C */ Fighter* ftCo_800A4A40(Fighter* fp);
/* 0A1AB4 */ float ftCo_800A1AB4(Fighter* fp0, Fighter* fp1);
/* 0A1BA8 */ bool ftCo_800A1BA8(Fighter* fp);
/* 0A1C44 */ bool ftCo_800A1C44(Fighter* fp);
/* 0A1CA8 */ bool ftCo_800A1CA8(Fighter* fp);
/* 0A1D88 */ Fighter* ftCo_800A4E8C(Fighter*, Vec3*);
/* 0A2040 */ bool ftCo_800A2040(Fighter* fp);
/* 0A2804 */ bool ftCo_800A5908(Item* ip);
/* 0A287C */ bool ftCo_800A5980(Fighter* fp);
/* 0A28BC */ bool ftCo_800A59C0(Item* ip);
/* 0A28E0 */ bool ftCo_800A59E4(Item* ip);
/* 0A2924 */ bool ftCo_800A5A28(Item* ip);
/* 0A41F4 */ bool ftCo_800B395C(Fighter_GObj* gobj, int);
/* 0A5A5C */ bool ftCo_800A5A5C(Item* ip);
/* 0A5A90 */ bool ftCo_800A5A90(Fighter* fp);
/* 0B07FC */ void ftCo_800B3900(Fighter_GObj* gobj);
/* 0B0858 */ UNK_RET ftCo_800B3958(UNK_PARAMS);

#endif

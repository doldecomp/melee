#include <dolphin/mtx/types.h>

char lbl_803C56D8[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
int lbl_803C5700[] = { 9, 10, 11, 12 };
Vec4 lbl_803C5710 = { 14, 0, -3, 3 };
char lbl_803C5720[] = "translate";
char lbl_803C572C[] = "fighter dynamics num over!\n";
char lbl_803C5748[] = "ftdynamics.c";

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif
char ftDynamics_assert_msg_0[] = "fp->dynamics_num < Ft_Dynamics_NumMax";
#ifdef MUST_MATCH
#pragma pop
#endif

f32 lbl_803C5780[] = { 0, 0.57, 0.57, 0.57, 0 };

struct {
    int zero1;
    int zero2;
    u32 flags;
    int neg1;
    f32* floats;
    int zero3;
    int zero4;
} lbl_803C5794 = {
    0, 0, 0x00050000, -1, lbl_803C5780, 0, 0,
};

char lbl_803C57B0[] = "no effect from animlist %d\n";

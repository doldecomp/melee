#include <MSL/buffer_io.h>

s32 __flush_buffer(BufferIoUnkStruct* arg0, s32* arg1)
{
    s32 temp_r0;
    s32 temp_r3;
    temp_r0 = arg0->x20 - arg0->x18;
    if (temp_r0 != 0) {
        arg0->x24 = temp_r0;
        if (arg0->x05.b4) {
            arg0 != 0;
        }

        temp_r3 = arg0->x3C(arg0->x00, arg0->x18, &arg0->x24, arg0->x44);

        if (arg1 != 0U) {
            *arg1 = arg0->x24;
        }

        if (temp_r3 != 0) {
            return temp_r3;
        }

        arg0->x14 += (s32) arg0->x24;
    }
    arg0->x20 = arg0->x18;
    arg0->x24 = (s32) arg0->x1C;
    arg0->x24 -= (s32) (arg0->x14 & arg0->x28);
    arg0->x30 = (s32) arg0->x14;
    return 0;
}

void __prep_buffer(BufferIoUnkStruct* arg0)
{
    arg0->x20 = (s32) arg0->x18;
    arg0->x24 = (s32) arg0->x1C;
    arg0->x24 = (s32) (arg0->x24 - (arg0->x14 & arg0->x28));
    arg0->x30 = (s32) arg0->x14;
    return;
}

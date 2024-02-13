#include <baselib/axdriver.h>

int lbAudioAx_800236B8(HSD_SM* arg0)
{
    AXDriverKeyOff(arg0);
    return -1;
}

int lbAudioAx_80024B94(int arg0, int arg1)
{
    int const limit = 0x4B0;
    if (arg1 < -limit) {
        arg1 = -limit;
    }
    if (arg1 > limit) {
        arg1 = limit;
    }
    return AXDriver_8038D4E4(arg0, arg1);
}

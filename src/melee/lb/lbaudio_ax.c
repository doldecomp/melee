#include <baselib/axdriver.h>

static s32 lbl_804D6408;

/// #lbAudioAx_8002306C

/// #lbAudioAx_80023090

/// #lbAudioAx_800230C8

/// #lbAudioAx_80023130

/// #lbAudioAx_80023220

/// #fn_80023254

/// #lbAudioAx_800233EC

/// #lbAudioAx_80023694

int lbAudioAx_800236B8(HSD_SM* arg0)
{
    AXDriverKeyOff(arg0);
    return -1;
}

/// #lbAudioAx_800236DC

/// #lbAudioAx_80023710

/// #lbAudioAx_80023730

/// #fn_80023750

/// #lbAudioAx_800237A8

/// #lbAudioAx_80023870

/// #lbAudioAx_8002392C

/// #lbAudioAx_80023968

/// #lbAudioAx_80023A44

/// #lbAudioAx_80023B24

/// #fn_80023ED4

/// #lbAudioAx_80023F28

/// #lbAudioAx_80024030

/// #lbAudioAx_800240B4

/// #lbAudioAx_8002411C

/// #lbAudioAx_80024184

/// #lbAudioAx_80024304

/// #lbAudioAx_8002438C

/// #lbAudioAx_800243F4

/// #fn_800244F4

/// #lbAudioAx_800245D4

/// #lbAudioAx_800245F4

/// #lbAudioAx_80024614

/// #lbAudioAx_80024634

/// #fn_80024654

/// #lbAudioAx_80024B1C

/// #lbAudioAx_80024B58

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

/// #lbAudioAx_80024BD0

/// #lbAudioAx_80024C08

/// #lbAudioAx_80024C84

/// #lbAudioAx_80024D50

/// #lbAudioAx_80024D78

/// #lbAudioAx_80024DC4

/// #lbAudioAx_80024E50

/// #lbAudioAx_80024E84

/// #lbAudioAx_80024F08

/// #lbAudioAx_80024F6C

/// #lbAudioAx_80024FDC

/// #lbAudioAx_80024FF4

/// #lbAudioAx_8002500C

/// #lbAudioAx_80025038

/// #lbAudioAx_80025064

void lbAudioAx_80025098(s32 arg0)
{
    lbl_804D6408 = arg0;
}

/// #fn_800250A0

/// #fn_800251EC

/// #fn_800253D8

/// #fn_800256BC

/// #fn_800259A0

/// #fn_800259EC

/// #fn_80025A98

/// #fn_80025B44

/// #fn_80025CBC

/// #fn_80025E38

/// #fn_80025FAC

/// #fn_800262A0

/// #fn_800263B4

/// #lbAudioAx_800263E8

/// #lbAudioAx_800264E4

/// #lbAudioAx_80026510

/// #lbAudioAx_800265C4

/// #fn_80026650

/// #fn_800267B0

/// #fn_800268B4

/// #fn_800269AC

/// #fn_80026C04

/// #fn_80026E58

/// #lbAudioAx_80026E84

/// #lbAudioAx_80026EBC

/// #lbAudioAx_80026F2C

/// #lbAudioAx_8002702C

/// #lbAudioAx_80027168

/// #fn_80027488

/// #lbAudioAx_80027648

/// #lbAudioAx_8002785C

/// #lbAudioAx_80027AB0

/// #lbAudioAx_80027DBC

/// #lbAudioAx_80027DF8

/// #lbAudioAx_8002835C

/// #lbAudioAx_8002838C

/// #lbAudioAx_80028690

/// #lbAudioAx_80028B2C

/// #lbAudioAx_80028B4C

/// #lbAudioAx_80028B6C

static s32 lbl_804D38CC = 0x7F;

void lbAudioAx_80028B90(void)
{
    lbl_804D38CC = 0x7F;
}

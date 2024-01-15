#ifndef SYSDOLPHIN_BASELIB_SYNTH_H
#define SYSDOLPHIN_BASELIB_SYNTH_H

#include <dolphin/os.h>

extern void (*HSD_Synth_804D7710)(s32, s32);
extern void (*HSD_Synth_804D7714)(OSContext*, ...);
extern int (*HSD_Synth_804D7718)(s32, s32, s32*, s32);

#endif

#ifndef _DOLPHIN_CARDMOUNT_H_
#define _DOLPHIN_CARDMOUNT_H_

int CARDProbe(long chan);
s32 CARDProbeEx(s32 chan, s32 *memSize, s32 *sectorSize);
s32 CARDMountAsync(s32 chan, void *workArea, CARDCallback detachCallback, CARDCallback attachCallback);
s32 CARDMount(s32 chan, void *workArea, CARDCallback detachCallback);
s32 CARDUnmount(s32 chan);

#endif // _DOLPHIN_CARDMOUNT_H_

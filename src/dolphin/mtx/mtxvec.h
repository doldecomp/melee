#ifndef DOLPHIN_MTX_MTXVEC_H
#define DOLPHIN_MTX_MTXVEC_H

#include <ctypes.h>

typedef f32 Mtx[3][4];
typedef struct _Vec Vec;

void PSMTXMUltiVec(Mtx, Vec*, Vec*);

#endif
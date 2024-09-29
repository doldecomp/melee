#include <placeholder.h>

#include "eflib.h"

#include "types.h"

#include <baselib/jobj.h>
#include <baselib/particle.h>
#include <baselib/psappsrt.h>

void efLib_8005CC2C(int arg0, HSD_JObj* arg1)
{
    UnkGeneratorStruct* particle = hsd_8039EFAC(0, arg0 / 1000, arg0, arg1);
    if (particle != NULL) {
        particle->x16_flags &= ~PSAPPSRT_UNK_B10;
    }
}

ef_UnkStruct0* efLib_8005FCD8(int arg0, int arg2, ef_UnkStruct1* arg3)
{
    UnkGeneratorMember* var_r3;
    UnkGeneratorStruct* temp_r3_2;
    ef_UnkStruct0* temp_r3;

    temp_r3 = efLib_8005BE88(0);
    if (temp_r3 != NULL) {
        temp_r3->x8 = fn_8005FBE4;
        temp_r3->x4 = arg2;
        temp_r3->x10 = arg3->x0;
        temp_r3->x14 = arg3->x4;
        temp_r3->x18 = arg3->x8;
        temp_r3_2 = hsd_8039EFAC(0, arg0 / 1000, arg0, temp_r3->x0->x0);
        if (temp_r3_2 != NULL) {
            var_r3 = temp_r3_2->x54;
            if (var_r3 == NULL) {
                var_r3 = psAddGeneratorAppSRT_begin(temp_r3_2, 0);
            }
            if (var_r3 != NULL) {
                var_r3->x4 = temp_r3_2;
                temp_r3_2->x16_flags &= ~PSAPPSRT_UNK_B09;
                temp_r3_2->x16_flags |= PSAPPSRT_UNK_B11;
            } else {
                hsd_8039D4DC(temp_r3_2);
            }
        }
    }
    return temp_r3;
}

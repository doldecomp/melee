#include "mpisland.h" // IWYU pragma: keep

#include "mplib.h"
#include "types.h"

#include "lb/lb_00B0.h"

#include <baselib/memory.h>

/* 05A6F8 */ static void mpIsland_8005A6F8(void);
/* 05A728 */ static void mpIsland_8005A728(void);
/* 458E88 */ struct mpIsland_80458E88_t mpIsland_80458E88;

void mpIsland_8005A6F8(void)
{
    mpIsland_80458E88.next = NULL;
    mpIsland_80458E88.x4 = 0;
    mpIsland_80458E88.x8.x = 0;
    mpIsland_80458E88.x8.y = 0;
    mpIsland_80458E88.x14.y = 0;
    mpIsland_80458E88.x14.z = 0;
    mpIsland_80458E88.x8.z = 0;
    mpIsland_80458E88.x14.x = 0;
    mpIsland_80458E88.x20 = 0;
}

void mpIsland_8005A728(void)
{
    short* v0;            // r27
    mp_UnkStruct2* v1;    // r28
    mpLib_804D64B8_t* v2; // r3
    // unk *test;
    int v3;                // r29
    unsigned char* result; // r3
    int v5;                // r21
    int* v6;               // r19
    int v7;                // r20
    float v8;              // fp31
    int v9;                // r18
    void* v10;             // r3
    void* v11;             // r25
    int v12;               // r0
    int v13;               // r5
    int v14;               // r3
    int* v15;              // r6
    int v16;               // r5
    int v17;               // r3
    int v18;               // ctr
    mpisland* v19;         // r24
    int v20;               // r26
    int v21;               // r27
    float v22;             // fp31
    s32* v22_2;
    int* v23; // r19
    s32* v24_2;
    mpisland* v24;           // r3
    mpisland* v25;           // r25
    int v26;                 // r4
    int v27;                 // r0
    int v28;                 // r6
    int* v29;                // r5
    int v30;                 // r4
    int v31;                 // r3
    int v32;                 // ctr
    unsigned char v33[1524]; // [sp+18h] [-648h] BYREF

    v0 = (short*) mpLib_8004D164();
    v1 = mpLib_8004D174();
    v2 = mpLib_8004D16C();
    v23 = &mpIsland_80458E88.x4;
    v24_2 = &mpIsland_80458E88.x8.x;
    v22_2 = &mpIsland_80458E88.x8.y;
    mpIsland_8005A6F8();

    memzero(v33, 0x600u);
    v5 = v0[9];
    v6 = 0;
    if (v0[9]) {
        v7 = v0[8];
        v8 = 0.0f;
        v9 = v7;
        while (v5) {
            v10 = HSD_MemAlloc(0x2C);
            v11 = v10;
            if (!v10) {
                __assert(__FILE__, 62, "mpisp");
            }
            if (v6) {
                v6 = v10;
            } else {
                mpIsland_80458E88.next = v10;
            }
            v6 = (int*) v10;
            v12 = v7;
            v13 = v7 == 0;
            v14 = 0;
            while (v7 != v13) {
                v33[v12] = 1;
                v15 = (int*) (v1 + 8 * v12);
                v16 = v15[1];
                if ((v16 & 0x10000) == 0 || (v16 & 0x40000) != 0) {
                    v14 = 1;
                }
                v13 = *(short*) (*v15 + 6);
                if (v13 == -1 ||
                    (*(unsigned short*) (*(int*) (v1 + 8 * v13) + 0xC) & 1) ==
                        0)
                {
                    break;
                }
                v12 = *(short*) (*v15 + 6);
            }
            if (v14) {
                v17 = 2;
            } else {
                v17 = 0;
            }
            /// @todo Rewrite as a struct ptr
            // *(int*) (v11 + 0x20) = v17;
            // *(int*) v11 = 0;
            // *(short*) (v11 + 0x24) = v7;
            // *(short*) (v11 + 0x26) = v12;
            // *(short*) (v11 + 4) = **(short**) (v1 + v9);
            // *(short*) (v11 + 6) = *(short*) (*(short*) (v1 + 8 * v12) + 2);
            // *(float*) (v11 + 8) =
            //     *(float*) (v2 + 0x18 * *(unsigned short*) (v11 + 4) + 8);
            // *(float*) (v11 + 0xC) =
            //     *(float*) (v2 + 0x18 * *(unsigned short*) (v11 + 4) + 0xC);
            // *(float*) (v11 + 0x10) = v8;
            // *(float*) (v11 + 0x14) =
            //     *(float*) (v2 + 0x18 * *(unsigned short*) (v11 + 6) + 8);
            // *(float*) (v11 + 0x18) =
            //     *(float*) (v2 + 0x18 * *(unsigned short*) (v11 + 6) + 0xC);
            // *(float*) (v11 + 0x1C) = v8;
            // --v5;
            // *(short*) (v11 + 0x28) = mpLib_80056B6C(v7++);
            // v7--;

            v18 = v5;
            result = &v33[v7];
            v9 += 8;
            if (v7) {
                do {
                    if (!*result) {
                        break;
                    }
                    ++result;
                    ++v7;
                    v9 += 8;
                    --v5;
                    v7--;
                } while (v18);
            }
        }
    }

    *v24_2 = (int) v6;
    v19 = 0;
    v20 = v0[0xB];
    if (v0[0xB]) {
        v21 = v0[0xA];
        // v22 = MEMORY[0xFFFF9648];
        *v23 = 8 * v21;
        while (v20) {
            v24 = (mpisland*) HSD_MemAlloc(0x2C);
            v25 = v24;
            if (!v24) {
                __assert("mpisland.c", 0x3E, "mpisp");
            }
            if (v19) {
                v19->x0[0] = (int) v24;
            } else {
                *v22_2 = (int) v24;
            }
            v26 = v21 == 0;
            v19 = v24;
            v27 = v21;
            v28 = 0;
            while (v21 != v26) {
                v33[v27] = 1;
                v29 = (int*) (v1 + 8 * v27);
                v30 = v29[1];
                if ((v30 & 0x10000) == 0 || (v30 & 0x40000) != 0) {
                    v28 = 1;
                }
                v26 = *(short*) (*v29 + 4);
                if (v26 == -1 ||
                    (*(short*) (*(int*) (v1 + 8 * v26) + 0xC) & 2) == 0)
                {
                    break;
                }
                v27 = *(short*) (*v29 + 4);
            }
            if (v28) {
                v31 = 2;
            } else {
                v31 = 0;
            }
            v25->x0[2] = v31;
            v25->x0[0] = 0;
            v25->x20[0] = v21;
            v25->x20[0] = v27;
            // v25->unk[1] = *(short*) (*(int*) (v1 + v23) + 2);
            v25->x0[1] = **(short**) (v1 + 8 * v27);
            v25->x0[2] = *(int*) (v2 + 0x18 * v25->x0[1] + 8);
            v25->x0[3] = *(int*) (v2 + 0x18 * v25->x0[1] + 0xC);
            v25->x0[4] = 0.0F;
            v25->x0[5] = *(float*) (v2 + 0x18 * v25->x0[1] + 8);
            v25->x0[6] = *(float*) (v2 + 0x18 * v25->x0[1] + 0xC);
            v25->x0[7] = 0.0F;
            --v20;
            v25->x20[2] = mpLib_80056B6C(v21++);
            v32 = v20;
            result = &v33[v21];
            v23 += 8;
            v20--;
            if (v20) {
                for (v32 = 0; v32 < 0; v32++) {
                    if (!*result) {
                        break;
                    }
                    ++result;
                    ++v21;
                    v23 += 8;
                    --v20;
                    --v32;
                }
            }
        }
    }
    v22_2 = v24_2;
}

mp_UnkStruct0* mpIsland_8005AB54(int surface_idx)
{
    if (mpLib_80054ED8(surface_idx)) {
        mp_UnkStruct2* v2 = mpLib_8004D174();
        bool done;
        mp_UnkStruct0* cur;

        for (cur = mpIsland_80458E88.next; cur; cur = cur->next) {
            int j, j_next;
            for (j = cur->x24; j != -1; j = j_next) {
                if (j == surface_idx) {
                    return cur;
                }

                if (j == cur->x26) {
                    break;
                }

                done = true;
                j_next = v2[j].x0->x6;

                if (j_next != -1 && (v2[j_next].x4 & 1)) {
                    done = false;
                }

                if (done) {
                    break;
                }
            }
        }
    }
    return NULL;
}

mp_UnkStruct0* mpIsland_8005AC14(Vec3* arg0, float arg1)
{
    int i;
    if (mpLib_8004F008(NULL, &i, 0, 0, -1, -1, -1, 0, 0, arg0->x, arg0->y,
                       arg0->x, arg0->y + arg1, 0.0F))
    {
        return mpIsland_8005AB54(i);
    }
    return NULL;
}

bool mpIsland_8005AC8C(mp_UnkStruct0* arg0)
{
    mpLib_804D64C0_t* temp_r3 = &mpLib_8004D17C()[arg0->x28];
    if (temp_r3->flags & 0x700) {
        return true;
    }
    if (temp_r3->flags & 0x700) {
        return true;
    }
    return false;
}

void mpIsland_8005ACE8(mp_UnkStruct5* arg0, Vec3* arg1, Vec3* arg2)
{
    int var_r31;
    mp_UnkStruct2* var_r30;
    int temp_r29;
    bool var_r28;
    bool var_r27;
    int i;

    mpLib_804D64C0_t* temp_r3;
    temp_r3 = &mpLib_8004D17C()[arg0->x28];
    var_r31 = temp_r3->x4[0];
    var_r30 = &mpLib_8004D174()[var_r31];
    temp_r29 = temp_r3->x4[1];

    var_r28 = true;
    var_r27 = true;
    if (arg1 != NULL) {
        *arg1 = arg0->x8;
    } else {
        var_r28 = false;
    }
    if (arg2 != NULL) {
        *arg2 = arg0->x14;
    } else {
        var_r27 = false;
    }

    for (i = 0; i < temp_r29 && var_r28 && var_r27; var_r31++) {
        if (var_r28 && var_r30->x0->x0 == arg0->x4) {
            mpLib_80054158(var_r31, arg1);
        } else if (var_r27 && var_r30->x0->x2 == arg0->x6) {
            mpLib_80053FF4(var_r31, arg2);
        }
        i++;
        var_r30++;
    }
}

#include "mpisland.h" // IWYU pragma: keep

#include "mplib.h"
#include "types.h"

#include "lb/lb_00B0.h"

#include <baselib/memory.h>

/* 3B73E8 */ mpIsland_Palette mpIsland_TerrainPalette = { {
    { mp_Terrain_Rock, { 0x80, 0x60, 0x60, 0xFF } },
    { mp_Terrain_Grass, { 0x40, 0xFF, 0x40, 0xFF } },
    { mp_Terrain_Dirt, { 0xC0, 0x60, 0x60, 0xFF } },
    { mp_Terrain_Wood, { 0xC0, 0x80, 0x40, 0xFF } },
    { mp_Terrain_LightMetal, { 0x40, 0x40, 0x40, 0xFF } },
    { mp_Terrain_HeavyMetal, { 0x60, 0x40, 0x40, 0xFF } },
    { mp_Terrain_Paper, { 0xC0, 0xC0, 0x60, 0xFF } },
    { mp_Terrain_Goop, { 0xFF, 0xFF, 0x60, 0xFF } },
    { mp_Terrain_Birdo, { 0xC0, 0xFF, 0xC0, 0xFF } },
    { mp_Terrain_Water, { 0x40, 0x40, 0xFF, 0xFF } },
    { mp_Terrain_Unk11, { 0x40, 0xFF, 0xFF, 0xFF } },
    { mp_Terrain_UFO, { 0xC0, 0xC0, 0xFF, 0xFF } },
    { mp_Terrain_Turtle, { 0xC0, 0xFF, 0x40, 0xFF } },
    { mp_Terrain_Snow, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { mp_Terrain_Ice, { 0xC0, 0xC0, 0xFF, 0xFF } },
    { mp_Terrain_GnW, { 0xC0, 0xC0, 0xC0, 0xFF } },
    { mp_Terrain_Unk17, { 0x0C, 0x0C, 0x0C, 0xFF } },
    { mp_Terrain_Checkered, { 0xFF, 0xFF, 0xC0, 0xFF } },
    { mp_Terrain_Unk19, { 0xFF, 0x05, 0x05, 0xFF } },
    { -1, { 0x00, 0x00, 0x00, 0x00 } },
} };

/* 458E88 */ struct mpIsland_80458E88_t mpIsland_80458E88;

void mpIsland_8005A6F8(void)
{
    mpIsland_80458E88.next = NULL;
    mpIsland_80458E88.x4 = NULL;
    mpIsland_80458E88.x8 = NULL;
    mpIsland_80458E88.xC = NULL;
    mpIsland_80458E88.x18 = NULL;
    mpIsland_80458E88.x1C = NULL;
    mpIsland_80458E88.x10 = NULL;
    mpIsland_80458E88.x14 = NULL;
    mpIsland_80458E88.x20 = NULL;
}

void mpIsland_8005A728(void)
{
    short* v0;    // r27
    CollLine* v1; // r28
    CollVtx* v2;  // r3
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
    v1 = mpGetGroundCollLine();
    v2 = mpGetGroundCollVtx();
    v23 = (int*) &mpIsland_80458E88.x4;
    v24_2 = (s32*) &mpIsland_80458E88.x8;
    v22_2 = (s32*) &mpIsland_80458E88.xC;
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
            // *(short*) (v11 + 0x28) = mpJointFromLine(v7++);
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
            v25->x20[2] = mpJointFromLine(v21++);
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
        CollLine* v2 = mpGetGroundCollLine();
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
                j_next = v2[j].x0->next_id0;

                if (j_next != -1 && (v2[j_next].flags & CollLine_Floor)) {
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
    if (mpCheckFloor(arg0->x, arg0->y, arg0->x, arg0->y + arg1, 0.0F, NULL, &i,
                     NULL, NULL, -1, -1, -1, NULL, NULL))
    {
        return mpIsland_8005AB54(i);
    }
    return NULL;
}

bool mpIsland_8005AC8C(mp_UnkStruct0* arg0)
{
    CollJoint* temp_r3 = &mpGetGroundCollJoint()[arg0->x28];
    if (temp_r3->flags & (CollJoint_B10 | CollJoint_B9 | CollJoint_B8)) {
        return true;
    }
    if (temp_r3->flags & (CollJoint_B10 | CollJoint_B9 | CollJoint_B8)) {
        return true;
    }
    return false;
}

void mpIsland_8005ACE8(mp_UnkStruct0* arg0, Vec3* arg1, Vec3* arg2)
{
    int var_r31;
    CollLine* var_r30;
    int temp_r29;
    bool var_r28;
    bool var_r27;
    int i;

    CollJoint* temp_r3;
    temp_r3 = &mpGetGroundCollJoint()[arg0->x28];
    var_r31 = temp_r3->inner->floor_start;
    var_r30 = &mpGetGroundCollLine()[var_r31];
    temp_r29 = temp_r3->inner->floor_count;

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
        if (var_r28 && var_r30->x0->v0_idx == arg0->x4) {
            mpFloorGetLeft(var_r31, arg1);
        } else if (var_r27 && var_r30->x0->v1_idx == arg0->x6) {
            mpFloorGetRight(var_r31, arg2);
        }
        i++;
        var_r30++;
    }
}

static float mpIsland_804D8158;

void mpIsland_8005AE1C(mp_UnkStruct0** arg0, mp_UnkStruct0** arg1, int arg2,
                       int arg3, bool arg4)
{
    mp_UnkStruct0* prev_b;
    mp_UnkStruct0* prev_a;
    mp_UnkStruct0* cur;
    mp_UnkStruct0* next;
    CollVtx* vtx;
    int end;
    float z_val;
    u16 v0;

    prev_b = NULL;
    prev_a = NULL;

    vtx = mpGetGroundCollVtx();
    cur = *arg0;
    end = arg2 + arg3;
    z_val = mpIsland_804D8158;

    goto loop1_check;
loop1_body:
    v0 = cur->x4;
    next = cur->next;

    if ((int) v0 < arg2) {
        if ((int) cur->x6 < arg2) {
            goto add_to_prev_b_1;
        }
    }

    if (end > (int) v0) {
        goto do_assign_1;
    }
    if (end <= (int) cur->x6) {
        goto add_to_prev_b_1;
    }

do_assign_1:
    cur->x8.x = vtx[v0].pos.x;
    cur->x8.y = vtx[cur->x4].pos.y;
    cur->x8.z = z_val;
    cur->x14.x = vtx[cur->x6].pos.x;
    cur->x14.y = vtx[cur->x6].pos.y;
    cur->x14.z = z_val;

    if (arg4) {
        goto add_to_prev_b_1;
    }
    if (cur->x20 & 2) {
        goto add_to_prev_b_1;
    }
    cur->x20 |= 2;
    cur->next = prev_a;
    prev_a = cur;
    goto loop1_next;

add_to_prev_b_1:
    cur->next = prev_b;
    prev_b = cur;

loop1_next:
    cur = next;
loop1_check:
    if (cur != NULL) {
        goto loop1_body;
    }

    cur = *arg1;
    z_val = mpIsland_804D8158;

    goto loop2_check;
loop2_body:
    v0 = cur->x4;
    next = cur->next;

    if ((int) v0 < arg2) {
        if ((int) cur->x6 < arg2) {
            goto add_to_prev_a_2;
        }
    }

    if (end > (int) v0) {
        goto do_assign_2;
    }
    if (end <= (int) cur->x6) {
        goto add_to_prev_a_2;
    }

do_assign_2:
    cur->x8.x = vtx[v0].pos.x;
    cur->x8.y = vtx[cur->x4].pos.y;
    cur->x8.z = z_val;
    cur->x14.x = vtx[cur->x6].pos.x;
    cur->x14.y = vtx[cur->x6].pos.y;
    cur->x14.z = z_val;

    if (arg4 == false) {
        goto add_to_prev_a_2;
    }
    if ((cur->x20 & 2) == 0) {
        goto add_to_prev_a_2;
    }
    cur->x20 &= ~2;
    cur->next = prev_b;
    prev_b = cur;
    goto loop2_next;

add_to_prev_a_2:
    cur->next = prev_a;
    prev_a = cur;

loop2_next:
    cur = next;
loop2_check:
    if (cur != NULL) {
        goto loop2_body;
    }

    *arg0 = prev_b;
    *arg1 = prev_a;
}

/// #mpIsland_8005B004

void mpIsland_8005B334(int arg0, int arg1, int arg2, bool arg3)
{
    mp_UnkStruct0* temp;

    if (mpIsland_80458E88.x8 != NULL) {
        mpIsland_80458E88.x8->next = NULL;
    } else {
        mpIsland_80458E88.next = NULL;
    }

    if (mpIsland_80458E88.xC != NULL) {
        mpIsland_80458E88.xC->next = NULL;
    } else {
        mpIsland_80458E88.x4 = NULL;
    }

    mpIsland_8005AE1C(&mpIsland_80458E88.next, &mpIsland_80458E88.x18, arg1,
                      arg2, arg3);
    mpIsland_8005AE1C(&mpIsland_80458E88.x4, &mpIsland_80458E88.x1C, arg1,
                      arg2, arg3);
    mpIsland_8005B004(&mpIsland_80458E88.x10, &mpIsland_80458E88.x20, arg0, 1,
                      arg1, arg2, arg3);
    mpIsland_8005B004(&mpIsland_80458E88.x14, &mpIsland_80458E88.x20, arg0, 2,
                      arg1, arg2, arg3);

    // Find end of first list and link
    temp = mpIsland_80458E88.next;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    if (temp != NULL) {
        temp->next = mpIsland_80458E88.x10;
    } else {
        mpIsland_80458E88.next = mpIsland_80458E88.x10;
    }
    mpIsland_80458E88.x8 = temp;

    // Find end of second list and link
    temp = mpIsland_80458E88.x4;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    if (temp != NULL) {
        temp->next = mpIsland_80458E88.x14;
    } else {
        mpIsland_80458E88.x4 = mpIsland_80458E88.x14;
    }
    mpIsland_80458E88.xC = temp;
}

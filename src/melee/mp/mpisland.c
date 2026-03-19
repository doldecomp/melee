#include "mpisland.h" // IWYU pragma: keep

#include "mplib.h"
#include "types.h"

#include "lb/lb_00B0.h"

#include <baselib/debug.h>
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

/* 4D8158 */ static float mpIsland_804D8158;
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
    MapCollData* map;
    CollLine* lines;
    CollVtx* vtx;
    mp_UnkStruct0* mpisp;
    mp_UnkStruct0* prev;
    int count;
    int line_idx;
    int end_idx;
    int hidden;
    s16 next;
    float z_val;
    int i;
    u8 visited[0x600];
    PAD_STACK(0x10);

    map = mpLib_8004D164();
    lines = mpGetGroundCollLine();
    vtx = mpGetGroundCollVtx();
    mpIsland_8005A6F8();

    memzero(visited, 0x600u);

    /* Process floor segments */
    count = map->floor_count;
    prev = NULL;
    if (count) {
        line_idx = map->floor_start;
        z_val = mpIsland_804D8158;
        while (count != 0) {
            mpisp = HSD_MemAlloc(0x2C);
            HSD_ASSERT(62, mpisp);
            if (prev) {
                prev->next = mpisp;
            } else {
                mpIsland_80458E88.next = mpisp;
            }
            prev = mpisp;
            end_idx = line_idx;
            hidden = 0;
            while (true) {
                visited[end_idx] = 1;
                if (!(lines[end_idx].flags & LINE_FLAG_ENABLED) ||
                    (lines[end_idx].flags & LINE_FLAG_HIDDEN))
                {
                    hidden = 1;
                }
                next = lines[end_idx].x0->next_id0;
                if (next == -1 || !(lines[next].x0->hi_flags & CollLine_Floor))
                {
                    break;
                }
                end_idx = next;
                if (line_idx == end_idx) {
                    break;
                }
            }
            mpisp->x20 = hidden ? 2 : 0;
            mpisp->next = NULL;
            mpisp->x24 = (short) line_idx;
            mpisp->x26 = (short) end_idx;
            mpisp->x4 = lines[line_idx].x0->v0_idx;
            mpisp->x6 = lines[end_idx].x0->v1_idx;
            mpisp->x8.x = vtx[mpisp->x4].pos.x;
            mpisp->x8.y = vtx[mpisp->x4].pos.y;
            mpisp->x8.z = z_val;
            mpisp->x14.x = vtx[mpisp->x6].pos.x;
            mpisp->x14.y = vtx[mpisp->x6].pos.y;
            mpisp->x14.z = z_val;
            mpisp->x28 = mpJointFromLine(line_idx);
            count--;
            line_idx++;
            {
                u8* p = &visited[line_idx];
                int ctr = count;
                if (count) {
                    do {
                        if (!*p) {
                            break;
                        }
                        p++;
                        line_idx++;
                        count--;
                    } while (--ctr);
                }
            }
        }
    }

    mpIsland_80458E88.x8 = prev;

    /* Process ceiling segments */
    prev = NULL;
    count = map->ceiling_count;
    if (count) {
        line_idx = map->ceiling_start;
        z_val = mpIsland_804D8158;
        for (; count != 0;) {
            mpisp = HSD_MemAlloc(0x2C);
            HSD_ASSERT(0x3E, mpisp);
            if (prev) {
                prev->next = mpisp;
            } else {
                mpIsland_80458E88.xC = mpisp;
            }
            prev = mpisp;
            end_idx = line_idx;
            hidden = 0;
            for (;;) {
                visited[end_idx] = 1;
                if (!(lines[end_idx].flags & LINE_FLAG_ENABLED) ||
                    (lines[end_idx].flags & LINE_FLAG_HIDDEN))
                {
                    hidden = 1;
                }
                next = lines[end_idx].x0->prev_id0;
                if (next == -1 ||
                    !(lines[next].x0->hi_flags & CollLine_Ceiling))
                {
                    break;
                }
                end_idx = next;
                if (line_idx == end_idx) {
                    break;
                }
            }
            mpisp->x20 = hidden ? 2 : 0;
            mpisp->next = NULL;
            mpisp->x24 = (short) line_idx;
            mpisp->x26 = (short) end_idx;
            mpisp->x4 = lines[line_idx].x0->v1_idx;
            mpisp->x6 = lines[end_idx].x0->v0_idx;
            mpisp->x8.x = vtx[mpisp->x4].pos.x;
            mpisp->x8.y = vtx[mpisp->x4].pos.y;
            mpisp->x8.z = z_val;
            mpisp->x14.x = vtx[mpisp->x6].pos.x;
            mpisp->x14.y = vtx[mpisp->x6].pos.y;
            mpisp->x14.z = z_val;
            mpisp->x28 = mpJointFromLine(line_idx);
            count--;
            line_idx++;
            {
                u8* p = &visited[line_idx];
                int ctr = count;
                if (count) {
                    do {
                        if (!*p) {
                            break;
                        }
                        p++;
                        line_idx++;
                        count--;
                    } while (--ctr);
                }
            }
        }
    }

    mpIsland_80458E88.x8 = prev;
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
    CollJoint* temp_r3;
    bool var_r27;
    int i;

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

void mpIsland_8005B004(mp_UnkStruct0** arg0, mp_UnkStruct0** arg1, int arg2,
                       int arg3, int arg4, int arg5, bool arg6)
{
    mp_UnkStruct0* cur;
    mp_UnkStruct0* prev;
    mp_UnkStruct0* next;
    mp_UnkStruct0* mpisp;
    CollLine* lines;
    CollVtx* vtx;
    CollJoint* joints;
    MapJoint* inner;
    int line_idx;
    int end_idx;
    int start_idx;
    int end_total;
    int loop;
    u32 type_flag;
    s16 link;
    float z_val;
    float min_x;
    float max_x;
    int i;
    u8 visited[0x600];
    PAD_STACK(16);

    type_flag = arg3 | 0x10;
    prev = NULL;
    cur = *arg0;

    while (cur != NULL) {
        next = cur->next;
        if (cur->x28 == arg2) {
            cur->next = *arg1;
            *arg1 = cur;
        } else {
            cur->next = prev;
            prev = cur;
        }
        cur = next;
    }
    *arg0 = prev;

    memzero(visited, 0x600u);

    joints = mpGetGroundCollJoint();
    joints = &joints[arg2];
    lines = mpGetGroundCollLine();
    vtx = mpGetGroundCollVtx();
    inner = joints->inner;
    z_val = mpIsland_804D8158;

    line_idx = inner->dynamic_start;
    end_total = inner->dynamic_start + inner->dynamic_count;

    for (; line_idx < end_total;) {
        if (visited[line_idx] != 0 ||
            (lines[line_idx].flags & 0x1F) != type_flag)
        {
            line_idx++;
            continue;
        }

        end_idx = line_idx;
        loop = 0;

        for (;;) {
            visited[end_idx] = 1;
            link = lines[end_idx].x0->prev_id0;
            if (link == -1) {
                break;
            }
            if ((lines[link].flags & 0x1F) != type_flag) {
                break;
            }
            end_idx = link;
            if (link == line_idx) {
                loop = 1;
                break;
            }
        }

        if (!loop) {
            start_idx = line_idx;

            for (;;) {
                visited[start_idx] = 1;
                link = lines[start_idx].x0->next_id0;
                if (link == -1) {
                    break;
                }
                if ((lines[link].flags & 0x1F) != type_flag) {
                    break;
                }
                start_idx = link;
                if (link == line_idx) {
                    loop = 1;
                    break;
                }
            }

            if (loop) {
                HSD_ASSERT(0x206, !loop);
                goto after_alloc;
            }
        } else {
            start_idx = end_idx;
            min_x = -F32_MAX;
            i = start_idx;
            max_x = F32_MAX;
            link = i;

            do {
                if (max_x > vtx[lines[i].x0->v0_idx].pos.x) {
                    max_x = vtx[lines[i].x0->v0_idx].pos.x;
                    end_idx = i;
                }
                if (min_x > vtx[lines[i].x0->v1_idx].pos.x) {
                    min_x = vtx[lines[i].x0->v1_idx].pos.x;
                    start_idx = i;
                }
                i = lines[i].x0->prev_id0;
            } while (i != link);
        }

    after_alloc:
        mpisp = *arg1;
        if (mpisp != NULL) {
            *arg1 = mpisp->next;
        } else {
            mpisp = HSD_MemAlloc(0x2C);
            HSD_ASSERT(0x3E, mpisp);
        }

        mpisp->x20 = arg6 ? 0 : 2;
        mpisp->next = NULL;
        mpisp->x24 = (short) end_idx;
        mpisp->x26 = (short) start_idx;
        mpisp->x4 = lines[end_idx].x0->v0_idx;
        mpisp->x6 = lines[start_idx].x0->v1_idx;
        mpisp->x8.x = vtx[mpisp->x4].pos.x;
        mpisp->x8.y = vtx[mpisp->x4].pos.y;
        mpisp->x8.z = z_val;
        mpisp->x14.x = vtx[mpisp->x6].pos.x;
        mpisp->x14.y = vtx[mpisp->x6].pos.y;
        mpisp->x14.z = z_val;
        mpisp->x28 = (short) arg2;

        mpisp->next = *arg0;
        *arg0 = mpisp;
    }
}

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

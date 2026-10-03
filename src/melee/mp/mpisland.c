#include "mpisland.h" // IWYU pragma: keep

#include <placeholder.h>

#include "mplib.h"
#include "types.h"
#include <melee/lb/lb_00B0.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/memory.h>

/* 3B73E8 */ mpIsland_Palette const mpIsland_TerrainPalette = { {
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
    mpIsland_80458E88.floors = NULL;
    mpIsland_80458E88.ceilings = NULL;
    mpIsland_80458E88.floors_tail = NULL;
    mpIsland_80458E88.ceilings_tail = NULL;
    mpIsland_80458E88.disabled_floors = NULL;
    mpIsland_80458E88.disabled_ceilings = NULL;
    mpIsland_80458E88.dynamic_floors = NULL;
    mpIsland_80458E88.dynamic_ceilings = NULL;
    mpIsland_80458E88.free_list = NULL;
}

static inline void mpIsland_AssertSeg(mpIsland* mpisp)
{
    HSD_ASSERT(62, mpisp);
}

struct mpIsland_8005A728_seg {
    mpIsland* p;
};

void mpIsland_8005A728(void)
{
    MapCollData* map;
    CollLine* lines;
    CollVtx* vtx;
    struct mpIsland_8005A728_seg seg;
    float z_val;
    int count;
    int line_idx;
    int end_idx;
    int next;
    int hidden;
    mpIsland* prev;
    u8 visited[0x600];
    PAD_STACK(0x10);

    map = mpLib_8004D164();
    lines = mpGetGroundCollLine();
    vtx = mpGetGroundCollVtx();
    mpIsland_8005A6F8();

    memzero(visited, sizeof(visited));

    /* Process floor segments */
    prev = NULL;
    if ((count = map->ranges[MapLineGroup_Floor].count) != 0) {
        line_idx = map->ranges[MapLineGroup_Floor].start;
        z_val = 0.0f;
        while (count != 0) {
            seg.p = HSD_MemAlloc(sizeof(mpIsland));
            mpIsland_AssertSeg(seg.p);
            if (prev) {
                prev->next = seg.p;
            } else {
                mpIsland_80458E88.floors = seg.p;
            }
            prev = seg.p;
            end_idx = line_idx;
            next = !line_idx;
            hidden = 0;
            while (line_idx != next) {
                visited[end_idx] = 1;
                if (!(lines[end_idx].flags & LINE_FLAG_ENABLED) ||
                    (lines[end_idx].flags & LINE_FLAG_HIDDEN))
                {
                    hidden = 1;
                }
                next = lines[end_idx].inner->next_id0;
                if (next == -1 ||
                    !(lines[next].inner->hi_flags & CollLine_Floor))
                {
                    break;
                }
                end_idx = next;
            }
            seg.p->flags = hidden ? 2 : 0;
            seg.p->next = NULL;
            seg.p->line0 = (s16) line_idx;
            seg.p->line1 = (s16) end_idx;
            seg.p->vtx0 = lines[line_idx].inner->v0_idx;
            seg.p->vtx1 = lines[end_idx].inner->v1_idx;
            seg.p->pos0.x = vtx[seg.p->vtx0].pos.x;
            seg.p->pos0.y = vtx[seg.p->vtx0].pos.y;
            seg.p->pos0.z = z_val;
            seg.p->pos1.x = vtx[seg.p->vtx1].pos.x;
            seg.p->pos1.y = vtx[seg.p->vtx1].pos.y;
            seg.p->pos1.z = z_val;
            seg.p->joint_id = mpJointFromLine(line_idx);
            count--;
            line_idx++;
            {
                u8* p = &visited[line_idx];
                int ctr;
                for (ctr = count; ctr != 0; ctr--) {
                    if (!*p) {
                        break;
                    }
                    p++;
                    line_idx++;
                    count--;
                }
            }
        }
    }

    mpIsland_80458E88.floors_tail = prev;

    /* Process ceiling segments */
    prev = NULL;
    (void) seg.p;
    count = map->ranges[MapLineGroup_Ceiling].count;
    if (count) {
        line_idx = map->ranges[MapLineGroup_Ceiling].start;
        z_val = 0.0f;
        while (count != 0) {
            seg.p = HSD_MemAlloc(sizeof(mpIsland));
            mpIsland_AssertSeg(seg.p);
            if (prev) {
                prev->next = seg.p;
            } else {
                mpIsland_80458E88.ceilings = seg.p;
            }
            prev = seg.p;
            end_idx = line_idx;
            next = !line_idx;
            hidden = 0;
            while (line_idx != next) {
                visited[end_idx] = 1;
                if (!(lines[end_idx].flags & LINE_FLAG_ENABLED) ||
                    (lines[end_idx].flags & LINE_FLAG_HIDDEN))
                {
                    hidden = 1;
                }
                next = lines[end_idx].inner->prev_id0;
                if (next == -1 ||
                    !(lines[next].inner->hi_flags & CollLine_Ceiling))
                {
                    break;
                }
                end_idx = next;
            }
            seg.p->flags = hidden ? 2 : 0;
            seg.p->next = NULL;
            seg.p->line0 = (s16) line_idx;
            seg.p->line1 = (s16) end_idx;
            seg.p->vtx0 = lines[line_idx].inner->v1_idx;
            seg.p->vtx1 = lines[end_idx].inner->v0_idx;
            seg.p->pos0.x = vtx[seg.p->vtx0].pos.x;
            seg.p->pos0.y = vtx[seg.p->vtx0].pos.y;
            seg.p->pos0.z = z_val;
            seg.p->pos1.x = vtx[seg.p->vtx1].pos.x;
            seg.p->pos1.y = vtx[seg.p->vtx1].pos.y;
            seg.p->pos1.z = z_val;
            seg.p->joint_id = mpJointFromLine(line_idx);
            count--;
            line_idx++;
            {
                u8* p = &visited[line_idx];
                int ctr;
                for (ctr = count; ctr != 0; ctr--) {
                    if (!*p) {
                        break;
                    }
                    p++;
                    line_idx++;
                    count--;
                }
            }
        }
    }

    mpIsland_80458E88.ceilings_tail = prev;
}

mpIsland* mpIsland_8005AB54(int surface_idx)
{
    if (mpLib_80054ED8(surface_idx)) {
        CollLine* v2 = mpGetGroundCollLine();
        bool done;
        mpIsland* cur;

        for (cur = mpIsland_80458E88.floors; cur; cur = cur->next) {
            int j, j_next;
            for (j = cur->line0; j != -1; j = j_next) {
                if (j == surface_idx) {
                    return cur;
                }

                if (j == cur->line1) {
                    break;
                }

                done = true;
                j_next = v2[j].inner->next_id0;

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

mpIsland* mpIsland_8005AC14(Vec3* pos, float dy)
{
    int line_id;
    if (mpCheckFloor(pos->x, pos->y, pos->x, pos->y + dy, 0.0F, NULL, &line_id,
                     NULL, NULL, -1, -1, -1, NULL, NULL))
    {
        return mpIsland_8005AB54(line_id);
    }
    return NULL;
}

bool mpIsland_8005AC8C(mpIsland* island)
{
    CollJoint* joint = &mpGetGroundCollJoint()[island->joint_id];
    if (joint->flags & (CollJoint_B10 | CollJoint_B9 | CollJoint_B8)) {
        return true;
    }
    if (joint->flags & (CollJoint_B10 | CollJoint_B9 | CollJoint_B8)) {
        return true;
    }
    return false;
}

void mpIsland_8005ACE8(mpIsland* island, Vec3* left, Vec3* right)
{
    int line_id;
    CollLine* line;
    int count;
    bool find_left;
    CollJoint* joint;
    bool find_right;
    int i;

    joint = &mpGetGroundCollJoint()[island->joint_id];
    line_id = joint->inner->ranges[MapLineGroup_Floor].start;
    line = &mpGetGroundCollLine()[line_id];
    count = joint->inner->ranges[MapLineGroup_Floor].count;

    find_left = true;
    find_right = true;
    if (left != NULL) {
        *left = island->pos0;
    } else {
        find_left = false;
    }
    if (right != NULL) {
        *right = island->pos1;
    } else {
        find_right = false;
    }

    for (i = 0; i < count && find_left && find_right; line_id++) {
        if (find_left && line->inner->v0_idx == island->vtx0) {
            mpFloorGetLeft(line_id, left);
        } else if (find_right && line->inner->v1_idx == island->vtx1) {
            mpFloorGetRight(line_id, right);
        }
        i++;
        line++;
    }
}

void mpIsland_8005AE1C(mpIsland** enabled_list, mpIsland** disabled_list,
                       int vtx_start, int vtx_count, bool enabled)
{
    mpIsland* enabled_head;
    mpIsland* disabled_head;
    mpIsland* cur;
    mpIsland* next;
    CollVtx* vtx;
    int end;
    float z_val;
    u16 v0;

    enabled_head = NULL;
    disabled_head = NULL;

    vtx = mpGetGroundCollVtx();
    cur = *enabled_list;
    end = vtx_start + vtx_count;
    z_val = 0.0f;

    for (; cur != NULL; cur = next) {
        v0 = cur->vtx0;
        next = cur->next;
        if ((v0 >= vtx_start || cur->vtx1 >= vtx_start) &&
            (end > v0 || end > cur->vtx1))
        {
            cur->pos0.x = vtx[v0].pos.x;
            cur->pos0.y = vtx[cur->vtx0].pos.y;
            cur->pos0.z = z_val;
            cur->pos1.x = vtx[cur->vtx1].pos.x;
            cur->pos1.y = vtx[cur->vtx1].pos.y;
            cur->pos1.z = z_val;
            if (!enabled && !(cur->flags & mpIsland_Disabled)) {
                cur->flags |= mpIsland_Disabled;
                cur->next = disabled_head;
                disabled_head = cur;
                continue;
            }
        }
        cur->next = enabled_head;
        enabled_head = cur;
    }

    cur = *disabled_list;
    z_val = 0.0f;

    for (; cur != NULL; cur = next) {
        v0 = cur->vtx0;
        next = cur->next;
        if ((v0 >= vtx_start || cur->vtx1 >= vtx_start) &&
            (end > v0 || end > cur->vtx1))
        {
            cur->pos0.x = vtx[v0].pos.x;
            cur->pos0.y = vtx[cur->vtx0].pos.y;
            cur->pos0.z = z_val;
            cur->pos1.x = vtx[cur->vtx1].pos.x;
            cur->pos1.y = vtx[cur->vtx1].pos.y;
            cur->pos1.z = z_val;
            if (enabled && (cur->flags & mpIsland_Disabled)) {
                cur->flags &= ~mpIsland_Disabled;
                cur->next = enabled_head;
                enabled_head = cur;
                continue;
            }
        }
        cur->next = disabled_head;
        disabled_head = cur;
    }

    *enabled_list = enabled_head;
    *disabled_list = disabled_head;
}

void mpIsland_8005B004(mpIsland** list, mpIsland** free_list, int joint_id,
                       int kind, int vtx_start, int vtx_count, bool enabled)
{
    UNUSED u8 _q0[8];
    mpIsland* cur;
    float z_val;
    u8 visited[0x600];
    mpIsland* next;
    mpIsland* prev;
    mpIsland* mpisp;
    CollLine* lines;
    CollVtx* vtx;
    CollJoint* joints;
    int line_idx;
    int end_idx;
    int start_idx;
    int end_total;
    int loop;
    u32 type_flag;
    s16 link;
    int cycle_start;
    float v1_x;
    float v0_x;
    int i;
    PAD_STACK(8);

    type_flag = kind | 0x10;
    prev = NULL;
    cur = *list;

    while (cur != NULL) {
        next = cur->next;
        if (cur->joint_id == joint_id) {
            cur->next = *free_list;
            *free_list = cur;
        } else {
            cur->next = prev;
            prev = cur;
        }
        cur = next;
    }
    *list = prev;

    memzero(visited, sizeof(visited));

    joints = mpGetGroundCollJoint();
    joints = &joints[joint_id];
    lines = mpGetGroundCollLine();
    vtx = mpGetGroundCollVtx();
    z_val = 0.0F;

    end_total = joints->inner->ranges[MapLineGroup_Dynamic].start +
                joints->inner->ranges[MapLineGroup_Dynamic].count;
    line_idx = joints->inner->ranges[MapLineGroup_Dynamic].start;

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
            link = lines[end_idx].inner->prev_id0;
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
                link = lines[start_idx].inner->next_id0;
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

            HSD_ASSERT(0x206, !loop);
        } else {
            i = start_idx = end_idx;
            v1_x = -F32_MAX;
            v0_x = F32_MAX;
            cycle_start = i;

            do {
                if (v0_x > vtx[lines[i].inner->v0_idx].pos.x) {
                    v0_x = vtx[lines[i].inner->v0_idx].pos.x;
                    end_idx = i;
                }
                {
                    if (v1_x > vtx[lines[i].inner->v1_idx].pos.x) {
                        v1_x = vtx[lines[i].inner->v1_idx].pos.x;
                        start_idx = i;
                    }
                }
                link = lines[i].inner->prev_id0;
                (void) lines[link];
                i = link;
            } while (link != cycle_start);
        }

        if ((mpisp = *free_list) != NULL) {
            *free_list = mpisp->next;
        } else {
            mpisp = HSD_MemAlloc(sizeof(mpIsland));
            mpIsland_AssertSeg(mpisp);
        }

        mpisp->flags = enabled ? 0 : mpIsland_Disabled;
        mpisp->next = NULL;
        mpisp->line0 = (s16) end_idx;
        mpisp->line1 = (s16) start_idx;
        mpisp->vtx0 = lines[end_idx].inner->v0_idx;
        mpisp->vtx1 = lines[start_idx].inner->v1_idx;
        mpisp->pos0.x = vtx[mpisp->vtx0].pos.x;
        mpisp->pos0.y = vtx[mpisp->vtx0].pos.y;
        mpisp->pos0.z = z_val;
        mpisp->pos1.x = vtx[mpisp->vtx1].pos.x;
        mpisp->pos1.y = vtx[mpisp->vtx1].pos.y;
        mpisp->pos1.z = z_val;
        mpisp->joint_id = (s16) joint_id;

        mpisp->next = *list;
        *list = mpisp;
    }
}

void mpIsland_8005B334(int joint_id, int vtx_start, int vtx_count,
                       bool enabled)
{
    mpIsland* tail;

    if (mpIsland_80458E88.floors_tail != NULL) {
        mpIsland_80458E88.floors_tail->next = NULL;
    } else {
        mpIsland_80458E88.floors = NULL;
    }

    if (mpIsland_80458E88.ceilings_tail != NULL) {
        mpIsland_80458E88.ceilings_tail->next = NULL;
    } else {
        mpIsland_80458E88.ceilings = NULL;
    }

    mpIsland_8005AE1C(&mpIsland_80458E88.floors,
                      &mpIsland_80458E88.disabled_floors, vtx_start, vtx_count,
                      enabled);
    mpIsland_8005AE1C(&mpIsland_80458E88.ceilings,
                      &mpIsland_80458E88.disabled_ceilings, vtx_start,
                      vtx_count, enabled);
    mpIsland_8005B004(&mpIsland_80458E88.dynamic_floors,
                      &mpIsland_80458E88.free_list, joint_id, CollLine_Floor,
                      vtx_start, vtx_count, enabled);
    mpIsland_8005B004(&mpIsland_80458E88.dynamic_ceilings,
                      &mpIsland_80458E88.free_list, joint_id, CollLine_Ceiling,
                      vtx_start, vtx_count, enabled);

    // Append the dynamic floors to the floor list
    tail = mpIsland_80458E88.floors;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }
    if (tail != NULL) {
        tail->next = mpIsland_80458E88.dynamic_floors;
    } else {
        mpIsland_80458E88.floors = mpIsland_80458E88.dynamic_floors;
    }
    mpIsland_80458E88.floors_tail = tail;

    // Append the dynamic ceilings to the ceiling list
    tail = mpIsland_80458E88.ceilings;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }
    if (tail != NULL) {
        tail->next = mpIsland_80458E88.dynamic_ceilings;
    } else {
        mpIsland_80458E88.ceilings = mpIsland_80458E88.dynamic_ceilings;
    }
    mpIsland_80458E88.ceilings_tail = tail;
}

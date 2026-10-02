#ifndef GALE01_05A6F8
#define GALE01_05A6F8

#include <melee/mp/forward.h>

#include <dolphin/mtx.h>
#include <melee/mp/types.h>

/* 05A6F8 */ void mpIsland_8005A6F8(void);
/* 05A728 */ void mpIsland_8005A728(void);
/* 05AB54 */ mpIsland* mpIsland_8005AB54(int surface_idx);
/* 05AC14 */ mpIsland* mpIsland_8005AC14(Vec3* pos, float dy);
/* 05AC8C */ bool mpIsland_8005AC8C(mpIsland* island);
/* 05ACE8 */ void mpIsland_8005ACE8(mpIsland* island, Vec3* left, Vec3* right);
/* 05AE1C */ void mpIsland_8005AE1C(mpIsland** enabled_list,
                                    mpIsland** disabled_list, int vtx_start,
                                    int vtx_count, bool enabled);
/* 05B004 */ void mpIsland_8005B004(mpIsland** list, mpIsland** free_list,
                                    int joint_id, int kind, int vtx_start,
                                    int vtx_count, bool enabled);
/* 05B334 */ void mpIsland_8005B334(int joint_id, int vtx_start, int vtx_count,
                                    bool enabled);
/* 3B73E8 */ extern mpIsland_Palette const mpIsland_TerrainPalette;
/* 458E88 */ extern struct mpIsland_80458E88_t mpIsland_80458E88;

#endif

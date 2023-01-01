#include <melee/ft/fighter.h>

#define MAX_FT_PARTS 140

#define JOBJ_NEXT(jobj)   ((jobj) == NULL ? NULL : (jobj)->next)
#define JOBJ_PARENT(jobj) ((jobj) == NULL ? NULL : (jobj)->parent)
#define JOBJ_CHILD(jobj)  ((jobj) == NULL ? NULL : (jobj)->child)

extern void func_80074194(Fighter* fighter, FighterBone* bone, HSD_JObj* jobj,
                          s32* dobj_index, u32 hierarchy_depth);

#define JOBJ_NEXT(jobj)   ((jobj) == NULL ? (HSD_JObj*)NULL : (jobj)->next)
#define JOBJ_PARENT(jobj) ((jobj) == NULL ? (HSD_JObj*)NULL : (jobj)->parent)
#define JOBJ_CHILD(jobj)  ((jobj) == NULL ? (HSD_JObj*)NULL : (jobj)->child)

#define MAX_FT_PARTS 140

typedef struct _FighterPartsTable {
    u8* joint_to_part;
    u8* part_to_joint;
    u32 parts_num;
} FighterPartsTable;

extern FighterPartsTable** ftPartsTable;

extern s32 func_8007506C(s32 ftkind, s32 part);

void func_800743E0(HSD_GObj* fighter_obj)
{
    u32 offset = 0;
    u32 part = 0;
    u32 hierarchy_depth = 0;
    HSD_JObj* jobj = fighter_obj->hsd_obj;
    Fighter* fighter = getFighter(fighter_obj);
    u32 dobj_count = 0;

    if (ftPartsTable[fighter->x4_fighterKind]->parts_num > MAX_FT_PARTS) {
        OSReport("fighter parts num over! player %d\n", fighter->xC_playerID);
        assert_line(503, 0);
    }

    for (; jobj != NULL; part++) {
        if (func_8007506C(fighter->x4_fighterKind, part) != 0) {
            fighter->x5E8_fighterBones[part].x0_jobj = NULL;
            continue;
        }

        func_80074194(fighter, fighter->x5E8_fighterBones[part].x0_jobj,
                      jobj, &dobj_count, hierarchy_depth);

        if ((HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) || JOBJ_CHILD(jobj) == NULL) {
            if (JOBJ_NEXT(jobj) == NULL) {
                while (1) {
                    if (JOBJ_PARENT(jobj) == NULL) {
                        jobj = NULL;
                        break;
                    }

                    if (JOBJ_NEXT(JOBJ_PARENT(jobj)) != NULL) {
                        jobj = JOBJ_NEXT(JOBJ_PARENT(jobj));
                        hierarchy_depth--;
                        break;
                    }

                    jobj = JOBJ_PARENT(jobj);
                    hierarchy_depth--;
                }
            } else {
                jobj = JOBJ_NEXT(jobj);
            }
        } else {
            jobj = JOBJ_CHILD(jobj);
            hierarchy_depth++;
        }
    }

    fighter->x5EC_dobj_list.count = dobj_count;
    if (part != ftPartsTable[fighter->x4_fighterKind]->parts_num) {
        OSReport("fighter parts num not match! player %d\n", fighter->xC_playerID);
        assert_line(546, 0);
    }
}
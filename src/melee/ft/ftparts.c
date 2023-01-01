#include <melee/ft/fighter.h>

#define MAX_FT_PARTS 140

#define JOBJ_NEXT(jobj) ((jobj) == NULL ? NULL : (jobj)->next)
#define JOBJ_PARENT(jobj) ((jobj) == NULL ? NULL : (jobj)->parent)
#define JOBJ_CHILD(jobj) ((jobj) == NULL ? NULL : (jobj)->child)

extern u32 func_8007506C(s32 ftkind, s32 part);

extern void func_80074194(Fighter* fighter, FighterBone* bone, HSD_JObj* jobj,
                          u32* dobj_index, u32 tree_depth);

void Fighter_SetupParts(HSD_GObj* fighter_obj)
{
    HSD_JObj* jobj = fighter_obj->hsd_obj;
    Fighter* fighter = (Fighter*) fighter_obj->user_data;
    u32 part = 0;
    u32 tree_depth = 0;
    u32 dobj_count = 0;

    if (ftPartsTable[fighter->x4_fighterKind]->parts_num > MAX_FT_PARTS) {
        OSReport("fighter parts num over! player %d\n", fighter->xC_playerID);
        __assert("ftparts.c", 503, "0");
    }

    while (jobj != NULL) {
        if (func_8007506C(fighter->x4_fighterKind, part) != 0) {
            fighter->x5E8_fighterBones[part].x0_jobj = NULL;
            part++;
            continue;
        }

        func_80074194(fighter, &fighter->x5E8_fighterBones[part], jobj,
                      &dobj_count, tree_depth);
        part++;

        if (!(HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) &&
            JOBJ_CHILD(jobj) != NULL)
        {
            // Descend the left side of the tree
            jobj = JOBJ_CHILD(jobj);
            tree_depth++;
            continue;
        }

        if (JOBJ_NEXT(jobj) != NULL) {
            // Visit bottom nodes from left to right
            jobj = JOBJ_NEXT(jobj);
            continue;
        }

        while (TRUE) {
            if (JOBJ_PARENT(jobj) == NULL) {
                // Finished
                jobj = NULL;
                break;
            } else {
                // Go back up the tree until we can continue to the right
                HSD_JObj* parent = JOBJ_PARENT(jobj);
                HSD_JObj* parent_next = JOBJ_NEXT(parent);

                if (parent_next != NULL) {
                    jobj = JOBJ_PARENT(jobj);
                    jobj = JOBJ_NEXT(jobj);
                    tree_depth--;
                    break;
                }

                jobj = JOBJ_PARENT(jobj);
                tree_depth--;
            }
        }
    }

    fighter->x5EC_dobj_list.count = dobj_count;

    if (part != ftPartsTable[fighter->x4_fighterKind]->parts_num) {
        OSReport("fighter parts num not match! player %d\n",
                 fighter->xC_playerID);
        __assert("ftparts.c", 546, "0");
    }
}

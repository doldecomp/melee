/**
 * @file gobjgxlink.c
 * @brief Game Object GX Link rendering queue management.
 * @details Implements insertion, unlinking, and reordering of GObjs within
 *          GX rendering queues (gx_link buckets). Maintains doubly linked lists
 *          sorted by render_priority, ensuring correct draw order across
 *          standard entity layers and camera rendering passes.
 * Module prefix: HSD_GObjGXLink / GObj_GX (SysDolphin Base Library entity system)
 */

#include "gobjgxlink.h"

#include "debug.h"
#include "gobj.h"

/**
 * @brief Inserts a GObj into a GX link queue immediately after hiprio_gobj.
 * @details If hiprio_gobj is NULL, gobj is placed at the head of the queue.
 *          Updates both head (HSD_GObjGXLinkHead) and tail (HSD_GObj_804D7820)
 *          pointers as needed.
 * @param gobj Target Game Object to insert.
 * @param hiprio_gobj Predecessor Game Object, or NULL if inserting at head.
 */
void GObj_GXReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj)
{
    u32 link = gobj->gx_link;

    gobj->prev_gx = hiprio_gobj;
    if (hiprio_gobj != NULL) {
        // If there is a higher priority predecessor, insert after it
        gobj->next_gx = hiprio_gobj->next_gx;
        hiprio_gobj->next_gx = gobj;
    } else {
        // Otherwise, place at the head of this GX link queue
        gobj->next_gx = HSD_GObjGXLinkHead[link];
        HSD_GObjGXLinkHead[link] = gobj;
    }

    if (gobj->next_gx != NULL) {
        gobj->next_gx->prev_gx = gobj;
    } else {
        // Queue tail updated
        HSD_GObj_804D7820[gobj->gx_link] = gobj;
    }
}

/**
 * @brief Inserts a GObj by scanning backwards from the tail of its GX link queue.
 * @details Traverses backwards while elements have higher render_priority than gobj,
 *          then inserts immediately after the first element with render_priority <= gobj.
 * @param gobj Target Game Object to insert.
 */
static inline void GObj_GXInsertFromTail(HSD_GObj* gobj)
{
    HSD_GObj* curr_gobj = HSD_GObj_804D7820[gobj->gx_link];
    while (curr_gobj != NULL && curr_gobj->render_priority > gobj->render_priority) {
        curr_gobj = curr_gobj->prev_gx;
    }
    GObj_GXReorder(gobj, curr_gobj);
}

/**
 * @brief Inserts a GObj by scanning forwards from the head of its GX link queue.
 * @details Traverses forwards while elements have lower render_priority than gobj,
 *          then inserts immediately before the first element with render_priority >= gobj.
 * @param gobj Target Game Object to insert.
 */
static inline void GObj_GXInsertFromHead(HSD_GObj* gobj)
{
    HSD_GObj* curr_gobj = HSD_GObjGXLinkHead[gobj->gx_link];
    while (curr_gobj != NULL && curr_gobj->render_priority < gobj->render_priority) {
        curr_gobj = curr_gobj->next_gx;
    }
    GObj_GXReorder(gobj,
                   curr_gobj != NULL ? curr_gobj->prev_gx : HSD_GObj_804D7820[gobj->gx_link]);
}

/**
 * @brief Dispatches insertion of a GObj into its GX link queue based on insertion mode.
 * @param gobj Target Game Object to insert.
 * @param where Insertion strategy:
 *              - 0: Scan backwards from tail
 *              - 1: Scan forwards from head
 *              - 3: Insert immediately before position (position->prev_gx)
 * @param position Reference GObj used when where == 3.
 */
static inline void GObj_GXInsert(HSD_GObj* gobj, s32 where, HSD_GObj* position)
{
    switch (where) {
    case 0:
        GObj_GXInsertFromTail(gobj);
        break;
    case 1:
        GObj_GXInsertFromHead(gobj);
        break;
    case 3:
        GObj_GXReorder(gobj, position->prev_gx);
        break;
    }
}

/**
 * @brief Configures GX render link properties and inserts the GObj from tail.
 * @param gobj Target Game Object.
 * @param render_cb Callback function invoked during GX passes.
 * @param gx_link GX render link bucket index (0..gx_link_max).
 * @param priority Render priority within the bucket (lower draws earlier).
 */
void GObj_SetupGXLink(HSD_GObj* gobj, GObj_RenderFunc render_cb, u8 gx_link,
                      u32 priority)
{
    HSD_ASSERT(167, gx_link <= HSD_GObjLibInitData.gx_link_max);
    gobj->render_cb = render_cb;
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 0, NULL);
}

/**
 * @brief Assigns a GObj to the camera/max GX link group and inserts from tail.
 * @details Places the GObj in bucket (gx_link_max + 1), which is evaluated during
 *          camera update traversals in HSD_GObj_80390FC0.
 * @param gobj Camera or top-level render Game Object.
 * @param render_cb Callback function invoked during camera pass.
 * @param priority Render priority within the max GX bucket.
 */
void GObj_SetupGXLinkMax(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                         u32 priority)
{
    u8 max_link = HSD_GObjLibInitData.gx_link_max;

    gobj->render_cb = render_cb;
    gobj->gx_link = max_link + 1;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 0, NULL);
}

/**
 * @brief Assigns a GObj to the camera/max GX link group and inserts from head.
 * @details Similar to GObj_SetupGXLinkMax, but inserts via head traversal to maintain
 *          ascending priority order among equal or higher priority entries.
 * @param gobj Camera or top-level render Game Object.
 * @param render_cb Callback function invoked during camera pass.
 * @param priority Render priority within the max GX bucket.
 */
void GObj_SetupGXLinkMaxSorted(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                                u32 priority)
{
    u8 max_link = HSD_GObjLibInitData.gx_link_max;

    gobj->render_cb = render_cb;
    gobj->gx_link = max_link + 1;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 1, NULL);
}

/**
 * @brief Unlinks a GObj from its current GX render link queue and resets its GX fields.
 * @param gobj Target Game Object to unlink.
 */
void HSD_GObjGXLink_8039084C(HSD_GObj* gobj)
{
    HSD_GObj* prev_gobj;
    HSD_GObj* next_gobj;

    HSD_ASSERT(415, gobj->gx_link != HSD_GOBJ_GXLINK_NONE);

    prev_gobj = gobj->prev_gx;
    if (prev_gobj != NULL) {
        prev_gobj->next_gx = gobj->next_gx;
    } else {
        HSD_GObjGXLinkHead[gobj->gx_link] = gobj->next_gx;
    }
    next_gobj = gobj->next_gx;
    if (next_gobj != NULL) {
        next_gobj->prev_gx = gobj->prev_gx;
    } else {
        HSD_GObj_804D7820[gobj->gx_link] = gobj->prev_gx;
    }
    gobj->gx_link = HSD_GOBJ_GXLINK_NONE;
    gobj->render_priority = 0;
    gobj->prev_gx = NULL;
    gobj->next_gx = NULL;
}

/**
 * @brief Modifies a GObj's GX render link group and priority, re-inserting from head.
 * @param gobj Target Game Object.
 * @param gx_link New GX render link bucket index.
 * @param priority New render priority within the bucket.
 */
void HSD_GObjGXLink_80390908(HSD_GObj* gobj, u8 gx_link, u8 priority)
{
    HSD_ASSERT(535, gx_link <= HSD_GObjLibInitData.gx_link_max);
    HSD_GObjGXLink_8039084C(gobj);
    gobj->gx_link = gx_link;
    gobj->render_priority = priority;
    GObj_GXInsert(gobj, 1, NULL);
}

/**
 * @brief Adopts the GX link and priority of another GObj and inserts immediately before it.
 * @param gobj Target Game Object to reposition.
 * @param other Reference Game Object whose GX queue and priority are inherited.
 */
void HSD_GObjGXLink_803909D8(HSD_GObj* gobj, HSD_GObj* other)
{
    u8 target_link;
    u8 target_prio;

    target_prio = other->render_priority;
    target_link = other->gx_link;

    HSD_GObjGXLink_8039084C(gobj);
    gobj->gx_link = target_link;
    gobj->render_priority = target_prio;
    GObj_GXInsert(gobj, 3, other);
}

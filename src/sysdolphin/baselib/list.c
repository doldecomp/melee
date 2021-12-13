#include <string.h>
#include <types.h>
#include <stddef.h>

#include "sysdolphin/baselib/list.h"

HSD_ObjAllocData slist_alloc_data;
HSD_ObjAllocData dlist_alloc_data;

void HSD_ListInitAllocData()
{
    HSD_ObjAllocInit(&slist_alloc_data, sizeof(HSD_SList), 4);
    HSD_ObjAllocInit(&dlist_alloc_data, sizeof(HSD_DList), 4);
}

HSD_ObjAllocData *HSD_SListGetAllocData()
{
    return &slist_alloc_data;
}

HSD_ObjAllocData *HSD_DListGetAllocData()
{
    return &dlist_alloc_data;
}

extern char lbl_804D5F48[7]; // "list.c"
extern char lbl_804D5F50[5]; // "list"
HSD_SList *HSD_SListAlloc()
{
    HSD_SList *list;

    list = HSD_ObjAlloc(&slist_alloc_data);
    if (list == NULL) {
        __assert(lbl_804D5F48, 76, lbl_804D5F50);
    }

    memset(list, 0, sizeof(HSD_SList));
    return list;
}

static inline HSD_SList *HSD_SListAlloc_inline()
{
    HSD_SList *list;

    list = HSD_ObjAlloc(&slist_alloc_data);
    if (list == NULL) {
        __assert(lbl_804D5F48, 76, lbl_804D5F50);
    }

    memset(list, 0, sizeof(HSD_SList));
    return list;
}

HSD_SList *HSD_SListAllocAndAppend(HSD_SList *next, void *data)
{
    HSD_SList *list;

    list = HSD_SListAlloc_inline();
    list->data = data;
    
    return HSD_SListAppendList(next, list);
}

HSD_SList *HSD_SListAllocAndPrepend(HSD_SList *next, void *data)
{
    HSD_SList *list;

    list = HSD_SListAlloc_inline();
    list->data = data;
    
    return HSD_SListPrependList(next, list);
}

extern char lbl_804D5F58[5]; // "next"
HSD_SList *HSD_SListAppendList(HSD_SList *list, HSD_SList *next)
{
    if (next == NULL) {
        __assert(lbl_804D5F48, 179, lbl_804D5F58);
    }

    if (list != NULL) {
        next->next = list->next;
        list->next = next;
        return list;
    }
    else {
        next->next = NULL;
        return next;
    }
}

extern char lbl_804D5F60[5]; // "prev"
HSD_SList *HSD_SListPrependList(HSD_SList *list, HSD_SList *prev)
{
    if (prev == NULL) {
        __assert(lbl_804D5F48, 202, lbl_804D5F60);
    }

    prev->next = list;
    return prev;
}

HSD_SList *HSD_SListRemove(HSD_SList *list)
{
    HSD_SList *next;

    if (list != NULL) {
        next = list->next;
        HSD_ObjFree(&slist_alloc_data, list);
        return next;
    }

    return NULL;
}
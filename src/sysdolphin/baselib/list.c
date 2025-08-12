#include "list.h"

#include "debug.h"

#include <platform.h>

#include <__mem.h>

HSD_ObjAllocData slist_alloc_data;
HSD_ObjAllocData dlist_alloc_data;

void HSD_ListInitAllocData(void)
{
    HSD_ObjAllocInit(&slist_alloc_data, sizeof(HSD_SList), 4);
    HSD_ObjAllocInit(&dlist_alloc_data, sizeof(HSD_DList), 4);
}

HSD_ObjAllocData* HSD_SListGetAllocData(void)
{
    return &slist_alloc_data;
}

HSD_ObjAllocData* HSD_DListGetAllocData(void)
{
    return &dlist_alloc_data;
}

HSD_SList* HSD_SListAlloc(void)
{
    HSD_SList* list;

    list = HSD_ObjAlloc(&slist_alloc_data);
    HSD_ASSERT(76, list);

    memset(list, 0, sizeof(HSD_SList));
    return list;
}

HSD_SList* HSD_SListAllocAndAppend(HSD_SList* next, void* data)
{
    HSD_SList* list;

    list = HSD_SListAlloc();
    list->data = data;

    return HSD_SListAppendList(next, list);
}

HSD_SList* HSD_SListAllocAndPrepend(HSD_SList* next, void* data)
{
    HSD_SList* list;

    list = HSD_SListAlloc();
    list->data = data;

    return HSD_SListPrependList(next, list);
}

HSD_SList* HSD_SListAppendList(HSD_SList* list, HSD_SList* next)
{
    HSD_ASSERT(179, next);

    if (list != NULL) {
        next->next = list->next;
        list->next = next;
        return list;
    } else {
        next->next = NULL;
        return next;
    }
}

HSD_SList* HSD_SListPrependList(HSD_SList* list, HSD_SList* prev)
{
    HSD_ASSERT(202, prev);
    prev->next = list;
    return prev;
}

HSD_SList* HSD_SListRemove(HSD_SList* list)
{
    HSD_SList* next;

    if (list != NULL) {
        next = list->next;
        HSD_ObjFree(&slist_alloc_data, list);
        return next;
    }

    return NULL;
}

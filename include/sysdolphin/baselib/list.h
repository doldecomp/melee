#ifndef _list_h_
#define _list_h_

#include <sysdolphin/baselib/objalloc.h>

typedef struct _HSD_SList {
    struct _HSD_SList* next;
    void* data;
} HSD_SList;

typedef struct _HSD_DList {
    struct _HSD_DList* next;
    struct _HSD_DList* prev;
    void* data;
} HSD_DList;

void HSD_ListInitAllocData();
HSD_ObjAllocData *HSD_SListGetAllocData();
HSD_ObjAllocData *HSD_DListGetAllocData();
HSD_SList *HSD_SListAlloc();
HSD_SList *HSD_SListAllocAndAppend(HSD_SList *next, void *data);
HSD_SList *HSD_SListAllocAndPrepend(HSD_SList *prev, void *data);
HSD_SList *HSD_SListAppendList(HSD_SList *list, HSD_SList *next);
HSD_SList *HSD_SListPrependList(HSD_SList *list, HSD_SList *prev);
HSD_SList *HSD_SListRemove(HSD_SList *list);

#endif

#include "sysdolphin/baselib/displayfunc.h"

typedef struct _HSD_ZList {
  Mtx pmtx;
  MtxPtr vmtx;
  HSD_JObj* jobj;
  u32 rendermode;

  struct {
    struct _HSD_ZList *texedge;
    struct _HSD_ZList *xlu;
  } sort;

  struct _HSD_ZList *next;
} HSD_ZList;

HSD_ObjAllocData zlist_alloc_data;

void HSD_ZListInitAllocData(void)
{
  HSD_ObjAllocInit(&zlist_alloc_data, sizeof(HSD_ZList), 4);
}

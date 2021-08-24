#include "displayfunc.h"

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

extern HSD_ObjAllocData lbl_804C0918;

void HSD_ZListInitAllocData(void)
{
  HSD_ObjAllocInit(&lbl_804C0918, sizeof(HSD_ZList), 4);
}

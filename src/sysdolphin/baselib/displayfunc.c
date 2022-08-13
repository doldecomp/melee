#include <sysdolphin/baselib/displayfunc.h>

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

void HSD_StateInitDirect(int vtxfmt, u32 param_2)
{
    HSD_ClearVtxDesc();
    GXSetVtxAttrFmt(vtxfmt, 9, 1, 4, 0);
    GXSetVtxAttrFmt(vtxfmt, 0xB, 1, 5, 0);
    HSD_StateInitTev();
    HSD_SetupRenderMode(param_2 | 0x28000000);
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetCurrentMtx(0);
}

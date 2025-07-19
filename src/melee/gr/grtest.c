#include <platform.h>

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "gr/granime.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/grtest.h"
#include "gr/types.h"
#include "gr/stage.h"
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include "gr/grdisplay.h"
#include <sysdolphin/baselib/controller.h>
S16Vec3 grTe_803E56B8[] = { { 0, 2, 1 }, { 1, 2, 2 }, { 2, 2, 3 }, { 3, 2, 4 }, { 4, 2, 5 }, { 5, 2, 6 }, { 6, 2, 7 }, { 7, 2, 8 }, { 8, 2, 9 }, { 9, 2, 10 }, { 10, 2, 11 }, { 12, 2, 16 }, { 13, 2, 17 }};
StageCallbacks grTe_803E5708[] = {
    { grTest_80207130,
	grTest_8020715C,
	grTest_80207164,
	grTest_80207168,
	0 },
    { grTest_802073D0,
	grTest_802073FC,
	grTest_80207404,
	grTest_80207408,
	0 },
    { grTest_8020716C,
	grTest_802071BC,
	grTest_802071C4,
	grTest_802073AC,
	0xC0000000 },
    { 0,
	0,
	0,
	0,
	0 }
};
StageData grTe_803E5764 = {
    0x01,
    grTe_803E5708,
    "/GrTe.dat",
    grTest_80206E30,
    grTest_80206E2C,
    grTest_80207014,
    grTest_80207018,
    grTest_8020703C,
    grTest_8020740C,
    grTest_80207414,
    1,
    grTe_803E56B8
};

float grTe_804D6A48;
//float grTe_804DB81C=0.0;
//float grTe_804DB820=-1.2217305;
//float grTe_804DB824=0.08726646;
//float grTe_804DB828=1.2217305;

void grTest_80206E2C(int) {}

/// #grTest_80206E30
void grTest_80206E30(void)
{
    HSD_GObj* r3;
    HSD_JObj* jobj;

    //grTest_802073B0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
	grTest_80207044(0);
	r3 = grTest_80207044(2);
	GET_GROUND(r3)->x8_callback = grTest_802073B0;
	r3 = grTest_80207044(1);
	jobj =  r3->hsd_obj;
	HSD_JObjSetScaleX(jobj,80.0);
	HSD_JObjSetScaleY(jobj,80.0);
	HSD_JObjSetScaleZ(jobj,80.0);
	
    //grIzumi_801CBCE8(0);
    //grIzumi_801CBCE8(1);
    //r3 = grIzumi_801CBCE8(3);
    //grAnime_801C8780(r3, 3, 0, 0.0f, 1.0f);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grTest_80207014(void) {}

void grTest_80207018(void)
{
    grZakoGenerator_801CAE04(false);
}

bool grTest_8020703C(void)
{
    return false;
}

/// #grTest_80207044
HSD_GObj* grTest_80207044(int gobj_id) {
	HSD_GObj* gobj;
	StageCallbacks* callbacks = &grTe_803E5708[gobj_id];
    gobj = Ground_801C14D0(gobj_id);
    if (gobj != NULL) {
		Ground* gp = GET_GROUND(gobj);
		gp->x8_callback = 0;
		gp->xC_callback = 0;
		Gobj_SetupGXLink(gobj,grDisplay_801C5DB0,3,0);
		//if(grIm_803E4718[gobj_id]) {
		//	int bruh = 4;
		//}
		if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }

        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }

        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
		//HSD_GObjProc_8038FD54(gobj,gobj_id,4);
		//if(callbacks) {
		//	callbacks->callback0(gobj);
		//}
	} else {
		OSReport("%s:%d: couldn t get gobj(id=%d)\n","grtest.c",0x35C, gobj_id);
	}
    
    return gobj;
}

void grTest_80207130(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_8020715C(HSD_GObj* gobj)
{
    return false;
}

void grTest_80207164(HSD_GObj* gobj) {}

void grTest_80207168(HSD_GObj* gobj) {}

void grTest_8020716C(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_802071BC(HSD_GObj* gobj)
{
    return false;
}

void grTest_802071C4(HSD_GObj* gobj){
	HSD_JObj* iVar2;
	u32 uVar3;
	HSD_PadStatus* pad;// = &HSD_PadMasterStatus[1];
	if ((HSD_PadMasterStatus[1].trigger & 0x100) != 0) {//HSD_PadMasterStatus[0]
		iVar2 = Ground_801C3FA4(gobj,0x10);
		if (iVar2) {
			//uVar3 = HSD_JObjGetFlags(iVar2);
			if (HSD_JObjGetFlags(iVar2) & 0x10) {
				HSD_JObjClearFlags(iVar2,0x10);
			} else {
				HSD_JObjSetFlags(iVar2,0x10);
			}
			grTe_804D6A48 = (float)0.0;
		}
	}
	pad = &HSD_PadMasterStatus[2];
	if ((HSD_PadMasterStatus[2].trigger & 0x100) != 0) {//HSD_PadMasterStatus[0]
		iVar2 = Ground_801C3FA4(gobj,0x11);
		if (iVar2) {
			//uVar3 = HSD_JObjGetFlags(iVar2);
			if (HSD_JObjGetFlags(iVar2) & 0x10) {
				HSD_JObjClearFlags(iVar2,0x10);
			} else {
				HSD_JObjSetFlags(iVar2,0x10);
			}
			grTe_804D6A48 = (float)0.0;
		}
	}
	pad = &HSD_PadMasterStatus[1];
	uVar3 = pad->button;
	if (uVar3 & 0x400) {
		if (grTe_804D6A48 > (float)-1.2217305 ) {
			grTe_804D6A48 = grTe_804D6A48 - (float)0.08726646;
		}
	}
	if (uVar3 & 0x800) {
		if (grTe_804D6A48 < (float)1.2217305) {
			grTe_804D6A48 = grTe_804D6A48 + (float)0.08726646;
		}
	}
	iVar2 = Ground_801C3FA4(gobj,11);
	if (iVar2) {
		HSD_JObjSetRotationZ(iVar2,grTe_804D6A48);
	}
}

void grTest_802073AC(HSD_GObj* gobj) {}

void grTest_802073B0(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTest_802073D0(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_802073FC(HSD_GObj* gobj)
{
    return false;
}

void grTest_80207404(HSD_GObj* gobj) {}

void grTest_80207408(HSD_GObj* gobj) {}

struct DynamicsDesc* grTest_8020740C(int)
{
    return false;
}

bool grTest_80207414(Vec3* a, int id, HSD_JObj* jobj)
{
    return true;
}

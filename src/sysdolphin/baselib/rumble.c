#include <platform.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/pad/forward.h>
#include <dolphin/pad/Pad.h>
#include <baselib/controller.h>
#include <baselib/rumble.h>

extern PadLibData HSD_PadLibData;

struct Struct804C22E0 lbl_804C22E0[4];

void HSD_PadRumbleOn(u8 a)
{
    bool intrEnabled = OSDisableInterrupts();
    struct Struct804C22E0* r5 = &lbl_804C22E0[a];

    r5->unk2 = 1;
    OSRestoreInterrupts(intrEnabled);
}

void func_803780DC(u8 a)
{
    bool intrEnabled = OSDisableInterrupts();
    struct Struct804C22E0* r5 = &lbl_804C22E0[a];

    r5->unk2 = 0;
    OSRestoreInterrupts(intrEnabled);
}

void func_80378128(struct Struct804C22E0* a, HSD_PadRumbleListData* b)
{
    RumbleInfo* r6 = &HSD_PadLibData.rumble_info;
    HSD_PadRumbleListData** r5 = &a->unk8;

    while ((*r5) != b)
        r5 = &(*r5)->next;
    *r5 = b->next;
    a->unk4--;
    b->next = r6->listdatap;
    r6->listdatap = b;
}

void func_80378170(u8 a)
{
    struct Struct804C22E0* r28 = &lbl_804C22E0[a];
    bool r29 = OSDisableInterrupts();
    HSD_PadRumbleListData* r4 = r28->unk8;

    while (r4 != NULL) {
        HSD_PadRumbleListData* r30 = r4->next;
        func_80378128(r28, r4);
        r4 = r30;
    }
    OSRestoreInterrupts(r29);
}

void func_80378208(void)
{
    int i;

    for (i = 0; i < 4; i++)
        func_80378170(i);
}

void func_80378280(u8 a, int b)
{
    struct Struct804C22E0* r31 = &lbl_804C22E0[a];
    bool r3 = OSDisableInterrupts();
    HSD_PadRumbleListData* r7 = r31->unk8;

    while (r7 != NULL) {
        HSD_PadRumbleListData* r6 = r7->next;
        if (r7->id == (unsigned) b)
            func_80378128(r31, r7);
        r7 = r6;
    }
    OSRestoreInterrupts(r3);
}

void func_80378330_inline(u8 a, int b)
{
    bool intrEnabled = OSDisableInterrupts();
    HSD_PadRumbleListData* r4 = lbl_804C22E0[a].unk8;

    while (r4 != NULL) {
        HSD_PadRumbleListData* next = r4->next;

        r4->pause = b;
        r4 = next;
    }
    OSRestoreInterrupts(intrEnabled);
}

void func_80378330(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    int i;
    for (i = 0; i < 4; i++)
        func_80378330_inline(i, 1);
}

void func_803783B0(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    int i;
    for (i = 0; i < 4; i++)
        func_80378330_inline(i, 0);
}

void func_80378430_inline(HSD_PadRumbleListData** r6,
                          HSD_PadRumbleListData* r7)
{
    HSD_PadRumbleListData* r5;

    while ((r5 = *r6) != NULL && r5->pri <= r7->pri)
        r6 = &r5->next;
    r7->next = r5;
    *r6 = r7;
}

int func_80378430(u8 a, int b, int c, int d, void* e)
{
    struct RumbleInfo* r31 = &HSD_PadLibData.rumble_info;
    struct Struct804C22E0* r30 = &lbl_804C22E0[a];
    int r29 = 0;
    bool intrEnabled = OSDisableInterrupts();
    HSD_PadRumbleListData* r7 = r31->listdatap;

    if (r7 != NULL && r30->unk4 < r31->max_list) {
        r31->listdatap = r7->next;
        r7->id = b;
        r7->pause = 0;
        r7->pri = d;
        r7->status = 0;
        r7->loop_count = 0;
        r7->wait = 0;
        r7->frame = c;
        r7->stack = NULL;
        r7->headp = e;
        r7->listp = e;
        func_80378430_inline(&r30->unk8, r7);
        r30->unk4++;
        r29 = 1;
    }
    OSRestoreInterrupts(intrEnabled);
    return r29;
}

void func_80378524(int a)
{
    bool intrEnabled = OSDisableInterrupts();

    HSD_PadLibData.rumble_info.unk2 = a;
    OSRestoreInterrupts(intrEnabled);
}

int func_80378560(HSD_PadRumbleListData* a, u8* b)
{
    if (a->pause == 1)
        return 0;
    while (a->wait == 0) {
        switch ((*(u8*) a->listp >> 5) & 7) {
        case 0:
            if (a->frame == -2)
                return 1;
            a->listp = a->headp;
            break;
        case 1:
            a->status = 2;
            a->wait = *a->listp & 0x1FFF;
            a->listp++;
            break;
        case 2:
            a->status = 1;
            a->wait = *a->listp & 0x1FFF;
            a->listp++;
            break;
        case 3:
            a->status = 0;
            a->wait = *a->listp & 0x1FFF;
            a->listp++;
            break;
        case 4:
            a->loop_count = *a->listp & 0x1FFF;
            a->listp++;
            a->stack = a->listp;
            break;
        case 5:
            if (--a->loop_count != 0)
                a->listp = a->stack;
            else
                a->listp++;
            break;
        }
    }
    *b = a->status;
    a->wait--;
    if (a->frame != -1 && a->frame != -2) {
        if (--a->frame == 0)
            return 1;
    }
    return 0;
}

void HSD_PadRumbleInterpret_inline(HSD_PadRumbleListData** r6,
                                   HSD_PadRumbleListData* r29)
{
    HSD_PadRumbleListData* r5;

    while ((r5 = *r6) != r29)
        r6 = &r5->next;
    *r6 = r29->next;
}

void HSD_PadRumbleInterpret(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    struct RumbleInfo* r31 = &HSD_PadLibData.rumble_info;
    struct Struct804C22E0* r30 = lbl_804C22E0;
    HSD_PadRumbleListData* r29;
    HSD_PadRumbleListData* r28;

    int i;
    for (i = 0; i < 4; i++, r30++) {
        r30->unk1 = 0;
        if (r31->unk2 == 0) {
            r30->unk1 = r30->unk2;
            r29 = r30->unk8;
            while (r29 != NULL) {
                r28 = r29->next;

                if (func_80378560((void*) r29, &r30->unk1) != 0) {
                    HSD_PadRumbleInterpret_inline(&r30->unk8, r29);
                    r30->unk4--;
                    r29->next = r31->listdatap;
                    r31->listdatap = r29;
                }
                r29 = r28;
            }
        }
        if (r30->unk1 != r30->unk0) {
            switch (r30->unk1) {
            case 0:
                PADControlMotor(i, 2);
                break;
            case 1:
                PADControlMotor(i, 0);
                break;
            case 2:
                PADControlMotor(i, 1);
                break;
            }
            r30->unk0 = r30->unk1;
        }
    }
}

struct Struct804C22E0 lbl_80406DE0 = { 0 };

void HSD_PadRumbleInit(u16 a, void* b)
{
    struct RumbleInfo* r6 = &HSD_PadLibData.rumble_info;
    int i;

    r6->unk2 = 0;
    r6->max_list = a;
    r6->listdatap = b;
    if (a != 0) {
        for (i = 0; i < a - 1; i++)
            r6->listdatap[i].next = &r6->listdatap[i + 1];
        r6->listdatap[i].next = 0;
    }
    for (i = 0; i < 4; i++)
        lbl_804C22E0[i] = lbl_80406DE0;
}

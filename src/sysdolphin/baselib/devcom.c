#include "devcom.h"

#include "devcom.static.h"

#include <baselib/debug.h>
#include <baselib/synth.h>

bool HSD_DevComIsBusy(int idx)
{
    return (bool) devComStatus[idx];
}

static void HSD_DevComUnlink(HSD_DevCom* dc)
{
    HSD_DevCom* curr;
    bool enabled = OSDisableInterrupts();
    int i = dc->dcReq & 3;

    if (devComStatus[i] == dc) {
        devComStatus[i] = dc->next;
        if (HSD_DevCom_804C6330[i] == dc) {
            HSD_DevCom_804C6330[i] = 0;
        }
        goto cleanup;
    }

    for (curr = devComStatus[i]; curr->next != NULL; curr = curr->next) {
        if (curr->next == dc) {
            curr->next = dc->next;
            if (HSD_DevCom_804C6330[i] == dc) {
                HSD_DevCom_804C6330[i] = curr;
            }
            OSRestoreInterrupts(enabled);
            return;
        }
    }
    HSD_ASSERT(0x6E, 0);

cleanup:
    OSRestoreInterrupts(enabled);
}

static void HSD_DevComStdCallback(ARQRequest* request)
{
    int i;

    if (request == &devComARQR[0][0]) {
        i = 0;
    } else if (request == &devComARQR[1][0]) {
        i = 1;
    } else {
        HSD_ASSERT(0xA5, 0);
    }
    aramstate = 0;
    devComRelayBufFlag[i] = false;
    HSD_DevComDVDWakeUp();
    HSD_DevComARAMWakeUp();
}

static inline void HSD_DevComARAMCallback_inline(HSD_DevCom* devcom)
{
    bool enabled = OSDisableInterrupts();
    devcom->next = HSD_DevCom_804D77F0;
    HSD_DevCom_804D77F0 = devcom;
    OSRestoreInterrupts(enabled);
}

static void HSD_DevComARAMCallback(ARQRequest* request)
{
    int i;
    void* buf;

    if (aramDC->type == 0x1A) {
        if (request == &devComARQR[0][0]) {
            i = 0;
        } else {
            i = 1;
        }
        buf = HSD_DevCom_804C6330_bufs[i];
    } else {
        buf = NULL;
    }

    if (aramDC->callback != NULL) {
        aramDC->callback(aramDC->dcReq, (int) aramDC->args, buf,
                                      aramDC->cancelflag);
    }

    HSD_DevComUnlink(aramDC);
    HSD_DevComARAMCallback_inline(aramDC);
    HSD_DevComStdCallback(request);
}

static inline int getRelayBufIdx(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (!devComRelayBufFlag[i]) {
            devComRelayBufFlag[i] = true;
            return i;
        }
    }
    return -1;
}

void HSD_DevComARAMWakeUp(void)
{
    bool enabled;
    s32 var_ctr_2;
    int req_idx;
    u32 var_r28;
    u32 var_r28_2;
    void* buf;
    void (*var_r26)(ARQRequest*);
    void (*var_r26_2)(ARQRequest*);
    int* var_r3_2;

    enabled = OSDisableInterrupts();
    if (aramstate != 0) {
        OSRestoreInterrupts(enabled);
        return;
    }
    aramDC = devComStatus[3];
    if (devComStatus[3] != NULL) {
        if (aramDC->cancelflag) {
            if (aramDC->callback != NULL) {
                aramDC->callback(aramDC->dcReq, (s32) aramDC->args, NULL, true);
            }
            HSD_DevComUnlink(aramDC);
            OSRestoreInterrupts(enabled);
            HSD_DevComARAMWakeUp();
            return;
        }
        req_idx = getRelayBufIdx();
        if (req_idx >= 0) {
            if (aramDC->type == 3) {
                if (aramDC->size > DEVCOM_BUF_SIZE) {
                    var_r26 = HSD_DevComStdCallback;
                    var_r28 = DEVCOM_BUF_SIZE;
                } else {
                    var_r26 = HSD_DevComARAMCallback;
                    var_r28 = aramDC->size;
                }

                var_ctr_2 = 0x200;
                var_r3_2 = HSD_DevCom_804C6330_bufs[req_idx];
                do {
                    int j;
                    for (j = 0; j < 8; j++) {
                        *var_r3_2++ = 0;
                    }
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);

                buf = HSD_DevCom_804C6330_bufs[req_idx];
                DCStoreRange(buf, DEVCOM_BUF_SIZE);
                ARQPostRequest(devComARQR[req_idx], 0, 0, 1, (u32) buf, aramDC->dest, var_r28, var_r26);
                aramDC->dest += var_r28;
                aramDC->size -= var_r28;
                aramstate = 1;
            } else if (aramDC->type == 0xB) {
                DCStoreRange((void*) aramDC->src, aramDC->size);
                ARQPostRequest(devComARQR[req_idx], 0, 0, 1, aramDC->src, aramDC->dest, aramDC->size, HSD_DevComARAMCallback);
                aramstate = 1;
            } else if (aramDC->type == 0x19) {
                DCInvalidateRange((void* ) aramDC->dest, aramDC->size);
                ARQPostRequest(devComARQR[req_idx], 0, 1, 1, aramDC->src, aramDC->dest, aramDC->size, HSD_DevComARAMCallback);
                aramstate = 1;
            } else if (aramDC->type == 0x1A) {
                buf = HSD_DevCom_804C6330_bufs[req_idx];
                DCInvalidateRange(buf, DEVCOM_BUF_SIZE);
                ARQPostRequest(devComARQR[req_idx], 0, 1, 1, aramDC->src, (u32) buf, aramDC->size, HSD_DevComARAMCallback);
                aramstate = 1;
            } else if (aramDC->type == 0x1B) {
                buf = HSD_DevCom_804C6330_bufs[req_idx];
                DCInvalidateRange(buf, DEVCOM_BUF_SIZE);
                if (aramDC->size > DEVCOM_BUF_SIZE) {
                    var_r26_2 = HSD_DevComStdCallback;
                    var_r28_2 = DEVCOM_BUF_SIZE;
                } else {
                    var_r26_2 = HSD_DevComARAMCallback;
                    var_r28_2 = aramDC->size;
                }
                ARQPostRequest(&devComARQR[req_idx][1], 0, 1, 1, aramDC->src, (u32) buf, var_r28_2, NULL);
                ARQPostRequest(&devComARQR[req_idx][0], 0, 0, 1, (u32) buf, aramDC->dest, var_r28_2, var_r26_2);
                aramDC->src += var_r28_2;
                aramDC->dest += var_r28_2;
                aramDC->size -= var_r28_2;
                aramstate = 1;
            }
        }
    }
    OSRestoreInterrupts(enabled);
}

static void HSD_DevComDVDStdCallback(ARQRequest* request)
{
    int i;
    if (request == &devComARQR[0][0]) {
        i = 0;
    } else if (request == &devComARQR[1][0]) {
        i = 1;
    } else {
        HSD_ASSERT(0x158, 0);
    }
    devComRelayBufFlag[i] = false;
    HSD_DevComDVDWakeUp();
    HSD_DevComARAMWakeUp();
}

static void HSD_DevComDVDARAMEndCallback(ARQRequest* request)
{
    int i;

    HSD_DevComDVDStdCallback(request);

    if (request == &devComARQR[0][0]) {
        i = 0;
    } else {
        i = 1;
    }

    if (HSD_DevCom_804D77FC[i]->callback != NULL && HSD_DevCom_804D7804 == 0) {
        HSD_DevCom_804D77FC[i]->callback(HSD_DevCom_804D77FC[i]->dcReq, (int) HSD_DevCom_804D77FC[i]->args, NULL, HSD_DevCom_804D77FC[i]->cancelflag);
    }
    HSD_DevComARAMCallback_inline(HSD_DevCom_804D77FC[i]);
    HSD_DevCom_804D77FC[i] = NULL;
}

static void HSD_DevComDVDMemCallback(s32 arg0, DVDFileInfo* unused)
{
    HSD_DevCom* temp_r31;
    bool enabled;

    if (arg0 == -1) {
        HSD_DevCom_804D7804 = 1;
    }
    if (dvdDC->size > 0x80000) {
        dvdDC->src += 0x80000;
        dvdDC->dest += 0x80000;
        dvdDC->size -= 0x80000;
        HSD_DevCom_804D77F5 = 0;
        HSD_DevComDVDWakeUp();
        return;
    }
    if (dvdDC->callback != NULL && HSD_DevCom_804D7804 == 0) {
        dvdDC->callback(dvdDC->dcReq, (int) dvdDC->args, NULL, dvdDC->cancelflag);
    }
    HSD_DevComUnlink(dvdDC);
    temp_r31 = dvdDC;
    enabled = OSDisableInterrupts();
    temp_r31->next = HSD_DevCom_804D77F0;
    HSD_DevCom_804D77F0 = temp_r31;
    OSRestoreInterrupts(enabled);
    HSD_DevCom_804D77F5 = 0;
    HSD_DevComDVDWakeUp();
}

static void HSD_DevComDVDCallback(s32 arg0, DVDFileInfo* unused)
{
    HSD_DevCom* temp_r30;
    s32 temp_r3;
    u16 temp_r0;

    PAD_STACK(8);

    if (arg0 == -1) {
        HSD_DevCom_804D7804 = 1;
    }
    temp_r0 = dvdDC->type;
    if (temp_r0 == 0x22) {
        if (dvdDC->size > DEVCOM_BUF_SIZE) {
            __assert("devcom.c", 0x18C, "dvdDC->size <= DEVCOM_BUF_SIZE");
        }
        if (dvdDC->callback == NULL) {
            __assert("devcom.c", 0x18D, "dvdDC->callback");
        }
        if (HSD_DevCom_804D7804 == 0) {
            dvdDC->callback(dvdDC->dcReq, (s32) dvdDC->args, HSD_DevCom_804C6330_bufs[HSD_DevCom_804D77F6], dvdDC->cancelflag);
        }
        HSD_DevComUnlink(dvdDC);
        temp_r30 = dvdDC;
        temp_r3 = OSDisableInterrupts();
        temp_r30->next = HSD_DevCom_804D77F0;
        HSD_DevCom_804D77F0 = temp_r30;
        OSRestoreInterrupts(temp_r3);
        HSD_DevCom_804D77F5 = 0;
        devComRelayBufFlag[HSD_DevCom_804D77F6] = false;
        HSD_DevComDVDWakeUp();
        HSD_DevComARAMWakeUp();
    } else if (temp_r0 == 0x23) {
        HSD_DevCom_804D77F7 = HSD_DevCom_804D77F6;
        if (dvdDC->size > DEVCOM_BUF_SIZE) {
            ARQPostRequest(devComARQR[HSD_DevCom_804D77F7], 0, 0, 1, (u32) HSD_DevCom_804C6330_bufs[HSD_DevCom_804D77F7], dvdDC->dest, DEVCOM_BUF_SIZE, HSD_DevComDVDStdCallback);
            dvdDC->src += DEVCOM_BUF_SIZE;
            dvdDC->dest += DEVCOM_BUF_SIZE;
            dvdDC->size -= DEVCOM_BUF_SIZE;
            HSD_DevCom_804D77F5 = 0;
            HSD_DevComDVDWakeUp();
        } else {
            HSD_DevCom_804D77FC[HSD_DevCom_804D77F7] = dvdDC;
            ARQPostRequest(devComARQR[HSD_DevCom_804D77F7], 0, 0, 1, (u32) HSD_DevCom_804C6330_bufs[HSD_DevCom_804D77F7], dvdDC->dest, dvdDC->size, HSD_DevComDVDARAMEndCallback);
            HSD_DevComUnlink(dvdDC);
            HSD_DevCom_804D77F5 = 0;
            HSD_DevComDVDWakeUp();
        }
    }
}

void HSD_DevComDVDWakeUp(void)
{
    bool enabled = OSDisableInterrupts();
    int i;
    int buf_idx;

    if (HSD_DevCom_804D77F5 != 0) {
        OSRestoreInterrupts(enabled);
        return;
    }
    for (i = 0; i < 3; i++) {
        if ((dvdDC = devComStatus[i])) {
            if (dvdDC->cancelflag) {
                if (dvdDC->callback != NULL) {
                    dvdDC->callback(dvdDC->dcReq, (s32) dvdDC->args, NULL, true);
                }
                HSD_DevComUnlink(dvdDC);
                OSRestoreInterrupts(enabled);
                HSD_DevComDVDWakeUp();
                return;
            }
            DVDFastOpen(dvdDC->file, &fileinfo);
            if (dvdDC->type == 0x21) {
                DVDReadAsyncPrio(&fileinfo, (void*) dvdDC->dest, MIN(dvdDC->size, 0x80000), (s32) dvdDC->src, HSD_DevComDVDMemCallback, 2);
                HSD_DevCom_804D77F5 = 1;
                OSRestoreInterrupts(enabled);
                return;
            }
            buf_idx = getRelayBufIdx();
            if (buf_idx >= 0) {
                HSD_DevCom_804D77F6 = buf_idx;
                DVDReadAsyncPrio(&fileinfo, HSD_DevCom_804C6330_bufs[buf_idx], MIN(dvdDC->size, DEVCOM_BUF_SIZE), dvdDC->src, HSD_DevComDVDCallback, 2);
                HSD_DevCom_804D77F5 = 1;
                OSRestoreInterrupts(enabled);
                return;
            }
        }
    }
    OSRestoreInterrupts(enabled);
}

static inline int HSD_DevComGetDestType(int type)
{
    return type & 7;
}

#define INIT_N_DEVCOMS 16

static inline void DevComLinkNext(HSD_DevCom* dc)
{
    int i;
    for (i = 1; i < INIT_N_DEVCOMS - 1; i++) {
        dc[i].next = &dc[i] + 1;
    }
    dc[i].next = NULL;
}

int HSD_DevComRequest(int file, uintptr_t src, uintptr_t dest, size_t size,
                      int type, int pri, HSD_DevComCallback cb, void* args)
{
    bool enabled;
    HSD_DevCom* dc;
    int result;

    enabled = OSDisableInterrupts();

    if ((dc = HSD_DevCom_804D77F0)) {
        HSD_DevCom_804D77F0 = dc->next;
        OSRestoreInterrupts(enabled);
    } else {
        dc = HSD_AudioMalloc(sizeof(HSD_DevCom) * INIT_N_DEVCOMS);
        DevComLinkNext(dc);

        HSD_DevCom_804D77F0 = &dc[1];
        OSRestoreInterrupts(enabled);
    }

    HSD_ASSERT(0x1ED, dc);
    HSD_ASSERT(0x1EE,
        !(HSD_DevComGetDestType(type) == DEVCOMDEST_SBUF
            && size > DEVCOM_BUF_SIZE));

    HSD_ASSERT(0x1EF, src % 32 == 0);
    HSD_ASSERT(0x1F0, dest % 32 == 0);
    HSD_ASSERT(0x1F1, size % 32 == 0);
    HSD_ASSERT(0x1F2, size != 0);

    pri = (type & 0x38) == 0x20 ? pri : 3;

    dc->file = file;
    dc->src = src;
    dc->dest = dest;
    dc->size = size;
    dc->type = type;
    dc->cancelflag = false;
    dc->callback = cb;
    dc->args = args;

    enabled = OSDisableInterrupts();
    result = HSD_DevCom_804D6050 + pri;
    dc->dcReq = result;
    HSD_DevCom_804D6050 += 4;
    if (HSD_DevCom_804C6330[pri] != NULL) {
        HSD_DevCom_804C6330[pri]->next = dc;
    }
    HSD_DevCom_804C6330[pri] = dc;
    dc->next = NULL;
    if (devComStatus[pri] == NULL) {
        devComStatus[pri] = dc;
        HSD_DevComDVDWakeUp();
        HSD_DevComARAMWakeUp();
    }
    OSRestoreInterrupts(enabled);

    return result;
}

static inline HSD_DevCom* HSD_DevComCancelEx_inline(int dcReq)
{
    HSD_DevCom* cur = devComStatus[dcReq & 3];
    while (cur != NULL) {
        if (cur->dcReq == dcReq) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int HSD_DevComCancelEx(int dcReq, u32 flags, HSD_DevComCallback cb, void* args)
{
    HSD_DevCom* dc;
    bool enabled = OSDisableInterrupts();

    if ((dc = HSD_DevComCancelEx_inline(dcReq))) {
        int tmp = dcReq & 3;
        if (flags & 1) {
            dc->callback = cb;
        }
        if (flags & 2) {
            dc->args = args;
        }
        if (devComStatus[tmp] == dc) {
            dc->cancelflag = true;
        } else {
            if (dc->callback != NULL) {
                dc->callback(dc->dcReq, (int) dc->args, NULL, true);
            }
            HSD_DevComUnlink(dc);
        }
    } else {
        int i;
        for (i = 0; i < 2; i++) {
            HSD_DevCom* dc = HSD_DevCom_804D77FC[i];
            if (dc != NULL && dc->dcReq == dcReq) {
                dc->callback = cb;
                dc->args = args;
                HSD_DevCom_804D77FC[i]->cancelflag = true;
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

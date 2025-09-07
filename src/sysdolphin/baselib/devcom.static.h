#include <dolphin/ar.h>
#include <dolphin/dvd.h>
#include <sysdolphin/baselib/devcom.h>

struct HSD_DevCom {
    HSD_DevCom* next;
    int dcReq;
    int file;
    intptr_t src;
    intptr_t dest;
    size_t size;
    u16 type;
    u16 cancelflag;
    HSD_DevComCallback callback;
    void* args;
};

#define DEVCOMDEST_SBUF 2
#define DEVCOM_BUF_SIZE 0x4000

static ARQRequest devComARQR[2][2];
static HSD_DevCom* devComStatus[4];
static HSD_DevCom* HSD_DevCom_804C6330[4];
static int HSD_DevCom_804C6330_bufs[2][DEVCOM_BUF_SIZE / sizeof(int)];
static DVDFileInfo fileinfo;

static HSD_DevCom* HSD_DevCom_804D77F0; // next devcom
static u8 aramstate;
static u8 HSD_DevCom_804D77F5;
static u8 HSD_DevCom_804D77F6;
static u8 HSD_DevCom_804D77F7;
static HSD_DevCom* dvdDC;
static HSD_DevCom* HSD_DevCom_804D77FC[2];
static s32 HSD_DevCom_804D7804;
static HSD_DevCom* aramDC;
static u8 devComRelayBufFlag[2];

static int HSD_DevCom_804D6050 = 4;

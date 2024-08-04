#ifndef _DOLPHIN_MCC_H_
#define _DOLPHIN_MCC_H_

enum MCC_CHANNEL {
    MCC_CHANNEL_SYSTEM = 0,
    MCC_CHANNEL_1 = 1,
    MCC_CHANNEL_2 = 2,
    MCC_CHANNEL_3 = 3,
    MCC_CHANNEL_4 = 4,
    MCC_CHANNEL_5 = 5,
    MCC_CHANNEL_6 = 6,
    MCC_CHANNEL_7 = 7,
    MCC_CHANNEL_8 = 8,
    MCC_CHANNEL_9 = 9,
    MCC_CHANNEL_10 = 10,
    MCC_CHANNEL_11 = 11,
    MCC_CHANNEL_12 = 12,
    MCC_CHANNEL_13 = 13,
    MCC_CHANNEL_14 = 14,
    MCC_CHANNEL_15 = 15,
};

typedef struct {
    /* 0x00 */ u8 firstBlock;
    /* 0x01 */ u8 blockLength;
    /* 0x02 */ u8 connect;
    /* 0x03 */ u8 isLocked;
} MCC_Info;

enum MCC_EXI {
    MCC_EXI_0 = 0,
    MCC_EXI_1 = 1,
    MCC_EXI_2 = 2,
};

enum MCC_SYSEVENT {
    MCC_SYSEVENT_UNKNOWN = 0,
    MCC_SYSEVENT_REBOOT = 1,
    MCC_SYSEVENT_INITIALIZED = 2,
    MCC_SYSEVENT_PING = 3,
    MCC_SYSEVENT_PING_RESULT = 4,
    MCC_SYSEVENT_FLUSH = 5,
};

typedef void (* MCC_CBEvent)(enum MCC_CHANNEL channel, u32, u32);
typedef void (* MCC_CBSysEvent)(enum MCC_SYSEVENT sysEvent);
typedef int (* MCC_CBEnumDevices)(long);

typedef struct {
    /* 0x00 */ u32 length;
    /* 0x04 */ u16 rsvd;
    /* 0x06 */ u16 protocol;
} MCC_Hdr;

typedef struct {
    /* 0x00 */ u32 code;
    /* 0x04 */ u32 number;
} MCC_HdrFio;

typedef struct {
    /* 0x00 */ MCC_Info info;
    /* 0x04 */ MCC_CBEvent callbackEvent;
    /* 0x08 */ u32 eventMask;
    /* 0x0C */ int isStreamDone;
    /* 0x10 */ int isStreamConnection;
} MCC_ChannelInfo;

enum MCC_MODE {
    MCC_MODE_MIN = 0,
    MCC_MODE_MAX = 1,
    MCC_MODE_ALL = 2,
};

enum MCC_CONNECT {
    MCC_CONNECT_DISCONNECT = 0,
    MCC_CONNECT_HOST_OPEN = 1,
    MCC_CONNECT_TARGET_OPEN = 2,
    MCC_CONNECT_CONNECTED = 3,
};

enum MCC_SYNC_STATE {
    MCC_SYNC = 0,
    MCC_ASYNC = 1,
};

enum FIO_ASYNC_STATE {
    FIO_ASYNC_STATE_IDOL = 0,
    FIO_ASYNC_STATE_BUSY = 1,
    FIO_ASYNC_STATE_DONE = 2,
};

struct FIO_Date {
    /* 0x00 */ u16 year;
    /* 0x02 */ u8 month;
    /* 0x03 */ u8 day;
};

struct FIO_Daytime {
    /* 0x00 */ u8 hour;
    /* 0x01 */ u8 minute;
    /* 0x02 */ u8 second;
    /* 0x03 */ u8 reserved;
};

struct FIO_Timestamp {
    /* 0x00 */ struct FIO_Date date;
    /* 0x04 */ struct FIO_Daytime time;
};

struct FIO_Stat {
    /* 0x00 */ u32 fileAttributes;
    /* 0x04 */ struct FIO_Timestamp creationTime;
    /* 0x0C */ struct FIO_Timestamp lastAccessTime;
    /* 0x14 */ struct FIO_Timestamp lastWriteTime;
    /* 0x1C */ u32 fileSizeHigh;
    /* 0x20 */ u32 fileSizeLow;
};

struct FIO_Finddata {
    /* 0x00 */ struct FIO_Stat stat;
    /* 0x24 */ char filename[256];
};

// fio.c
int FIOInit(enum MCC_EXI exiChannel, enum MCC_CHANNEL chID, u8 blockSize);
void FIOExit(void);
int FIOQuery(void);
u8 FIOGetLastError();
int FIOFopen(const char *filename, u32 mode);
int FIOFclose(int handle);
u32 FIOFread(int handle, void *data, u32 size);
u32 FIOFwrite(int handle, void * data, u32 size);
u32 FIOFseek(int handle, long offset, u32 mode);
int FIOFprintf(int handle, const char *format, ...);
int FIOFflush(int handle);
int FIOFstat(int handle, struct FIO_Stat *stat);
int FIOFerror(int handle);
int FIOFindFirst(const char *filename, struct FIO_Finddata *finddata);
int FIOFindNext(struct FIO_Finddata *finddata);
u32 FIOGetAsyncBufferSize(void);
int FIOFreadAsync(int handle, void * data, u32 size);
int FIOFwriteAsync(int handle, void * data, u32 size);
int FIOCheckAsyncDone(u32 * result);

// mcc.c
int MCCStreamOpen(enum MCC_CHANNEL chID, u8 blockSize);
int MCCStreamClose(enum MCC_CHANNEL chID);
int MCCStreamWrite(enum MCC_CHANNEL chID, void *data, u32 dataBlockSize);
u32 MCCStreamRead(enum MCC_CHANNEL chID, void *data);
int MCCInit(enum MCC_EXI exiChannel, u8 timeout, MCC_CBSysEvent callbackSysEvent);
void MCCExit(void);
int MCCPing(void);
int MCCEnumDevices(MCC_CBEnumDevices callbackEnumDevices);
u8 MCCGetFreeBlocks(enum MCC_MODE mode);
u8 MCCGetLastError(void);
int MCCGetChannelInfo(enum MCC_CHANNEL chID, MCC_Info *info);
int MCCGetConnectionStatus(enum MCC_CHANNEL chID, enum MCC_CONNECT *connect);
int MCCNotify(enum MCC_CHANNEL chID, u32 notify);
u32 MCCSetChannelEventMask(enum MCC_CHANNEL chID, u32 event);
int MCCOpen(enum MCC_CHANNEL chID, u8 blockSize, MCC_CBEvent callbackEvent);
int MCCClose(enum MCC_CHANNEL chID);
int MCCLock(enum MCC_CHANNEL chID);
int MCCUnlock(enum MCC_CHANNEL chID);
int MCCRead(enum MCC_CHANNEL chID, u32 offset, void *data, long size, enum MCC_SYNC_STATE async);
int MCCWrite(enum MCC_CHANNEL chID, u32 offset, void *data, long size, enum MCC_SYNC_STATE async);
int MCCCheckAsyncDone();

#endif // _DOLPHIN_MCC_H_

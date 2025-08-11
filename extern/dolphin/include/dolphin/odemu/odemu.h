#ifndef _DOLPHIN_ODEMU_H_
#define _DOLPHIN_ODEMU_H_

int DBRead(void*, u32);
int DBWrite(const void* data, u32 size);
int DBInitInterrupts(void);
int DBQueryData(void);
void DBOpen(void);
void DBClose(void);
int Hu_IsStub(void);

#endif

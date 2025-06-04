#ifndef _DOLPHIN_ODEMU_H_
#define _DOLPHIN_ODEMU_H_

int Hu_IsStub();
void DBInitInterrupts();
long DBQueryData();
unsigned long DBRead();
unsigned long DBWrite();
void DBOpen();
void DBClose();

#endif

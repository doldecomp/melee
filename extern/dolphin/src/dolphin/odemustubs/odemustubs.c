#include <dolphin.h>

int Hu_IsStub();
void DBInitInterrupts();
long DBQueryData();
unsigned long DBRead();
unsigned long DBWrite();
void DBOpen();
void DBClose();

int Hu_IsStub() {
    return 1;
}

void DBInitComm() {
    
}

void DBInitInterrupts() {

}

long DBQueryData() {
    return 0;
}

unsigned long DBRead() {
    return 0;
}

unsigned long DBWrite() {
    return 0;
}

void DBOpen() {
    
}

void DBClose() {
    
}

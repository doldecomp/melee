#define EOF -1

typedef struct
{
    const char * NextChar;
    int    NullCharDetected;
} __InStrCtrl;

enum __ReadProcActions
{
	__GetAChar,
	__UngetAChar,
	__TestForError
};

//lbl_803257E8
int __StringRead(void * isc, int ch, int Action) {
    char RetVal;

    __InStrCtrl * Iscp = (__InStrCtrl*)isc;
    switch (Action) {
        case __GetAChar:
            RetVal = *(Iscp->NextChar);
            if (RetVal == '\0') {
                Iscp->NullCharDetected = 1;
                return EOF;
            } else {
                Iscp->NextChar++;
                return (int)RetVal;
            }
        case __UngetAChar:
            if (!Iscp->NullCharDetected) {
                Iscp->NextChar--;
            } else {
                Iscp->NullCharDetected = 0;
            }
            return ch;
        case __TestForError:
            return Iscp->NullCharDetected;
        default:
            return 0;
    }
}


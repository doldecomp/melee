#ifndef _DOLPHIN_CARDWRITE_H_
#define _DOLPHIN_CARDWRITE_H_

long CARDWriteAsync(struct CARDFileInfo * fileInfo, void * buf, long length, long offset, void (* callback)(long, long));
long CARDWrite(struct CARDFileInfo * fileInfo, void * buf, long length, long offset);

#endif // _DOLPHIN_CARDWRITE_H_

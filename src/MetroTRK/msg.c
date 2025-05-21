#include "MetroTRK/msg.h"

#include "MetroTRK/dolphin_trk_glue.h"

DSError TRKMessageSend(MessageBuffer* msg)
{
    return TRK_WriteUARTN(msg->fData, msg->fLength);
}
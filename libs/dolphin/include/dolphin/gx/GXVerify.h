#ifndef _DOLPHIN_GX_GXVERIFY_H_
#define _DOLPHIN_GX_GXVERIFY_H_

typedef enum {
    GX_WARN_NONE,
    GX_WARN_SEVERE,
    GX_WARN_MEDIUM,
    GX_WARN_ALL
} GXWarningLevel;

typedef void (*GXVerifyCallback)(GXWarningLevel level, u32 id, char *msg);

void GXSetVerifyLevel(GXWarningLevel level);
GXVerifyCallback GXSetVerifyCallback(GXVerifyCallback cb);

#endif

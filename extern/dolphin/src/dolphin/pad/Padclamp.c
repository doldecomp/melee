#include <dolphin.h>
#include <dolphin/pad.h>

static unsigned char TriggerMin;
static unsigned char TriggerMax;

// functions
static void ClampStick(signed char * px, signed char * py);
static void ClampTrigger(unsigned char * trigger);

static void ClampStick(signed char * px, signed char * py) {
    int x;
    int y;
    int signX;
    int signY;
    int d;

    x = *px;
    y = *py;

    if (x >= 0) {
        signX = 1;
    } else {
        signX = -1;
        x = -x;
    }
    if (y >= 0) {
        signY = 1;
    } else {
        signY = -1;
        y = -y;
    }
    if (x <= 0xF) {
        x = 0;
    } else {
        x -= 0xF;
    }
    if (y <= 0xF) {
        y = 0;
    } else {
        y -= 0xF;
    }
    if (x == 0 && y == 0) {
        *px = *py = 0;
        return;
    }
    if ((y * 0x34) <= (x * 0x34)) {
        d = (x * 0x34) + (y * 0x16);
        if (d > 0xF08) {
            x = (s8) ((x * 0xF08) / d);
            y = (s8) ((y * 0xF08) / d);
        }
    } else {
        d = (y * 0x34) + (x * 0x16);
        if (d > 0xF08) {
            x = (s8) ((x * 0xF08) / d);
            y = (s8) ((y * 0xF08) / d);
        }
    }
    *px = signX * x;
    *py = signY * y;
}

static void ClampTrigger(unsigned char * trigger) {
    if (*trigger <= TriggerMin) {
        *trigger = 0;
        return;
    }
    if (TriggerMax < *trigger) {
        *trigger = TriggerMax;
    }
    *trigger -= TriggerMin;
}

void PADClamp(PADStatus * status) {
    int i;

    if (PADGetSpec() < PAD_SPEC_4) {
        TriggerMin = 0x28;
        TriggerMax = 0xB4;
    } else {
        TriggerMin = 0x10;
        TriggerMax = 0x9C;
    }

    for(i = 0; i < 4; i++, status++) {
        if (status->err == PAD_ERR_NONE) {
            ClampStick(&status->stickX, &status->stickY);
            ClampStick(&status->substickX, &status->substickY);
            ClampTrigger(&status->triggerLeft);
            ClampTrigger(&status->triggerRight);
        }
    }
}

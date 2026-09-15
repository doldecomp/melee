#include <dolphin.h>
#include <dolphin/mix.h>

u16 __MIXVolumeTable[965] = {
    0,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      1,      1,
    1,      1,      1,      1,      1,      1,      2,      2,
    2,      2,      2,      2,      2,      2,      2,      2,
    2,      2,      2,      2,      2,      2,      2,      2,
    2,      2,      2,      2,      2,      2,      2,      2,
    2,      2,      2,      2,      2,      2,      2,      2,
    2,      3,      3,      3,      3,      3,      3,      3,
    3,      3,      3,      3,      3,      3,      3,      3,
    3,      3,      3,      3,      3,      3,      3,      3,
    3,      3,      4,      4,      4,      4,      4,      4,
    4,      4,      4,      4,      4,      4,      4,      4,
    4,      4,      4,      4,      4,      5,      5,      5,
    5,      5,      5,      5,      5,      5,      5,      5,
    5,      5,      5,      5,      5,      6,      6,      6,
    6,      6,      6,      6,      6,      6,      6,      6,
    6,      6,      7,      7,      7,      7,      7,      7,
    7,      7,      7,      7,      7,      7,      8,      8,
    8,      8,      8,      8,      8,      8,      8,      8,
    9,      9,      9,      9,      9,      9,      9,      9,
    9,      10,     10,     10,     10,     10,     10,     10,
    10,     10,     11,     11,     11,     11,     11,     11,
    11,     12,     12,     12,     12,     12,     12,     12,
    13,     13,     13,     13,     13,     13,     13,     14,
    14,     14,     14,     14,     14,     15,     15,     15,
    15,     15,     16,     16,     16,     16,     16,     17,
    17,     17,     17,     17,     18,     18,     18,     18,
    18,     19,     19,     19,     19,     19,     20,     20,
    20,     20,     21,     21,     21,     21,     22,     22,
    22,     22,     23,     23,     23,     24,     24,     24,
    24,     25,     25,     25,     26,     26,     26,     26,
    27,     27,     27,     28,     28,     28,     29,     29,
    29,     30,     30,     30,     31,     31,     32,     32,
    32,     33,     33,     33,     34,     34,     35,     35,
    35,     36,     36,     37,     37,     38,     38,     38,
    39,     39,     40,     40,     41,     41,     42,     42,
    43,     43,     44,     44,     45,     45,     46,     46,
    47,     47,     48,     49,     49,     50,     50,     51,
    51,     52,     53,     53,     54,     55,     55,     56,
    56,     57,     58,     58,     59,     60,     61,     61,
    62,     63,     63,     64,     65,     66,     66,     67,
    68,     69,     70,     70,     71,     72,     73,     74,
    75,     75,     76,     77,     78,     79,     80,     81,
    82,     83,     84,     85,     86,     87,     88,     89,
    90,     91,     92,     93,     94,     95,     96,     97,
    98,     100,    101,    102,    103,    104,    106,    107,
    108,    109,    111,    112,    113,    114,    116,    117,
    118,    120,    121,    123,    124,    126,    127,    128,
    130,    131,    133,    135,    136,    138,    139,    141,
    143,    144,    146,    148,    149,    151,    153,    155,
    156,    158,    160,    162,    164,    166,    168,    170,
    171,    173,    175,    178,    180,    182,    184,    186,
    188,    190,    192,    195,    197,    199,    202,    204,
    206,    209,    211,    214,    216,    219,    221,    224,
    226,    229,    231,    234,    237,    240,    242,    245,
    248,    251,    254,    257,    260,    263,    266,    269,
    272,    275,    278,    282,    285,    288,    292,    295,
    298,    302,    305,    309,    312,    316,    320,    323,
    327,    331,    335,    339,    343,    347,    351,    355,
    359,    363,    367,    371,    376,    380,    384,    389,
    393,    398,    403,    407,    412,    417,    422,    427,
    431,    436,    442,    447,    452,    457,    462,    468,
    473,    479,    484,    490,    495,    501,    507,    513,
    519,    525,    531,    537,    543,    550,    556,    562,
    569,    576,    582,    589,    596,    603,    610,    617,
    624,    631,    638,    646,    653,    661,    669,    676,
    684,    692,    700,    708,    716,    725,    733,    742,
    750,    759,    768,    777,    786,    795,    804,    813,
    823,    832,    842,    852,    861,    871,    881,    892,
    902,    912,    923,    934,    945,    955,    967,    978,
    989,    1001,   1012,   1024,   1036,   1048,   1060,   1072,
    1085,   1097,   1110,   1123,   1136,   1149,   1162,   1176,
    1189,   1203,   1217,   1231,   1245,   1260,   1274,   1289,
    1304,   1319,   1334,   1350,   1365,   1381,   1397,   1414,
    1430,   1446,   1463,   1480,   1497,   1515,   1532,   1550,
    1568,   1586,   1604,   1623,   1642,   1661,   1680,   1700,
    1719,   1739,   1759,   1780,   1800,   1821,   1842,   1864,
    1885,   1907,   1929,   1951,   1974,   1997,   2020,   2043,
    2067,   2091,   2115,   2140,   2164,   2190,   2215,   2241,
    2266,   2293,   2319,   2346,   2373,   2401,   2429,   2457,
    2485,   2514,   2543,   2573,   2602,   2632,   2663,   2694,
    2725,   2757,   2789,   2821,   2853,   2887,   2920,   2954,
    2988,   3023,   3058,   3093,   3129,   3165,   3202,   3239,
    3276,   3314,   3353,   3391,   3431,   3470,   3511,   3551,
    3592,   3634,   3676,   3719,   3762,   3805,   3849,   3894,
    3939,   3985,   4031,   4078,   4125,   4173,   4221,   4270,
    4319,   4369,   4420,   4471,   4523,   4575,   4628,   4682,
    4736,   4791,   4846,   4902,   4959,   5017,   5075,   5133,
    5193,   5253,   5314,   5375,   5438,   5501,   5564,   5629,
    5694,   5760,   5827,   5894,   5962,   6031,   6101,   6172,
    6243,   6316,   6389,   6463,   6538,   6613,   6690,   6767,
    6846,   6925,   7005,   7086,   7168,   7251,   7335,   7420,
    7506,   7593,   7681,   7770,   7860,   7951,   8043,   8136,
    8230,   8326,   8422,   8520,   8618,   8718,   8819,   8921,
    9025,   9129,   9235,   9342,   9450,   9559,   9670,   9782,
    9895,   10010,  10126,  10243,  10362,  10482,  10603,  10726,
    10850,  10976,  11103,  11231,  11361,  11493,  11626,  11761,
    11897,  12035,  12174,  12315,  12458,  12602,  12748,  12895,
    13045,  13196,  13349,  13503,  13659,  13818,  13978,  14140,
    14303,  14469,  14636,  14806,  14977,  15151,  15326,  15504,
    15683,  15865,  16049,  16234,  16422,  16613,  16805,  17000,
    17196,  17396,  17597,  17801,  18007,  18215,  18426,  18640,
    18856,  19074,  19295,  19518,  19744,  19973,  20204,  20438,
    20675,  20914,  21156,  21401,  21649,  21900,  22153,  22410,
    22669,  22932,  23197,  23466,  23738,  24013,  24291,  24572,
    24857,  25144,  25436,  25730,  26028,  26329,  26634,  26943,
    27255,  27570,  27890,  28213,  28539,  28870,  29204,  29542,
    29884,  30230,  30580,  30934,  31293,  31655,  32022,  32392,
    32767,  33147,  33531,  33919,  34312,  34709,  35111,  35518,
    35929,  36345,  36766,  37192,  37622,  38058,  38499,  38944,
    39395,  39851,  40313,  40780,  41252,  41730,  42213,  42702,
    43196,  43696,  44202,  44714,  45232,  45756,  46286,  46821,
    47364,  47912,  48467,  49028,  49596,  50170,  50751,  51339,
    51933,  52535,  53143,  53758,  54381,  55011,  55648,  56292,
    56944,  57603,  58270,  58945,  59627,  60318,  61016,  61723,
    62438,  63161,  63892,  64632,  65380
};

int __MIXPanTableL[128] = {
    0x00000000,
    0x00000000,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFE,
    0xFFFFFFFE,
    0xFFFFFFFE,
    0xFFFFFFFD,
    0xFFFFFFFD,
    0xFFFFFFFC,
    0xFFFFFFFC,
    0xFFFFFFFC,
    0xFFFFFFFB,
    0xFFFFFFFB,
    0xFFFFFFFB,
    0xFFFFFFFA,
    0xFFFFFFFA,
    0xFFFFFFF9,
    0xFFFFFFF9,
    0xFFFFFFF9,
    0xFFFFFFF8,
    0xFFFFFFF8,
    0xFFFFFFF7,
    0xFFFFFFF7,
    0xFFFFFFF6,
    0xFFFFFFF6,
    0xFFFFFFF6,
    0xFFFFFFF5,
    0xFFFFFFF5,
    0xFFFFFFF4,
    0xFFFFFFF4,
    0xFFFFFFF3,
    0xFFFFFFF3,
    0xFFFFFFF2,
    0xFFFFFFF2,
    0xFFFFFFF2,
    0xFFFFFFF1,
    0xFFFFFFF1,
    0xFFFFFFF0,
    0xFFFFFFF0,
    0xFFFFFFEF,
    0xFFFFFFEF,
    0xFFFFFFEE,
    0xFFFFFFEE,
    0xFFFFFFED,
    0xFFFFFFEC,
    0xFFFFFFEC,
    0xFFFFFFEB,
    0xFFFFFFEB,
    0xFFFFFFEA,
    0xFFFFFFEA,
    0xFFFFFFE9,
    0xFFFFFFE9,
    0xFFFFFFE8,
    0xFFFFFFE7,
    0xFFFFFFE7,
    0xFFFFFFE6,
    0xFFFFFFE6,
    0xFFFFFFE5,
    0xFFFFFFE4,
    0xFFFFFFE4,
    0xFFFFFFE3,
    0xFFFFFFE2,
    0xFFFFFFE2,
    0xFFFFFFE1,
    0xFFFFFFE0,
    0xFFFFFFDF,
    0xFFFFFFDF,
    0xFFFFFFDE,
    0xFFFFFFDD,
    0xFFFFFFDC,
    0xFFFFFFDC,
    0xFFFFFFDB,
    0xFFFFFFDA,
    0xFFFFFFD9,
    0xFFFFFFD8,
    0xFFFFFFD8,
    0xFFFFFFD7,
    0xFFFFFFD6,
    0xFFFFFFD5,
    0xFFFFFFD4,
    0xFFFFFFD3,
    0xFFFFFFD2,
    0xFFFFFFD1,
    0xFFFFFFD0,
    0xFFFFFFCF,
    0xFFFFFFCE,
    0xFFFFFFCD,
    0xFFFFFFCC,
    0xFFFFFFCA,
    0xFFFFFFC9,
    0xFFFFFFC8,
    0xFFFFFFC7,
    0xFFFFFFC5,
    0xFFFFFFC4,
    0xFFFFFFC3,
    0xFFFFFFC1,
    0xFFFFFFC0,
    0xFFFFFFBE,
    0xFFFFFFBD,
    0xFFFFFFBB,
    0xFFFFFFB9,
    0xFFFFFFB8,
    0xFFFFFFB6,
    0xFFFFFFB4,
    0xFFFFFFB2,
    0xFFFFFFB0,
    0xFFFFFFAD,
    0xFFFFFFAB,
    0xFFFFFFA9,
    0xFFFFFFA6,
    0xFFFFFFA3,
    0xFFFFFFA0,
    0xFFFFFF9D,
    0xFFFFFF9A,
    0xFFFFFF96,
    0xFFFFFF92,
    0xFFFFFF8D,
    0xFFFFFF88,
    0xFFFFFF82,
    0xFFFFFF7B,
    0xFFFFFF74,
    0xFFFFFF6A,
    0xFFFFFF5D,
    0xFFFFFF4C,
    0xFFFFFF2E,
    0xFFFFFC78
};

int __MIXPanTableR[128] = {
    0xFFFFFC78,
    0xFFFFFF2E,
    0xFFFFFF4C,
    0xFFFFFF5D,
    0xFFFFFF6A,
    0xFFFFFF74,
    0xFFFFFF7B,
    0xFFFFFF82,
    0xFFFFFF88,
    0xFFFFFF8D,
    0xFFFFFF92,
    0xFFFFFF96,
    0xFFFFFF9A,
    0xFFFFFF9D,
    0xFFFFFFA0,
    0xFFFFFFA3,
    0xFFFFFFA6,
    0xFFFFFFA9,
    0xFFFFFFAB,
    0xFFFFFFAD,
    0xFFFFFFB0,
    0xFFFFFFB2,
    0xFFFFFFB4,
    0xFFFFFFB6,
    0xFFFFFFB8,
    0xFFFFFFB9,
    0xFFFFFFBB,
    0xFFFFFFBD,
    0xFFFFFFBE,
    0xFFFFFFC0,
    0xFFFFFFC1,
    0xFFFFFFC3,
    0xFFFFFFC4,
    0xFFFFFFC5,
    0xFFFFFFC7,
    0xFFFFFFC8,
    0xFFFFFFC9,
    0xFFFFFFCA,
    0xFFFFFFCC,
    0xFFFFFFCD,
    0xFFFFFFCE,
    0xFFFFFFCF,
    0xFFFFFFD0,
    0xFFFFFFD1,
    0xFFFFFFD2,
    0xFFFFFFD3,
    0xFFFFFFD4,
    0xFFFFFFD5,
    0xFFFFFFD6,
    0xFFFFFFD7,
    0xFFFFFFD8,
    0xFFFFFFD8,
    0xFFFFFFD9,
    0xFFFFFFDA,
    0xFFFFFFDB,
    0xFFFFFFDC,
    0xFFFFFFDC,
    0xFFFFFFDD,
    0xFFFFFFDE,
    0xFFFFFFDF,
    0xFFFFFFDF,
    0xFFFFFFE0,
    0xFFFFFFE1,
    0xFFFFFFE2,
    0xFFFFFFE2,
    0xFFFFFFE3,
    0xFFFFFFE4,
    0xFFFFFFE4,
    0xFFFFFFE5,
    0xFFFFFFE6,
    0xFFFFFFE6,
    0xFFFFFFE7,
    0xFFFFFFE7,
    0xFFFFFFE8,
    0xFFFFFFE9,
    0xFFFFFFE9,
    0xFFFFFFEA,
    0xFFFFFFEA,
    0xFFFFFFEB,
    0xFFFFFFEB,
    0xFFFFFFEC,
    0xFFFFFFEC,
    0xFFFFFFED,
    0xFFFFFFEE,
    0xFFFFFFEE,
    0xFFFFFFEF,
    0xFFFFFFEF,
    0xFFFFFFF0,
    0xFFFFFFF0,
    0xFFFFFFF1,
    0xFFFFFFF1,
    0xFFFFFFF2,
    0xFFFFFFF2,
    0xFFFFFFF2,
    0xFFFFFFF3,
    0xFFFFFFF3,
    0xFFFFFFF4,
    0xFFFFFFF4,
    0xFFFFFFF5,
    0xFFFFFFF5,
    0xFFFFFFF6,
    0xFFFFFFF6,
    0xFFFFFFF6,
    0xFFFFFFF7,
    0xFFFFFFF7,
    0xFFFFFFF8,
    0xFFFFFFF8,
    0xFFFFFFF9,
    0xFFFFFFF9,
    0xFFFFFFF9,
    0xFFFFFFFA,
    0xFFFFFFFA,
    0xFFFFFFFB,
    0xFFFFFFFB,
    0xFFFFFFFB,
    0xFFFFFFFC,
    0xFFFFFFFC,
    0xFFFFFFFC,
    0xFFFFFFFD,
    0xFFFFFFFD,
    0xFFFFFFFE,
    0xFFFFFFFE,
    0xFFFFFFFE,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0x00000000,
    0x00000000
};

u8 __MIXAIVolumeTable[50] = {
    0x00, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x02,
    0x02, 0x02, 0x02, 0x03,
    0x03, 0x04, 0x04, 0x05,
    0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C,
    0x0E, 0x10, 0x12, 0x14,
    0x16, 0x19, 0x1C, 0x20,
    0x24, 0x28, 0x2D, 0x32,
    0x39, 0x40, 0x47, 0x50,
    0x5A, 0x65, 0x71, 0x7F,
    0x8F, 0xA0, 0xB4, 0xCA,
    0xE3, 0xFF
};

static struct MIXChannel __MIXChannel[64];

static int __MIXDvdStreamAttenCurrent;
static int __MIXDvdStreamAttenUser;

// functions
static u16 __MIXGetVolume(int db);
static int __MIXGetPanL(int pan);
static int __MIXGetPanR(int pan);
static void __MIXResetChannel(struct MIXChannel * channel);
static void __MIXSetPan(struct MIXChannel * channel);
static int __MIXClampPan(int pan);

static u16 __MIXGetVolume(int db) {
    if (db <= -0x388) {
        return 0;
    }
    if (db >= 0x3C) {
        return 0xFF64;
    }
    return __MIXVolumeTable[db + 0x388];
}

static int __MIXGetPanL(int pan) {
    ASSERTLINE(0xE8, (pan < 128) && (pan >= 0));
    return __MIXPanTableL[pan];
}

static int __MIXGetPanR(int pan) {
    ASSERTLINE(0xFC, (pan < 128) && (pan >= 0));
    return __MIXPanTableR[pan];
}

static void __MIXResetChannel(struct MIXChannel * channel) {
    channel->mode = 0x50000000;
    channel->input = 0;
    channel->auxA = -0x3C0;
    channel->auxB = -0x3C0;
    channel->l = __MIXGetPanL(0x40);
    channel->r = __MIXGetPanR(0x40);
    channel->f = __MIXGetPanR(0);
    channel->b = __MIXGetPanL(0);
    channel->fader = 0;
    channel->pan = 0x40;
    channel->span = 0x7F;
    channel->v   = channel->vL  = channel->vR  = channel->vS  = channel->vAL = 
    channel->vAR = channel->vAS = channel->vBL = channel->vBR = channel->vBS = 0;
}

static void __MIXSetPan(struct MIXChannel * channel) {
    channel->l = __MIXGetPanL(channel->pan);
    channel->r = __MIXGetPanR(channel->pan);
    channel->f = __MIXGetPanR(channel->span);
    channel->b = __MIXGetPanL(channel->span);    
}

static int __MIXClampPan(int pan) {
    if (pan < 0) {
        return 0;
    }
    if (pan > 0x7F) {
        return 0x7F;
    }
    return pan;    
}

void MIXInit(void) {
    int i;

    for(i = 0; i < 64; i++) {
        __MIXResetChannel(&__MIXChannel[i]);
    }
    __MIXDvdStreamAttenCurrent = 0;
    __MIXDvdStreamAttenUser = 0;
}

void MIXQuit(void) {
    
}

void MIXInitChannel(AXVPB * axvpb, u32 mode, int input, int auxA, int auxB, int pan, int span, int fader) {
    int old;
    struct MIXChannel * c;
    u16 mixerCtrl;
    u16 * p;

    ASSERTLINE(0x199, axvpb);
    c = &__MIXChannel[axvpb->index];
    c->axvpb = axvpb;
    c->mode = (mode & 7);
    c->input = input;
    c->auxA = auxA;
    c->auxB = auxB;
    c->pan = pan;
    c->span = span;
    c->fader = fader;
    __MIXSetPan(c);
    if (c->mode & 4) {
        c->v = 0U;
    } else {
        c->v = __MIXGetVolume(input);
    }
    c->vL = __MIXGetVolume(c->fader + c->l + c->f);
    c->vR = __MIXGetVolume(c->fader + c->r + c->f);
    c->vS = __MIXGetVolume(c->fader + c->b);
    if (c->mode & 1) {
        c->vAL = __MIXGetVolume(c->auxA + c->l + c->f);
        c->vAR = __MIXGetVolume(c->auxA + c->r + c->f);
        c->vAS = __MIXGetVolume(c->auxA + c->b - 0x3C);
    } else {
        c->vAL = __MIXGetVolume(c->fader + c->auxA + c->l + c->f);
        c->vAR = __MIXGetVolume(c->fader + c->auxA + c->r + c->f);
        c->vAS = __MIXGetVolume(c->fader + c->auxA + c->b - 0x3C);
    }
    if (c->mode & 2) {
        c->vBL = __MIXGetVolume(c->auxB + c->l + c->f);
        c->vBR = __MIXGetVolume(c->auxB + c->r + c->f);
        c->vBS = __MIXGetVolume(c->auxB + c->b - 0x3C);
    } else {
        c->vBL = __MIXGetVolume(c->fader + c->auxB + c->l + c->f);
        c->vBR = __MIXGetVolume(c->fader + c->auxB + c->r + c->f);
        c->vBS = __MIXGetVolume(c->fader + c->auxB + c->b - 0x3C);
    }
    old = OSDisableInterrupts();
    axvpb->pb.ve.currentVolume = c->v;
    axvpb->pb.ve.currentDelta = 0;

    p = (u16*)&axvpb->pb.mix;
    *(p) = c->vL; p+=1;
    *(p) = 0; p+=1;
    *(p) = c->vR; p+=1;
    *(p) = 0; p+=1;
    *(p) = c->vAL; p+=1;
    *(p) = 0;  p+=1;
    *(p) = c->vAR; p+=1;
    *(p) = 0;  p+=1;
    *(p) = c->vBL; p+=1;
    *(p) = 0;  p+=1;
    *(p) = c->vBR; p+=1;
    *(p) = 0;  p+=1;
    *(p) = c->vBS; p+=1;
    *(p) = 0;  p+=1;
    *(p) = c->vS; p+=1;
    *(p) = 0;  p+=1;
    *(p) = c->vAS; p+=1;
    *(p) = 0;  p+=1;

    mixerCtrl = 0;
    if ((axvpb->pb.mix.vAuxAL != 0) || (axvpb->pb.mix.vAuxAR != 0) || (axvpb->pb.mix.vAuxAS != 0)) {
        mixerCtrl |= 1;
    }
    if ((axvpb->pb.mix.vAuxBL != 0) || (axvpb->pb.mix.vAuxBR != 0) || (axvpb->pb.mix.vAuxBS != 0)) {
        mixerCtrl |= 2;
    }
    if ((axvpb->pb.mix.vS != 0) || (axvpb->pb.mix.vAuxAS != 0) || (axvpb->pb.mix.vAuxBS != 0)) {
        mixerCtrl |= 4;
    }
    axvpb->pb.mixerCtrl = mixerCtrl;
    axvpb->sync |= (AX_SYNC_FLAG_COPYMXRCTRL | AX_SYNC_FLAG_COPYAXPBMIX | AX_SYNC_FLAG_COPYVOL);
    OSRestoreInterrupts(old);
}

void MIXReleaseChannel(AXVPB * axvpb) {
    ASSERTLINE(0x20C, axvpb);
    __MIXChannel[axvpb->index].axvpb = 0;
}

void MIXResetControls(AXVPB * p) {
    __MIXResetChannel(&__MIXChannel[p->index]);
}

void MIXSetInput(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->input = dB;
    channel->mode |= 0x10000000;
}

void MIXAdjustInput(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->input += dB;
    channel->mode |= 0x10000000;
}

int MIXGetInput(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    return channel->input;
}

void MIXAuxAPostFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->mode &= 0xFFFFFFFE;
    channel->mode |= 0x40000000;
}

void MIXAuxAPreFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->mode |= 0x40000001;
}

int MIXAuxAIsPostFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    if (channel->mode & 1) {
        return 0;
    }
    return 1;
}

void MIXSetAuxA(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->auxA = dB;
    channel->mode |= 0x40000000;
}

void MIXAdjustAuxA(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->auxA += dB;
    channel->mode |= 0x40000000;
}

int MIXGetAuxA(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    return channel->auxA;
}

void MIXAuxBPostFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->mode &= 0xFFFFFFFD;
    channel->mode |= 0x40000000;
}

void MIXAuxBPreFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->mode |= 0x40000002;
}

int MIXAuxBIsPostFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    if (channel->mode & 2) {
        return 0;
    }
    return 1;
}

void MIXSetAuxB(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->auxB = dB;
    channel->mode |= 0x40000000;
}

void MIXAdjustAuxB(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->auxB += dB;
    channel->mode |= 0x40000000;
}

int MIXGetAuxB(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    return channel->auxB;
}

void MIXSetPan(AXVPB * p, int pan) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->pan = __MIXClampPan(pan);
    __MIXSetPan(channel);
    channel->mode |= 0x40000000;
}

void MIXAdjustPan(AXVPB * p, int pan) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->pan = __MIXClampPan(channel->pan + pan);
    __MIXSetPan(channel);
    channel->mode |= 0x40000000;
}

int MIXGetPan(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    return channel->pan;
}

void MIXSetSPan(AXVPB * p, int span) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->span = __MIXClampPan(span);
    __MIXSetPan(channel);
    channel->mode |= 0x40000000;
}

void MIXAdjustSPan(AXVPB * p, int span) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->span = __MIXClampPan(channel->span + span);
    __MIXSetPan(channel);
    channel->mode |= 0x40000000;
}

int MIXGetSPan(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    return channel->span;
}

void MIXMute(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->mode |= 0x10000004;
}

void MIXUnMute(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->mode &= 0xFFFFFFFB;
    channel->mode |= 0x10000000;
}

int MIXIsMute(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    if (channel->mode & 4) {
        return 1;
    }
    return 0;
}

void MIXSetFader(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->fader = dB;
    channel->mode |= 0x40000000;
}

void MIXAdjustFader(AXVPB * p, int dB) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    channel->fader += dB;
    channel->mode |= 0x40000000;
}

int MIXGetFader(AXVPB * p) {
    struct MIXChannel * channel;

    channel = &__MIXChannel[p->index];
    return channel->fader;
}

void MIXSetDvdStreamFader(int dB) {
    int db;

    db = dB;
    if (db < -0x31) {
        db = -0x31;
    }
    if (db > 0) {
        db = 0;
    }
    __MIXDvdStreamAttenUser = db;
}

int MIXGetDvdStreamFader(void) {
    return __MIXDvdStreamAttenUser;
}

void MIXUpdateSettings(void) {
    int i;
    int setNewMixLevel;
    int setNewInputLevel;
    struct MIXChannel * c;
    AXVPB * axvpb;
    u16 mixerCtrl;
    u16 * p;

    for(i = 0; i < 64; i++) {
        setNewInputLevel = 0;
        setNewMixLevel = 0;
        c = &__MIXChannel[i];
        axvpb = c->axvpb;
        if (axvpb) {
            if (c->mode & 0x20000000) {
                c->v = c->v1;
                c->mode &= 0xDFFFFFFF;
                setNewInputLevel = 1;
            }
            if (c->mode & 0x10000000) {
                if (c->mode & 4) {
                    c->v1 = 0U;
                } else {
                    c->v1 = __MIXGetVolume(c->input);
                }
                c->mode |= 0x20000000;
                setNewInputLevel = 1;
            }
            if (c->mode & 0x80000000) {
                c->vL = c->vL1;
                c->vR = c->vR1;
                c->vS = c->vS1;
                c->vAL = c->vAL1;
                c->vAR = c->vAR1;
                c->vAS = c->vAS1;
                c->vBL = c->vBL1;
                c->vBR = c->vBR1;
                c->vBS = c->vBS1;
                c->mode &= 0x7FFFFFFF;
                setNewMixLevel = 1;
            }
            if (c->mode & 0x40000000) {
                c->vL1 = __MIXGetVolume(c->fader + c->l + c->f);
                c->vR1 = __MIXGetVolume(c->fader + c->r + c->f);
                c->vS1 = __MIXGetVolume(c->fader + c->b - 0x3C);
                if (c->mode & 1) {
                    c->vAL1 = __MIXGetVolume(c->auxA + c->l + c->f);
                    c->vAR1 = __MIXGetVolume(c->auxA + c->r + c->f);
                    c->vAS1 = __MIXGetVolume(c->auxA + c->b - 0x3C);
                } else {
                    c->vAL1 = __MIXGetVolume(c->fader + c->auxA + c->l + c->f);
                    c->vAR1 = __MIXGetVolume(c->fader + c->auxA + c->r + c->f);
                    c->vAS1 = __MIXGetVolume(c->fader + c->auxA + c->b - 0x3C);
                }
                if (c->mode & 2) {
                    c->vBL1 = __MIXGetVolume(c->auxB + c->l + c->f);
                    c->vBR1 = __MIXGetVolume(c->auxB + c->r + c->f);
                    c->vBS1 = __MIXGetVolume(c->auxB + c->b - 0x3C);
                } else {
                    c->vBL1 = __MIXGetVolume(c->fader + c->auxB + c->l + c->f);
                    c->vBR1 = __MIXGetVolume(c->fader + c->auxB + c->r + c->f);
                    c->vBS1 = __MIXGetVolume(c->fader + c->auxB + c->b - 0x3C);
                }
                c->mode &= 0xBFFFFFFF;
                c->mode |= 0x80000000;
                setNewMixLevel = 1;
            }
            if (setNewInputLevel != 0 && axvpb) {
                axvpb->pb.ve.currentVolume = c->v;
                axvpb->pb.ve.currentDelta = ((c->v1 - c->v) / 160);
                axvpb->sync |= 0x200;
            }
            if (setNewMixLevel != 0 && axvpb) {
                p = (u16*)&axvpb->pb.mix;
                *(p) = c->vL; p+=1;
                *(p) = ((c->vL1 - c->vL) / 160); p+=1;
                *(p) = c->vR; p+=1;
                *(p) = ((c->vR1 - c->vR) / 160); p+=1;
                *(p) = c->vAL; p+=1;
                *(p) = ((c->vAL1 - c->vAL) / 160); p+=1;
                *(p) = c->vAR; p+=1;
                *(p) = ((c->vAR1 - c->vAR) / 160); p+=1;
                *(p) = c->vBL; p+=1;
                *(p) = ((c->vBL1 - c->vBL) / 160); p+=1;
                *(p) = c->vBR; p+=1;
                *(p) = ((c->vBR1 - c->vBR) / 160); p+=1;
                *(p) = c->vBS; p+=1;
                *(p) = ((c->vBS1 - c->vBS) / 160); p+=1;
                *(p) = c->vS; p+=1;
                *(p) = ((c->vS1 - c->vS) / 160); p+=1;
                *(p) = c->vAS; p+=1;
                *(p) = ((c->vAS1 - c->vAS) / 160); p+=1;
                mixerCtrl = 0;
                if ((axvpb->pb.mix.vAuxAL != 0) || (axvpb->pb.mix.vAuxAR != 0) || (axvpb->pb.mix.vAuxAS != 0)) {
                    mixerCtrl |= 1;
                }
                if ((axvpb->pb.mix.vAuxBL != 0) || (axvpb->pb.mix.vAuxBR != 0) || (axvpb->pb.mix.vAuxBS != 0)) {
                    mixerCtrl |= 2;
                }
                if ((axvpb->pb.mix.vS != 0) || (axvpb->pb.mix.vAuxAS != 0) || (axvpb->pb.mix.vAuxBS != 0)) {
                    mixerCtrl |= 4;
                }
                if ((axvpb->pb.mix.vDeltaL != 0) || (axvpb->pb.mix.vDeltaR != 0) || (axvpb->pb.mix.vDeltaS != 0) || (axvpb->pb.mix.vDeltaAuxAL != 0) 
                 || (axvpb->pb.mix.vDeltaAuxAR != 0) || (axvpb->pb.mix.vDeltaAuxAS != 0) || (axvpb->pb.mix.vDeltaAuxBL != 0) || (axvpb->pb.mix.vDeltaAuxBR != 0) 
                 || (axvpb->pb.mix.vDeltaAuxBS != 0)) {
                    mixerCtrl |= 8;
                }
                axvpb->pb.mixerCtrl = mixerCtrl;
                axvpb->sync |= 0x12;
            }
        }
    }
    if (__MIXDvdStreamAttenUser > __MIXDvdStreamAttenCurrent) {
        __MIXDvdStreamAttenCurrent += 1;
        AISetStreamVolLeft(__MIXAIVolumeTable[__MIXDvdStreamAttenCurrent]);
        AISetStreamVolRight(__MIXAIVolumeTable[__MIXDvdStreamAttenCurrent]);
        return;
    }
    if (__MIXDvdStreamAttenUser < __MIXDvdStreamAttenCurrent) {
        __MIXDvdStreamAttenCurrent -= 1;
        AISetStreamVolLeft(__MIXAIVolumeTable[__MIXDvdStreamAttenCurrent]);
        AISetStreamVolRight(__MIXAIVolumeTable[__MIXDvdStreamAttenCurrent]);
    }
}

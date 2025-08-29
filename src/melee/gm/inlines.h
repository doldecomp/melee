#ifndef MELEE_GM_INLINES_H
#define MELEE_GM_INLINES_H

/// @todo Is a macro the best way?
#define SKIP_CMD(cmd, n)                                                      \
    do {                                                                      \
        int i;                                                                \
        for (i = 0; i < (n); i++) {                                           \
            ++(cmd)->u;                                                       \
        }                                                                     \
    } while (0);

#define NEXT_CMD(cmd)                                                         \
    do {                                                                      \
        ++(cmd)->u;                                                           \
    } while (0);

#endif

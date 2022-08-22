enum my_enum {
    ZERO,
    // Test two enum names with the same value
    TWO = 2,
    TWO_TOO = 2,
    THREE,
};

const enum my_enum array[4] = {THREE, TWO_TOO, TWO, ZERO};

enum my_enum test(enum my_enum x) {
    switch (x) {
        case ZERO:
            return array[0];
        case TWO:
            return array[1];
        case THREE:
            return array[2];
    }
    return ZERO;
}

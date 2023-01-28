enum my_enum test(enum my_enum x) {
    switch (x) {                                    /* irregular */
    case ZERO:
        return array->unk0;
    case TWO_TOO:
        return array->unk4;
    case THREE:
        return array->unk8;
    default:
        return ZERO;
    }
}

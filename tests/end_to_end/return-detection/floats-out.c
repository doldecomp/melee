f32 bar();                                          /* extern */

f32 test(void) {
    f32 var_f0;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    var_f0 = bar();
    if (4 == 0) {
        goto block_3;
    }
block_1:
    if (1 == 0) {
        goto block_3;
    }
    bar();
    var_f0 = 2.0f;
block_3:
    if ((1 < 1) < 0) {
        goto block_1;
    }
    return var_f0;
}

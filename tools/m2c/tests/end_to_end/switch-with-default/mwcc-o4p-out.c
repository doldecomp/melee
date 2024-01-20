extern s32 glob;

s32 test(s32 arg0) {
    s32 var_r31;

    var_r31 = arg0;
    switch (var_r31) {                              /* irregular */
    case 9:
        break;
    case 2:
        var_r31 -= 1;
        /* fallthrough */
    case 3:
        glob += 1;
        break;
    case 13:
        var_r31 *= 2;
        break;
    default:
        var_r31 = var_r31 / 2;
        break;
    }
    test(glob);
    if ((s32) glob == 0) {
        glob = var_r31;
    }
    return 2;
}

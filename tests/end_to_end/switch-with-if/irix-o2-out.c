extern s32 D_4101D0;

void test(s32 arg0) {
    switch (arg0) {                                 /* switch 1 */
    case 1:                                         /* switch 1 */
    case 2:                                         /* switch 1 */
    case 3:                                         /* switch 1 */
    case 4:                                         /* switch 1 */
        D_4101D0 = 1;
        if (arg0 == 1) {
            D_4101D0 = 2;
        }
        break;
    case 5:                                         /* switch 1 */
    case 6:                                         /* switch 1 */
        if (arg0 == 1) {
            D_4101D0 = 1;
        } else {
            D_4101D0 = 2;
        }
        break;
    }
    switch (arg0) {                                 /* switch 2 */
    case 1:                                         /* switch 2 */
    case 2:                                         /* switch 2 */
    case 3:                                         /* switch 2 */
    case 4:                                         /* switch 2 */
        D_4101D0 = 1;
        if (arg0 == 1) {
            D_4101D0 = 2;
            return;
        }
    default:                                        /* switch 2 */
        return;
    case 5:                                         /* switch 2 */
    case 6:                                         /* switch 2 */
        if (arg0 == 1) {
            D_4101D0 = 1;
            return;
        }
        D_4101D0 = 2;
        break;
    }
}

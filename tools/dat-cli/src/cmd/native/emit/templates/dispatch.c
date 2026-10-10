
/* Compare tokens, retaining identifier boundaries such as `struct Foo`. */
static int word_character(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

static int same_type(const char* left, const char* right)
{
    for (;;) {
        while (*left == ' ' || *left == '\t' || *left == '\n') {
            left++;
        }
        while (*right == ' ' || *right == '\t' || *right == '\n') {
            right++;
        }
        if (*left != *right) {
            return 0;
        }
        if (*left == '\0') {
            return 1;
        }
        if (word_character(*left)) {
            do {
                if (*left++ != *right++) {
                    return 0;
                }
            } while (word_character(*left) && word_character(*right));
            if (word_character(*left) != word_character(*right)) {
                return 0;
            }
        } else {
            left++;
            right++;
        }
    }
}

int32_t melee_dat_type(const char* spelling)
{
    if (spelling == NULL) {
        return DAT_NONE;
    }
    for (size_t i = 0; i < DAT_COUNTOF(dispatch); i++) {
        if (same_type(spelling, dispatch[i].name)) {
            return dispatch[i].type;
        }
    }
    return DAT_NONE;
}

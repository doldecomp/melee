
int32_t e = dat_reader_resolve(a, t->target);
if (e == DAT_NONE) {
    return true;
}
for (uint32_t i = 0; i < t->count; i++) {
    if (!dat_reader_fits(a, offset + i * dat_reader_T(a, e)->size, e)) {
        return false;
    }
}
return true;

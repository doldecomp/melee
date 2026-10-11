
uint32_t value = dat_reader_word(a, offset);
if (bits_has(&a->archive->reloc, offset, a->archive->size)) {
    dat_reader_mark_pointer(a, offset, a->archive->size);
    if (dat_reader_pointee(a, t->target) != DAT_NONE) {
        dat_reader_reference(a, native, value, t->target);
        dat_reader_read_object(a, value, t->target, a->env, NULL, native);
    } else {
        dat_reader_untyped(a);
        dat_reader_store_pointer(native, a->archive->data + value);
    }
} else {
    dat_reader_store_unrelocated(a, offset, value, native);
}

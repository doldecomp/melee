
uint32_t value = dat_reader_word(a, offset);
if (bits_has(&a->archive->reloc, offset, a->archive->size)) {
    bits_set(&a->pointer, offset, a->archive->size);
    if (dat_reader_pointee(a, t->target) != DAT_NONE) {
        dat_reader_reference(a, native, value, t->target);
        dat_reader_push(a, value, t->target, a->env, NULL, native);
    } else {
        dat_reader_untyped(a);
        dat_reader_store_pointer(native, a->archive->data + value);
    }
} else {
    dat_reader_unrelocated(a, offset, value);
    dat_reader_store_pointer(native,
                             dat_reader_unrelocated_value(a, offset, value));
}

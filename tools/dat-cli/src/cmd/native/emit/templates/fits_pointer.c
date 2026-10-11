
uint32_t w = dat_reader_word(a, offset);
return bits_has(&a->archive->reloc, offset, a->archive->size) ||
       bits_has(&a->archive->extern_slot, offset, a->archive->size) ||
       w == 0 || w == UINT32_MAX;

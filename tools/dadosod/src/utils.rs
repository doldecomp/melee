use dol::DolSectionType;

pub(crate) fn get_section_flags(kind: DolSectionType) -> &'static str {
    match kind {
        DolSectionType::Text => "\"ax\"",
        DolSectionType::Data => "\"wa\"",
        DolSectionType::Bss => "\"\", @nobits",
    }
}

#[inline]
pub(crate) fn align(address: u32, alignment: u32) -> u32 {
    !(alignment - 1u32) & (alignment + address) - 1
}

use anyhow::{Context, Result, bail};
use object::{
    Architecture, BinaryFormat, Endianness, SectionKind, SymbolKind,
    SymbolScope,
    elf::{STB_GLOBAL, STT_OBJECT, STV_DEFAULT, SymbolInfo, SymbolOther},
    write::{Object, StandardSegment, Symbol},
};
use std::range::Range;
use winnow::{
    ModalResult, Parser,
    binary::be_u32,
    combinator::repeat,
    token::{rest, take},
};

#[derive(Debug, Clone, Copy)]
pub struct ArchiveHeader {
    pub file_size: u32,
    pub data_size: u32,
    pub reloc_count: u32,
    pub public_count: u32,
    pub extern_count: u32,

    /// Only ever "001B" or null in the files and never used in-game;
    /// probably a string like CardState::comment.
    pub version: [u8; 12],
}

#[derive(Debug, Clone, Copy)]
pub struct NamedSymbol {
    pub offset: u32,
    pub symbol: u32,
}

#[derive(Debug, Clone, Copy)]
pub struct ResolvedPublicSymbol {
    pub data: Range<u32>,
    pub name: Range<u32>,
}

#[derive(Debug)]
pub struct Archive<'a> {
    pub header: ArchiveHeader,
    pub data: &'a [u8],
    pub relocs: Vec<u32>,
    pub publics: Vec<NamedSymbol>,
    pub externs: Vec<NamedSymbol>,
    pub symbols: &'a [u8],
}

fn take_array<const N: usize>(input: &mut &[u8]) -> ModalResult<[u8; N]> {
    let slice: &[u8] = take(N).parse_next(input)?;
    slice.try_into().map_err(|_| {
        winnow::error::ErrMode::Backtrack(winnow::error::ContextError::new())
    })
}

pub fn header(input: &mut &[u8]) -> ModalResult<ArchiveHeader> {
    Ok(ArchiveHeader {
        file_size: be_u32.parse_next(input)?,
        data_size: be_u32.parse_next(input)?,
        reloc_count: be_u32.parse_next(input)?,
        public_count: be_u32.parse_next(input)?,
        extern_count: be_u32.parse_next(input)?,
        version: take_array.parse_next(input)?,
    })
}

pub fn reloc(input: &mut &[u8]) -> ModalResult<u32> {
    be_u32.parse_next(input)
}

pub fn public(input: &mut &[u8]) -> ModalResult<NamedSymbol> {
    Ok(NamedSymbol {
        offset: be_u32.parse_next(input)?,
        symbol: be_u32.parse_next(input)?,
    })
}

pub fn external(input: &mut &[u8]) -> ModalResult<NamedSymbol> {
    Ok(NamedSymbol {
        offset: be_u32.parse_next(input)?,
        symbol: be_u32.parse_next(input)?,
    })
}

pub fn archive<'a>(input: &mut &'a [u8]) -> ModalResult<Archive<'a>> {
    let header = header(input)?;
    Ok(Archive {
        header,
        data: take(header.data_size as usize).parse_next(input)?,
        relocs: repeat(header.reloc_count as usize, reloc)
            .parse_next(input)?,
        publics: repeat(header.public_count as usize, public)
            .parse_next(input)?,
        externs: repeat(header.extern_count as usize, external)
            .parse_next(input)?,
        symbols: rest.parse_next(input)?,
    })
}

impl<'a> Archive<'a> {
    pub fn parse(bytes: &'a [u8]) -> Result<Self> {
        let mut input = bytes;
        let mut parsed = archive
            .parse_next(&mut input)
            .map_err(|e| anyhow::anyhow!("DAT parse error: {e:?}"))?;

        if parsed.header.file_size != bytes.len() as u32 {
            bail!(
                "byte-order mismatch or truncated file: header says {} bytes, buffer is {} bytes",
                parsed.header.file_size,
                bytes.len(),
            );
        }

        // TODO: Kind of hacky but archive symbols are not actually in order
        parsed.publics.sort_unstable_by_key(|ns| ns.offset);
        parsed.externs.sort_unstable_by_key(|ns| ns.offset);

        Ok(parsed)
    }

    // TODO: Lookup based on next symbol table start
    pub fn symbol_at(&self, offset: u32) -> Option<&'a [u8]> {
        let start = offset as usize;
        if start >= self.symbols.len() {
            return None;
        }
        let end = self.symbols[start..].iter().position(|&b| b == 0)? + start;
        Some(&self.symbols[start..end])
    }

    pub fn public_size(&self, index: usize) -> Option<u32> {
        let len = self.publics.len();

        if index >= len {
            return None;
        }
        let ns = self.publics[index];

        let next_offset = if index == len - 1 {
            self.header.data_size
        } else {
            self.publics[index + 1].offset
        };

        assert!(ns.offset < next_offset);
        Some(next_offset - ns.offset)
    }

    /// Public symbols with their names, in offset order.
    pub fn named_publics(
        &self,
    ) -> impl Iterator<Item = (&'a [u8], NamedSymbol)> + '_ {
        self.publics
            .iter()
            .filter_map(|&p| Some((self.symbol_at(p.symbol)?, p)))
    }

    /// Bytes from `offset` to the next public symbol after it, or to the
    /// end of the data: an upper bound on the size of what `offset` labels.
    pub fn extent(&self, offset: u32) -> u32 {
        let next = self
            .publics
            .iter()
            .map(|p| p.offset)
            .find(|&o| o > offset)
            .unwrap_or(self.header.data_size);
        next.saturating_sub(offset)
    }

    pub fn get_public(&self, name: &[u8]) -> Option<&'a [u8]> {
        self.publics.iter().find_map(|p| {
            let sym = self.symbol_at(p.symbol)?;
            (sym == name).then(|| &self.data[p.offset as usize..])
        })
    }

    pub fn get_external(&self, idx: usize) -> Option<&'a [u8]> {
        let e = self.externs.get(idx)?;
        self.symbol_at(e.symbol)
    }

    pub fn externals_iter(
        &self,
    ) -> impl Iterator<Item = (&NamedSymbol, &'a [u8])> + '_ {
        self.externs
            .iter()
            .filter_map(|e| self.symbol_at(e.symbol).map(|s| (e, s)))
    }

    const SMALL_DATA_MAX: u64 = 8;

    pub fn to_object(&self) -> Result<Vec<u8>> {
        dbg!(
            self.symbols
                .split(|&b| b == 0) // Split on every null byte
                .filter(|chunk| !chunk.is_empty()) // Skip empty chunks (e.g., trailing or double nulls)
                .filter_map(|chunk| str::from_utf8(chunk).ok()) // Convert valid UTF-8/ASCII to &str
                .collect::<Vec<_>>()
        );
        let mut obj = Object::new(
            BinaryFormat::Elf,
            Architecture::PowerPc,
            Endianness::Big,
        );

        let data = obj.add_section(
            obj.segment_name(StandardSegment::Data).to_vec(),
            b".data".to_vec(),
            SectionKind::Data,
        );
        let sdata = obj.add_section(
            obj.segment_name(StandardSegment::Data).to_vec(),
            b".sdata".to_vec(),
            SectionKind::Data,
        );

        dbg!(self.header);
        dbg!(self.symbols.len());
        let mut publics: Vec<_> = self.publics.iter().collect();
        publics.sort_by_key(|p| p.offset);

        let data_size = self.header.data_size;

        for (i, NamedSymbol { offset, symbol }) in
            self.publics.iter().chain(self.externs.iter()).enumerate()
        {
            let name = self.symbol_at(*symbol).with_context(|| {
                format!("public at offset {:#x} has no symbol", *offset)
            })?;
            let next =
                publics.get(i + 1).map(|n| n.offset).unwrap_or(data_size);
            let size = next.saturating_sub(*offset) as u64;

            let start = *offset as usize;
            let end = start + size as usize;
            let bytes = &self.data[start..end];

            let section = if size <= Self::SMALL_DATA_MAX {
                sdata
            } else {
                data
            };
            obj.append_section_data(section, bytes, 4);

            let section_offset =
                obj.section(section).data().len() as u64 - size;

            obj.add_symbol(dbg!(Symbol {
                name: name.to_vec(),
                value: section_offset,
                size,
                kind: SymbolKind::Data,
                scope: SymbolScope::Compilation,
                weak: false,
                section: object::write::SymbolSection::Section(section),
                flags: object::write::SymbolFlags::Elf {
                    st_info: SymbolInfo((STB_GLOBAL.0 << 4) + STT_OBJECT.0),
                    st_other: SymbolOther(STV_DEFAULT.0),
                },
            }));
        }

        // TODO: no anyhow here
        obj.write().context("writing object")
    }
}

use anyhow::{Result, bail};
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

/// An archive as `HSD_ArchiveParse` reads it, with its tables in file
/// order: the game looks names up in that order, first match wins.
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
    /// Parse one archive, refusing anything the game would misread: a size
    /// that isn't the file's (`HSD_ArchiveParse`'s byte-order check), a
    /// relocation outside the data (`Locate` would write past it), or a
    /// name outside the symbol table. Relocations needn't be aligned: the
    /// game relocates one at a halfword (`TyMnInfo.dat`).
    pub fn parse(bytes: &'a [u8]) -> Result<Self> {
        let mut input = bytes;
        let parsed = archive
            .parse_next(&mut input)
            .map_err(|e| anyhow::anyhow!("DAT parse error: {e:?}"))?;

        if parsed.header.file_size != bytes.len() as u32 {
            bail!(
                "byte-order mismatch or truncated file: header says {} bytes, buffer is {} bytes",
                parsed.header.file_size,
                bytes.len(),
            );
        }
        let data_size = parsed.header.data_size;
        if let Some(&r) =
            parsed.relocs.iter().find(|&&r| r.checked_add(4).is_none_or(|end| end > data_size))
        {
            bail!("relocation at {r:#X} is outside the data ({data_size:#X} bytes)");
        }
        for (kind, table) in [("public", &parsed.publics), ("extern", &parsed.externs)] {
            if let Some(ns) = table.iter().find(|ns| parsed.symbol_at(ns.symbol).is_none()) {
                bail!("{kind} at {:#X} names {:#X}, outside the symbol table", ns.offset, ns.symbol);
            }
        }
        if let Some(ns) = parsed.publics.iter().find(|ns| ns.offset > data_size) {
            bail!("public at {:#X} is outside the data ({data_size:#X} bytes)", ns.offset);
        }

        Ok(parsed)
    }

    /// Every archive in `bytes`, with its offset: usually one, but some files
    /// (`Pl??AJ.dat`) pack several, each padded to 32 bytes.
    pub fn parse_packed(bytes: &'a [u8]) -> Result<Vec<(usize, Self)>> {
        let mut archives = Vec::new();
        let mut offset = 0;
        while offset < bytes.len() {
            let rest = &bytes[offset..];
            let size = header
                .parse_next(&mut &rest[..])
                .map_err(|e| anyhow::anyhow!("DAT parse error: {e:?}"))?
                .file_size as usize;
            if size == 0 || size > rest.len() {
                bail!("archive at {offset:#X} has size {size:#X}");
            }
            archives.push((offset, Self::parse(&rest[..size])?));
            offset += size.next_multiple_of(32);
        }
        Ok(archives)
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

    /// Bytes from the `index`th public symbol to the next one after it, or
    /// to the end of the data.
    pub fn public_size(&self, index: usize) -> Option<u32> {
        Some(self.extent(self.publics.get(index)?.offset))
    }

    /// Public symbols with their names, in the archive's order.
    pub fn named_publics(
        &self,
    ) -> impl Iterator<Item = (&'a [u8], NamedSymbol)> + '_ {
        // `parse` checked that every name resolves
        self.publics
            .iter()
            .filter_map(|&p| Some((self.symbol_at(p.symbol)?, p)))
    }

    /// Where the loader writes each extern's address, by offset, with the
    /// extern's name: as `HSD_ArchiveLocateExtern` does, a chain from the
    /// extern's offset through the words, each holding the next offset,
    /// until -1 or the end of the data.
    pub fn extern_slots(&self) -> std::collections::BTreeMap<u32, &'a [u8]> {
        let mut slots = std::collections::BTreeMap::new();
        for e in &self.externs {
            let Some(name) = self.symbol_at(e.symbol) else {
                continue;
            };
            let mut offset = e.offset;
            while offset != u32::MAX
                && (offset as usize) + 4 <= self.data.len()
                && slots.insert(offset, name).is_none()
            {
                let at = offset as usize;
                offset = u32::from_be_bytes(
                    self.data[at..at + 4].try_into().unwrap(),
                );
            }
        }
        slots
    }

    /// Bytes from `offset` to the next public symbol after it, or to the
    /// end of the data: an upper bound on the size of what `offset` labels.
    pub fn extent(&self, offset: u32) -> u32 {
        let next = self
            .publics
            .iter()
            .map(|p| p.offset)
            .filter(|&o| o > offset)
            .min()
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
}

//! Read initialized data by virtual address from an original DOL.

use anyhow::{Context, Result, bail, ensure};

struct Section<'a> {
    address: u32,
    data: &'a [u8],
}

pub struct Dol<'a> {
    sections: Vec<Section<'a>>,
}

impl<'a> Dol<'a> {
    pub fn parse(bytes: &'a [u8]) -> Result<Self> {
        ensure!(bytes.len() >= 0x100, "truncated DOL header");
        let word =
            |at| u32::from_be_bytes(bytes[at..at + 4].try_into().unwrap());
        let mut sections: Vec<Section<'a>> = Vec::new();
        // Seven text and eleven data sections, in parallel header arrays.
        for i in 0..18 {
            let size = word(0x90 + i * 4);
            if size == 0 {
                continue;
            }
            let offset = usize::try_from(word(i * 4))?;
            let address = word(0x48 + i * 4);
            let end = u64::from(address) + u64::from(size);
            ensure!(end <= 1 << 32, "DOL section {i}: address overflow");
            ensure!(
                sections.iter().all(|s| {
                    end <= u64::from(s.address)
                        || u64::from(address)
                            >= u64::from(s.address) + s.data.len() as u64
                }),
                "DOL section {i}: overlapping virtual addresses"
            );
            ensure!(offset >= 0x100, "DOL section {i}: data in header");
            let file_end = offset
                .checked_add(usize::try_from(size)?)
                .context("DOL section file offset overflow")?;
            let data = bytes
                .get(offset..file_end)
                .with_context(|| format!("DOL section {i}: truncated data"))?;
            sections.push(Section { address, data });
        }
        Ok(Self { sections })
    }

    /// The rest of the file-backed section containing `address`. BSS and
    /// gaps have no initialized bytes in the DOL.
    fn rest(&self, address: u32) -> Result<&'a [u8]> {
        for section in &self.sections {
            let Some(at) = address.checked_sub(section.address) else {
                continue;
            };
            if let Some(rest) = section
                .data
                .get(at as usize..)
                .filter(|rest| !rest.is_empty())
            {
                return Ok(rest);
            }
        }
        bail!("DOL has no initialized data at {address:#X}")
    }

    pub fn bytes(&self, address: u32, size: u32) -> Result<&'a [u8]> {
        self.rest(address)?
            .get(..usize::try_from(size)?)
            .with_context(|| {
                format!("DOL range at {address:#X} of size {size:#X} exceeds section")
            })
    }

    pub fn string(&self, address: u32) -> Result<&'a str> {
        let rest = self.rest(address)?;
        let end = rest.iter().position(|&b| b == 0).with_context(|| {
            format!("unterminated DOL string at {address:#X}")
        })?;
        Ok(std::str::from_utf8(&rest[..end])?)
    }
}

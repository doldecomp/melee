//! Validate the ranges used by ftData_80085A14 and ftData_80085CD8.

use anyhow::{Context, Result, bail, ensure};
use melee_dat::hsd::{Archive, PackedMotion};
use object::{Object, ObjectSection, ObjectSymbol};
use std::{
    fs,
    io::{self, Write},
    path::PathBuf,
};

#[derive(clap::Args)]
pub struct Args {
    /// Linked game ELF containing the fighter filename and count tables
    #[arg(long, default_value = "build/GALE01/main.elf")]
    elf: PathBuf,
    /// Extracted disc files
    #[arg(long, default_value = "orig/GALE01/files")]
    files: PathBuf,
}

struct Memory<'a> {
    file: object::File<'a>,
}

impl<'a> Memory<'a> {
    fn bytes(&self, address: u64, size: u64) -> Result<&'a [u8]> {
        for section in self.file.sections() {
            if let Some(bytes) = section.data_range(address, size)? {
                return Ok(bytes);
            }
        }
        bail!("ELF has no data at {address:#X} of size {size:#X}")
    }

    fn global(&self, name: &str) -> Result<&'a [u8]> {
        let symbol = self
            .file
            .symbols()
            .find(|s| s.name().ok() == Some(name))
            .with_context(|| format!("ELF has no symbol `{name}`"))?;
        ensure!(symbol.size() > 0, "ELF symbol `{name}` has no size");
        self.bytes(symbol.address(), symbol.size())
    }

    fn string(&self, address: u32) -> Result<&'a str> {
        let address = u64::from(address);
        for section in self.file.sections() {
            let Some(at) = address.checked_sub(section.address()) else {
                continue;
            };
            let data = section.data()?;
            let Some(rest) =
                data.get(at as usize..).filter(|rest| !rest.is_empty())
            else {
                continue;
            };
            let end =
                rest.iter().position(|&b| b == 0).with_context(|| {
                    format!("unterminated ELF string at {address:#X}")
                })?;
            return Ok(std::str::from_utf8(&rest[..end])?);
        }
        bail!("ELF has no string at {address:#X}")
    }
}

fn word(bytes: &[u8], at: usize) -> Result<u32> {
    let end = at.checked_add(4).context("word offset overflow")?;
    let bytes = bytes
        .get(at..end)
        .with_context(|| format!("no word at {at:#X}"))?;
    Ok(u32::from_be_bytes(bytes.try_into().unwrap()))
}

fn motions<'a>(
    archive: &Archive<'a>,
    symbol: &str,
    count: usize,
) -> Result<Vec<PackedMotion<'a>>> {
    let (_, root) = archive
        .named_publics()
        .find(|(name, _)| *name == symbol.as_bytes())
        .with_context(|| format!("no public symbol `{symbol}`"))?;
    // ftData.xC points to Fighter_WaitAnimData[count]. The game uses x4
    // as the packed-file offset, x8 as the exact archive size, and x0 as
    // the public FigaTree name. The linked ELF gives the runtime count.
    let field = root
        .offset
        .checked_add(0xC)
        .context("ftData offset overflow")?;
    ensure!(
        archive.relocs.contains(&field),
        "{symbol}.xC is not relocated"
    );
    let at = word(archive.data, field as usize)? as usize;
    let end = count
        .checked_mul(24)
        .and_then(|size| at.checked_add(size))
        .context("motion table size overflow")?;
    ensure!(
        end <= archive.data.len(),
        "{symbol}.xC has fewer than {count} motions"
    );
    let mut entries = Vec::with_capacity(count);
    for i in 0..count {
        let at = at + i * 24;
        let offset = word(archive.data, at + 4)?;
        let size = word(archive.data, at + 8)?;
        let name = if size == 0 {
            &[][..]
        } else {
            ensure!(
                archive.relocs.contains(&(at as u32)),
                "motion {i}: name is not relocated"
            );
            let name = word(archive.data, at)? as usize;
            let rest = archive
                .data
                .get(name..)
                .with_context(|| format!("motion {i}: name outside data"))?;
            let end = rest
                .iter()
                .position(|&b| b == 0)
                .with_context(|| format!("motion {i}: unterminated name"))?;
            &rest[..end]
        };
        entries.push(PackedMotion {
            offset,
            size,
            symbol: name,
        });
    }
    Ok(entries)
}

pub fn run(args: Args) -> Result<()> {
    let bytes =
        fs::read(&args.elf).with_context(|| args.elf.display().to_string())?;
    let memory = Memory {
        file: object::File::parse(&*bytes)?,
    };
    ensure!(
        memory.file.architecture() == object::Architecture::PowerPc
            && !memory.file.is_little_endian(),
        "expected a big-endian PowerPC game ELF"
    );
    let counts = memory.global("ftData_Table_Unk0")?;
    let names = memory.global("ftData_803C1F40")?;
    let packed = memory.global("ftData_803C23E4")?;
    ensure!(
        counts.len() % 8 == 0
            && names.len() == counts.len()
            && packed.len() == counts.len() / 2,
        "fighter filename and count tables have different lengths"
    );
    let mut out = io::stdout().lock();
    let (mut tables, mut checked, mut unreferenced) = (0, 0, 0);
    for kind in 0..counts.len() / 8 {
        let dat = word(names, kind * 8)?;
        let aj = word(packed, kind * 4)?;
        if dat == 0 || aj == 0 {
            continue;
        }
        let dat = memory.string(dat)?;
        let symbol = memory.string(word(names, kind * 8 + 4)?)?;
        let aj = memory.string(aj)?;
        let count = word(counts, kind * 8 + 4)? as usize;
        let result = (|| {
            let dat_bytes = fs::read(args.files.join(dat))?;
            let archive = Archive::parse(&dat_bytes)?;
            let entries = motions(&archive, symbol, count)?;
            let packed_bytes = fs::read(args.files.join(aj))?;
            Archive::check_packed_motions(&packed_bytes, &entries)
        })()
        .with_context(|| format!("fighter {kind}: {dat} → {aj}"))?;
        writeln!(
            out,
            "{aj}: {} motions checked, {} unreferenced archives",
            result.checked, result.unreferenced
        )?;
        tables += 1;
        checked += result.checked;
        unreferenced += result.unreferenced;
    }
    ensure!(tables > 0, "no fighter animation files were checked");
    writeln!(
        out,
        "{tables} fighter tables: {checked} motions checked, {unreferenced} unreferenced archive instances"
    )?;
    Ok(())
}

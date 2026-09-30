use anyhow::{Result, bail};
use std::path::PathBuf;

pub mod project;
pub mod samples;
pub mod symbols;
pub mod types;

/// A DWARF file from `--dwarf`, else `$MELEE_DWARF_ELF`.
pub fn dwarf_path(path: Option<PathBuf>) -> Result<PathBuf> {
    match path.or_else(|| std::env::var_os("MELEE_DWARF_ELF").map(Into::into))
    {
        Some(path) => Ok(path),
        None => bail!("no DWARF file: pass --dwarf or set MELEE_DWARF_ELF"),
    }
}

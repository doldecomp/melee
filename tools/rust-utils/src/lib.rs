// TODO: thiserror
use anyhow::{Context, Result};
use globset::{Glob, GlobSet, GlobSetBuilder};
use lazy_static::lazy_static;
use log::debug;
use regex::Regex;
use std::{
    env,
    fs::OpenOptions,
    io::{Read, Seek, Write},
    path::{Path, PathBuf},
};
use walkdir::WalkDir;

lazy_static! {
    pub static ref ROOT: PathBuf = Path::new(env!("CARGO_MANIFEST_DIR"))
        .ancestors()
        .nth(2)
        .expect("Failed to find the project root directory.")
        .to_owned();
    pub static ref ROOT_STR: String = ROOT.to_string_lossy().to_string();
    pub static ref SRC_FILES: GlobSet = GlobSetBuilder::new()
        .add(
            Glob::new(&format!(
                "{}/{{asm,src,docs}}/**/*.{{s,c,h,dox,md}}",
                *ROOT_STR
            ))
            .expect("Failed to create source files glob.")
        )
        .add(
            Glob::new(&format!("{}/obj_files.mk", *ROOT_STR))
                .expect("Failed to parse obj_files glob.")
        )
        .build()
        .expect("Failed to create SRC_FILES glob.");
}

pub fn set_current_dir() -> anyhow::Result<()> {
    env::set_current_dir(&*ROOT)
        .context("Failed to change directory to project root.")
}

pub fn replace_all<'to>(from: &Regex, to: &'to str) -> Result<()> {
    replace_all_with(from, |_| to)
}

pub fn replace_all_with<'to, F>(from: &Regex, to: F) -> Result<()>
where
    F: Fn(&Path) -> &'to str,
{
    for entry in WalkDir::new(&*ROOT) {
        let entry = entry?;
        let path = entry.path();
        if entry.file_type().is_file() && SRC_FILES.is_match(path) {
            debug!("Replacing in {path:?}.");
            replace(from, &to(path), path)?;
        }
    }
    Ok(())
}

pub fn replace(from: &Regex, to: &str, path: &Path) -> Result<()> {
    let mut file = OpenOptions::new().read(true).write(true).open(path)?;
    let mut buffer = String::new();
    file.read_to_string(&mut buffer)?;

    debug!("{from} -> {to}");
    let updated_contents = from.replace_all(&buffer, to);
    file.seek(std::io::SeekFrom::Start(0))?;
    file.set_len(updated_contents.len() as u64)?;
    file.write_all(updated_contents.as_bytes())?;

    Ok(())
}

use anyhow::{Context, Result};
use globset::{Glob, GlobSet, GlobSetBuilder};
use lazy_static::lazy_static;
use log::debug;
use memmap2::MmapOptions;
use regex::Regex;
use std::{
    borrow::Borrow,
    collections::HashMap,
    env,
    fs::OpenOptions,
    hash::BuildHasher,
    io::{self, Read, Seek, SeekFrom, Write},
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
        .add(
            Glob::new(&format!("{}/ldscript.lcf", *ROOT_STR))
                .expect("Failed to parse ldscript glob.")
        )
        .add(
            Glob::new(&format!(
                "{}/config/**/{{symbols,splits}}.txt",
                *ROOT_STR
            ))
            .expect("Failed to parse dtk config glob.")
        )
        .build()
        .expect("Failed to create SRC_FILES glob.");
}

pub fn set_current_dir() -> anyhow::Result<()> {
    env::set_current_dir(&*ROOT)
        .context("Failed to change directory to project root.")
}

pub fn walk_src() -> Result<Vec<PathBuf>> {
    WalkDir::new(&*ROOT)
        .into_iter()
        .filter_map(|res| {
            res.map(|entry| {
                let path = entry.path();
                if entry.file_type().is_file() && SRC_FILES.is_match(path) {
                    Some(path.to_owned())
                } else {
                    None
                }
            })
            .context("Failed to resolve WalkDir entry.")
            .transpose()
        })
        .collect::<Result<Vec<_>>>()
}

pub fn replace(from: &Regex, to: &str, path: impl AsRef<Path>) -> Result<()> {
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

fn is_identifier(c: char) -> bool {
    matches!(c, 'a'..='z' | 'A'..='Z' | '0'..='9' | '_')
}

/// TODO: Rewrite this using simple regex or nom
pub fn replace_symbols<K, V, S>(
    path: impl AsRef<Path>,
    replacements: &HashMap<K, V, S>,
) -> io::Result<()>
where
    K: Eq + PartialEq + std::hash::Hash + Borrow<str>,
    V: AsRef<str>,
    S: BuildHasher,
{
    let mut file = OpenOptions::new().read(true).write(true).open(path)?;
    let mmap = unsafe { MmapOptions::new().map_mut(&file)? };
    let content = String::from_utf8_lossy(&mmap);

    let mut buffer = String::with_capacity(content.len());

    let mut start = 0;
    while let Some(end) = content[start..].find(|c| !is_identifier(c)) {
        let old = &content[start..start + end];

        match replacements.get(old) {
            Some(new) => buffer.push_str(new.as_ref()),
            None => buffer.push_str(old),
        }

        start += end;
        if let Some(next_start) = content[start..].find(is_identifier) {
            buffer.push_str(&content[start..start + next_start]);
            start += next_start;
        } else {
            break;
        }
    }
    if start < content.len() {
        buffer.push_str(&content[start..]);
    }

    file.seek(SeekFrom::Start(0))?;
    file.write_all(buffer.as_bytes())?;
    file.set_len(buffer.len() as u64)?;

    Ok(())
}

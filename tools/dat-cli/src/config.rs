use crate::serde::*;
use anyhow::{Context, Result};
use globset::{Glob, GlobSetBuilder};
use jwalk::WalkDir;
use serde::{Deserialize, Serialize};
use std::{
    borrow::Cow,
    env, fs,
    path::{Path, PathBuf},
};
use typed_path::Utf8UnixPathBuf;

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct ProjectConfig {
    #[serde(with = "unix_path")]
    pub base: Utf8UnixPathBuf,
    pub include: Vec<String>,
    #[serde(with = "unix_path")]
    pub symbols: Utf8UnixPathBuf,
    pub samples: SamplesConfig,
}

/// Where `samples` writes, and how it compiles.
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct SamplesConfig {
    /// Everything generated: `target/`, `src/`, `base/`, `objdiff.json`.
    #[serde(with = "unix_path")]
    pub dir: Utf8UnixPathBuf,
    /// A game object in `build.ninja`; samples compile with its command.
    #[serde(with = "unix_path")]
    pub compile_like: Utf8UnixPathBuf,
}

pub fn get_config(
    proj_path: Option<impl AsRef<Path>>,
    cfg_path: impl AsRef<Path>,
) -> Result<ProjectConfig> {
    let path = proj_path_to(proj_path, cfg_path)?;
    let f = fs::File::open(path)?;
    Ok(serde_yaml::from_reader(f)?)
}

// TODO: thiserror
pub fn resolve_proj_path<'p, P>(
    proj_path: Option<&'p P>,
) -> Result<Cow<'p, Path>>
where
    P: AsRef<Path> + ?Sized,
{
    match proj_path {
        Some(p) => Ok(Cow::Borrowed(p.as_ref())),
        None => env::current_dir()
            .map(Cow::Owned)
            .context("failed to fall back to current directory"),
    }
}

// TODO: thiserror
pub fn proj_path_to<P, D>(proj_path: Option<P>, dst: D) -> Result<PathBuf>
where
    P: AsRef<Path>,
    D: AsRef<Path>,
{
    Ok(resolve_proj_path(proj_path.as_ref())?.join(dst))
}

/// Single opaque error. Add one variant to your app enum:
///   #[error(transparent)]
///   Gather(#[from] GatherError),
#[derive(Debug, thiserror::Error)]
#[error("{0}")]
pub struct GatherError(String);

pub fn gather_files(
    root: impl AsRef<Path>,
    patterns: &[String],
) -> Result<Vec<PathBuf>, GatherError> {
    // A leading `!` excludes what the pattern matches
    let mut include = GlobSetBuilder::new();
    let mut exclude = GlobSetBuilder::new();
    for pat in patterns {
        let (builder, glob) = match pat.strip_prefix('!') {
            Some(glob) => (&mut exclude, glob),
            None => (&mut include, pat.as_str()),
        };
        builder.add(
            Glob::new(glob)
                .map_err(|e| GatherError(format!("bad glob `{pat}`: {e}")))?,
        );
    }
    let build = |builder: GlobSetBuilder| {
        builder
            .build()
            .map_err(|e| GatherError(format!("glob set: {e}")))
    };
    let (include, exclude) = (build(include)?, build(exclude)?);

    let mut out = Vec::new();
    for entry in WalkDir::new(&root).into_iter().filter_map(Result::ok) {
        if !entry.file_type().is_file() {
            continue;
        }

        let path = entry.path();

        let rel = path
            .strip_prefix(&root)
            .map_err(|e| GatherError(format!("strip prefix: {e}")))?;

        // Bridge the typed relative path to std::path::Path for matching.
        let rel_std = std::path::Path::new(rel);

        if include.is_match(rel_std) && !exclude.is_match(rel_std) {
            out.push(path);
        }
    }
    Ok(out)
}

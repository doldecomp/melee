use anyhow::Context;
use std::env;
use std::path::Path;

// TODO: thiserror
pub fn set_current_dir() -> anyhow::Result<()> {
    env::set_current_dir(
        Path::new(env!("CARGO_MANIFEST_DIR"))
            .ancestors()
            .nth(2)
            .with_context(|| "Failed to find project root directory.")?,
    )
    .with_context(|| "Failed to change directory to project root.")
}

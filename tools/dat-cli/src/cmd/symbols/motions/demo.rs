//! Demo motion groups selected by ftDemo_SetArchiveData and ftDemo_CreateFighter.

use super::{Args, global, motions, word};
use anyhow::{Context, Result, ensure};
use melee_dat::{
    config::gather_files,
    dol::Dol,
    dtk::SymbolFile,
    hsd::{Archive, archive_name},
};
use std::{
    collections::{BTreeMap, BTreeSet},
    fs,
    io::Write,
    ops::Range,
};

struct DemoFile<'a> {
    kind: usize,
    motions: Range<usize>,
    symbol: &'a str,
}

fn requests<'a>(
    memory: &Dol<'a>,
    symbols: &SymbolFile,
    counts: &[u8],
    kinds: usize,
) -> Result<Vec<DemoFile<'a>>> {
    let names = global(memory, symbols, "ftData_803C2468")?;
    let getters = global(memory, symbols, "ftData_803C24EC")?;
    ensure!(
        counts.len() == kinds * 8
            && names.len() == kinds * 4
            && getters.len() == names.len(),
        "fighter and demo tables have different lengths"
    );
    // These getters return entries of the named DOL tables. Their indices
    // start at motion 14, after the four common demo groups.
    let extra = [
        (
            "ftMr_Init_GetMotionFileString",
            "ftMr_Init_DemoViMotionFilenames",
        ),
        ("ftKb_Init_GetMotionFileString", "ftKb_Init_803CA5A4"),
        ("ftLg_Init_GetMotionFileString", "ftLg_Init_803D0AAC"),
        ("ftGk_Init_GetMotionFileString", "ftGk_Init_803D3984"),
    ]
    .into_iter()
    .map(|(getter, table)| Ok((symbols.lookup(getter)?.address, table)))
    .collect::<Result<Vec<_>>>()?;
    let mut files = Vec::new();
    for kind in 0..kinds {
        let count = word(counts, kind * 8 + 4)? as usize;
        let at = word(names, kind * 4)?;
        if at != 0 {
            let names = memory.bytes(at, 16)?;
            // ftDemo_CreateFighter selects result, intro, ending and vi-wait.
            for (i, motions) in
                [0..10, 10..12, 12..13, 13..14].into_iter().enumerate()
            {
                let name = word(names, i * 4)?;
                if name == 0 {
                    continue;
                }
                ensure!(
                    motions.end <= count,
                    "fighter {kind}: demo group exceeds {count} motions"
                );
                files.push(DemoFile {
                    kind,
                    motions,
                    symbol: memory.string(name)?,
                });
            }
        }
        let getter = word(getters, kind * 4)?;
        if getter == 0 {
            ensure!(count <= 14, "fighter {kind}: no movie motion getter");
            continue;
        }
        let (_, table) = extra
            .iter()
            .find(|(address, _)| *address == getter)
            .with_context(|| {
                format!(
                    "fighter {kind}: unknown movie motion getter {getter:#X}"
                )
            })?;
        let names = global(memory, symbols, table)?;
        ensure!(
            count >= 14 && names.len() == (count - 14) * 4,
            "fighter {kind}: {table} does not cover motions 14..{count}"
        );
        let mut groups = Vec::new();
        for i in 0..names.len() / 4 {
            let name = word(names, i * 4)?;
            if name != 0 {
                groups.push((14 + i, memory.string(name)?));
            }
        }
        ensure!(
            groups.first().is_some_and(|&(start, _)| start == 14),
            "fighter {kind}: {table} has no name for motion 14"
        );
        for (i, &(start, symbol)) in groups.iter().enumerate() {
            // Kirby's first movie loads motions 14..17 together; the two
            // null name slots belong to that same payload.
            let end = groups.get(i + 1).map_or(count, |&(start, _)| start);
            files.push(DemoFile {
                kind,
                motions: start..end,
                symbol,
            });
        }
    }
    Ok(files)
}

pub(super) fn run(
    args: &Args,
    memory: &Dol,
    symbols: &SymbolFile,
    names: &[u8],
    out: &mut impl Write,
) -> Result<()> {
    let counts = global(memory, symbols, "ftData_UnkIntPairs")?;
    let requests = requests(memory, symbols, counts, names.len() / 8)?;
    let kinds: BTreeSet<_> = requests.iter().map(|r| r.kind).collect();
    let mut data = BTreeMap::new();
    for &kind in &kinds {
        let dat = memory.string(word(names, kind * 8)?)?;
        let path = args.files.join(dat);
        data.insert(
            kind,
            fs::read(&path).with_context(|| path.display().to_string())?,
        );
    }
    let mut tables = BTreeMap::new();
    for (&kind, bytes) in &data {
        let symbol = memory.string(word(names, kind * 8 + 4)?)?;
        let count = word(counts, kind * 8 + 4)? as usize;
        let entries = (|| {
            let archive = Archive::parse(bytes)?;
            motions(&archive, symbol, 0x14, count)
        })()
        .with_context(|| format!("fighter {kind}: {symbol}.x14"))?;
        tables.insert(kind, entries);
    }
    let mut by_symbol: BTreeMap<_, Vec<_>> = BTreeMap::new();
    for request in &requests {
        by_symbol.entry(request.symbol).or_default().push(request);
    }
    let mut found = BTreeSet::new();
    let (mut groups, mut checked, mut unreferenced) = (0, 0, 0);
    let mut files = gather_files(&args.files, &["*.dat".to_owned()])?;
    files.sort();
    for path in files {
        let bytes =
            fs::read(&path).with_context(|| path.display().to_string())?;
        let archives = Archive::parse_packed(&bytes)
            .with_context(|| path.display().to_string())?;
        for (at, archive) in archives {
            for (name, public) in archive.named_publics() {
                let Some(requests) = std::str::from_utf8(name)
                    .ok()
                    .and_then(|name| by_symbol.get(name))
                else {
                    continue;
                };
                let start = public.offset as usize;
                let end = start + archive.extent(public.offset) as usize;
                let payload = &archive.data[start..end];
                let file = archive_name(&path.display().to_string(), at);
                for request in requests {
                    let label = format!(
                        "{file}:{} (fighter {}, motions {}..{})",
                        request.symbol,
                        request.kind,
                        request.motions.start,
                        request.motions.end
                    );
                    let result = Archive::check_packed_motions(
                        payload,
                        &tables[&request.kind][request.motions.clone()],
                    )
                    .with_context(|| label.clone())?;
                    writeln!(
                        out,
                        "{label}: {} motions checked, {} unreferenced archives",
                        result.checked, result.unreferenced
                    )?;
                    groups += 1;
                    checked += result.checked;
                    unreferenced += result.unreferenced;
                }
                found.insert(requests[0].symbol);
            }
        }
    }
    let missing: Vec<_> = by_symbol
        .keys()
        .copied()
        .filter(|name| !found.contains(name))
        .collect();
    ensure!(
        missing.is_empty(),
        "missing demo symbols: {}",
        missing.join(", ")
    );
    writeln!(
        out,
        "{} demo fighters: {groups} groups, {checked} motions checked, {unreferenced} unreferenced archive instances",
        kinds.len()
    )?;
    Ok(())
}

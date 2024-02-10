use crate::{
    address::Address, decompme_api::Completion, parse::hex, scratch::Scratch,
};
use ahash::AHashMap;
use anyhow::{bail, Result};
use lazy_static::lazy_static;
use log::{error, info, warn};
use nom::{
    branch::alt,
    bytes::complete::{tag, tag_no_case, take_until1, take_while1},
    combinator::{map, opt},
    error::{FromExternalError, ParseError, VerboseError},
    multi::separated_list1,
    number::complete::float,
    sequence::{preceded, separated_pair, terminated},
    IResult,
};
use petgraph::{
    algo::is_cyclic_directed, graph::DiGraph, prelude::*, visit::Walker,
};
use rayon::prelude::*;
use std::{
    fmt::Write,
    fs::{self, File},
    io::{BufWriter, Write as _},
    num::ParseIntError,
    path::PathBuf,
};
use time::{format_description::well_known::Rfc3339, OffsetDateTime};

lazy_static! {
    static ref TXT_PATH: PathBuf =
        melee_utils::ROOT.join("config/GALE01/scratches.txt");
}

fn completion<'a, E>(input: &'a str) -> IResult<&'a str, Completion, E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    use Completion::*;
    alt((
        map(tag("OK"), |_| Ok),
        map(terminated(float, tag("%")), |f| Percent(f / 100.0)),
    ))(input)
}

pub(crate) fn scratch<'a, E>(input: &'a str) -> IResult<&'a str, Scratch, E>
where
    E: ParseError<&'a str>
        + FromExternalError<&'a str, ParseIntError>
        + FromExternalError<&'a str, time::error::Parse>,
{
    let (input, ((name, (completion, addr)), attrs)) = separated_pair(
        separated_pair(
            take_until1(" = "),
            tag(" = "),
            separated_pair(completion, tag(":"), address),
        ),
        tag("; // "),
        separated_list1(
            tag(" "),
            separated_pair(
                take_until1(":"),
                tag(":"),
                take_while1(|c| c != ' '),
            ),
        ),
    )(input)?;

    let attrs: AHashMap<_, _> = attrs.into_iter().collect();
    let opt_str = |k: &'static str| attrs.get(k).copied().map(str::to_owned);
    let req_str = |k: &'static str| {
        attrs.get(k).copied().ok_or_else(|| {
            nom::Err::Error(E::from_error_kind(k, nom::error::ErrorKind::Tag))
        })
    };
    let req_dt = |k: &'static str| {
        req_str(k).and_then(|s| {
            OffsetDateTime::parse(s, &Rfc3339).map_err(|e| {
                nom::Err::Error(E::from_external_error(
                    s,
                    nom::error::ErrorKind::MapRes,
                    e,
                ))
            })
        })
    };
    let author = opt_str("author");
    let parent = opt_str("parent");
    let id = req_str("id")?.to_owned();
    let created = req_dt("created")?;
    let updated = req_dt("updated")?;
    Ok((
        input,
        Scratch {
            name: name.to_owned(),
            completion,
            id,
            addr,
            author,
            parent,
            created,
            updated,
        },
    ))
}

pub(crate) fn address<'a, E>(input: &'a str) -> IResult<&'a str, Address, E>
where
    E: ParseError<&'a str>
        + FromExternalError<&'a str, ParseIntError>
        + FromExternalError<&'a str, time::error::Parse>,
{
    alt((
        map(tag_no_case("INLINE"), |_| Address::Inline),
        map(preceded(opt(tag_no_case("0x")), hex(8)), Address::Value),
        map(tag_no_case("TODO"), |_| Address::Todo),
        map(tag_no_case("UNKNOWN"), |_| Address::Unknown),
        map(tag_no_case("ERROR"), |_| Address::Error),
    ))(input)
}

pub(crate) fn save(scratches: &mut Vec<Scratch>) -> Result<()> {
    let file = File::create(&*TXT_PATH)?;
    let mut w = BufWriter::new(file);
    scratches.par_sort_unstable_by(Scratch::txt_order);
    for scratch in scratches {
        match writeln!(w, "{}", scratch.to_txt()?) {
            Ok(()) => (),
            Err(e) => error!("{}", e),
        }
    }
    w.flush()?;
    Ok(())
}

pub(crate) fn load() -> Result<Vec<Scratch>> {
    let path = &*TXT_PATH;
    if !path.exists() {
        return Ok(Vec::new());
    }

    let mut raw = Vec::new();
    let input = fs::read_to_string(path)?;
    for line in input.lines() {
        let line = line.trim();
        if line.len() > 0 {
            raw.push(line.to_owned());
        }
    }
    raw.par_sort_unstable();
    raw.dedup();

    let mut succeeded = Vec::with_capacity(raw.len());
    let mut failed = false;
    for line in raw {
        match scratch::<VerboseError<&str>>(&line) {
            Ok((_, scratch)) => succeeded.push(scratch),
            Err(e) => {
                failed = true;
                error!("{}", e);
            }
        }
    }

    if failed {
        bail!("failed to parse some scratches, stopping");
    }

    Ok(succeeded)
}

pub(crate) fn fix_families(scratches: &mut Vec<Scratch>) -> Result<()> {
    let mut graph = DiGraph::<_, ()>::new();
    let mut node_indices = AHashMap::new();
    let hash_builder = ahash::RandomState::default();

    for (i, scratch) in scratches.iter().enumerate() {
        let hash = hash_builder.hash_one(&scratch.id);
        let node_idx = graph.add_node(i);
        node_indices.insert(hash, node_idx);
    }

    for scratch in scratches.iter() {
        if let Some(parent) = &scratch.parent {
            let parent_hash = hash_builder.hash_one(parent);
            if let Some(parent_node) = node_indices.get(&parent_hash) {
                let scratch_hash = hash_builder.hash_one(&scratch.id);
                let scratch_node = node_indices.get(&scratch_hash).unwrap();
                graph.add_edge(*parent_node, *scratch_node, ());
            }
        }
    }

    if is_cyclic_directed(&graph) {
        bail!("cycle detected in the graph");
    }

    let roots: Vec<_> = graph.externals(Direction::Incoming).collect();

    for root in roots {
        match propagate_addresses(scratches, &graph, root) {
            Ok(()) => continue,
            Err(e) => warn!("{}", e),
        }
    }

    Ok(())
}

fn propagate_addresses(
    scratches: &mut Vec<Scratch>,
    graph: &DiGraph<usize, ()>,
    root: NodeIndex,
) -> Result<()> {
    use Address::*;
    let dfs = Dfs::new(graph, root);
    let nodes: Vec<_> = dfs.iter(graph).collect();

    let mut addr = Unknown;
    let mut originator = String::new();
    for &node in &nodes {
        let scratch = &scratches[graph[node]];
        match (scratch.addr, addr) {
            (Unknown | Todo, _) => continue,
            (scratch_addr, Unknown) => {
                debug_assert_eq!(originator, "");
                addr = scratch_addr;
                originator.write_str(&scratch.id)?;
            }
            (scratch_addr, cur_addr) if scratch_addr != cur_addr => {
                bail!(
                    "scratch {} has addr {} but its ancestor {} has {}",
                    &scratch.id,
                    scratch_addr,
                    originator,
                    cur_addr,
                );
            }
            _ => continue,
        }
    }

    if addr != Unknown {
        for &node in &nodes {
            let scratch = &mut scratches[graph[node]];
            if scratch.addr == addr {
                continue;
            }
            debug_assert_ne!(scratch.id, originator);
            info!(
                "addr of {} inferred from {} to be {}",
                scratch.id, originator, addr
            );
            scratch.addr = addr;
        }
    }

    Ok(())
}

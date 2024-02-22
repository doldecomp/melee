use crate::{
    address::Address,
    decompme_api, dtk_config,
    scratch::{try_parse_addr, Scratch},
    scratch_config::{self},
};
use ahash::AHashMap;
use anyhow::{anyhow, bail, Context, Result};
use backoff::ExponentialBackoff;
use lazy_static::lazy_static;
use log::{error, info};
use reqwest::blocking::Client;
use serde::{Deserialize, Serialize};
use std::{fmt::Display, io::Read as _, time::Duration, usize};
use time::{format_description::well_known::Rfc3339, OffsetDateTime};
use url::Url;

lazy_static! {
    pub static ref SCRATCHES_ENDPOINT: Url = {
        const PRESET: usize = 63;
        let mut url = Url::parse("https://decomp.me/api/scratch").unwrap();
        url.query_pairs_mut()
            .append_pair("format", "json")
            .append_pair("preset", &PRESET.to_string());
        url
    };
}

#[derive(Serialize, Deserialize, Debug)]
struct Owner {
    is_anonymous: bool,
    username: String,
}

#[derive(Serialize, Deserialize, Debug)]
pub(crate) struct ScratchResponse {
    slug: String,
    owner: Option<Owner>,
    #[serde(with = "time::serde::rfc3339")]
    last_updated: OffsetDateTime,
    #[serde(with = "time::serde::rfc3339")]
    creation_time: OffsetDateTime,
    name: String,
    parent: Option<String>,
    score: i32,
    max_score: i32,
    match_override: bool,
}

#[derive(Serialize, Deserialize, Debug)]
pub(crate) struct ScratchesResponse {
    next: Option<Url>,
    results: Vec<ScratchResponse>,
}

#[derive(Debug, PartialEq, PartialOrd, Clone)]
pub(crate) enum Completion {
    Percent(f32),
    Ok,
}

impl Display for Completion {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        use Completion::*;
        const PLACES: usize = 2;
        match self {
            Ok => write!(f, "OK"),
            Percent(p) => {
                let s = format!("{:.*}", PLACES, p * 100.0);
                let s = s.trim_end_matches('0');
                let s = s.trim_end_matches('.');
                write!(f, "{}%", s)
            }
        }
    }
}

#[derive(Debug, Default)]
pub(crate) struct Scratches {
    pub(crate) next: Option<Url>,
    pub(crate) succeeded: Vec<Scratch>,
    pub(crate) skipped: Vec<ScratchResponse>,
}

pub(crate) fn scratches<'a, F: Fn(&str) -> Option<u32>>(
    json: &str,
    resolve_addr: &F,
) -> Result<Scratches> {
    let response: ScratchesResponse =
        serde_json::from_str(json).context("failed to parse the response")?;
    let mut ret = Scratches::default();
    ret.next = response.next;

    for raw in response.results {
        let &ScratchResponse {
            score,
            match_override,
            max_score,
            ..
        } = &raw;
        if !match_override && (score < 0 || score >= max_score) {
            ret.skipped.push(raw);
            continue;
        }
        let ScratchResponse {
            slug,
            owner,
            last_updated,
            creation_time,
            name,
            score,
            max_score,
            match_override,
            parent,
        } = raw;
        let username = owner.filter(|o| !o.is_anonymous).map(|o| o.username);
        let completion = if match_override {
            1.0
        } else {
            let max_score = max_score as f32;
            let score = max_score - score as f32;
            let completion = score / max_score;
            completion
        };
        let addr: Address =
            resolve_addr(&name).or(try_parse_addr(&name)).into();
        ret.succeeded.push(Scratch {
            id: slug,
            parent,
            author: username,
            addr,
            name,
            created: creation_time,
            updated: last_updated,
            completion: Completion::Percent(completion),
        });
    }

    Ok(ret)
}

fn fetch_url(client: &Client, count: usize, url: &str) -> Result<String> {
    let op = || -> Result<_, backoff::Error<anyhow::Error>> {
        info!("requesting page {}, {}", count, url);
        let mut resp = client
            .get(url)
            .send()
            .map_err(|e| backoff::Error::transient(anyhow!(e)))?;
        let mut content = String::new();
        resp.read_to_string(&mut content)
            .map_err(|e| backoff::Error::permanent(anyhow!(e)))?;
        Ok(content)
    };

    let backoff = ExponentialBackoff::default();
    backoff::retry(backoff, op).map_err(anyhow::Error::msg)
}

pub(crate) fn seed_loop(from: Option<Url>, update: bool) -> Result<()> {
    const MAX_PAGE_SIZE: usize = 100;
    const TIMEOUT: u64 = 10;

    let client = Client::builder()
        .timeout(Duration::from_secs(TIMEOUT))
        .gzip(true)
        .brotli(true)
        .build()?;
    let mut next = from.unwrap_or_else(|| {
        let mut url = SCRATCHES_ENDPOINT.to_owned();
        if !update {
            url.query_pairs_mut()
                .append_pair("page_size", &MAX_PAGE_SIZE.to_string());
        }
        url
    });

    let mut latest = OffsetDateTime::UNIX_EPOCH;
    let symbols = dtk_config::symbol_to_addr()?;
    let hash_builder = ahash::RandomState::default();
    let mut scratches = {
        let vec = scratch_config::load()?;
        let mut map = AHashMap::with_capacity(vec.len());
        let mut valid = true;
        for scratch in vec {
            let hash = hash_builder.hash_one(&scratch.id);
            if let Some(existing) = map.get(&hash) {
                if existing != &scratch {
                    error!("found duplicate scratch id {}", scratch.id);
                    valid = false;
                }
            }
            latest = latest.max(scratch.created);
            map.insert(hash, scratch);
        }
        if valid {
            map
        } else {
            bail!("duplicate scratches found, stopping");
        }
    };

    for i in 0..usize::MAX {
        let text = fetch_url(&client, i, &next.to_string())?;
        let page = decompme_api::scratches(&text, &symbols)?;

        let page_next = match page.next {
            Some(v) => v,
            None => break,
        };

        next = page_next;

        let mut update_done = false;

        for scratch in page.succeeded {
            let hash = hash_builder.hash_one(&scratch.id);
            update_done |= scratch.created <= latest;
            if let Some(existing) = scratches.get_mut(&hash) {
                if let Err(e) = existing.merge(scratch) {
                    error!("{}", e)
                }
            } else {
                scratches.insert(hash, scratch);
            }
        }

        if update && update_done {
            eprintln!(
                "found a scratch created at or before {}, stopping",
                latest.format(&Rfc3339)?
            );
            break;
        }
    }

    let mut buffer = scratches.into_iter().map(|(_, v)| v).collect::<Vec<_>>();
    scratch_config::fix_families(&mut buffer)?;
    scratch_config::save(&mut buffer)?;
    Ok(())
}

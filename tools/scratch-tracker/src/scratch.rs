use crate::{address::Address, decompme_api::Completion};
use anyhow::{bail, Result};
use log::{info, warn};
use std::{
    cmp::Ordering,
    fmt::Write as _,
    ops::{Deref as _, RangeInclusive},
};
use time::{
    format_description::well_known::Rfc3339, OffsetDateTime, UtcOffset,
};

#[derive(Debug, Clone, PartialEq)]
pub(crate) struct Scratch {
    pub(crate) id: String,
    pub(crate) name: String,
    pub(crate) addr: Address,
    pub(crate) author: Option<String>,
    pub(crate) parent: Option<String>,
    pub(crate) completion: Completion,
    pub(crate) created: OffsetDateTime,
    pub(crate) updated: OffsetDateTime,
}

impl Scratch {
    fn fmt_datetime(
        dt: &OffsetDateTime,
    ) -> Result<String, time::error::Format> {
        dt.to_offset(UtcOffset::UTC).format(&Rfc3339)
    }

    pub(crate) fn to_txt(&self) -> Result<String> {
        let mut s = String::new();
        write!(
            s,
            "{} = {}:{}; //",
            &self.name, &self.completion, &self.addr
        )?;

        if let Some(author) = &self.author {
            if author.contains(char::is_whitespace) {
                bail!("author \"{}\" contains whitespace", author);
            }
            write!(s, " author:{}", author)?;
        }

        write!(s, " id:{}", &self.id)?;

        if let Some(parent) = &self.parent {
            write!(s, " parent:{}", parent)?;
        }

        write!(s, " updated:{}", Self::fmt_datetime(&self.updated)?)?;
        write!(s, " created:{}", Self::fmt_datetime(&self.created)?)?;

        Ok(s)
    }

    pub(crate) fn txt_order(a: &Self, b: &Self) -> Ordering {
        match a.addr.cmp(&b.addr) {
            Ordering::Equal => {}
            ordering => return ordering,
        }

        match b.completion.partial_cmp(&a.completion) {
            None | Some(Ordering::Equal) => {}
            Some(ordering) => return ordering,
        }

        match a.updated.partial_cmp(&b.updated) {
            None | Some(Ordering::Equal) => {}
            Some(ordering) => return ordering,
        }

        match a.created.partial_cmp(&b.created) {
            None | Some(Ordering::Equal) => {}
            Some(ordering) => return ordering,
        }

        match a.author.cmp(&b.author) {
            Ordering::Equal => {}
            ordering => return ordering,
        }

        match a.id.cmp(&b.id) {
            Ordering::Equal => {}
            ordering => return ordering,
        }

        Ordering::Equal
    }

    pub(crate) fn merge(&mut self, other: Self) -> Result<()> {
        if self.id != other.id {
            bail!("tried to merge {} with {}", self.id, other.id);
        }

        let id = self.id.deref();

        if self.completion != Completion::Ok {
            self.completion = other.completion;
        }

        if other.addr.is_set() && self.addr != other.addr {
            if self.addr.is_unset() {
                self.addr = other.addr;
            } else {
                warn!(
                    "addr of {} changed from {} to {}",
                    id, self.addr, other.addr
                );
            }
        }

        match (&self.author, other.author) {
            (None, theirs @ Some(_)) => {
                info!(
                    "author of {} updated to {}",
                    id,
                    theirs.as_deref().unwrap()
                );
                self.author = theirs;
            }
            (Some(mine), None) => {
                warn!("author of {} ({}) was removed", id, mine)
            }
            (Some(mine), Some(theirs)) if *mine != theirs => {
                warn!("author of {} changed from {} to {}", id, mine, theirs)
            }
            _ => (),
        };

        if self.parent != other.parent {
            warn!(
                "parent of {} changed from {:?} to {:?}",
                id, self.parent, other.parent
            );
            self.parent = other.parent;
        }

        if self.created != other.created {
            warn!(
                "creation time of {} changed from {} to {}",
                id, self.created, other.created
            );
            self.created = other.created;
        }

        match self.updated.cmp(&other.updated) {
            Ordering::Less => {
                info!("{} updated at {}", id, other.updated);
                self.updated = other.updated;
            }
            Ordering::Greater => {
                warn!(
                    "updated time of {} moved backward from {} to {}",
                    id, self.updated, other.updated
                );
            }
            Ordering::Equal => (),
        }

        Ok(())
    }
}

pub(crate) fn try_parse_addr(input: &str) -> Option<u32> {
    const ADDR_SPACE: RangeInclusive<u32> = 0x80003100..=0x804DEC00;
    let mut hex: u32 = 0;
    let mut count: u32 = 0;
    for c in input.chars().rev() {
        if c.is_ascii_hexdigit() {
            hex |= c.to_digit(16).unwrap().wrapping_shl(4 * count);
            count += 1;
            continue;
        }
        if count == 8 {
            break;
        }
        count = 0;
        hex = 0;
    }
    if count == 8 && ADDR_SPACE.contains(&hex) {
        Some(hex)
    } else {
        None
    }
}

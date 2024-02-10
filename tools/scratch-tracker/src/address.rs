use crate::scratch_config::address;
use anyhow::{anyhow, Result};
use nom::{combinator::all_consuming, error::VerboseError};
use std::{fmt, str::FromStr};

#[derive(Debug, Copy, Clone, Eq, Ord, PartialEq, PartialOrd)]
pub(crate) enum Address {
    Todo,
    Inline,
    Value(u32),
    Unknown,
    Error,
}

impl Address {
    pub(crate) fn is_unset(&self) -> bool {
        match *self {
            Self::Todo | Self::Unknown => true,
            Self::Inline | Self::Value(_) | Self::Error => false,
        }
    }

    pub(crate) fn is_set(&self) -> bool {
        match *self {
            Self::Inline | Self::Value(_) | Self::Error => true,
            Self::Todo | Self::Unknown => false,
        }
    }
}

impl From<Option<u32>> for Address {
    fn from(item: Option<u32>) -> Self {
        match item {
            Some(value) => Address::Value(value),
            None => Address::Unknown,
        }
    }
}

impl fmt::Display for Address {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Address::Inline => write!(f, "INLINE"),
            Address::Value(v) => write!(f, "0x{:08X}", v),
            Address::Todo => write!(f, "TODO"),
            Address::Unknown => write!(f, "UNKNOWN"),
            Address::Error => write!(f, "ERROR"),
        }
    }
}

impl<'a> FromStr for Address {
    type Err = anyhow::Error;

    fn from_str(s: &str) -> Result<Address> {
        let (_, addr) = all_consuming(address::<VerboseError<&str>>)(s)
            .map_err(|e| anyhow!("{}", e))?;
        Ok(addr)
    }
}

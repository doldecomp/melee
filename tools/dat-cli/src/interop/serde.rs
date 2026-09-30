use serde::{Deserialize, Deserializer, Serialize, Serializer};

pub mod vec_range_as_tuples {
    use super::*;
    use std::range::RangeInclusive;

    pub fn serialize<T, S>(
        ranges: &[RangeInclusive<T>],
        serializer: S,
    ) -> Result<S::Ok, S::Error>
    where
        T: Copy,
        T: Serialize,
        S: Serializer,
    {
        let tuples: Vec<_> =
            ranges.iter().map(|r| (r.start, r.last)).collect();
        tuples.serialize(serializer)
    }

    pub fn deserialize<'de, T, D>(
        deserializer: D,
    ) -> Result<Vec<RangeInclusive<T>>, D::Error>
    where
        T: Deserialize<'de>,
        D: Deserializer<'de>,
    {
        let tuples: Vec<(T, T)> = Vec::deserialize(deserializer)?;
        Ok(tuples
            .into_iter()
            .map(|(start, last)| RangeInclusive { start, last })
            .collect())
    }
}

pub mod unix_path {
    use super::*;
    use typed_path::Utf8UnixPathBuf;

    pub fn serialize<S>(
        path: &Utf8UnixPathBuf,
        s: S,
    ) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        s.serialize_str(path.as_str())
    }

    pub fn deserialize<'de, D>(
        deserializer: D,
    ) -> Result<Utf8UnixPathBuf, D::Error>
    where
        D: Deserializer<'de>,
    {
        String::deserialize(deserializer).map(Utf8UnixPathBuf::from)
    }
}

pub mod unix_path_option {
    use super::*;
    use typed_path::Utf8UnixPathBuf;

    pub fn serialize<S>(
        path: &Option<Utf8UnixPathBuf>,
        s: S,
    ) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        if let Some(path) = path {
            s.serialize_str(path.as_str())
        } else {
            s.serialize_none()
        }
    }

    pub fn deserialize<'de, D>(
        deserializer: D,
    ) -> Result<Option<Utf8UnixPathBuf>, D::Error>
    where
        D: Deserializer<'de>,
    {
        Ok(Option::<String>::deserialize(deserializer)?
            .map(Utf8UnixPathBuf::from))
    }
}

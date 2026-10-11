//! Synthetic C readers use the production emitter, without game inputs.
use super::{
    emit,
    generator::{Generator, Kind, MemberRow, Place, ScriptRow, TypeRow},
};
use crate::cmd::project::Project;
use anyhow::{Context, Result, bail};
use melee_dat::{
    dwarf::{TypeGraph, canonical::Canonical, expr::Expr},
    symbols::SymbolFile,
};
use serde_json::Value;
use std::{collections::HashMap, fs, path::Path};

pub fn generate(out: &Path) -> Result<()> {
    fs::create_dir_all(out)?;
    for (name, data) in [
        (
            "unit",
            include_str!("../../../native/tests/schemas/unit.json"),
        ),
        (
            "raw_refs",
            include_str!("../../../native/tests/schemas/raw_refs.json"),
        ),
        (
            "array_refs",
            include_str!("../../../native/tests/schemas/array_refs.json"),
        ),
    ] {
        let input: Value = serde_json::from_str(data)?;
        let original = input["types"].as_array().context("fixture types")?;
        let mut groups = vec![("base".to_owned(), original.clone())];
        if let Some(variants) = input["variants"].as_object() {
            for (variant, overrides) in variants {
                let mut types = original.clone();
                for (key, fields) in
                    overrides.as_object().context("variant")?
                {
                    let ty = types
                        .iter_mut()
                        .find(|t| t["key"] == *key)
                        .context("variant type")?;
                    for (field, value) in
                        fields.as_object().context("type overrides")?
                    {
                        ty[field] = value.clone();
                    }
                }
                groups.push((variant.clone(), types));
            }
        }
        let graph = TypeGraph::default();
        let project = Project {
            canonical: Canonical::new(&graph),
            graph,
            base: Default::default(),
            include: vec![],
            macros: Default::default(),
            root_types: Default::default(),
            root_bindings: Default::default(),
            symbols: SymbolFile::parse("")?,
            symbol_types: Default::default(),
        };
        let mut generators = Vec::new();
        for (group, types) in groups {
            let keys: HashMap<&str, i32> = types
                .iter()
                .enumerate()
                .map(|(i, t)| {
                    Ok((t["key"].as_str().context("key")?, (i + 1) as i32))
                })
                .collect::<Result<_>>()?;
            let mut generator = Generator::new(&project);
            for t in &types {
                generator.types.push(row(t, &keys)?);
            }
            generators.push((group, generator));
        }
        let code = emit::fixture(&generators)?;
        fs::write(out.join(format!("{name}.h")), code)?;
    }
    Ok(())
}

fn row(t: &Value, keys: &HashMap<&str, i32>) -> Result<TypeRow> {
    let key = text(t, "key");
    let ty = |key: &str| -> Result<i32> {
        if key.is_empty() {
            Ok(0)
        } else {
            keys.get(key)
                .copied()
                .with_context(|| format!("unknown fixture type {key}"))
        }
    };
    let expr = |field| expression(t, field);
    let kind = match text(t, "kind") {
        "int" => Kind::Int,
        "float" => Kind::Float,
        "pointer" => Kind::Pointer,
        "struct" => Kind::Struct,
        "union" => Kind::Union,
        "array" => Kind::Array,
        "typedef" => Kind::Typedef,
        _ => bail!("fixture kind"),
    };
    let mut row = TypeRow {
        name: text(t, "name").into(),
        id: ty(key)? as u32,
        kind,
        size: number(t, "size"),
        native_size: text(t, "native_size").into(),
        target: ty(text(t, "target"))?,
        resolved: ty(t["resolved"].as_str().unwrap_or(key))?,
        count: number(t, "count"),
        raw: t["raw"] == true,
        blob: t["blob"] == true,
        is_signed: t["is_signed"] == true,
        has_pointers: t["has_pointers"] == true,
        has_extent: t["has_extent"] == true,
        unbounded: t["unbounded"] == true,
        terminator: expr("terminator")?,
        terminator_length: number(t, "terminator_length"),
        count_tag: expr("count_tag")?,
        type_tag: ty(text(t, "type_tag"))?,
        script: t["byte_script"]
            .as_str()
            .map(|s| Expr::parse(s).context("script").map(ScriptRow::Bytes))
            .transpose()?,
        ..Default::default()
    };
    if let Some(members) = t["members"].as_array() {
        for m in members {
            let place = if let Some(field) = m["field"].as_str() {
                if number(m, "bit_size") > 0 {
                    Place::Bits {
                        record: text(m, "record").into(),
                        field: field.into(),
                    }
                } else {
                    Place::Field {
                        record: text(m, "record").into(),
                        field: field.into(),
                    }
                }
            } else {
                Place::At {
                    offset: m["native_offset"].as_str().unwrap_or("0").into(),
                    size: m["native_size"].as_str().unwrap_or("0").into(),
                }
            };
            let mut binds = Vec::new();
            if let Some(values) = m["binds"].as_object() {
                for (name, value) in values {
                    binds.push((
                        name.clone(),
                        Expr::parse(value.as_str().context("binding")?)
                            .context("binding expression")?,
                    ));
                }
            }
            row.members.push(MemberRow {
                name: m["name"].as_str().map(str::to_owned),
                ty: ty(text(m, "type"))?,
                offset: m["offset"].as_u64(),
                bit_offset: number(m, "bit_offset"),
                bit_size: number(m, "bit_size"),
                extent: m["extent"] == true,
                place,
                count: expression(m, "count")?,
                terminator: expression(m, "terminator")?,
                terminator_length: number(m, "terminator_length"),
                cond: expression(m, "cond")?,
                type_tag: ty(text(m, "type_tag"))?,
                script: None,
                binds,
                annotations: vec![],
            });
        }
    }
    Ok(row)
}
fn text<'a>(v: &'a Value, key: &str) -> &'a str {
    v[key].as_str().unwrap_or("")
}
fn number(v: &Value, key: &str) -> u64 {
    v[key].as_u64().unwrap_or(0)
}
fn expression(v: &Value, key: &str) -> Result<Option<Expr>> {
    v[key]
        .as_str()
        .map(|s| Expr::parse(s).with_context(|| format!("fixture {key}: {s}")))
        .transpose()
}

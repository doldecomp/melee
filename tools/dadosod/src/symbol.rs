use std::{io::{Read, Seek}};
use std::collections::BTreeMap;
use serde::{Deserialize, Serialize};
use csv;

#[derive(Debug, Default, PartialEq, Eq, Clone, Serialize, Deserialize)]
pub struct Symbol {
    #[serde(alias = "localAddress")]
    #[serde(alias = "SectionAddress")]
    pub section_address: Option<u32>,
    
    #[serde(default)]
    #[serde(alias = "Size")]
    pub size: u32,
    
    #[serde(default)]
    #[serde(alias = "Alignment")]
    pub alignment: u32,
    
    #[serde(alias = "globalAddress")]
    #[serde(alias = "VirtualAddress")]
    pub virtual_address: u32,
    
    #[serde(alias = "Name")]
    pub name: String,
    
    #[serde(alias = "Parent")]
    pub parent: Option<String>,
    
    #[serde(alias = "translationUnit")]
    #[serde(alias = "TranslationUnit")]
    pub translation_unit: Option<String>,
}

impl Symbol {
    pub fn with_name(name: String, virtual_address: u32) -> Self {
        Symbol {
            virtual_address,
            name,
            ..Default::default()
        }
    }

    pub fn from_csv<R>(r: R) -> Result<BTreeMap<u32, Self>, Box<dyn std::error::Error>>
    where
        R: Read + Seek, 
    {
   
        let mut symbols: BTreeMap<u32, Self> = BTreeMap::new();
        let mut rdr = csv::ReaderBuilder::new().
            delimiter(b',').quote(b'"').escape(Some(b'\\')).trim(csv::Trim::All).from_reader(r);
        for result in rdr.deserialize() {
            let symbol: Symbol = result?;
            symbols.insert(symbol.virtual_address, symbol);
        }
        Ok(symbols)
    }
}
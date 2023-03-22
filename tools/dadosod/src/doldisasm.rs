use argh::FromArgs;
use dol::{Dol, DolSection, DolSectionType};
use std::collections::HashMap;
use std::io::{BufWriter, Write};
use std::{
    collections::BTreeMap,
    fs::{File, OpenOptions},
    path::{Path, PathBuf},
};

use crate::symbol::Symbol;
use crate::tracker::GPRTracker;
use crate::utils::{align, get_section_flags};

#[derive(Debug, PartialEq, FromArgs)]
#[argh(subcommand, name = "dol")]
/// disassembly operations for `.dol` Wii/GC executable file
pub struct DolCmd {
    /// path of the `.dol` Wii/GC executable file
    #[argh(positional)]
    dol_file_path: PathBuf,

    /// path to where every thing would be placed (assembly file, lfc, etc..)
    #[argh(option, short='o')]
    output_path: Option<PathBuf>,

    /// path of the map file
    #[argh(option, short = 'm')]
    map_file_path: Option<PathBuf>,

    /// write symbols in their translation unit, if specified
    #[argh(option, default = "true")]
    write_translation_unit: bool,

    /// detect function by calls (unreliable)
    #[argh(option, default = "false")]
    detect_functions: bool,
}

impl DolCmd {
    pub fn run(&self) -> Result<(), Box<dyn std::error::Error>> {
        let dol_file = File::open(&self.dol_file_path)?;
        let mut dol_file = Dol::read_from(&dol_file)?;

        // Try giving each section a name
        let section_name_map = calculate_section_names(&mut dol_file);
        assert_eq!(section_name_map.len(), dol_file.header.sections.len());

        let mut symbols_map = if let Some(map_file_path) = &self.map_file_path {
            let map_file = File::open(&map_file_path)?;
            print!("Reading Symbols .. ");
            let map = Symbol::from_csv(map_file)?;
            println!("{}", map.len());
            map
        } else {
            let mut map = BTreeMap::default();
            map.insert(
                dol_file.header.entry_point,
                Symbol::with_name("__start".into(), dol_file.header.entry_point),
            );
            map
        };

        println!("Sections:");
        for (si, section) in dol_file.header.sections.iter().enumerate() {
            let section_name = section_name_map.get(&si).unwrap();
            println!(
                "[{:2}] => {:<12} 0x{:08X} 0x{:08X} 0x{:08X} 0x{:08X}",
                si,
                section_name,
                section.offset,
                section.target,
                section.target + section.size,
                section.size
            );
        }

        // Analyse sections
        let mut tracker = GPRTracker::new(&mut symbols_map, self.detect_functions);

        for section in &dol_file.header.sections {
            let section_data = dol_file.section_data(section);

            if section.kind == DolSectionType::Text {
                tracker.analyze_text_section(&dol_file, &section_data, section.target);
            } else if section.kind == DolSectionType::Data {
                tracker.analyze_data_section(&dol_file, &section_data, section.target);
            }
        }

        let output_path = if let Some(path) = &self.output_path {
            path.clone()
        } else {
            let dol_full_path = std::fs::canonicalize(&self.dol_file_path)?;
            let parent = dol_full_path.parent().unwrap();
            parent.to_path_buf()
        };

        let asm_path = output_path.join("asm");
        std::fs::create_dir_all(&asm_path)?;

        let include_path = output_path.join("include");
        std::fs::create_dir_all(&include_path)?;

        {
            println!("\nWriting Macro File");
            let mut macro_file = create_file(&include_path.join("macros.s"))?;
            write_macro_file(&mut macro_file, &dol_file, &section_name_map, &tracker)?;
        }

        let grouped_symbols = if self.write_translation_unit {
            tracker.label_names.values().fold(
                HashMap::new(),
                |mut init: HashMap<String, Vec<&Symbol>>, ref item| {
                    if let Some(translation_unit) = &item.translation_unit {
                        if !translation_unit.is_empty() && item.size > 0 {
                            if let Some(entry) = init.get_mut(translation_unit) {
                                entry.push(item);
                            } else {
                                init.insert(translation_unit.clone(), vec![*item]);
                            }
                        }
                    }
                    init
                },
            )
        } else {
            HashMap::new()
        };

        let remove_symbols_data = self.write_translation_unit && grouped_symbols.len() > 0;

        if grouped_symbols.len() > 0 {
            println!("\nWriting Translation Units");
            for (translation_unit, symbols) in grouped_symbols {
                let mut full_tu_path = output_path.join(&translation_unit);
                full_tu_path.set_extension("s");

                std::fs::create_dir_all(full_tu_path.parent().unwrap())?;
                let mut tu_file = create_file(&full_tu_path)?;

                println!(" - {}", translation_unit);
                writeln!(tu_file, ".include \"macros.s\"\n")?;

                let mut last_section_index = -1i32;
                for symbol in symbols {
                    let section = dol_file.header.section_at(symbol.virtual_address).unwrap();

                    if section.kind == DolSectionType::Bss {
                        continue;
                    }

                    let si = dol_file
                        .header
                        .sections
                        .iter()
                        .position(|s| s.target == section.target)
                        .unwrap();

                    if last_section_index != si as i32 {
                        let section_flags = get_section_flags(section.kind);
                        let section_name = &section_name_map[&si];
                        writeln!(tu_file, ".section {}, {}", section_name, section_flags)?;
                    }

                    last_section_index = si as i32;

                    let data = dol_file.virtual_data_at(symbol.virtual_address, symbol.size)?;
                    match section.kind {
                        DolSectionType::Text => tracker.write_text_section(
                            &mut tu_file,
                            data,
                            symbol.virtual_address,
                            0,
                            false,
                        )?,
                        DolSectionType::Data => tracker.write_data_section(
                            &mut tu_file,
                            data,
                            symbol.virtual_address,
                            0,
                            false,
                        )?,
                        DolSectionType::Bss => unreachable!(),
                    }

                    writeln!(tu_file)?;
                }
            }
        }

        println!("\nWriting Sections Files");
        for (si, section) in dol_file.header.sections.iter().enumerate() {
            let section_name = &section_name_map[&si];
            let section_file_name = format!("{}.s", section_name.replace(".", ""));
            let section_file_path = asm_path.join(&section_file_name);
            let mut section_file = create_file(&section_file_path)?;
            let start = section.target;
            let size = section.size;
            let end = start + size;

            let section_flags = get_section_flags(section.kind);

            writeln!(section_file, ".include \"macros.s\"\n")?;
            writeln!(
                section_file,
                ".section {}, {}  # 0x{:08X} - 0x{:08X} ; 0x{:08X}\n",
                section_name, section_flags, start, end, size as u32
            )?;

            let section_data = dol_file.section_data(section);

            match section.kind {
                DolSectionType::Text => tracker.write_text_section(
                    &mut section_file,
                    &section_data,
                    start,
                    section.offset,
                    remove_symbols_data,
                )?,
                DolSectionType::Data => tracker.write_data_section(
                    &mut section_file,
                    &section_data,
                    start,
                    section.offset,
                    remove_symbols_data,
                )?,
                DolSectionType::Bss => tracker.write_bss_section(&mut section_file, size, start)?,
            }
        }

        {
            println!("\nWriting Linker Script");
            let mut linker_script_file = create_file(output_path.join("ldscript.lcf"))?;
            write_linker_script_file(&mut linker_script_file, &dol_file, &section_name_map)?;
        }

        println!("Finished");

        Ok(())
    }
}

const SPRS: [(&str, i32); 68] = [
    ("XER", 1),
    ("LR", 8),
    ("CTR", 9),
    ("DSISR", 18),
    ("DAR", 19),
    ("DEC", 22),
    ("SDR1", 25),
    ("SRR0", 26),
    ("SRR1", 27),
    ("SPRG0", 272),
    ("SPRG1", 273),
    ("SPRG2", 274),
    ("SPRG3", 275),
    ("EAR", 282),
    ("PVR", 287),
    ("IBAT0U", 528),
    ("IBAT0L", 529),
    ("IBAT1U", 530),
    ("IBAT1L", 531),
    ("IBAT2U", 532),
    ("IBAT2L", 533),
    ("IBAT3U", 534),
    ("IBAT3L", 535),
    ("DBAT0U", 536),
    ("DBAT0L", 537),
    ("DBAT1U", 538),
    ("DBAT1L", 539),
    ("DBAT2U", 540),
    ("DBAT2L", 541),
    ("DBAT3U", 542),
    ("DBAT3L", 543),
    ("GQR0", 912),
    ("GQR1", 913),
    ("GQR2", 914),
    ("GQR3", 915),
    ("GQR4", 916),
    ("GQR5", 917),
    ("GQR6", 918),
    ("GQR7", 919),
    ("HID2", 920),
    ("WPAR", 921),
    ("DMA_U", 922),
    ("DMA_L", 923),
    ("UMMCR0", 936),
    ("UPMC1", 937),
    ("UPMC2", 938),
    ("USIA", 939),
    ("UMMCR1", 940),
    ("UPMC3", 941),
    ("UPMC4", 942),
    ("USDA", 943),
    ("MMCR0", 952),
    ("PMC1", 953),
    ("PMC2", 954),
    ("SIA", 955),
    ("MMCR1", 956),
    ("PMC3", 957),
    ("PMC4", 958),
    ("SDA", 959),
    ("HID0", 1008),
    ("HID1", 1009),
    ("IABR", 1010),
    ("DABR", 1013),
    ("L2CR", 1017),
    ("ICTC", 1019),
    ("THRM1", 1020),
    ("THRM2", 1021),
    ("THRM3", 1022),
];

fn write_macro_file<W>(
    dst: &mut W,
    dol_file: &Dol,
    section_name_map: &BTreeMap<usize, String>,
    tracker: &GPRTracker,
) -> Result<(), Box<dyn std::error::Error>>
where
    W: Write,
{
    writeln!(dst, "/*")?;
    writeln!(dst, "Sections:")?;

    for (si, section) in dol_file.header.sections.iter().enumerate() {
        let section_name = section_name_map.get(&si).unwrap();
        write!(dst, "\t{:<12}", section_name)?;
        writeln!(
            dst,
            "0x{:08X}  0x{:08X}  0x{:08X}  0x{:08X}",
            section.offset,
            section.target,
            section.target + section.size,
            section.size
        )?;
    }

    writeln!(dst, "Entry Point: 0x{:08X}", dol_file.header.entry_point)?;
    writeln!(dst, "*/")?;

    // Write macros
    writeln!(dst, "\n# General Purpose Registers (GPRs)")?;
    for i in 0..32 {
        writeln!(dst, ".set r{}, {}", i, i)?;
    }

    writeln!(dst, "\n# Floating Point Registers (FPRs)")?;
    for i in 0..32 {
        writeln!(dst, ".set f{}, {}", i, i)?;
    }

    writeln!(dst, "\n# Graphics Quantization Registers (GQRs)")?;
    for i in 0..8 {
        writeln!(dst, ".set qr{}, {}", i, i)?;
    }

    writeln!(dst, "\n# Special Purpose Registers (SPRs)")?;
    for (name, i) in SPRS {
        writeln!(dst, ".set {}, {}", name, i)?;
    }

    if tracker.r13_addr != 0 {
        writeln!(dst, "\n# Small Data Area (read/write) Base")?;
        writeln!(dst, ".set _SDA_BASE_, 0x{:08X}", tracker.r13_addr)?;
    }
    if tracker.r2_addr != 0 {
        writeln!(dst, "\n# Small Data Area (read only) Base")?;
        writeln!(dst, ".set _SDA2_BASE_, 0x{:08X}", tracker.r2_addr)?;
    }

    writeln!(dst)?;

    Ok(())
}

fn write_linker_script_file<W>(
    dst: &mut W,
    dol_file: &Dol,
    section_name_map: &BTreeMap<usize, String>,
) -> Result<(), Box<dyn std::error::Error>>
where
    W: Write,
{
    writeln!(
        dst,
        "MEMORY\n{{\ntext : origin = 0x{:08X}\n}}\n",
        &dol_file.header.sections[0].target
    )?;
    writeln!(dst, "SECTIONS\n{{")?;
    writeln!(dst, "\tGROUP:\n\t{{")?;

    let mut last_section_end = dol_file.header.sections[0].target;
    for (si, section) in dol_file.header.sections.iter().enumerate() {
        let section_name = section_name_map.get(&si).unwrap();
        let section_align = if last_section_end == section.target {
            0x20
        } else if align(last_section_end, 0x80) == section.target {
            0x80
        } else if align(last_section_end, 0x40) == section.target {
            0x40
        } else {
            println!("Unknown alignment for `{}`", section_name);
            0x20
        };

        writeln!(
            dst,
            "\t\t{:<12} ALIGN({:#X}) : {{}}",
            section_name, section_align
        )?;
        last_section_end = section.target + section.size;
    }

    writeln!(dst, "\t\t{:<12} ALIGN({:#X}) : {{}}", ".stack", 0x100)?;
    writeln!(dst, "\t}} > text\n")?; // GROUP

    let last_section_name = section_name_map
        .get(&(dol_file.header.sections.len() - 1))
        .unwrap();
    let last_section_name_sanitized = last_section_name.replace(".", "_");

    writeln!(
        dst,
        "\t_stack_addr = (_f{} + SIZEOF({}) + 65536 + 0x7) & ~0x7;",
        last_section_name_sanitized, last_section_name
    )?;
    writeln!(
        dst,
        "\t_stack_end = _f{} + SIZEOF({});",
        last_section_name_sanitized, last_section_name
    )?;
    writeln!(dst, "\t_db_stack_addr = (_stack_addr + 0x2000);")?;
    writeln!(dst, "\t_db_stack_end = _stack_addr;")?;
    writeln!(dst, "\t__ArenaLo = (_db_stack_addr + 0x1f) & ~0x1f;")?;
    writeln!(dst, "\t__ArenaHi = 0x81700000;")?;

    writeln!(dst, "}}")?; // SECTIONS
    Ok(())
}

/// CodeWarrior/MetroWerks compiler emit a limited set of section so for
/// most game we can infer them. **THIS IS NOT EXPECTED TO BE PERFECT**
fn calculate_section_names(dol_file: &mut Dol) -> BTreeMap<usize, String> {
    let mut names_map: BTreeMap<usize, String> = Default::default();

    let sections = &mut dol_file.header.sections;

    // In any case, Use a dummy name for the text sections
    let mut bss_counter = 0usize;
    {
        let mut text_counter = 0usize;
        let mut data_counter = 0usize;
        for (si, section) in sections.iter().enumerate() {
            match section.kind {
                DolSectionType::Text => {
                    names_map.insert(si, format!(".text{}", text_counter));
                    text_counter += 1;
                }
                DolSectionType::Data => {
                    names_map.insert(si, format!(".data{}", data_counter));
                    data_counter += 1;
                }
                DolSectionType::Bss => {
                    assert_eq!(bss_counter, 0);
                    names_map.insert(si, ".bss".into());
                    bss_counter += 1;
                }
            }
        }
    }

    assert_eq!(bss_counter, 1);
    let bss_section_index = sections
        .iter()
        .position(|s| s.kind == DolSectionType::Bss)
        .unwrap();

    let section_after_bss_count = sections.iter().skip(bss_section_index + 1).count();

    if section_after_bss_count == 2 {
        // The Wii/GC SDK generate a little bit of content for the `.sdata` and `.sdata2` section
        // So, there should always be at least does two section

        // How are we calculating the `.sbss` and `.sbss2` section?
        // The CodeWarrior/Metrowerks compiler order the `.sbss` and `.sbss2` like so:
        //     .bss
        //     .sdata
        //     .sbss
        //     .sdata2
        //     .sbss2 (optional)
        // The things is that this section are unified into a singular section and that
        // unified section's size is calculated like so:
        //     unified_bss_size = last_bss_section_rom_end - bss_rom
        // With this information we can divide the dol's bss section back into his original form

        let sdata_section_index = bss_section_index + 1;
        let mut sdata2_section_index = bss_section_index + 2;
        let sdata_section = &sections[sdata_section_index];
        let sdata2_section = &sections[sdata2_section_index];

        let bss_section = &sections[bss_section_index];
        let bss_section_rom_end = bss_section.target + bss_section.size;
        let sdata2_rom_end = sdata2_section.target + sdata2_section.size;

        // Set the sdata section name
        names_map.insert(sdata_section_index, ".sdata".into());

        // Calculate sbss section
        let sdata_rom_end = sdata_section.target + sdata_section.size;
        if sdata2_section.target > sdata_rom_end {
            let sbss_size = sdata2_section.target - sdata_rom_end;

            // Insert .sbss section name
            names_map.insert(sdata2_section_index, ".sbss".into());

            // We are going to introduce a new section to the dol, so we have to give the sdata2 section a new index
            sdata2_section_index += 1;

            // Insert newly discover section
            let sbss_target = sdata_rom_end;
            sections.insert(
                sdata_section_index + 1,
                DolSection {
                    kind: DolSectionType::Bss,
                    index: 0,
                    offset: 0,
                    target: sbss_target,
                    size: sbss_size,
                },
            );
        }

        // Insert sdata2 section name
        names_map.insert(sdata2_section_index, ".sdata2".into());

        // Calculate sbss2 size
        if bss_section_rom_end > sdata2_rom_end {
            let sbss2_size = bss_section_rom_end - sdata2_rom_end;
            // Insert `.sbss2` section name
            names_map.insert(sdata2_section_index + 1, ".sbss2".into());

            // Insert newly discover section
            let sbss2_target = bss_section_rom_end - sbss2_size;
            sections.push(DolSection {
                kind: DolSectionType::Bss,
                index: 0,
                offset: 0,
                target: sbss2_target,
                size: sbss2_size,
            });
        }
    } else {
        println!(
            "WARNING! Unexpected number `{}` of section were found after the `.bss` section",
            section_after_bss_count
        );
    }

    // Set the correct size to the bss size
    if section_after_bss_count >= 1 {
        // Since the bss "section" given by the dol is simply the size of the range created by the
        // elf's bss section start address and the end address of the last bss (NOBITS) section,
        // we can calculate the real size, by subtracting the next section's start address and the bss
        // section target address

        let bss_section = &sections[bss_section_index];
        let section_after = &sections[bss_section_index + 1];
        let bss_size = section_after.target - bss_section.target;

        let bss_section = &mut sections[bss_section_index];
        bss_section.size = bss_size;
    }

    let mut last_text_section_index = 0;

    // How many text section? We are only expecting `.init`
    let text_section_count = sections
        .iter()
        .filter(|s| s.kind == DolSectionType::Text)
        .count();
    if text_section_count == 2 {
        let init_section_index = 0usize;

        // The CodeWarrior/MetroWerk compiler emit the text section like so:
        //     [0] .init (required)
        //     [1] .extab (optional)
        //     [2] .extabindex (optional)
        //     [3] .text (required)

        let text_section_index = if sections[init_section_index + 1].kind == DolSectionType::Text {
            init_section_index + 1
        } else {
            init_section_index + 3
        };

        last_text_section_index = text_section_index;

        let text_section = &sections[text_section_index];
        if text_section.kind == DolSectionType::Text {
            names_map.insert(init_section_index, ".init".into());
            names_map.insert(text_section_index, ".text".into());

            // How many section between the `.init` and `.text` section
            if text_section_index - init_section_index - 1 == 2 {
                // Make sure that the two section in-between are data section
                if sections
                    .iter()
                    .skip(init_section_index + 1)
                    .take(2)
                    .filter(|s| s.kind == DolSectionType::Data)
                    .count()
                    == 2
                {
                    // Mark them as `extab` and `extabindex`
                    // We have to add a `_`, because if manually linking those data section
                    // the linker would throw error because does section are suppose to be auto-generated
                    names_map.insert(init_section_index + 1, "extab_".into());
                    names_map.insert(init_section_index + 2, "extabindex_".into());
                } else {
                    println!("WARNING! Unknown section type was found between the two expected data section");
                }
            }
        } else {
            println!(
                "WARNING! Unknown Section ({:?}, {:#X}, 0x{:08X}, {:#X})",
                text_section.kind, text_section.offset, text_section.target, text_section.size
            );
        }
    } else {
        println!(
            "WARNING! Too many text section were found `{}`",
            text_section_count
        );
        for section in sections.iter().enumerate() {
            if section.1.kind == DolSectionType::Text {
                last_text_section_index = section.0;
            }
        }
    }

    // CodeWarrior/MetroWerks compiler emit the remaining .data section like so:
    //     .text (last_text_section_index)
    //     .ctors
    //     .dtors
    //     .file (only seen in ogws)
    //     .rodata
    //     .data
    //     .bss (bss_section_index)

    let data_section_count = bss_section_index - last_text_section_index - 1;
    if data_section_count == 5 {
        names_map.insert(last_text_section_index + 1, ".ctors".into());
        names_map.insert(last_text_section_index + 2, ".dtors".into());
        names_map.insert(last_text_section_index + 3, ".file".into());
        names_map.insert(last_text_section_index + 4, ".rodata".into());
        names_map.insert(last_text_section_index + 5, ".data".into());
    } else if data_section_count == 4 {
        names_map.insert(last_text_section_index + 1, ".ctors".into());
        names_map.insert(last_text_section_index + 2, ".dtors".into());
        names_map.insert(last_text_section_index + 3, ".rodata".into());
        names_map.insert(last_text_section_index + 4, ".data".into());
    } else {
        println!("WARNING! Unknown data section count `{}` were found between the `.text` and `.bss` section", data_section_count);
    }

    return names_map;
}

#[inline]
fn create_file<P>(path: P) -> std::io::Result<BufWriter<File>>
where
    P: AsRef<Path>,
{
    Ok(BufWriter::new(
        OpenOptions::new()
            .write(true)
            .truncate(true)
            .create(true)
            .open(&path)?,
    ))
}

use std::fmt::Write as FmtWrite;
use std::{
    collections::{BTreeMap, BTreeSet},
    io::Write as IoWrite,
};

use crate::symbol::Symbol;
use crate::utils::align;
use dol::{Dol, DolSectionType};
use ppc750cl::{self, formatter::FormattedIns, Argument, Ins, Opcode};

#[derive(Debug)]
pub enum LabelAddress {
    HA(u32),
    H(u32),
    L(u32),
    SDA21(u32),
    BRANCH(u32),
}

impl LabelAddress {
    pub fn get(&self) -> u32 {
        match self {
            LabelAddress::HA(v) => v,
            LabelAddress::H(v) => v,
            LabelAddress::L(v) => v,
            LabelAddress::SDA21(v) => v,
            LabelAddress::BRANCH(v) => v,
        }
        .clone()
    }

    pub fn get_addr_and_suffix(&self) -> (u32, &str) {
        match self {
            LabelAddress::HA(v) => (v.clone(), "ha"),
            LabelAddress::H(v) => (v.clone(), "h"),
            LabelAddress::L(v) => (v.clone(), "l"),
            LabelAddress::SDA21(v) => (v.clone(), "sda21"),
            LabelAddress::BRANCH(v) => (v.clone(), ""),
        }
    }
}

// General Purpose Register Tracker
#[derive(Debug)]
pub struct GPRTracker<'a> {
    pub r2_addr: u32,
    pub r13_addr: u32,

    // instruction's address -> label address
    pub ins_labels: BTreeMap<u32, LabelAddress>,

    // label address
    pub labels: BTreeSet<u32>,

    // section's block name
    pub label_names: &'a mut BTreeMap<u32, Symbol>,

    // attempt to detect function
    detect_functions: bool,
}

impl<'a> GPRTracker<'a> {
    pub fn new(
        symbols: &'a mut BTreeMap<u32, Symbol>,
        detect_functions: bool,
    ) -> Self {
        let mut data = Self {
            r2_addr: 0,
            r13_addr: 0,
            ins_labels: Default::default(),
            labels: Default::default(),
            detect_functions,
            label_names: symbols,
        };

        data.labels.extend(data.label_names.keys());

        data
    }

    fn add_label(&mut self, ins: u32, label: LabelAddress) {
        self.labels.insert(label.get());
        self.ins_labels.insert(ins, label);
    }

    pub fn analyze_text_section(
        &mut self,
        dol_file: &Dol,
        code: &[u8],
        code_address: u32,
    ) {
        // register -> value
        let mut registers = BTreeMap::<u32, u32>::new();
        // register -> `lis` instruction address
        let mut lis_address = BTreeMap::<u32, u32>::new();

        for ins in ppc750cl::disasm_iter(code, code_address) {
            self.track_ins_register(
                dol_file,
                &ins,
                &mut registers,
                &mut lis_address,
            );
        }
    }

    fn track_ins_register(
        &mut self,
        dol_file: &Dol,
        ins: &Ins,
        registers: &mut BTreeMap<u32, u32>,
        lis_address: &mut BTreeMap<u32, u32>,
    ) {
        // Detect Branches
        if matches!(ins.op, Opcode::B | Opcode::Bc) {
            let branch_dest = ins.branch_dest().unwrap();

            if is_addr_in_section(dol_file, branch_dest.clone()) {
                // Since at least is a branch into a known section treat it as a label
                self.add_label(ins.addr, LabelAddress::BRANCH(branch_dest));

                if !is_label_addr_in_src_section(dol_file, branch_dest, ins.addr)
                    // if is not a conditional branch, treat it as a function
                    || (self.detect_functions && (ins.op == Opcode::B || ins.field_BO() == 20))
                {
                    self.label_names.insert(
                        branch_dest,
                        Symbol::with_name(
                            format!("func_{:08X}", branch_dest),
                            branch_dest,
                        ),
                    );
                }
            }
        } else if ins.op == Opcode::Addis && ins.field_rA() == 0 {
            // lis rD, uimm
            let r_d = ins.field_rD() as u32;
            registers.insert(r_d, (ins.field_uimm() << 16) as u32);
            lis_address.insert(r_d, ins.addr);
        } else if self.is_low_addi(ins, registers)
            || self.is_low_ori(ins, registers)
            || (is_load_store(ins)
                && registers.contains_key(&(ins.field_rA() as u32)))
        {
            // Detect split load (low part)
            // addi rD, rA, simm
            // ori rA, rS, uimm
            // lXX/sXX rD, offset, rA

            let mut is_ori = false;
            let mut is_addi = false;
            let hi_load_reg = if ins.op == Opcode::Addi {
                is_addi = true;
                ins.field_rA() as u32
            } else if ins.op == Opcode::Ori {
                is_ori = true;
                ins.field_rS() as u32
            } else {
                ins.field_rA() as u32
            };

            let &hi_load = registers.get(&hi_load_reg).unwrap();
            let target_address = combine_split_load_value(hi_load, ins);

            // Give the `lis` instruction a label for his offset
            if let Some(entry) = lis_address.remove_entry(&hi_load_reg) {
                if target_address >= 0x80_00_00_00 {
                    self.ins_labels
                        .insert(ins.addr, LabelAddress::L(target_address));

                    let target_address = if is_ori {
                        LabelAddress::H(target_address)
                    } else {
                        LabelAddress::HA(target_address)
                    };
                    self.ins_labels.insert(entry.1, target_address);
                }
            }

            if is_addr_in_section(dol_file, target_address) {
                self.labels.insert(target_address);

                if !self.label_names.contains_key(&target_address)
                    && !is_label_addr_in_src_section(
                        dol_file,
                        target_address,
                        ins.addr,
                    )
                {
                    self.label_names.insert(
                        target_address.clone(),
                        Symbol::with_name(
                            self.get_label_for(target_address.clone()),
                            target_address.clone(),
                        ),
                    );
                }
            }

            if is_addi {
                registers.remove_entry(&(ins.field_rD() as u32));
            } else if is_ori {
                registers.remove_entry(&(ins.field_rA() as u32));
            }

            // detect r2/r13 initialization
            if is_ori && ins.field_rA() == ins.field_rS() {
                if self.r2_addr == 0 && ins.field_rA() == 2 {
                    self.r2_addr = target_address;
                } else if self.r13_addr == 0 && ins.field_rA() == 13 {
                    self.r13_addr = target_address;
                }
            }
        } else if !is_store_insn(ins) && !is_storef_insn(ins) {
            // Remove record if register is overwritten
            let simplified = ins.clone().simplified();
            if simplified.args.len() >= 1 {
                if let Argument::GPR(r) = &simplified.args[0] {
                    registers.remove(&(r.0 as u32));
                }
            }
        }

        if ins.op == Opcode::Addi {
            let base_address = if ins.field_rA() == 13 && self.r13_addr != 0 {
                self.r13_addr
            } else if ins.field_rA() == 2 && self.r2_addr != 0 {
                self.r2_addr
            } else {
                return;
            };

            let offset = ins.field_simm() as i32;
            let target_address = if offset >= 0 {
                base_address.wrapping_add(offset as u32)
            } else {
                base_address.wrapping_sub(offset.unsigned_abs())
            };

            if is_addr_in_section(dol_file, target_address) {
                self.add_label(ins.addr, LabelAddress::SDA21(target_address));
            }
        } else if is_load_store(ins) {
            let rdest = ins.field_rA() as u32;
            let base_address = if rdest == 13 && self.r13_addr != 0 {
                self.r13_addr
            } else if rdest == 2 && self.r2_addr != 0 {
                self.r2_addr
            } else {
                return;
            };

            let offset = ins.field_offset();
            let target_address = if offset >= 0 {
                base_address.wrapping_add(offset as u32)
            } else {
                base_address.wrapping_sub(offset.unsigned_abs() as u32)
            };

            if is_addr_in_section(dol_file, target_address) {
                self.add_label(ins.addr, LabelAddress::SDA21(target_address));
            }
        }
    }

    pub fn analyze_data_section(
        &mut self,
        dol_file: &Dol,
        data: &[u8],
        data_address: u32,
    ) {
        let data_address_end = data_address + data.len() as u32;
        let mut section_labels =
            SectionLabels::from(data_address, data_address_end, &self.labels);

        let mut offset = 0u32;
        while (offset as usize) < data.len() {
            let label_address = data_address + offset;
            let label_size = section_labels.get_label_size(label_address);

            // We don't care for small label
            if label_size < 4 {
                offset += label_size;
                continue;
            }

            let mut label_pos = 0u32;
            let label_data =
                &data[offset as usize..(offset + label_size) as usize];
            while label_pos < label_size {
                let unaligned = align(data_address + offset + label_pos, 4)
                    - (data_address + offset + label_pos);

                if unaligned > 0 {
                    label_pos += unaligned;
                    continue;
                }

                let c_str = read_c_string(label_data, label_pos as usize);
                if c_str.len() > 3 {
                    label_pos += (c_str.len() as u32) + 1;
                    continue;
                }

                if label_pos + 4 > label_size {
                    break;
                }

                let word = read_u32(label_data, label_pos as usize);
                if is_addr_in_section(dol_file, word) {
                    self.labels.insert(word);

                    if !self.label_names.contains_key(&word)
                        && !is_label_addr_in_src_section(
                            dol_file,
                            word,
                            data_address + offset + label_pos,
                        )
                    {
                        self.label_names.insert(
                            word,
                            Symbol::with_name(self.get_label_for(word), word),
                        );
                    }
                }

                label_pos += 4;
            }
            offset += label_size;
        }
    }

    pub fn write_text_section<W>(
        &self,
        dst: &mut W,
        code: &[u8],
        code_address: u32,
        file_offset: u32,
        remove_symbols_code: bool,
    ) -> Result<(), Box<dyn std::error::Error>>
    where
        W: IoWrite,
    {
        let code_symbols = if remove_symbols_code {
            self.label_names
                .values()
                .filter(|s| {
                    s.size > 0
                        && s.virtual_address >= code_address
                        && s.virtual_address + s.size
                            < code_address + code.len() as u32
                })
                .collect()
        } else {
            Vec::default()
        };

        let get_symbol = |addr: u32| {
            code_symbols.iter().find(|s| {
                addr >= s.virtual_address && addr < s.virtual_address + s.size
            })
        };

        let mut skip_count = 0u32;
        for ins in ppc750cl::disasm_iter(code, code_address) {
            if skip_count > 0 {
                skip_count -= 1;
                continue;
            }

            if let Some(code_symbol) = get_symbol(ins.addr) {
                skip_count = (code_symbol.size / 4) - 1;
                continue;
            }

            let ins_addr = ins.addr;
            let ins_offset = ins_addr - code_address;
            let ins_bytes = vec![
                code[(ins_offset + 0) as usize],
                code[(ins_offset + 1) as usize],
                code[(ins_offset + 2) as usize],
                code[(ins_offset + 3) as usize],
            ];

            if self.labels.contains(&ins_addr) {
                if self.label_names.contains_key(&ins_addr) {
                    writeln!(
                        dst,
                        "\n.global {}",
                        self.get_label_for(ins_addr)
                    )?;
                }

                writeln!(dst, "{}:", self.get_label_for(ins_addr))?;
            }

            let prefix_comment = format!(
                "/* {:08X} {:08X}  {:02X} {:02X} {:02X} {:02X} */",
                ins_addr,
                file_offset + ins_offset,
                ins_bytes[0],
                ins_bytes[1],
                ins_bytes[2],
                ins_bytes[3]
            );

            let ins_str = if let Ok(s) = self.format_instruction(&ins) {
                s
            } else {
                format!("{}", FormattedIns(ins.clone()))
            };

            writeln!(dst, "{}\t{}", prefix_comment, ins_str)?;
        }

        Ok(())
    }

    fn format_instruction(
        &self,
        ins: &Ins,
    ) -> Result<String, Box<dyn std::error::Error>> {
        if ins.op == Opcode::Illegal {
            return Ok(if ins.code == 0 {
                // Most likely alignment bytes
                format!(".4byte 0x{:08X}", ins.code)
            } else {
                format!(".4byte 0x{:08X}  /* <illegal> */", ins.code)
            });
        }

        // Special Case - Assembler doesn't handle the instruction mnemonic
        if ins.op == Opcode::Lmw && ins.field_rD() == 0 {
            return Ok(format!(
                ".4byte 0x{:08X}  /* illegal {} */",
                ins.code,
                FormattedIns(ins.clone())
            ));
        }

        // Special Case - Most likely data as instruction
        if ins.op == Opcode::Bc && !ins.field_AA() {
            if ins.field_BD() == 0 {
                return Ok(format!(
                    ".4byte 0x{:08X}  /* {} */",
                    ins.code,
                    FormattedIns(ins.clone())
                ));
            }
        }

        let simple = ins.clone().simplified();
        let mut f = String::new();

        write!(f, "{}{}", simple.mnemonic, simple.suffix)?;
        let mut writing_offset = false;
        for (i, arg) in simple.args.iter().enumerate() {
            if i == 0 {
                write!(f, " ")?;
            }
            if i > 0 && !writing_offset {
                write!(f, ", ")?;
            }

            if let Argument::Offset(val) = arg {
                if let Some(label) = self.ins_labels.get(&ins.addr) {
                    let (addr, suffix) = label.get_addr_and_suffix();
                    write!(f, "{}@{}(", self.get_label_for(addr), suffix)?;
                } else {
                    write!(f, "{}(", val)?;
                }
                writing_offset = true;
                continue;
            } else if let Argument::Simm(_) = arg {
                if let Some(label) = self.ins_labels.get(&ins.addr) {
                    let (addr, suffix) = label.get_addr_and_suffix();
                    write!(f, "{}@{}", self.get_label_for(addr), suffix)?;
                } else {
                    write!(f, "{}", arg)?;
                }
            } else if let Argument::Uimm(_) = arg {
                if let Some(label) = self.ins_labels.get(&ins.addr) {
                    let (addr, suffix) = label.get_addr_and_suffix();
                    write!(f, "{}@{}", self.get_label_for(addr), suffix)?;
                } else {
                    write!(f, "{}", arg)?;
                }
            } else if let Argument::BranchDest(_) = arg {
                if let Some(label) = self.ins_labels.get(&ins.addr) {
                    write!(f, "{}", self.get_label_for(label.get()))?;
                } else {
                    write!(f, "{}", arg)?;
                }
            } else {
                write!(f, "{}", arg)?;
            }

            if writing_offset {
                write!(f, ")")?;
                writing_offset = false;
            }
        }

        Ok(f)
    }

    fn get_label_for(&self, addr: u32) -> String {
        if self.labels.contains(&addr) {
            if let Some(lbl) = self.label_names.get(&addr) {
                lbl.name.clone()
            } else {
                format!("lbl_{:08X}", addr)
            }
        } else {
            format!("0x{:08X}", addr)
        }
    }

    pub fn write_data_section<W>(
        &self,
        dst: &mut W,
        data: &[u8],
        data_address: u32,
        file_offset: u32,
        remove_symbols_data: bool,
    ) -> Result<(), Box<dyn std::error::Error>>
    where
        W: IoWrite,
    {
        let data_address_end = data_address + data.len() as u32;

        let mut section_labels =
            SectionLabels::from(data_address, data_address_end, &self.labels);

        let data_symbols = if remove_symbols_data {
            self.label_names
                .values()
                .filter(|s| {
                    s.size > 0
                        && s.virtual_address >= data_address
                        && s.virtual_address + s.size < data_address_end
                })
                .collect()
        } else {
            Vec::default()
        };

        let get_symbol = |addr: u32| {
            data_symbols.iter().find(|s| {
                addr >= s.virtual_address && addr < s.virtual_address + s.size
            })
        };

        let mut offset = 0u32;
        while (offset as usize) < data.len() {
            let label_file_offset = file_offset + offset;
            let label_address = offset + data_address;

            if let Some(code_symbol) = get_symbol(label_address) {
                offset += code_symbol.size;

                if let Some(next_label_pos) = section_labels
                    .labels
                    .iter()
                    .skip(section_labels.label_access_index)
                    .position(|l| *l >= (offset + data_address))
                {
                    section_labels.label_access_index += next_label_pos;
                } else {
                    section_labels.label_access_index =
                        section_labels.labels.len()
                }

                continue;
            }

            if self.labels.contains(&label_address) {
                // The address have a label
                writeln!(
                    dst,
                    "\n.global {0}\n{0}:",
                    self.get_label_for(label_address)
                )?;
            }

            let label_size = section_labels.get_label_size(label_address);
            assert!(label_address + label_size <= data_address_end);

            writeln!(dst, "\n\t# ROM: {:#X}", label_file_offset)?;

            if label_size == 1 {
                writeln!(dst, "\t.byte 0x{:02X}", data[offset as usize])?;
            } else if label_size == 2 {
                writeln!(
                    dst,
                    "\t.2byte 0x{:04X}",
                    read_u16(data, offset as usize)
                )?;
            } else {
                // size > 2
                let mut label_pos = 0u32;
                let label_data =
                    &data[offset as usize..(offset + label_size) as usize];
                while label_pos < label_size {
                    let section_off = label_address + label_pos;
                    let diff = align(section_off, 4) - section_off;
                    if diff > 0 {
                        let pad_end =
                            std::cmp::min(label_pos + diff, label_size);
                        let pad =
                            &label_data[label_pos as usize..pad_end as usize];

                        if pad.len() as u32 == diff
                            && pad.iter().all(|&v| v == 0x0u8)
                        {
                            writeln!(dst, "\t.balign 4")?;
                        } else {
                            writeln!(
                                dst,
                                "\t.byte {}",
                                hex_string(pad).unwrap()
                            )?;
                        }

                        label_pos += pad.len() as u32;
                        continue;
                    }

                    let strv = read_c_string(label_data, label_pos as usize);
                    if strv.len() > 3 {
                        label_pos += (strv.len() as u32) + 1;
                        writeln!(dst, "\t.asciz \"{}\"", escape_string(strv))?;
                        continue;
                    }

                    if label_pos + 4 <= label_size {
                        let word = read_u32(label_data, label_pos as usize);
                        label_pos += 4;

                        if word == 0 {
                            writeln!(dst, "\t.4byte 0")?;
                        } else {
                            writeln!(
                                dst,
                                "\t.4byte {}",
                                self.get_label_for(word)
                            )?;
                        }
                    } else {
                        let end_slice = &label_data[label_pos as usize..];
                        if end_slice.len() > 0 {
                            writeln!(
                                dst,
                                "\t.byte {}",
                                hex_string(end_slice).unwrap()
                            )?;
                            label_pos += end_slice.len() as u32;
                            assert_eq!(label_pos, label_size);
                        }
                    }
                }
            }

            offset += label_size;
        }

        assert_eq!(offset, data.len() as u32);
        Ok(())
    }

    pub fn write_bss_section<W>(
        &self,
        dst: &mut W,
        section_size: u32,
        data_address: u32,
    ) -> Result<(), Box<dyn std::error::Error>>
    where
        W: IoWrite,
    {
        let data_address_end = data_address + section_size;
        let mut section_labels =
            SectionLabels::from(data_address, data_address_end, &self.labels);

        let mut offset = 0u32;
        while offset < section_size {
            let label_address = offset + data_address;
            if self.labels.contains(&label_address) {
                // The address have a label
                writeln!(
                    dst,
                    "\n.global {0}\n{0}:",
                    self.get_label_for(label_address)
                )?;
            }

            let size = section_labels.get_label_size(label_address);
            assert!(label_address + size <= data_address_end);

            writeln!(dst, "\t.skip {:#X}", size)?;
            offset += size;
        }

        assert_eq!(offset, section_size);

        Ok(())
    }

    #[inline]
    fn is_low_addi(&self, ins: &Ins, registers: &BTreeMap<u32, u32>) -> bool {
        let field_r_a = ins.field_rA() as u32;
        return ins.op == Opcode::Addi
            && field_r_a != 0
            && registers.contains_key(&field_r_a);
    }

    #[inline]
    fn is_low_ori(&self, ins: &Ins, registers: &BTreeMap<u32, u32>) -> bool {
        let r_a = ins.field_rA() as u32;
        let r_s = ins.field_rS() as u32;
        return ins.op == Opcode::Ori
            && !(r_a == 0 && r_s == 0 && ins.field_uimm() == 0)
            && registers.contains_key(&r_s);
    }
}

struct SectionLabels {
    // Section End Address
    section_end: u32,
    // label address
    labels: Vec<u32>,
    // Keep track of the last accessed label
    label_access_index: usize,
}

impl SectionLabels {
    pub fn from(
        section_start: u32,
        section_end: u32,
        labels: &BTreeSet<u32>,
    ) -> Self {
        Self {
            section_end,
            labels: labels
                .iter()
                .filter(|&&l| l >= section_start && l < section_end)
                .cloned()
                .collect(),
            label_access_index: 0,
        }
    }

    /// @return u32 - size of the current label
    pub fn get_label_size(&mut self, label_address: u32) -> u32 {
        if let Some(&nearest_label) = self.labels.get(self.label_access_index)
        {
            if label_address == nearest_label {
                // Find the next nearest label so we can, calculate the size
                self.label_access_index += 1;

                if let Some(&next_nearest_label) =
                    self.labels.get(self.label_access_index)
                {
                    assert!(next_nearest_label > label_address);
                    // Gap between labels
                    next_nearest_label - label_address
                } else {
                    // Gap between the label and the end of the section
                    self.section_end - label_address
                }
            } else {
                // The address did not had a label, calculate the gap between labels
                nearest_label - label_address
            }
        } else {
            self.section_end - label_address
        }
    }
}

#[inline]
fn read_u32(data: &[u8], pos: usize) -> u32 {
    return ((data[pos + 0] as u32) << 24)
        | ((data[pos + 1] as u32) << 16)
        | ((data[pos + 2] as u32) << 8)
        | ((data[pos + 3] as u32) << 0);
}

#[inline]
fn read_u16(data: &[u8], pos: usize) -> u16 {
    return ((data[pos + 0] as u16) << 8) | ((data[pos + 1] as u16) << 0);
}

fn is_ascii(code: u8) -> bool {
    if code >= 0x20u8 && code <= 0x7Eu8 {
        return true;
    }

    // Tab, Newline
    if code == 0x09 || code == 0x0A {
        return true;
    }

    return false;
}

fn read_c_string(data: &[u8], mut pos: usize) -> String {
    let mut retval = String::with_capacity(3);

    while pos < data.len() {
        let c = data[pos];
        if !is_ascii(c) {
            break;
        }

        retval.push(c as char);
        pos += 1;
    }

    return if pos < data.len() && data[pos] == 0x0u8 {
        retval
    } else {
        String::default()
    };
}

fn hex_string(data: &[u8]) -> Result<String, Box<dyn std::error::Error>> {
    let mut retval = String::with_capacity(data.len() * 5);

    for pos in 0..data.len() {
        if pos > 0 {
            write!(retval, ", 0x{:02X}", data[pos])?;
        } else {
            write!(retval, "0x{:02X}", data[pos])?;
        }
    }

    Ok(retval)
}

fn escape_string(value: String) -> String {
    let mut retval = String::with_capacity(value.len());

    for c in value.chars() {
        match c {
            '\\' => retval.push_str("\\\\"),
            '"' => retval.push_str("\\\""),
            '\n' => retval.push_str("\\n"),
            '\t' => retval.push_str("\\t"),
            _ => retval.push(c),
        }
    }

    retval
}

pub fn is_addr_in_section(dol: &Dol, addr: u32) -> bool {
    // Check if it's inside on of the sections
    for section in &dol.header.sections {
        if section.kind == DolSectionType::Text && (addr & 3) != 0 {
            continue;
        }

        if addr >= section.target && addr < section.target + section.size {
            return true;
        }
    }

    return false;
}

/// Computes the combined value from a lis, addi/ori instruction pair
pub fn combine_split_load_value(mut hi_addr: u32, lo_load: &Ins) -> u32 {
    if lo_load.op == Opcode::Ori {
        hi_addr |= lo_load.field_uimm() as u32;
    } else if lo_load.op == Opcode::Addi {
        let simm = lo_load.field_simm() as i32;
        if simm >= 0 {
            hi_addr = hi_addr.wrapping_add(simm as u32);
        } else {
            hi_addr = hi_addr.wrapping_sub(simm.unsigned_abs());
        }
    } else {
        assert!(is_load_store(lo_load));
        let offset = lo_load.field_offset() as i32;
        if offset >= 0 {
            hi_addr = hi_addr.wrapping_add(offset as u32);
        } else {
            hi_addr = hi_addr.wrapping_sub(offset.unsigned_abs());
        }
    }
    return hi_addr;
}

// Check if label address belong to the same section than the instruction
pub fn is_label_addr_in_src_section(
    dol: &Dol,
    label_addr: u32,
    src_addr: u32,
) -> bool {
    for section in &dol.header.sections {
        let start = section.target;
        let size = section.size;
        if size == 0 {
            continue;
        }

        let end = start + size;
        if label_addr >= start && label_addr < end {
            return src_addr >= start && src_addr < end;
        }
    }

    // We don't check the bss section, because even if the label belong to it, the ins cannot
    return false;
}

fn is_load_insn(ins: &Ins) -> bool {
    matches!(
        ins.op,
        Opcode::Lbz
            | Opcode::Lbzu
            | Opcode::Lha
            | Opcode::Lhau
            | Opcode::Lhz
            | Opcode::Lhzu
            | Opcode::Lmw
            | Opcode::Lwz
            | Opcode::Lwzu
    )
}

fn is_loadf_insn(ins: &Ins) -> bool {
    matches!(
        ins.op,
        Opcode::Lfd | Opcode::Lfdu | Opcode::Lfs | Opcode::Lfsu
    )
}

fn is_store_insn(ins: &Ins) -> bool {
    matches!(
        ins.op,
        Opcode::Stb
            | Opcode::Stbu
            | Opcode::Sth
            | Opcode::Sthu
            | Opcode::Stmw
            | Opcode::Stw
            | Opcode::Stwu
    )
}

fn is_storef_insn(ins: &Ins) -> bool {
    matches!(
        ins.op,
        Opcode::Stfd | Opcode::Stfdu | Opcode::Stfs | Opcode::Stfsu
    )
}

fn is_load_store(ins: &Ins) -> bool {
    return is_load_insn(&ins)
        || is_loadf_insn(&ins)
        || is_store_insn(&ins)
        || is_storef_insn(&ins);
}

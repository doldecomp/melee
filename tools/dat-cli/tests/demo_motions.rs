//! Exercise the CLI with original-format DOL tables and nested DAT archives.

use std::{
    fs,
    path::PathBuf,
    process::{Command, Output},
    sync::atomic::{AtomicUsize, Ordering},
};

fn word(bytes: &mut [u8], at: usize, value: u32) {
    bytes[at..at + 4].copy_from_slice(&value.to_be_bytes());
}

fn read_word(bytes: &[u8], at: usize) -> u32 {
    u32::from_be_bytes(bytes[at..at + 4].try_into().unwrap())
}

fn string(bytes: &mut Vec<u8>, text: &str) -> u32 {
    let at = bytes.len() as u32;
    bytes.extend_from_slice(text.as_bytes());
    bytes.push(0);
    at
}

fn archive(data: &[u8], relocs: &[u32], publics: &[(&str, u32)]) -> Vec<u8> {
    let mut bytes = vec![0; 32];
    bytes.extend_from_slice(data);
    for &at in relocs {
        bytes.extend_from_slice(&at.to_be_bytes());
    }
    let mut names = Vec::new();
    for &(name, at) in publics {
        bytes.extend_from_slice(&at.to_be_bytes());
        bytes.extend_from_slice(&string(&mut names, name).to_be_bytes());
    }
    bytes.extend_from_slice(&names);
    let size = bytes.len() as u32;
    word(&mut bytes, 0, size);
    word(&mut bytes, 4, data.len() as u32);
    word(&mut bytes, 8, relocs.len() as u32);
    word(&mut bytes, 12, publics.len() as u32);
    bytes
}

#[derive(Clone, Copy)]
struct Motion {
    offset: u32,
    size: u32,
    name: &'static str,
}

fn bank() -> (Vec<u8>, Motion, Motion) {
    let first = archive(&[0; 4], &[], &[("anim", 0)]);
    let unused = archive(&[0; 4], &[], &[("unused", 0)]);
    let last = archive(&[0; 4], &[], &[("last", 0)]);
    let mut bytes = first.clone();
    bytes.resize(bytes.len().next_multiple_of(32), 0xA5);
    bytes.extend_from_slice(&unused);
    bytes.resize(bytes.len().next_multiple_of(32), 0x5A);
    let offset = bytes.len() as u32;
    bytes.extend_from_slice(&last);
    (
        bytes,
        Motion {
            offset: 0,
            size: first.len() as u32,
            name: "anim",
        },
        Motion {
            offset,
            size: last.len() as u32,
            name: "last",
        },
    )
}

fn fighter(normal: Motion, demo: &[Motion]) -> Vec<u8> {
    let mut data = vec![0; 48 + demo.len() * 24];
    word(&mut data, 0xC, 24);
    word(&mut data, 0x14, 48);
    let mut relocs = vec![0xC, 0x14];
    for (i, motion) in std::iter::once(&normal).chain(demo).enumerate() {
        let at = 24 + i * 24;
        word(&mut data, at + 4, motion.offset);
        word(&mut data, at + 8, motion.size);
        if motion.size != 0 {
            let name = string(&mut data, motion.name);
            word(&mut data, at, name);
            relocs.push(at as u32);
        }
    }
    archive(&data, &relocs, &[("ftData", 0)])
}

struct Dol {
    data: Vec<u8>,
    symbols: String,
}

impl Dol {
    const BASE: u32 = 0x80001000;

    fn string(&mut self, text: &str) -> u32 {
        Self::BASE + string(&mut self.data, text)
    }

    fn table(&mut self, name: &str, words: &[u32]) -> u32 {
        self.data.resize(self.data.len().next_multiple_of(4), 0);
        let address = Self::BASE + self.data.len() as u32;
        for word in words {
            self.data.extend_from_slice(&word.to_be_bytes());
        }
        self.symbols.push_str(&format!(
            "{name} = .data:{address:#X}; // size:{}\n",
            words.len() * 4
        ));
        address
    }

    fn bytes(&self) -> Vec<u8> {
        let mut bytes = vec![0; 0x100];
        word(&mut bytes, 0, 0x100);
        word(&mut bytes, 0x48, Self::BASE);
        word(&mut bytes, 0x90, self.data.len() as u32);
        bytes.extend_from_slice(&self.data);
        bytes
    }
}

struct Fixture {
    root: PathBuf,
    copy_payload: usize,
}

impl Fixture {
    fn new() -> Self {
        static NEXT: AtomicUsize = AtomicUsize::new(0);
        let root = std::env::temp_dir().join(format!(
            "melee-dat-demo-{}-{}",
            std::process::id(),
            NEXT.fetch_add(1, Ordering::Relaxed)
        ));
        fs::create_dir(&root).unwrap();
        let (bank, first, last) = bank();
        fs::write(root.join("Normal.dat"), &bank).unwrap();
        let other = archive(&[0; 4], &[], &[("other", 0)]);
        // Zero-size entries need neither a valid offset nor a relocated name.
        let empty = Motion {
            offset: u32::MAX,
            size: 0,
            name: "",
        };
        let mut demo = vec![empty; 18];
        demo[0] = first;
        demo[1] = first; // repeated reference
        demo[10] = last;
        demo[12] = first;
        demo[13] = last;
        demo[14] = first;
        demo[15] = last; // Kirby's null name slot still has a motion
        demo[17] = Motion {
            offset: 0,
            size: other.len() as u32,
            name: "other",
        };
        fs::write(root.join("PlA.dat"), fighter(first, &demo)).unwrap();
        let mut shared = vec![empty; 14];
        shared[13] = last;
        fs::write(root.join("PlB.dat"), fighter(first, &shared)).unwrap();

        let mut data = vec![0x7F; 12];
        let mut publics = Vec::new();
        for name in ["result", "intro", "ending", "wait", "movieA", "movieB"] {
            publics.push((name, data.len() as u32));
            data.extend_from_slice(if name == "movieB" {
                &other
            } else {
                &bank
            });
        }
        publics.push(("trailer", data.len() as u32));
        data.extend_from_slice(&[0; 4]);
        fs::write(root.join("Demo.dat"), archive(&data, &[], &publics))
            .unwrap();
        // Check every definition of the same symbol, including a packed
        // outer archive and a nonzero offset within its data.
        let mut copy = archive(&[0; 4], &[], &[("unrelated", 0)]);
        copy.resize(copy.len().next_multiple_of(32), 0xA5);
        let copy_payload = copy.len() + 32 + 16;
        let mut data = vec![0; 16];
        data.extend_from_slice(&bank);
        copy.extend_from_slice(&archive(&data, &[], &[("intro", 16)]));
        fs::write(root.join("IntroCopy.dat"), copy).unwrap();

        let mut dol = Dol {
            data: Vec::new(),
            symbols: String::new(),
        };
        let a = dol.string("PlA.dat");
        let b = dol.string("PlB.dat");
        let root_name = dol.string("ftData");
        let normal = dol.string("Normal.dat");
        let names: Vec<_> =
            ["result", "intro", "ending", "wait", "movieA", "movieB"]
                .map(|name| dol.string(name))
                .into();
        let common = dol.table("common", &names[..4]);
        let shared = dol.table("shared", &[0, 0, 0, names[3]]);
        dol.table("ftData_Table_Unk0", &[0, 1, 0, 1]);
        dol.table("ftData_803C1F40", &[a, root_name, b, root_name]);
        dol.table("ftData_803C23E4", &[normal, normal]);
        dol.table("ftData_UnkIntPairs", &[0, 18, 0, 14]);
        dol.table("ftData_803C2468", &[common, shared]);
        dol.table("ftData_803C24EC", &[0x80000104, 0]);
        dol.table("ftKb_Init_803CA5A4", &[names[4], 0, 0, names[5]]);
        for (i, name) in ["ftMr", "ftKb", "ftLg", "ftGk"].iter().enumerate() {
            dol.symbols.push_str(&format!(
                "{name}_Init_GetMotionFileString = .text:{:#X};\n",
                0x80000100u32 + i as u32 * 4
            ));
        }
        fs::write(root.join("main.dol"), dol.bytes()).unwrap();
        fs::write(root.join("symbols.txt"), dol.symbols).unwrap();
        Self { root, copy_payload }
    }

    fn run(&self) -> Output {
        Command::new(env!("CARGO_BIN_EXE_melee-dat"))
            .args(["symbols", "check-motions", "--dol"])
            .arg(self.root.join("main.dol"))
            .arg("--symbols")
            .arg(self.root.join("symbols.txt"))
            .arg("--files")
            .arg(&self.root)
            .output()
            .unwrap()
    }

    fn change(&self, file: &str, change: impl FnOnce(&mut Vec<u8>)) {
        let path = self.root.join(file);
        let mut bytes = fs::read(&path).unwrap();
        change(&mut bytes);
        fs::write(path, bytes).unwrap();
    }

    fn error(&self, expected: &str) {
        let output = self.run();
        let error = String::from_utf8(output.stderr).unwrap();
        assert!(!output.status.success(), "unexpected success");
        assert!(error.contains(expected), "{error}");
    }
}

impl Drop for Fixture {
    fn drop(&mut self) {
        fs::remove_dir_all(&self.root).unwrap();
    }
}

#[test]
fn common_movie_shared_and_repeated_payloads() {
    let fixture = Fixture::new();
    let output = fixture.run();
    assert!(
        output.status.success(),
        "{}",
        String::from_utf8_lossy(&output.stderr)
    );
    let report = String::from_utf8(output.stdout).unwrap();
    assert!(report.contains("2 fighter tables: 2 motions checked"));
    assert!(
        report
            .contains("movieA (fighter 0, motions 14..17): 2 motions checked")
    );
    assert!(report.contains("2 demo fighters: 8 groups, 10 motions checked, 13 unreferenced archive instances"));
}

#[test]
fn rejects_bad_movie_ranges_sizes_and_names() {
    let at = 32 + 48 + 15 * 24;
    let fixture = Fixture::new();
    fixture.change("PlA.dat", |bytes| word(bytes, at + 4, 1));
    fixture.error("movieA (fighter 0, motions 14..17)");
    fixture.error("not an archive boundary");

    let fixture = Fixture::new();
    fixture.change("PlA.dat", |bytes| {
        let size = read_word(bytes, at + 8);
        word(bytes, at + 8, size.next_multiple_of(32));
    });
    fixture.error("table size");

    let fixture = Fixture::new();
    fixture.change("PlA.dat", |bytes| {
        let name = read_word(bytes, at - 24);
        word(bytes, at, name);
    });
    fixture.error("no public symbol `anim`");
}

#[test]
fn reports_missing_demo_payloads() {
    let fixture = Fixture::new();
    fixture.change("Demo.dat", |bytes| {
        let at = bytes.windows(7).position(|b| b == b"movieB\0").unwrap();
        bytes[at..at + 6].copy_from_slice(b"unused");
    });
    fixture.error("missing demo symbols: movieB");
}

#[test]
fn validates_every_copy_and_unreferenced_nested_archive() {
    let fixture = Fixture::new();
    fixture.change("IntroCopy.dat", |bytes| {
        // The second nested archive is not referenced by the intro motion.
        word(bytes, fixture.copy_payload + 64, u32::MAX);
    });
    fixture.error("IntroCopy.dat@");
    fixture.error("archive at 0x40");
}

#[test]
fn requires_the_demo_table_pointer_to_be_relocated() {
    let fixture = Fixture::new();
    fixture.change("PlA.dat", |bytes| {
        let relocs = 32 + read_word(bytes, 4) as usize;
        word(bytes, relocs + 4, 0x10);
    });
    fixture.error("ftData.x14 is not relocated");
}

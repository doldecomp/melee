use anyhow::{anyhow, Context};
use clang_sys::{CXDiagnosticSeverity, *};
use glob::glob;
use itertools::Itertools;
use log::{debug, info, warn};
use melee_utils::set_current_dir;
use std::{
    cmp::Ordering::{Equal, Greater, Less},
    collections::{HashMap, HashSet},
    ffi::{CStr, CString},
    fs::read_to_string,
    path::{Path, PathBuf},
    ptr::null_mut,
};
use string_interner::{symbol::SymbolU32, StringInterner};

#[derive(PartialEq, PartialOrd, Ord, Eq, Hash, Debug, Clone)]
enum Severity {
    Ignored = CXDiagnostic_Ignored as isize,
    Note = CXDiagnostic_Note as isize,
    Warning = CXDiagnostic_Warning as isize,
    Error = CXDiagnostic_Error as isize,
    Fatal = CXDiagnostic_Fatal as isize,
}

impl std::fmt::Display for Severity {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", &self.to_static_string())
    }
}

impl Severity {
    fn to_static_string(&self) -> &'static str {
        match &self {
            Severity::Ignored => "Ignored",
            Severity::Note => "Note",
            Severity::Warning => "Warning",
            Severity::Error => "Error",
            Severity::Fatal => "Fatal",
        }
    }
}

#[allow(non_upper_case_globals)]
impl From<CXDiagnosticSeverity> for Severity {
    fn from(other: CXDiagnosticSeverity) -> Severity {
        match other {
            CXDiagnostic_Ignored => Severity::Ignored,
            CXDiagnostic_Note => Severity::Note,
            CXDiagnostic_Warning => Severity::Warning,
            CXDiagnostic_Error => Severity::Error,
            CXDiagnostic_Fatal => Severity::Fatal,
            _ => unreachable!(
                "Unexpected {} value: {}",
                std::any::type_name::<CXDiagnosticSeverity>(),
                other
            ),
        }
    }
}

#[derive(PartialEq, Eq, Hash)]
struct DiagnosticInfo {
    severity: Severity,
    category_id: u32,
    category: SymbolU32,
    option: Option<SymbolU32>,
    filename: SymbolU32,
    line: u32,
    column: u32,
    spelling: SymbolU32,
}

fn main() -> ! {
    let code = match process_issues() {
        Ok(0) => {
            println!("Issues: OK");
            exitcode::OK
        }
        Ok(count) => {
            eprintln!("Issues: {}", count);
            exitcode::DATAERR
        }
        Err(e) => {
            eprintln!("Error: {}", e);
            exitcode::IOERR
        }
    };

    std::process::exit(code);
}

fn process_issues() -> anyhow::Result<usize> {
    env_logger::builder().format_timestamp_nanos().init();
    set_current_dir()?;

    let extra_flags = ["-ferror-limit=0"];

    let args: Vec<CString> = read_to_string("compile_flags.txt")
        .context("Failed to read the compile flags.")?
        .split_whitespace()
        .chain(extra_flags)
        .map(CString::new)
        .collect::<Result<_, _>>()?;

    let args_ptrs: Vec<*const i8> = args.iter().map(|s| s.as_ptr()).collect();

    let mut str_interner = StringInterner::default();
    let mut items: HashSet<DiagnosticInfo> = HashSet::new();

    process_index(
        args_ptrs.as_ptr(),
        args_ptrs.len() as i32,
        &mut str_interner,
        &mut items,
    )?;

    let paths_map = map_paths(&str_interner, &items)?;
    let items = sort_info(items, paths_map, &str_interner);
    let count = items.len();

    print_info(items, &str_interner)?;

    Ok(count)
}

fn process_index(
    args: *const *const i8,
    n_args: i32,
    str_interner: &mut StringInterner,
    items: &mut HashSet<DiagnosticInfo>,
) -> anyhow::Result<()> {
    let index = unsafe { clang_createIndex(0, 0) };

    let result = process_glob(index, args, n_args, str_interner, items);

    unsafe {
        clang_disposeIndex(index);
    }

    result
}

fn process_glob(
    index: CXIndex,
    args: *const *const i8,
    n_args: i32,
    str_interner: &mut StringInterner,
    items: &mut HashSet<DiagnosticInfo>,
) -> anyhow::Result<()> {
    glob("src/**/*.[ch]")
        .context("Failed to parse the glob.")?
        .map(|p| p.context("Failed to get a real file from the path."))
        .try_for_each(|p| {
            process_tu(p?, args, n_args, index, str_interner, items)
        })
}

fn process_tu(
    path_buf: PathBuf,
    args: *const *const i8,
    n_args: i32,
    index: CXIndex,
    str_interner: &mut StringInterner,
    items: &mut HashSet<DiagnosticInfo>,
) -> anyhow::Result<()> {
    let path_str = path_buf.to_string_lossy();

    info!("Parsing \"{path_str}\".");
    get_or_intern(&path_str, str_interner);

    let path_cstr = CString::new(path_str.to_string())?;
    let path_ptr = path_cstr.as_ptr() as *const i8;

    let mut tu: CXTranslationUnit = null_mut();

    let cx_result = unsafe {
        clang_parseTranslationUnit2(
            index,
            path_ptr,
            args,
            n_args,
            null_mut(),
            0,
            clang_defaultEditingTranslationUnitOptions(),
            &mut tu,
        )
    };

    let result = if cx_result == CXError_Success {
        process_diagnostics(tu, str_interner, items)
    } else {
        warn!("Failed to parse \"{path_str}\" with error code {cx_result}.");
        Ok(())
    };

    unsafe {
        clang_disposeTranslationUnit(tu);
    }

    result
}

fn process_diagnostics(
    tu: CXTranslationUnit,
    str_interner: &mut StringInterner,
    items: &mut HashSet<DiagnosticInfo>,
) -> anyhow::Result<()> {
    let diagnostics = unsafe { clang_getDiagnosticSetFromTU(tu) };
    let count = unsafe { clang_getNumDiagnosticsInSet(diagnostics) };

    debug!("Found {count} diagnostics.");

    let result = (0..count).try_for_each(|i| {
        let diagnostic_info =
            process_diagnostic(diagnostics, i, str_interner)?;
        items.insert(diagnostic_info);
        Ok(())
    });

    unsafe {
        clang_disposeDiagnosticSet(diagnostics);
    }

    result
}

fn process_diagnostic(
    diagnostics: CXDiagnosticSet,
    diagnostic_idx: u32,
    str_interner: &mut StringInterner,
) -> anyhow::Result<DiagnosticInfo> {
    let diagnostic =
        unsafe { clang_getDiagnosticInSet(diagnostics, diagnostic_idx) };

    let result = process_info(diagnostic, str_interner);

    unsafe {
        clang_disposeDiagnostic(diagnostic);
    }

    result
}

fn resolve_str(
    symbol: SymbolU32,
    str_interner: &StringInterner,
) -> anyhow::Result<&str> {
    str_interner
        .resolve(symbol)
        .ok_or(anyhow!("Failed resolve the symbol."))
}

fn process_info(
    diagnostic: CXDiagnostic,
    str_interner: &mut StringInterner,
) -> anyhow::Result<DiagnosticInfo> {
    let (filename, line, column) = {
        let mut file: CXFile = null_mut();
        let mut line: u32 = 0;
        let mut column: u32 = 0;
        let location = unsafe { clang_getDiagnosticLocation(diagnostic) };

        unsafe {
            clang_getSpellingLocation(
                location,
                &mut file as *mut CXFile,
                &mut line as *mut u32,
                &mut column as *mut u32,
                null_mut(),
            );
        }

        let filename =
            cxstr_to_symbol(unsafe { clang_getFileName(file) }, str_interner)
                .unwrap_or(str_interner.get_or_intern("<Unknown>"));

        (filename, line, column)
    };

    let severity: Severity =
        unsafe { clang_getDiagnosticSeverity(diagnostic) }.into();

    let category_id = unsafe { clang_getDiagnosticCategory(diagnostic) };

    let category = cxstr_to_symbol(
        unsafe { clang_getDiagnosticCategoryText(diagnostic) },
        str_interner,
    )
    .unwrap_or(str_interner.get_or_intern("<Unknown>"));

    let option = cxstr_to_symbol(
        unsafe { clang_getDiagnosticOption(diagnostic, null_mut()) },
        str_interner,
    );

    let spelling = cxstr_to_symbol(
        unsafe { clang_getDiagnosticSpelling(diagnostic) },
        str_interner,
    )
    .unwrap_or(str_interner.get_or_intern("<Unknown>"));

    Ok(DiagnosticInfo {
        severity,
        category_id,
        category,
        option,
        filename,
        line,
        column,
        spelling,
    })
}

fn cxstr_to_symbol(
    cxstr: CXString,
    str_interner: &mut StringInterner,
) -> Option<SymbolU32> {
    let cstr = unsafe { clang_getCString(cxstr) };

    if cstr.is_null() {
        return None;
    }

    let result = unsafe { CStr::from_ptr(cstr) }
        .to_string_lossy()
        .into_owned();

    if result.len() < 1 {
        return None;
    }

    unsafe {
        clang_disposeString(cxstr);
    }

    Some(get_or_intern(&result, str_interner))
}

fn get_or_intern(str: &str, str_interner: &mut StringInterner) -> SymbolU32 {
    match str_interner.get(str) {
        Some(symbol) => symbol,
        None => {
            debug!("Interning \"{str}\".");
            str_interner.get_or_intern(str)
        }
    }
}

fn map_paths(
    str_interner: &StringInterner,
    items: &HashSet<DiagnosticInfo>,
) -> anyhow::Result<HashMap<SymbolU32, Box<Path>>> {
    items
        .iter()
        .map(|i| {
            let sym = i.filename;
            let str = resolve_str(sym, str_interner)?;
            let path = PathBuf::from(str).into_boxed_path();
            Ok((sym, path))
        })
        .collect::<Result<_, _>>()
}

fn sort_info(
    items: HashSet<DiagnosticInfo>,
    paths_map: HashMap<SymbolU32, Box<Path>>,
    str_interner: &StringInterner,
) -> Vec<DiagnosticInfo> {
    info!("Sorting items.");

    items
        .into_iter()
        .sorted_by(|a, b| {
            (a.severity.cmp(&b.severity).reverse())
                .then_with(|| a.category_id.cmp(&b.category_id))
                .then_with(|| match (a.option, b.option) {
                    (Some(a), Some(b)) => {
                        let a = resolve_str(a, &str_interner);
                        let b = resolve_str(b, &str_interner);

                        match (a, b) {
                            (Ok(a), Ok(b)) => a.cmp(&b),
                            _ => Equal,
                        }
                    }
                    (None, Some(_)) => Less,
                    (Some(_), None) => Greater,
                    (None, None) => Equal,
                })
                .then_with(|| {
                    let a = &*paths_map[&a.filename];
                    let b = &*paths_map[&b.filename];

                    let a_depth = a.components().count();
                    let b_depth = b.components().count();

                    // Sort by depth first
                    if a_depth != b_depth {
                        return a_depth.cmp(&b_depth);
                    }

                    // Sort lexicographically within each depth level
                    for (a, b) in a.components().zip(b.components()) {
                        match a.cmp(&b) {
                            Equal => continue,
                            order => return order,
                        }
                    }

                    Equal
                })
                .then_with(|| a.line.cmp(&b.line))
                .then_with(|| a.column.cmp(&b.column))
                .then_with(|| {
                    let a = resolve_str(a.spelling, str_interner);
                    let b = resolve_str(b.spelling, str_interner);

                    match (a, b) {
                        (Ok(a), Ok(b)) => a.cmp(&b),
                        _ => Equal,
                    }
                })
        })
        .collect()
}

fn print_info(
    items: Vec<DiagnosticInfo>,
    str_interner: &StringInterner,
) -> anyhow::Result<()> {
    info!("Printing items.");

    let indent = "    ";
    let depth = 0;

    for (key, items) in &items.into_iter().group_by(|i| i.severity.clone()) {
        let items = items.collect_vec();
        let margin = indent.repeat(depth);
        let count = items.len();

        println!("{margin}{key} ({count})");
        let depth = depth + 1;

        for (key, items) in &items.into_iter().group_by(|i| i.category.clone())
        {
            let key = resolve_str(key, &str_interner)?;
            let items = items.collect_vec();
            let margin = indent.repeat(depth);
            let count = items.len();

            println!("{margin}{key} ({count})");
            let depth = depth + 1;

            for (key, items) in
                &items.into_iter().group_by(|i| i.option.clone())
            {
                let key = match key {
                    Some(option) => {
                        format!("[{}]", resolve_str(option, &str_interner)?)
                    }
                    None => "required".into(),
                };
                let items = items.collect_vec();
                let margin = indent.repeat(depth);
                let count = items.len();

                println!("{margin}{key} ({count})");
                let depth = depth + 1;

                for (key, items) in
                    &items.into_iter().group_by(|i| i.filename.clone())
                {
                    let key = resolve_str(key, &str_interner)?;
                    let items = items.collect_vec();
                    let margin = indent.repeat(depth);
                    let count = items.len();

                    println!("{margin}{key} ({count})");
                    let depth = depth + 1;

                    for item in items {
                        println!(
                            "{}{}:{}: {}",
                            indent.repeat(depth),
                            item.line,
                            item.column,
                            resolve_str(item.spelling, &str_interner)?
                        );
                    }
                }
            }
        }
    }

    Ok(())
}

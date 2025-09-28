package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"lukechampine.com/flagg"
)

func main() {
	log.SetFlags(0)
	var typeName string
	var fix bool
	var conservative, onlyMatched bool
	root := flagg.Root
	rootDir := root.String("root", "../../", "root directory containing C sources and asm")
	cmdFindFns := flagg.New("findfns", "Find function types to fix")
	cmdFindFns.StringVar(&typeName, "type", "", "Enumerate functions in tables with a known type")
	cmdFindFns.BoolVar(&fix, "fix", false, "Immediately apply fixes instead of listing them")
	cmdFixFns := flagg.New("fixfns", "Fix function types")
	cmdFixFns.BoolVar(&conservative, "conservative", false, "only fix UNK_RET/UNK_PARAMS functions")
	cmdRename := flagg.New("rename", "Rename anonymous functions based on hardcoded patterns")
	cmdRename.StringVar(&typeName, "type", "", "type of struct to derive names from")
	cmdUnk := flagg.New("unk", "Search for UNK_RET functions in asm data")
	cmdOpSeq := flagg.New("opseq", "Search for a sequence of opcodes")
	cmdOpSeq.BoolVar(&onlyMatched, "m", true, "only print functions that are 100% matched")
	cmd := flagg.Parse(flagg.Tree{
		Cmd: root,
		Sub: []flagg.Tree{
			{Cmd: cmdFindFns},
			{Cmd: cmdFixFns},
			{Cmd: cmdRename},
			{Cmd: cmdUnk},
			{Cmd: cmdOpSeq},
		},
	})

	report := loadReport(filepath.Join(*rootDir, "build", "GALE01", "report.json"))

	// parse source and asm files
	srcDir := filepath.Join(*rootDir, "src", "melee")
	hFiles := findFiles(srcDir, ".h")
	cFiles := findFiles(srcDir, ".c")
	if len(hFiles)+len(cFiles) == 0 {
		log.Fatalln("No source files found in", *rootDir)
	}
	asmDir := filepath.Join(*rootDir, "build", "GALE01", "asm", "melee")
	asmFiles := findFiles(asmDir, ".s")
	if len(asmFiles) == 0 {
		log.Fatalln("No asm files found in", asmDir)
	}
	fmt.Println("Sources: ", len(hFiles), ".h files,", len(cFiles), ".c files,", len(asmFiles), ".s files")
	tables := extractAsmTables(asmFiles)

	visitStructs := func(typeName string, st CStructType, fn func(string, string, int, *CStructValue)) {
		for _, path := range append(hFiles, cFiles...) {
			for _, name := range parseTableDecls(path, typeName) {
				if tab, ok := tables[name]; ok && len(tab)%len(st.Fields) == 0 {
					for index := range len(tab) / len(st.Fields) {
						sv := st.New().(*CStructValue)
						if sv.parse(tab[index*len(st.Fields):][:len(st.Fields)]) {
							fn(path, name, index, sv)
						}
					}
				}
			}
		}
	}
	runTypes := func(typeName string, fn func(string, CStructType)) {
		switch typeName {
		case "":
			fmt.Println("No type specified. Available types:")
			for name := range structTypes {
				fmt.Println(" -", name)
			}
		case "all":
			for name, typ := range structTypes {
				fn(name, typ)
			}
		default:
			tableType, ok := structTypes[typeName]
			if !ok {
				log.Fatalf("Unknown type: %s", typeName)
			}
			fn(typeName, tableType)
		}
	}
	applyRewrites := func(fnTypes map[string]*CFuncValue) {
		fmt.Println("Identified", len(fnTypes), "candidate functions for updating.")
		if len(fnTypes) == 0 {
			fmt.Println("Nothing to do, exiting.")
			return
		}
		totalSigs := 0
		totalFiles := 0
		for _, path := range append(hFiles, cFiles...) {
			fmt.Printf("\rChecking %-70v", path[:min(57, len(path))]+"...")
			sigs := fixSignatures(path, fnTypes, conservative)
			totalSigs += sigs
			if sigs > 0 {
				totalFiles++
				s := "es"
				if sigs == 1 {
					s = ""
				}
				fmt.Printf("%3d fix%s\n", sigs, s)
			}
		}
		fmt.Println()
		fmt.Printf("Fixed %v signatures across %v source files.\n", totalSigs, totalFiles)
	}

	switch cmd {
	case cmdFindFns:
		if cmd.NArg() != 0 {
			cmd.Usage()
			return
		}
		runTypes(typeName, func(typeName string, st CStructType) {
			fnTypes := make(map[string]*CFuncValue)
			visitStructs(typeName, st, func(path, name string, index int, sv *CStructValue) {
				for _, f := range sv.Fields {
					if fn, ok := f.(*CFuncValue); ok {
						fnTypes[fn.Name] = fn
					}
				}
			})
			if fix {
				applyRewrites(fnTypes)
			} else {
				var lines []string
				for name, fn := range fnTypes {
					lines = append(lines, fmt.Sprintf("%s: %s", name, fn))
				}
				sort.Strings(lines)
				for _, line := range lines {
					fmt.Println(line)
				}
			}
		})

	case cmdFixFns:
		if cmd.NArg() != 1 {
			cmd.Usage()
			return
		}
		fixList, err := os.ReadFile(cmd.Arg(0))
		if err != nil {
			log.Fatal(err)
		}
		fnTypes := make(map[string]*CFuncValue)
		for _, line := range bytes.Split(fixList, []byte("\n")) {
			if line = bytes.TrimSpace(line); len(line) == 0 {
				continue
			}
			name, fixed, ok := bytes.Cut(line, []byte(": "))
			if !ok {
				log.Fatalf("Invalid format: %q", line)
			}
			fnTypes[string(name)] = parseCFuncValue(fixed)
		}
		applyRewrites(fnTypes)

	case cmdRename:
		if cmd.NArg() != 0 {
			cmd.Usage()
			return
		}

		canonicalPrefix := func(typeName string, path string) string {
			switch typeName {
			case "ItemStateTable":
				itKind := strings.TrimPrefix(strings.TrimSuffix(filepath.Base(path), filepath.Ext(path)), "it")
				itKind = strings.ToUpper(itKind[:1]) + itKind[1:]
				return fmt.Sprintf("it%s_UnkMotion", itKind)
			case "MinorScene":
				gmKind := strings.TrimPrefix(strings.TrimSuffix(filepath.Base(path), filepath.Ext(path)), "gm")
				gmKind = strings.ToUpper(gmKind[:1]) + gmKind[1:]
				return fmt.Sprintf("gm%s_UnkScene", gmKind)
			case "StageData":
				grKind := strings.TrimPrefix(strings.TrimSuffix(filepath.Base(path), filepath.Ext(path)), "gr")
				grKind = strings.ToUpper(grKind[:1]) + grKind[1:]
				return fmt.Sprintf("gr%s_UnkStage", grKind)
			case "ItemLogicTable":
				itKind := strings.TrimPrefix(strings.TrimSuffix(filepath.Base(path), filepath.Ext(path)), "it")
				itKind = strings.ToUpper(itKind[:1]) + itKind[1:]
				return fmt.Sprintf("it%s_Logic", itKind)
			default:
				panic("unhandled type: " + typeName)
			}
		}

		canonicalFieldNames := func(typeName string) []string {
			switch typeName {
			case "ItemStateTable":
				return []string{"", "Anim", "Phys", "Coll"}
			case "MinorScene":
				return []string{"", "Prep", "Decide"}
			case "StageData":
				return []string{"", "", "", "", "", "OnLoad", "OnStart", "", "", "", "", "", ""}
			case "ItemLogicTable":
				return []string{"", "Spawned", "Destroyed", "PickedUp", "Dropped", "Thrown", "DmgDealt", "DmgReceived", "EnteredAir", "Reflected", "Clanked", "Absorbed", "ShieldBounced", "HitShield", "EvtUnk"}
			default:
				panic("unhandled type: " + typeName)
			}
		}

		runTypes(typeName, func(typeName string, st CStructType) {
			renames := make(map[string]string)
			visitStructs(typeName, st, func(path, name string, index int, sv *CStructValue) {
				prefix := canonicalPrefix(typeName, path)
				fieldNames := canonicalFieldNames(typeName)
				for i, f := range sv.Fields {
					if fn, ok := f.(*CFuncValue); ok && fieldNames[i] != "" {
						renames[fn.Name] = fmt.Sprintf("%s%d_%s", prefix, index, fieldNames[i])
					}
				}
			})
			fmt.Println("Identified", len(renames), "functions to rename.")
			if len(renames) == 0 {
				fmt.Println("Nothing to do, exiting.")
				return
			}

			// if there are conflicts, skip all of them
			inv := make(map[string][]string)
			for k, v := range renames {
				inv[v] = append(inv[v], k)
			}
			for newName, oldNames := range inv {
				if len(oldNames) > 1 {
					fmt.Printf("Skipping %s (conflict: %v)\n", newName, oldNames)
					for _, oldName := range oldNames {
						delete(renames, oldName)
					}
				}
			}

			var replacePairs []string
			for oldName, newName := range renames {
				replacePairs = append(replacePairs, oldName, newName)
			}
			replacer := strings.NewReplacer(replacePairs...)

			totalFiles := 0
			renameFile := func(path string) {
				fmt.Printf("\rChecking %-70v", path[:min(57, len(path))]+"...")
				content, err := os.ReadFile(path)
				if err != nil {
					log.Fatalf("Failed to read file: %v", err)
				}
				contentStr := string(content)
				updated := replacer.Replace(contentStr)
				if updated != contentStr {
					if err := os.WriteFile(path, []byte(updated), 0644); err != nil {
						log.Fatalf("Failed to write file %s: %v", path, err)
					}
					fmt.Printf("\rUpdated %-70v\n", path[:min(57, len(path))])
					totalFiles++
				}
			}

			for _, path := range append(append(hFiles, cFiles...), asmFiles...) {
				renameFile(path)
			}
			renameFile(filepath.Join(*rootDir, "config", "GALE01", "symbols.txt"))

			fmt.Println()
			if totalFiles > 0 {
				fmt.Printf("Renamed %d symbols in %d files.\n", len(renames), totalFiles)
			} else {
				fmt.Println("Nothing to rename.")
			}
		})

	case cmdUnk:
		if cmd.NArg() != 0 {
			cmd.Usage()
			return
		}
		fmt.Println("Found", len(tables), "asm tables in", asmDir)
		fnNames := make(map[string]string)
		for name, entries := range tables {
			for _, entry := range entries {
				if entry.Size != 4 {
					continue
				}
				fnNames[entry.Value] = name
			}
		}
		fmt.Println("Found", len(fnNames), "symbols in tables.")
		var tables []string
		seen := make(map[string]struct{})
		findUNKs := func(path string) (n int) {
			content, err := os.ReadFile(path)
			if err != nil {
				log.Fatalf("Failed to read file %s: %v", path, err)
			}
			for name := range fnNames {
				if bytes.Contains(content, fmt.Appendf(nil, "UNK_RET %s", name)) {
					if _, ok := seen[fnNames[name]]; !ok {
						tables = append(tables, fnNames[name])
						seen[fnNames[name]] = struct{}{}
						n++
					}
				}
			}
			return n
		}
		total := 0
		for _, path := range append(hFiles, cFiles...) {
			fmt.Printf("\rChecking %-70v", path[:min(57, len(path))]+"...")
			n := findUNKs(path)
			total += n
			if n > 0 {
				fmt.Printf("%3d found, %4d total\n", n, len(tables))
			}
		}
		sort.Strings(tables)
		fmt.Println("\nFound", len(tables), "asm tables with UNK_RET functions:")
		for _, name := range tables {
			fmt.Println(name)
		}

	case cmdOpSeq:
		if cmd.NArg() != 1 {
			cmd.Usage()
			return
		}
		ops := bytes.Split([]byte(cmd.Arg(0)), []byte(","))
		for i := range ops {
			ops[i] = append([]byte("*/	"), bytes.TrimSpace(ops[i])...)
		}

		var results [][2]string
		for _, path := range asmFiles {
			contents, err := os.ReadFile(path)
			if err != nil {
				log.Fatalln("Failed to read file:", path, err)
			}
			lines := bytes.Split(contents, []byte("\n"))
			var decl []byte
			for i := 0; i < len(lines)-len(ops); i++ {
				if bytes.HasPrefix(lines[i], []byte(".fn")) {
					decl, _, _ = bytes.Cut(bytes.TrimPrefix(lines[i], []byte(".fn ")), []byte(","))
				}
				match := true
				for j, op := range ops {
					if !bytes.Contains(lines[i+j], op) {
						match = false
						break
					}
				}
				if match {
					if onlyMatched && !report.isMatched(string(decl)) {
						continue
					}
					s := fmt.Sprintf("%s:%d", path, i+1)
					results = append(results, [2]string{s, string(decl)})
				}
			}
		}
		sort.Slice(results, func(i, j int) bool {
			return report.size(results[i][1]) < report.size(results[j][1])
		})
		for _, res := range results {
			fmt.Printf("%4d %s\n", report.size(res[1]), res[0])
		}
	}
}

func findFiles(dir string, ext string) []string {
	var files []string
	err := filepath.WalkDir(dir, func(path string, _ os.DirEntry, err error) error {
		if filepath.Ext(path) == ext {
			files = append(files, path)
		}
		return err
	})
	if err != nil {
		log.Fatalf("Error walking directory: %v", err)
	}
	return files
}

type AsmTableEntry struct {
	Size  int
	Value string
}

func extractAsmTables(paths []string) map[string][]AsmTableEntry {
	tables := make(map[string][]AsmTableEntry)
	for _, path := range paths {
		contents, err := os.ReadFile(path)
		if err != nil {
			log.Fatalln("Failed to read file:", path, err)
		}
		objects := bytes.Split(contents, []byte(".obj "))
		for _, object := range objects {
			if !bytes.Contains(object, []byte("byte")) {
				continue
			}
			lines := strings.Split(string(object), "\n")
			symbol, _, _ := strings.Cut(strings.TrimSpace(lines[0]), ",")
			var entries []AsmTableEntry
			for _, line := range lines[1:] {
				typ, val, _ := strings.Cut(strings.TrimSpace(line), " ")
				var size int
				switch typ {
				case ".byte":
					size = 1
				case ".2byte":
					size = 2
				case ".4byte":
					size = 4
				case ".8byte":
					size = 8
				default:
					continue
				}
				// TODO: support other sizes
				if size != 4 {
					continue
				}
				entries = append(entries, AsmTableEntry{Size: size, Value: val})
			}
			tables[symbol] = entries
		}
	}
	return tables
}

type MatchReportFunction struct {
	Name         string  `json:"name"`
	Size         int     `json:"size,string"`
	MatchPercent float64 `json:"fuzzy_match_percent"`
}

type MatchReport struct {
	matches map[string]MatchReportFunction
}

func (mr *MatchReport) isMatched(fnName string) bool {
	f, ok := mr.matches[fnName]
	return ok && f.MatchPercent == 100
}

func (mr *MatchReport) size(fnName string) int {
	return mr.matches[fnName].Size
}

func loadReport(path string) *MatchReport {
	content, err := os.ReadFile(path)
	if err != nil {
		log.Fatalf("Failed to read report file %s: %v", path, err)
	}
	var report struct {
		Units []struct {
			Name      string
			Functions []MatchReportFunction
		}
	}
	if err := json.Unmarshal(content, &report); err != nil {
		log.Fatalf("Failed to unmarshal report file %s: %v", path, err)
	}
	matches := make(map[string]MatchReportFunction)
	for _, unit := range report.Units {
		for _, fn := range unit.Functions {
			matches[fn.Name] = fn
		}
	}
	return &MatchReport{matches: matches}
}

package main

import (
	"bytes"
	"fmt"
	"log"
	"maps"
	"os"
	"path/filepath"
	"sort"
	"strconv"
	"strings"

	"lukechampine.com/flagg"
)

func main() {
	log.SetFlags(0)
	root := flagg.Root
	rootDir := root.String("root", "../../", "root directory containing C sources and asm")
	cmdFixTab := flagg.New("fixtab", "Fix function types for a given table type")
	tableTypeName := cmdFixTab.String("type", "", "table type to fix")
	cmdUnk := flagg.New("unk", "Search for UNK_RET functions in asm data")
	cmd := flagg.Parse(flagg.Tree{
		Cmd: root,
		Sub: []flagg.Tree{
			{Cmd: cmdFixTab},
			{Cmd: cmdUnk},
		},
	})

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

	switch cmd {
	case cmdFixTab:
		if cmd.NArg() != 0 {
			cmd.Usage()
			return
		}

		fix := func(tableTypeName string, tableType TableType) {
			fnTypes := make(map[string]FuncType)
			for _, path := range append(hFiles, cFiles...) {
				for _, name := range parseTableDecls(path, tableTypeName) {
					fmt.Println("Found table", name, "in", path)
					if tab, ok := tables[name]; ok && len(tab)%len(tableType.Fields) == 0 {
						maps.Insert(fnTypes, tableType.parse(tab))
					}
				}
			}
			fmt.Println("Identified", len(fnTypes), "candidate functions for updating.")
			if len(fnTypes) == 0 {
				fmt.Println("Nothing to do, exiting.")
				return
			}
			totalSigs := 0
			totalFiles := 0
			for _, path := range append(hFiles, cFiles...) {
				fmt.Printf("\rChecking %-70v", path[:min(57, len(path))]+"...")
				sigs := fixSignatures(path, fnTypes)
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
			fmt.Printf("\nFixed %v signatures across %v source files.\n", totalSigs, totalFiles)
		}

		switch *tableTypeName {
		case "":
			fmt.Println("No table type specified. Available types:")
			for name := range tableTypes {
				fmt.Println(" -", name)
			}
		case "all":
			for name, typ := range tableTypes {
				fmt.Println("Fixing table type", name)
				fix(name, typ)
			}
		default:
			tableType, ok := tableTypes[*tableTypeName]
			if !ok {
				log.Fatalf("Unknown table type: %s", *tableTypeName)
			}
			fix(*tableTypeName, tableType)
		}

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
		candidates := make(map[string]struct{})
		findUNKs := func(path string) (n int) {
			content, err := os.ReadFile(path)
			if err != nil {
				log.Fatalf("Failed to read file %s: %v", path, err)
			}
			for name := range fnNames {
				if bytes.Contains(content, []byte(fmt.Sprintf("UNK_RET %s", name))) {
					n++
					candidates[name] = struct{}{}
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
				fmt.Printf("%3d found, %4d total\n", n, len(candidates))
			}
		}
		var tables []string
		seen := make(map[string]struct{})
		for name := range candidates {
			if _, ok := seen[fnNames[name]]; !ok {
				tables = append(tables, fnNames[name])
				seen[fnNames[name]] = struct{}{}
			}
		}
		sort.Strings(tables)
		fmt.Println("\nFound", len(tables), "asm tables with UNK_RET functions:")
		for _, name := range tables {
			fmt.Println(name)
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

func (e AsmTableEntry) Integer() int64 {
	if e.Value == "NULL" {
		return 0
	}
	i, _ := strconv.ParseInt(e.Value, 16, e.Size*8)
	return i
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

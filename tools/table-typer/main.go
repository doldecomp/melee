package main

import (
	"bytes"
	"fmt"
	"log"
	"maps"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

func main() {
	log.SetFlags(0)
	if len(os.Args) != 3 {
		fmt.Println("Usage: table-typer <table-type> <root dir>")
		return
	}

	tableTypeName, rootDir := os.Args[1], os.Args[2]
	tableType, ok := tableTypes[tableTypeName]
	if !ok {
		log.Fatalf("Unknown table type: %s", tableTypeName)
	}
	srcDir := filepath.Join(rootDir, "src", "melee")
	cFiles := findFiles(srcDir, ".c")
	hFiles := findFiles(srcDir, ".h")
	if len(cFiles)+len(hFiles) == 0 {
		log.Fatalln("No source files found in", rootDir)
	}
	asmDir := filepath.Join(rootDir, "build", "GALE01", "asm", "melee")
	asmFiles := findFiles(asmDir, ".s")
	if len(asmFiles) == 0 {
		log.Fatalln("No asm files found in", asmDir)
	}
	tables := extractAsmTables(asmFiles)

	fnTypes := make(map[string]FuncType)
	for _, path := range hFiles {
		for _, name := range parseTableDecls(path, tableTypeName) {
			if tab, ok := tables[name]; ok && len(tab)%tableType.NumEntries == 0 {
				maps.Insert(fnTypes, tableType.parse(tab))
			}
		}
	}
	fmt.Println("Found", len(fnTypes), "functions in asm tables with known types.")

	totalSigs := 0
	totalFiles := 0
	for _, path := range append(cFiles, hFiles...) {
		fmt.Printf("\rChecking %-70v", path[:min(57, len(path))]+"...")
		sigs := fixSignatures(path, fnTypes)
		totalSigs += sigs
		if sigs > 0 {
			totalFiles++
			fmt.Printf("%d fixes\n", sigs)
		}
	}
	fmt.Printf("\nFixed %v signatures across %v source files.\n", totalSigs, totalFiles)
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
	val, _ := strconv.ParseInt(e.Value, 16, e.Size*8)
	return val
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
				fields := strings.Fields(line)
				if len(fields) != 2 {
					continue
				}
				var size int
				switch fields[0] {
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
				entries = append(entries, AsmTableEntry{Size: size, Value: fields[1]})
			}
			tables[symbol] = entries
		}
	}
	return tables
}

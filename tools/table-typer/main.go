package main

import (
	"bytes"
	"encoding/binary"
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
	if len(os.Args) != 4 {
		fmt.Println("Usage: table-typer <table-type> <src dir> <asm dir>")
		return
	}
	tableTypeName, srcDir, asmDir := os.Args[1], os.Args[2], os.Args[3]
	tableType, ok := tableTypes[tableTypeName]
	if !ok {
		log.Fatalf("Unknown table type: %s", tableTypeName)
	}
	cFiles := findFiles(srcDir, ".c")
	hFiles := findFiles(srcDir, ".h")
	if len(cFiles)+len(hFiles) == 0 {
		log.Fatalln("No source files found in", srcDir)
	}
	asmFiles := findFiles(asmDir, ".s")
	if len(asmFiles) == 0 {
		log.Fatalln("No asm files found in", asmDir)
	}
	tables := extractAsmTables(asmFiles)

	fnTypes := make(map[string]FuncType)
	for _, path := range hFiles {
		for _, tableAddr := range parseTableDecls(path, tableTypeName) {
			if tab, ok := tables[tableAddr]; ok && len(tab)%tableType.Sizeof == 0 {
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

func extractAsmTables(paths []string) map[string][]byte {
	appendAsmData := func(b []byte, line string) []byte {
		entry := strings.TrimSpace(line)
		for _, s := range []string{".4byte ", "it_", ".L_", "0x"} {
			entry = strings.TrimPrefix(entry, s)
		}
		if len(entry) == 0 {
			return b
		} else if entry == "NULL" {
			entry = "0"
		}
		i, _ := strconv.ParseInt(entry, 16, 64)
		return binary.BigEndian.AppendUint32(b, uint32(i))
	}

	tables := make(map[string][]byte)
	for _, path := range paths {
		contents, err := os.ReadFile(path)
		if err != nil {
			log.Fatalln("Failed to read file:", path, err)
		}
		sections := bytes.Split(contents, []byte(".section "))
		for _, section := range sections {
			if bytes.Contains(section, []byte(".text")) || bytes.Contains(section, []byte(".sdata")) {
				continue
			}

			globals := strings.Split(string(section), ".global ")
			for _, global := range globals {
				if !strings.Contains(global, ".4byte") {
					continue
				}

				lines := strings.Split(global, "\n")
				addr := strings.TrimSpace(lines[0])
				if strings.Contains(addr, "_") {
					addr = addr[strings.Index(addr, "_")+1:]
				}
				var data []byte
				for _, line := range lines[2:] {
					data = appendAsmData(data, line)
				}
				tables[addr] = data
			}
		}
	}
	return tables
}

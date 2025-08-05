package main

import (
	"bytes"
	"fmt"
	"iter"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func normalizeType(t string) string {
	return strings.NewReplacer(
		"Item_GObj", "HSD_GObj",
		"Fighter_GObj", "HSD_GObj",
	).Replace(t)
}

type CType interface {
	equivalentTo(other CType) bool
}

type FuncType struct {
	Return string
	Params []string
}

func (ft FuncType) equivalentTo(other CType) bool {
	ot, ok := other.(FuncType)
	if !ok || normalizeType(ft.Return) != normalizeType(ot.Return) || len(ft.Params) != len(ot.Params) {
		return false
	}
	for i, param := range ft.Params {
		if normalizeType(param) != normalizeType(ot.Params[i]) {
			return false
		}
	}
	return true
}

type FuncSignature struct {
	Type       FuncType
	Name       string
	ParamNames []string
}

func (fs FuncSignature) String() string {
	var params []string
	for i := range fs.ParamNames {
		if fs.ParamNames[i] == "" {
			params = append(params, fs.Type.Params[i]) // just type
		} else {
			params = append(params, fmt.Sprintf("%s %s", fs.Type.Params[i], fs.ParamNames[i]))
		}
	}
	return fmt.Sprintf("%s %s(%s)", fs.Type.Return, fs.Name, strings.Join(params, ", "))
}

type TableType struct {
	NumAsmEntries int
	Fields        []CType
}

var tableTypes = map[string]TableType{
	"ItemStateTable": {
		NumAsmEntries: 4,
		Fields: []CType{
			nil, // enum_t
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
		},
	},
	"ItemLogicTable": {
		NumAsmEntries: 15,
		Fields: []CType{
			nil, // ItemStateTable*
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*", "Item_GObj*"}},
		},
	},
	"sdata_ItemGXLink": {
		NumAsmEntries: 1,
		Fields: []CType{
			FuncType{"void", []string{"HSD_GObj*", "int"}},
		},
	},
	"StageCallbacks": {
		NumAsmEntries: 5,
		Fields: []CType{
			FuncType{"void", []string{"Ground_GObj*"}},
			FuncType{"bool", []string{"Ground_GObj*"}},
			FuncType{"void", []string{"Ground_GObj*"}},
			FuncType{"void", []string{"Ground_GObj*"}},
			nil, // u32
		},
	},
}

func (tt TableType) parse(entries []AsmTableEntry) iter.Seq2[string, FuncType] {
	return func(yield func(string, FuncType) bool) {
		for len(entries) > 0 {
			for _, field := range tt.Fields {
				entry := entries[0]
				entries = entries[1:]
				switch t := field.(type) {
				case FuncType:
					if entry.Value == "NULL" {
						continue
					}
					if !yield(entry.Value, t) {
						return
					}
				}
			}
		}
	}
}

func parseTableDecls(path string, tableType string) []string {
	content, err := os.ReadFile(path)
	if err != nil {
		log.Fatalf("Failed to read file %s: %v", path, err)
	}
	var decls []string
	matches := regexp.MustCompile(fmt.Sprintf(`%v\s+(\w+)\[(?:\d+)?\][\s={;]+`, tableType)).FindAllStringSubmatch(string(content), -1)
	for _, match := range matches {
		if len(match) > 1 {
			decls = append(decls, match[1])
		}
	}
	return decls
}

func fixSignatures(path string, fnTypes map[string]FuncType) int {
	content, err := os.ReadFile(path)
	if err != nil {
		log.Fatalf("Failed to read file %s: %v", path, err)
	}
	n := 0
	for name, ft := range fnTypes {
		if bytes.Contains(content, []byte(name)) {
			var changed bool
			content, changed = fixSignature(content, name, ft)
			if changed {
				n++
			}
		}
	}
	if n > 0 {
		if err := os.WriteFile(path, content, 0644); err != nil {
			log.Fatalf("Failed to write file %s: %v", path, err)
		}
	}
	return n
}

func fixSignature(content []byte, name string, ft FuncType) ([]byte, bool) {
	changed := false
	lines := bytes.Split(content, []byte("\n"))
	for i, line := range lines {
		if orig, sig, ok := parseFuncSignature(name, line); ok {
			if !sig.Type.equivalentTo(ft) {
				sig.Type = ft
				sig.ParamNames = sig.ParamNames[:len(ft.Params)] // bit of a hack
				lines[i] = bytes.Replace(lines[i], orig, []byte(sig.String()), 1)
				changed = true
			}
		}
	}
	return bytes.Join(lines, []byte("\n")), changed
}

func parseFuncSignature(name string, line []byte) ([]byte, FuncSignature, bool) {
	i := bytes.Index(line, []byte(name+"("))
	if i < 0 {
		return nil, FuncSignature{}, false
	}
	retEnd := bytes.LastIndexByte(line[:i], ' ')
	retStart := retEnd - 1
	for retStart > 0 && isIdentByte(line[retStart-1]) {
		retStart--
	}
	returnType := string(bytes.TrimSpace(line[retStart:retEnd]))
	if returnType == "" || returnType == "return" {
		// actually a function call, not a declaration
		return nil, FuncSignature{}, false
	}
	paramStart := i + len(name) + 1
	paramEnd := paramStart + bytes.IndexByte(line[paramStart:], ')')
	params := bytes.Split(line[paramStart:paramEnd], []byte(","))
	isDecl := strings.Contains(string(line), ";")
	var paramTypes, paramNames []string
	renames := 0
	for _, param := range params {
		typ, name, _ := strings.Cut(strings.TrimSpace(string(param)), " ")
		if strings.HasPrefix(name, "*") {
			typ += "*"
			name = strings.TrimPrefix(name, "*")
		}
		// TODO: handle this more generically
		if name == "" && !isDecl {
			name = "gobj"
			if renames++; renames > 1 {
				name += strconv.Itoa(renames)
			}
		}
		paramTypes = append(paramTypes, typ)
		paramNames = append(paramNames, name)
	}
	orig := line[retStart : paramEnd+1]
	sig := FuncSignature{
		Type:       FuncType{Return: returnType, Params: paramTypes},
		Name:       string(line[retEnd+1 : i+len(name)]),
		ParamNames: paramNames,
	}
	return orig, sig, true
}

func isIdentByte(b byte) bool {
	return b == '_' ||
		(b >= 'a' && b <= 'z') ||
		(b >= 'A' && b <= 'Z') ||
		(b >= '0' && b <= '9')

}

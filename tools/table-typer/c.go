package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"iter"
	"log"
	"os"
	"regexp"
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
		params = append(params, fmt.Sprintf("%s %s", fs.Type.Params[i], fs.ParamNames[i]))
	}
	return fmt.Sprintf("%s %s(%s)", fs.Type.Return, fs.Name, strings.Join(params, ", "))
}

type TableType struct {
	Sizeof int
	Fields []CType
}

var tableTypes = map[string]TableType{
	"ItemStateTable": {
		Sizeof: 16,
		Fields: []CType{
			nil, // "enum_t",
			FuncType{"bool", []string{"Item_GObj*"}},
			FuncType{"void", []string{"Item_GObj*"}},
			FuncType{"bool", []string{"Item_GObj*"}},
		},
	},
}

func (tt TableType) parse(asmData []byte) iter.Seq2[string, FuncType] {
	buf := bytes.NewBuffer(asmData)
	return func(yield func(string, FuncType) bool) {
		for buf.Len() > 0 {
			entry := buf.Next(tt.Sizeof)
			for i, field := range tt.Fields {
				switch t := field.(type) {
				case FuncType:
					addr := binary.BigEndian.Uint32(entry[i*4:])
					if addr == 0 {
						continue
					}
					if !yield(fmt.Sprintf("%X", addr), t) {
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
	matches := regexp.MustCompile(fmt.Sprintf(`extern\s+%v\s+(\w+)\[\];`, tableType)).FindAllStringSubmatch(string(content), -1)
	for _, match := range matches {
		if len(match) > 1 {
			decls = append(decls, match[1])
		}
	}
	// TODO: could be more generic
	for i := range decls {
		if u := strings.LastIndexByte(decls[i], '_'); u != -1 {
			decls[i] = decls[i][u+1:]
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
	for addr, ft := range fnTypes {
		if bytes.Contains(content, []byte(addr)) {
			var changed bool
			content, changed = fixSignature(content, addr, ft)
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

func fixSignature(content []byte, addr string, ft FuncType) ([]byte, bool) {
	changed := false
	lines := bytes.Split(content, []byte("\n"))
	for i, line := range lines {
		if orig, sig, ok := parseFuncSignature(addr, line); ok {
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
	returnType := bytes.TrimSpace(line[retStart:retEnd])
	if len(returnType) == 0 {
		return nil, FuncSignature{}, false
	}
	paramStart := i + len(name) + 1
	paramEnd := paramStart + bytes.IndexByte(line[paramStart:], ')')
	params := bytes.Split(line[paramStart:paramEnd], []byte(","))
	var paramTypes, paramNames []string
	for _, param := range params {
		typ, name, _ := strings.Cut(strings.TrimSpace(string(param)), " ")
		if strings.HasPrefix(name, "*") {
			typ += "*"
			name = strings.TrimPrefix(name, "*")
		}
		// TODO: handle this more generically
		if name == "" {
			name = "gobj"
		}
		paramTypes = append(paramTypes, typ)
		paramNames = append(paramNames, name)
	}
	orig := line[retStart : paramEnd+1]
	sig := FuncSignature{
		Type:       FuncType{Return: string(returnType), Params: paramTypes},
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

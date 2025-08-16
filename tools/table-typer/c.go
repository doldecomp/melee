package main

import (
	"bytes"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func defaultName(typ string, prevParams []string) string {
	name := "arg"
	switch typ {
	case "HSD_GObj*", "Item_GObj*", "Ground_GObj*":
		name = "gobj"
	case "Vec3*":
		name = "vec"
	case "HSD_JObj*":
		name = "jobj"
	case "bool":
		name = "flag"
	}
	for i, p := range prevParams {
		if name == p {
			name += strconv.Itoa(i)
		}
	}
	return name
}

func normalizeType(t string) string {
	return strings.NewReplacer(
		"Item_GObj", "HSD_GObj",
		"Fighter_GObj", "HSD_GObj",
	).Replace(t)
}

func equivalent(a, b CType) bool {
	switch a := a.(type) {
	case CFuncType:
		b, ok := b.(CFuncType)
		if !ok {
			return false
		}
		if normalizeType(a.Return) != normalizeType(b.Return) || len(a.Params) != len(b.Params) {
			return false
		}
		for i, param := range a.Params {
			if normalizeType(param) != normalizeType(b.Params[i]) {
				return false
			}
		}
		return true
	default:
		panic("unhandled CType")
	}
}

type CValue interface{ Type() CType }
type CType interface{ New() CValue }

type CFuncType struct {
	Return string
	Params []string
}

type CFuncValue struct {
	typ        CFuncType
	Name       string
	ParamNames []string
}

type CFieldType struct {
	Name string
	Type CType
}

type CStructType struct {
	Fields []CFieldType
}

type CStructValue struct {
	typ    CStructType
	Fields []CValue
}

func (fv CFuncValue) Type() CType   { return fv.typ }
func (sv CStructValue) Type() CType { return sv.typ }

func (ft CFuncType) New() CValue {
	v := &CFuncValue{
		typ:        ft,
		Name:       "",
		ParamNames: make([]string, len(ft.Params)),
	}
	for i := range ft.Params {
		v.ParamNames[i] = defaultName(ft.Params[i], v.ParamNames[:i])
	}
	return v
}

func (st CStructType) New() CValue {
	v := &CStructValue{
		typ:    st,
		Fields: make([]CValue, len(st.Fields)),
	}
	for i := range st.Fields {
		if st.Fields[i].Type != nil {
			v.Fields[i] = st.Fields[i].Type.New()
		}
	}
	return v
}

func (fv *CFuncValue) setType(ft CFuncType) {
	fv.typ = ft
	// special case for void
	if len(ft.Params) == 1 && ft.Params[0] == "void" {
		fv.ParamNames[0] = ""
		return
	}
	if len(fv.ParamNames) < len(ft.Params) {
		// orig had too few params; fill in the rest with default names
		for len(fv.ParamNames) < len(ft.Params) {
			fv.ParamNames = append(fv.ParamNames, defaultName(ft.Params[len(fv.ParamNames)], fv.ParamNames))
		}
	} else if len(fv.ParamNames) > len(ft.Params) {
		// orig had too many params; try to preserve what they had before
		fv.ParamNames = fv.ParamNames[:len(ft.Params)]
	}
}

func (ft *CFuncType) isUnk() bool {
	return ft.Return == "UNK_RET" ||
		(len(ft.Params) == 1 && ft.Params[0] == "UNK_PARAMS")
}

func (fv CFuncValue) String() string {
	var params []string
	for i := range fv.ParamNames {
		if fv.ParamNames[i] == "" {
			params = append(params, fv.typ.Params[i]) // just type
		} else {
			params = append(params, fmt.Sprintf("%s %s", fv.typ.Params[i], fv.ParamNames[i]))
		}
	}
	return fmt.Sprintf("%s %s(%s)", fv.typ.Return, fv.Name, strings.Join(params, ", "))
}

var ignoredField = CFieldType{}

var structTypes = map[string]CStructType{
	"ItemStateTable": {
		Fields: []CFieldType{
			ignoredField, // enum_t
			{"animated", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"physics_updated", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"collided", &CFuncType{"bool", []string{"Item_GObj*"}}},
		},
	},
	"ItemLogicTable": {
		Fields: []CFieldType{
			ignoredField, // ItemStateTable*
			{"spawned", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"destroyed", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"picked_up", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"dropped", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"thrown", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"dmg_dealt", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"dmg_received", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"entered_air", &CFuncType{"void", []string{"Item_GObj*"}}},
			{"reflected", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"clanked", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"absorbed", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"shield_bounced", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"hit_shield", &CFuncType{"bool", []string{"Item_GObj*"}}},
			{"evt_unk", &CFuncType{"void", []string{"Item_GObj*", "Item_GObj*"}}},
		},
	},
	"sdata_ItemGXLink": {
		Fields: []CFieldType{
			{"x0_renderFunc", &CFuncType{"void", []string{"HSD_GObj*", "int"}}},
		},
	},

	"StageCallbacks": {
		Fields: []CFieldType{
			{"callback0", &CFuncType{"void", []string{"Ground_GObj*"}}},
			{"callback1", &CFuncType{"bool", []string{"Ground_GObj*"}}},
			{"callback2", &CFuncType{"void", []string{"Ground_GObj*"}}},
			{"callback3", &CFuncType{"void", []string{"Ground_GObj*"}}},
			ignoredField, // u32
		},
	},

	"MajorScene": {
		Fields: []CFieldType{
			ignoredField, // u8 + u8 + padding
			{"Load", &CFuncType{"void", []string{"void"}}},
			{"Unload", &CFuncType{"void", []string{"void"}}},
			{"Init", &CFuncType{"void", []string{"void"}}},
			ignoredField, // MinorScene*
		},
	},

	"MinorScene": {
		Fields: []CFieldType{
			ignoredField, // u8 + u8 + u16
			{"Prep", &CFuncType{"void", []string{"MinorScene*"}}},
			{"Decide", &CFuncType{"void", []string{"MinorScene*"}}},
		},
	},

	"MinorSceneHandler": {
		Fields: []CFieldType{
			ignoredField,
			{"OnFrame", &CFuncType{"void", []string{"void"}}},
			{"OnLoad", &CFuncType{"void", []string{"void*"}}},
			{"OnLeave", &CFuncType{"void", []string{"void*"}}},
			{"unk_func", &CFuncType{"void", []string{"void"}}},
		},
	},

	"StageData": {
		Fields: []CFieldType{
			ignoredField, // u32
			ignoredField, // StageCallbacks*
			ignoredField, // char*
			{"callback0", &CFuncType{"void", []string{"void"}}},
			{"callback1", &CFuncType{"void", []string{"bool"}}},
			{"OnLoad", &CFuncType{"void", []string{"void"}}},
			{"OnStart", &CFuncType{"void", []string{"void"}}},
			{"callback4", &CFuncType{"bool", []string{"void"}}},
			{"callback5", &CFuncType{"DynamicsDesc*", []string{"enum_t"}}},
			{"callback6", &CFuncType{"bool", []string{"Vec3*", "int", "HSD_JObj*"}}},
			ignoredField, // u32
			ignoredField, // S16Vec3*
			ignoredField, // size_t
		},
	},

	"gm_803DF94C_t": {
		Fields: []CFieldType{
			{"x0", &CFuncType{"void", []string{"HSD_GObj*"}}},
			{"x4", &CFuncType{"void", []string{"int"}}},
		},
	},
}

func (cs *CStructValue) parse(entries []AsmTableEntry) bool {
	if len(entries) != len(cs.Fields) {
		return false
	}
	for i := range cs.Fields {
		entry := entries[0]
		entries = entries[1:]
		switch f := cs.Fields[i].(type) {
		case *CFuncValue:
			_, err := strconv.Atoi(entry.Value)
			if entry.Value == "NULL" || strings.Trim(entry.Value, "0x") == "" {
				cs.Fields[i] = nil
			} else if err == nil || strings.HasPrefix(entry.Value, "0x") {
				return false
			} else {
				f.Name = entry.Value
			}
		}
	}
	return true
}

func parseTableDecls(path string, tableType string) []string {
	content, err := os.ReadFile(path)
	if err != nil {
		log.Fatalf("Failed to read file %s: %v", path, err)
	}

	var decls []string
	matches := regexp.MustCompile(fmt.Sprintf(`(?s)%s\s+([\w\[\],\s]+)[;=]`, tableType)).FindAllStringSubmatch(string(content), -1)
	for _, match := range matches {
		if len(match) > 1 {
			for _, decl := range strings.Split(match[1], ",") {
				if i := strings.IndexByte(decl, '['); i >= 0 {
					decl = decl[:i]
				}
				decls = append(decls, strings.Trim(strings.TrimSpace(decl), "[]*"))
			}
		}
	}
	return decls
}

func fixSignatures(path string, fnTypes map[string]*CFuncValue, conservative bool) int {
	content, err := os.ReadFile(path)
	if err != nil {
		log.Fatalf("Failed to read file %s: %v", path, err)
	}

	n := 0
	fix := func(name string, ft CFuncType) {
		changed := false
		lines := bytes.Split(content, []byte("\n"))
		for i, line := range lines {
			if raw, ok := locateFunc(name, line); ok {
				sig := parseCFuncValue(raw)
				if conservative && !sig.typ.isUnk() {
					continue
				}
				if !equivalent(sig.typ, ft) {
					sig.setType(ft)
					lines[i] = bytes.Replace(lines[i], raw, []byte(sig.String()), 1)
					changed = true
				}
			}
		}
		if changed {
			content = bytes.Join(lines, []byte("\n"))
			n++
		}
	}

	for name, ft := range fnTypes {
		if bytes.Contains(content, []byte(name)) {
			fix(name, ft.typ)
		}
	}
	if n > 0 {
		if err := os.WriteFile(path, content, 0644); err != nil {
			log.Fatalf("Failed to write file %s: %v", path, err)
		}
	}
	return n
}

func locateFunc(name string, line []byte) ([]byte, bool) {
	i := bytes.Index(line, []byte(name+"("))
	if i < 0 {
		return nil, false
	}
	retEnd := bytes.LastIndexByte(line[:i], ' ')
	if retEnd < 0 {
		// TODO: handle multi-line signatures
		return nil, false
	}
	retStart := retEnd - 1
	for retStart > 0 && isIdentByte(line[retStart-1]) {
		retStart--
	}
	returnType := string(bytes.TrimSpace(line[retStart:retEnd]))
	if returnType == "" || returnType == "return" {
		// actually a function call, not a declaration
		return nil, false
	}
	paramStart := bytes.IndexByte(line, '(')
	paramEnd := bytes.IndexByte(line, ')')
	if paramStart < 0 || paramEnd < 0 {
		// TODO: handle multi-line signatures
		return nil, false
	}
	return line[retStart : paramEnd+1], true
}

func parseCFuncValue(src []byte) *CFuncValue {
	returnType := string(bytes.TrimSpace(src[:bytes.IndexByte(src, ' ')]))
	name := string(bytes.TrimSpace(src[bytes.IndexByte(src, ' ')+1 : bytes.IndexByte(src, '(')]))

	paramStart := bytes.IndexByte(src, '(') + 1
	paramEnd := bytes.IndexByte(src, ')')
	params := bytes.Split(src[paramStart:paramEnd], []byte(","))
	isDecl := strings.Contains(string(src), ";")
	var paramTypes, paramNames []string
	for _, param := range params {
		typ, name, _ := strings.Cut(strings.TrimSpace(string(param)), " ")
		switch typ {
		case "struct", "unsigned":
			var moreTyp string
			moreTyp, name, _ = strings.Cut(strings.TrimSpace(name), " ")
			typ += " " + moreTyp
		}
		if strings.HasPrefix(name, "*") {
			typ += "*"
			name = strings.TrimPrefix(name, "*")
		}
		if name == "" && !isDecl {
			name = defaultName(typ, paramNames)
		}
		paramTypes = append(paramTypes, typ)
		paramNames = append(paramNames, name)
	}
	return &CFuncValue{
		typ:        CFuncType{Return: returnType, Params: paramTypes},
		Name:       name,
		ParamNames: paramNames,
	}
}

func isIdentByte(b byte) bool {
	return b == '_' ||
		(b >= 'a' && b <= 'z') ||
		(b >= 'A' && b <= 'Z') ||
		(b >= '0' && b <= '9')
}

package fh

import (
	"bufio"
	"embed"
	"fmt"
	"os"
	"strconv"
	"strings"
	"text/template"
	"time"
)

var GREEN string = "\033[38;5;184m"
var ORANGE string = "\033[38;5;202m"
var GRAY string = "\033[38;5;109m"
var RED string = "\033[38;5;160m"
var RESET string = "\033[0m"

//go:embed templates
var basefiles embed.FS

type UserData struct {
	PJName   string
	Language string
	License  string
	LicNum   string
	Author   string
	Year     string
	VCS      string
	Pwd      string
	Build    string
}

func isBetween(num, min, max int) bool {
	//exclusive on top
	if (num >= min) && (num < max) {
		return true
	} else {
		return false
	}
}

func ErrCheck(err error) {
	if nil != err {
		fmt.Printf("Error: %v\n", err)
		os.Exit(-1)
	}
}

func getTime() string {
	t := time.Now()
	currentyear := t.Year()

	return strconv.Itoa(currentyear)
}

func SanitizeStrings(dirtyString *string) {

	*dirtyString = strings.ReplaceAll(*dirtyString, "\n", "")
	*dirtyString = strings.TrimSpace(*dirtyString)
}

func getData(ud *UserData) {
	var err error

	ud.Pwd, err = os.Getwd()
	ErrCheck(err)

	reader := bufio.NewReader(os.Stdin)
	fmt.Printf(GREEN + "Project" + RESET + " name:")
	ud.PJName, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.PJName)

	fmt.Printf(GREEN + "Language:" + RESET)
	ud.Language, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.Language)

	if ud.Language != "go" {
		fmt.Printf(GREEN + "Build system:" + RESET)
		ud.Build, err = reader.ReadString('\n')
		ErrCheck(err)
		SanitizeStrings(&ud.Build)
	}

	fmt.Printf(GREEN + "License:\n" + RESET)
	fmt.Printf("\t" + RED + "[B]SD:" + RESET + "\n\t" + ORANGE + "[G]PL:" + RESET + "\n\t[N]one\n")
	fmt.Printf("Selection: ")
	ud.License, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.License)
	if ud.License[0] == 'b' || ud.License[0] == 'B' {
		fmt.Printf("Which " + RED + "BSD" + RESET + " license do you want? ")
		ud.LicNum, err = reader.ReadString('\n')
		ErrCheck(err)
		SanitizeStrings(&ud.LicNum)
		dummy, _ := strconv.Atoi(ud.LicNum)
		if !isBetween(dummy, 1, 5) {
			fmt.Printf("Defaulting to BSD 3\n")
		}
	} else if ud.License[0] == 'g' || ud.License[0] == 'G' {
		fmt.Printf("Which " + ORANGE + "GPL" + RESET + " license do you want? ")
		ud.LicNum, err = reader.ReadString('\n')
		ErrCheck(err)
		SanitizeStrings(&ud.LicNum)
	}

	fmt.Print(GREEN + "Author:" + RESET)
	ud.Author, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.Author)

	fmt.Print(ORANGE + "Git" + RESET + " or " + GRAY + "HG?" + RESET)
	ud.VCS, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.VCS)
}

/********************************
 * File and directories
 ********************************/
func DirectoryCreation(patheroo string) {
	_, err := os.Stat(patheroo)
	if true == os.IsNotExist(err) {
		os.Mkdir(patheroo, 0700)
	} else {
		fmt.Printf("Could not create %s already EXISTS\n", strings.ReplaceAll(patheroo, "./", ""))
	}
}

func FileExistence(patheroo string) bool {
	_, err := os.Stat(patheroo)
	if true == os.IsNotExist(err) {
		return true
	} else {
		return false
	}
}

/********************************
 * Build systems
 ********************************/
func BuildSystemC(ud UserData) {
	switch ud.Build {
	case "cmake":
		TemplateHandling("templates/CMakeLists.tmpl", "./CMakeLists.txt", ud)
	case "meson":
		TemplateHandling("templates/c.meson.tmpl", "./meson.build", ud)
	case "premake":
		TemplateHandling("templates/premake5.tmpl", "./premake5.lua", ud)
	default:
		fmt.Printf("\nDefaulting to CMake!\n")
		TemplateHandling("templates/CMakeLists.tmpl", "./CMakeLists.txt", ud)
	}
}

func BuildSystemCXX(ud UserData) {
	switch ud.Build {
	case "cmake":
		TemplateHandling("templates/CMakeLists.cxx.tmpl", "./CMakeLists.txt", ud)
	case "meson":
		TemplateHandling("templates/cxx.meson.tmpl", "./meson.build", ud)
	case "premake":
		TemplateHandling("templates/premake5.cxx.tmpl", "./premake5.lua", ud)
	default:
		fmt.Printf("\nDefaulting to CMake!\n")
		TemplateHandling("templates/CMakeLists.cxx.tmpl", "./CMakeLists.txt", ud)
	}
}

/********************************
 * templates
 ********************************/

func TemplateHandling(tmplPath, filePath string, ud UserData) {
	if !FileExistence(filePath) {
		fmt.Printf("File %s already exists\n", strings.ReplaceAll(filePath, "./", ""))
		return
	}

	t, err := template.ParseFS(basefiles, tmplPath)
	ErrCheck(err)
	f, err := os.Create(filePath)
	defer f.Close()

	ErrCheck(err)
	err = t.Execute(f, ud)
	ErrCheck(err)
}

/********************************
 * version control system
 ********************************/
func vcsHandling(ud UserData) {
	switch ud.VCS {
	case "hg":
		hgFiles(ud)
	case "git":
		gitFiles(ud)
	case "both":
		fmt.Println("Using HG and Git!")
		gitFiles(ud)
		hgFiles(ud)
	default:
		fmt.Println("Defaulting to git!")
		hgFiles(ud)
	}
}
func gitFiles(ud UserData) {
	TemplateHandling("templates/gitignore.tmpl", "./.gitignore", ud)
	TemplateHandling("templates/gitattributes.tmpl", "./.gitattributes", ud)
}
func hgFiles(ud UserData) {
	TemplateHandling("templates/hgignore.tmpl", "./.hgignore", ud)
}

/********************************
 * Language files
 ********************************/
func cFiles(ud UserData) {
	BuildSystemC(ud)
	TemplateHandling("templates/main.c.tmpl", "./src/main.c", ud)
	TemplateHandling("templates/clang-format.tmpl", "./.clang-format", ud)
}
func cppFiles(ud UserData) {
	BuildSystemCXX(ud)
	TemplateHandling("templates/main.cxx.tmpl", "./src/main.cxx", ud)
	TemplateHandling("templates/clang-format.tmpl", "./.clang-format", ud)
}
func goFiles(ud UserData) {
	TemplateHandling("templates/taskfile.tmpl", "./Taskfile.yml", ud)
	TemplateHandling("templates/main.go.tmpl", "./src/main.go", ud)
}

func FileCreation(ud UserData) {
	switch ud.Language {
	case "c":
		cFiles(ud)
	case "cpp":
		cppFiles(ud)
	case "go":
		goFiles(ud)
	default:
		fmt.Printf("\nDefaulting to C!\n")
		cFiles(ud)
	}
}

func LicenseCreation(ud UserData) {
	switch ud.License {
	case "gpl":
		switch ud.LicNum {
		case "2":
			TemplateHandling("templates/gpl2.tmpl", "./LICENSE", ud)
		case "2 or later":
			TemplateHandling("templates/gpl2orl.tmpl", "./LICENSE", ud)
		case "3":
			TemplateHandling("templates/gpl3.tmpl", "./LICENSE", ud)
		case "3 or later":
			TemplateHandling("templates/gpl3orl.tmpl", "./LICENSE", ud)
		default:
			TemplateHandling("templates/gpl3.tmpl", "./LICENSE", ud)
		}
	case "g":
		switch ud.LicNum {
		case "2":
			TemplateHandling("templates/gpl2.tmpl", "./LICENSE", ud)
		case "2 or later":
			TemplateHandling("templates/gpl2orl.tmpl", "./LICENSE", ud)
		case "3":
			TemplateHandling("templates/gpl3.tmpl", "./LICENSE", ud)
		case "3 or later":
			TemplateHandling("templates/gpl3orl.tmpl", "./LICENSE", ud)
		default:
			TemplateHandling("templates/gpl3.tmpl", "./LICENSE", ud)
		}

	case "bsd":
		switch ud.LicNum {
		case "1":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		case "2":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		case "3":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		case "4":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		default:
			TemplateHandling("templates/bsd3.tmpl", "./LICENSE", ud)
		}
	case "b":
		switch ud.LicNum {
		case "1":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		case "2":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		case "3":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		case "4":
			TemplateHandling("templates/bsd1.tmpl", "./LICENSE", ud)
		default:
			TemplateHandling("templates/bsd3.tmpl", "./LICENSE", ud)
		}
	default:
		fmt.Println("Defaulting to GPL3")
		TemplateHandling("templates/gpl3.tmpl", "./LICENSE", ud)
	}
}

func FileHandling(ud UserData) {
	DirectoryCreation("./include")
	DirectoryCreation("./lib")
	DirectoryCreation("./src")
	FileCreation(ud)
	LicenseCreation(ud)
	vcsHandling(ud)
	TemplateHandling("templates/README.tmpl", "./README.md", ud)
}

func InitETR() {
	var empty UserData
	if len(os.Args) > 1 {
		switch os.Args[1] {
		case "git":
			fmt.Printf("Only creating" + GREEN + " gitignore" + RESET + " and" + GREEN + " gitattributes.\n" + RESET)
			gitFiles(empty)
			os.Exit(0)
		case "hg":
			fmt.Printf("Only creating" + GREEN + " hgignore.\n" + RESET)
			hgFiles(empty)
			os.Exit(0)
		case "both":
			fmt.Printf("Only creating" + GREEN + " gitignore, gitattributes" + RESET + " and" + GREEN + " hgignore.\n" + RESET)
			hgFiles(empty)
			gitFiles(empty)
			os.Exit(0)
		default:
			fmt.Printf("If you're going to pass arguments, the only usage is for\nadding gitignore (and gittributes), hgignore or both of them.\n")
			os.Exit(1)
		}
	}

	var ud UserData

	getData(&ud)
	ud.Year = getTime()

	FileHandling(ud)
}

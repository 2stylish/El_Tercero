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

//go:embed templates
var basefiles embed.FS

type UserData struct {
	PJName   string
	Language string
	License  string
	LicNum   string
	Author   string
	Year     string
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
		fmt.Printf("Error reading: %v\n", err)
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

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Project name:")
	ud.PJName, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.PJName)

	fmt.Print("Language:")
	ud.Language, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.Language)

	fmt.Printf("License:\n")
	fmt.Printf("\tBSD:\n\t[N]one\n")
	fmt.Printf("Selection: ")
	ud.License, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.License)
	if ud.License[0] == 'b' || ud.License[0] == 'B' {
		fmt.Printf("Which BSD license do you want? ")
		ud.LicNum, err = reader.ReadString('\n')
		ErrCheck(err)
		SanitizeStrings(&ud.LicNum)
		dummy, _ := strconv.Atoi(ud.LicNum)
		if !isBetween(dummy, 1, 5) {
			fmt.Printf("Defaulting to BSD 3\n")
		}
	}

	fmt.Print("Author:")
	ud.Author, err = reader.ReadString('\n')
	ErrCheck(err)
	SanitizeStrings(&ud.Author)
}

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

func TemplateHandling(tmplPath, filePath string, ud UserData) {
	if !FileExistence(filePath) {
		fmt.Printf("File %s already exists\n", strings.ReplaceAll(filePath, "./", ""))
		return
	}

	t, err := template.ParseFS(basefiles, tmplPath)
	ErrCheck(err)
	f, err := os.Create(filePath)

	ErrCheck(err)
	err = t.Execute(f, ud)
	ErrCheck(err)
	defer f.Close()
}

func FileCreation(ud UserData) {
	switch ud.Language {
	case "c":
		TemplateHandling("templates/gitignore.tmpl", "./.gitignore", ud)
		TemplateHandling("templates/gitattributes.tmpl", "./.gitattributes", ud)
		TemplateHandling("templates/c.meson.tmpl", "./meson.build", ud)
		TemplateHandling("templates/README.tmpl", "./README.md", ud)
		TemplateHandling("templates/main.c.tmpl", "./src/main.c", ud)
	case "cpp":
		TemplateHandling("templates/gitignore.tmpl", "./.gitignore", ud)
		TemplateHandling("templates/gitattributes.tmpl", "./.gitattributes", ud)
		TemplateHandling("templates/cxx.meson.tmpl", "./meson.build", ud)
		TemplateHandling("templates/README.tmpl", "./README.md", ud)
		TemplateHandling("templates/main.cxx.tmpl", "./src/main.cxx", ud)
	case "go":
		TemplateHandling("templates/gitignore.tmpl", "./.gitignore", ud)
		TemplateHandling("templates/gitattributes.tmpl", "./.gitattributes", ud)
		TemplateHandling("templates/README.tmpl", "./README.md", ud)
		TemplateHandling("templates/main.go.tmpl", "./src/main.go", ud)
	default:
		fmt.Println("Defaulting to C!")
		TemplateHandling("templates/gitignore.tmpl", "./.gitignore", ud)
		TemplateHandling("templates/gitattributes.tmpl", "./.gitattributes", ud)
		TemplateHandling("templates/c.meson.tmpl", "./meson.build", ud)
		TemplateHandling("templates/README.tmpl", "./README.md", ud)
		TemplateHandling("templates/main.c.tmpl", "./src/main.c", ud)
	}
}

func LicenseCreation(ud UserData) {
	switch ud.License {
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
	}
}

func FileHandling(ud UserData) {
	DirectoryCreation("./src")
	DirectoryCreation("./lib")
	FileCreation(ud)
	LicenseCreation(ud)
}

func InitETR() {
	if len(os.Args) > 1 {
		fmt.Println("Who told you to put flags? lol")
		fmt.Println("Exiting CUZ FUCK YOU")
		os.Exit(-1)
	}

	var ud UserData

	getData(&ud)
	ud.Year = getTime()

	FileHandling(ud)
}

package main

/* https://golang.org/cmd/cgo/#hdr-Go_references_to_C */

// typedef int (*intFunc) ();
import "C"
import "fmt"

//export invokeGoEncrypt
func invokeGoEncrypt() {
	fmt.Printf("  go encrypt\n")
}

func main() {}

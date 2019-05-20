package main 

import "os/exec"


func main() {

	exec.Command("/bin/echo ", "Hello, World!") 
} 

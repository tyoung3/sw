package github.com/tyoung3/sw

import "fmt"
import "sync"

/*
Print prints integers and strings received from port 0, prefixed
with the process identifier(arg[0]) string,
*/
func Print(wg *sync.WaitGroup,
	arg []string,
	c chan interface{}) {

	defer wg.Done()
	s := arg[0]

	for {
		ip, ok := <-c
		if ok != true {
			return
		}
		switch ip.(type) {
		case string:
			fmt.Println(s, ip)
		case int:
			fmt.Println(s, "Int:", ip)
		default:
			fmt.Println(s, "type mismatch")
		}
	}
}

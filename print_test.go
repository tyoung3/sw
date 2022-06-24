package github.com/tyoung3/sw

import "testing"
import "fmt"
import "sync"

func TestPrint(t *testing.T) {
	var wg sync.WaitGroup
	arg := []string{"Print"}

	fmt.Println("TestPrint")
	c := make(chan interface{})

	go func() {
		c <- 7
		c <- 11
		c <- "OK?"
		close(c)
	}()

	wg.Add(1)
	go Print(&wg, arg, c)
	fmt.Println("TestPrint wait c ")
	wg.Wait()
	fmt.Println("TestPrint done.")
}

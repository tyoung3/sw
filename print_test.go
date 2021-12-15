package sw

import "testing"
import "fmt"
import "sync"

func TestPrint(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup
	arg := []string{"TestPrint", "xx"}

	fmt.Println("TestPrint")
	cs = append(cs, make(chan interface{}))
	c := cs[0]

	go func() {
		c <- 7
		c <- 11
		c <- "OK?"
		close(c)
	}()

	wg.Add(1)
	go Print(&wg, arg, cs)
	fmt.Println("TestPrint wait c ")
	wg.Wait()
	fmt.Println("TestPrint done.")
}

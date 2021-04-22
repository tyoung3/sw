package swbase

import "testing"
import "fmt"
import "sync"

func TestGen(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestGen", "7"}

	fmt.Println(arg[0])
	cs = append(cs, make(chan interface{}))
	c := cs[0]

	go func() {
		for {
			s, ok := <-c
			if ok == true {
				fmt.Println("TestGen.go", s)
			} else {
				fmt.Println("TestGen Ended")
				return
			}
		}
	}()

	wg.Add(1)
	go Gen(&wg, arg, cs)
	wg.Wait()

}

package sw

import "testing"
import "fmt"
import "sync"

func TestGens(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestGens", "3"}

	fmt.Println(arg[0])
	cs = append(cs, make(chan interface{}))
	c := cs[0]

	go func() {
		for {
			s, ok := <-c
			if ok == true {
				fmt.Println("TestGens.go", s)
			} else {
				fmt.Println("TestGens Ended")
				return
			}
		}
	}()

	wg.Add(1)
	go Gens(&wg, arg, cs)
	wg.Wait()

}

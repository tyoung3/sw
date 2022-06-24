package github.com/tyoung3/sw

import "testing"
import "fmt"
import "sync"

func TestGens(t *testing.T) {
	var wg sync.WaitGroup

	arg := []string{"TestGens", "3"}

	fmt.Println(arg[0])
	c := make(chan interface{})

	wg.Add(2)
	
	go func() {
	  defer wg.Done()
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
	
	go Gens(&wg, arg, c)
	wg.Wait()

}

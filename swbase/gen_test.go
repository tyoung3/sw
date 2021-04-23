package swbase

/*
	Gen Number Start Increment
	Emit Number integer IPs bginning with Start, incementing IPs by Increment.
	E.x Gen "5" "2" "3" should emit 2 5 8 11 14
*/

import "testing"
import "fmt"
import "sync"

func TestGen(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"ABC", "3", "5", "7"}

	cs = append(cs, make(chan interface{}))
	c := cs[0]

	go func() {
		defer wg.Done()
		for {
			s, ok := <-c
			if ok == true {
				fmt.Println("tGen", s)
			} else {
				fmt.Println("TestGen Ended")
				return
			}
		}
	}()

	wg.Add(2)
	go Gen(&wg, arg, cs)
	wg.Wait()

}

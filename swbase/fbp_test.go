package swbase

import (
	"sync"
	"testing"
)

func TestFBP(t *testing.T) {
	var cs []chan interface{}
	var wg1 sync.WaitGroup

	for i := 0; i < 6; i++ {
		cs = append(cs, make(chan interface{}, 1))
	}

	Launch(&wg1, []string{"OPT"}, Print, cs[0:1])

	// wg1.Add(1)
	go func() {
		defer wg1.Done()
		cs[0] <- "TestFBP"
	}()

	wg1.Wait()

}

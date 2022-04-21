package swutility

import (
	"fmt"
	"github.com/tyoung3/sw"
	"sync"
	"testing"
)

func TestCollate(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	fmt.Println("TestCollate")
	ch0 := make(chan interface{})
	ch1 := make(chan interface{})
	ch2 := make(chan interface{})
	ch3 := make(chan interface{})
	ch4 := make(chan interface{})
	ch5 := make(chan interface{})
	cs = append(cs, ch0)
	cs = append(cs, ch1)
	cs = append(cs, ch2)
	cs = append(cs, ch3)
	cs = append(cs, ch4)
	cs = append(cs, ch5)

	wg.Add(7)
	
	go sw.Print(&wg, []string{"Match0"}, ch2)
	go sw.Print(&wg, []string{"Match1"}, ch3)
	go sw.Print(&wg, []string{"Miss0"},  ch4)
	go sw.Print(&wg, []string{"Miss1"},  ch5)

	go func() {
		defer close(cs[1])
		defer wg.Done()
		ch1 <- 3
		ch1 <- 6
		ch1 <- 9
		ch1 <- 12
		ch1 <- 12
		ch1 <- 15
	}()

	go func() {
		defer close(cs[0])
		defer wg.Done()
		ch0 <- 2
		ch0 <- 4
		ch0 <- 6
		ch0 <- 6
		ch0 <- 8
		ch0 <- 10
		ch0 <- 12
		ch0 <- 14
		ch0 <- 17
	}()

	go Collate (&wg, []string{"Collate"}, cs[0:6])
  fmt.Println("TestCollate Waiting")
	wg.Wait()
  fmt.Println("TestCollate Ended")
}

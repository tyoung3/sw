package swutility

import (
	"fmt"
	sw "github.com/tyoung3/sw"
	"sync"
	"testing"
)

func TestCollate(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	fmt.Println("TestCollate2:")
	cs = append(cs, make(chan interface{}))
	cs = append(cs, make(chan interface{}))
	cs = append(cs, make(chan interface{}))
	cs = append(cs, make(chan interface{}))
	cs = append(cs, make(chan interface{}))
	cs = append(cs, make(chan interface{}))

	sw.Launch(&wg, []string{"Match0"}, sw.Print, cs[2:3])
	sw.Launch(&wg, []string{"Match1"}, sw.Print, cs[3:4])
	sw.Launch(&wg, []string{"Miss0"}, sw.Print, cs[4:5])
	sw.Launch(&wg, []string{"Miss1"}, sw.Print, cs[5:6])

	wg.Add(1)
	go func() {
		cs[1] <- 3
		cs[1] <- 6
		cs[1] <- 9
		cs[1] <- 12
		cs[1] <- 12
		cs[1] <- 15
		close(cs[1])
		fmt.Println("End1")
		wg.Done()
	}()

	wg.Add(1)
	go func() {
		cs[0] <- 2
		cs[0] <- 4
		cs[0] <- 6
		cs[0] <- 6
		cs[0] <- 8
		cs[0] <- 10
		cs[0] <- 12
		cs[0] <- 14
		cs[0] <- 17
		close(cs[0])
		fmt.Println("End0")
		wg.Done()
	}()

	//wg.Add(1)
	go sw.Launch(&wg, []string{"Collate"}, Collate, cs[0:6])
	wg.Wait()

}

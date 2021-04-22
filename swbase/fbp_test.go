package swbase

import (
	"sync"
	"testing"
)

func TestFBP(t *testing.T) {
	var cs []chan interface{}
	var wg1 sync.WaitGroup

	for i := 0; i < 6; i++ {
		cs = append(cs, make(chan interface{}, 1024))
	}

	Launch(&wg1, []string{"P1"},      Print, cs[3:4])
	Launch(&wg1, []string{"Q1", "7"}, Gen, cs[3:4])

	Launch(&wg1, []string{"P2"},      Print, cs[0:1])
	Launch(&wg1, []string{"Q2", "2"}, Gen, cs[1:2])
	Launch(&wg1, []string{"Q3", "3"}, Gen, cs[2:3])
	wg1.Add(1)
	MergeInt(&wg1, cs[0], cs[1], cs[2])

	wg1.Wait()

}

/*
	/* NETWORK:
			Partition 1:
	     (Q1 Gen)out1 -> in1(A Print)

	     	Partition 2:
		 (Q2 Gen)out1 -> in1(B Print)
	     (Q3 Gen)out1 -> in1(B Print)

*/

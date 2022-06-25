package github.com/tyoung3/sw

/* NETWORK:
   (Q Gen)out1 -> in1(S split)out1 -> in1(A1 Print)
   (S)out2                           -> in1(A2 Print)
   (S)out3					       -> in1(A3 Print)
*/

import (
	"sync"
	"testing"
)

func TestSplit2(t *testing.T) {
	var cs []chan interface{}
	var wg1 sync.WaitGroup

	for i := 0; i < 4; i++ {
		cs = append(cs, make(chan interface{}, 1024))
	}
   
	cs0 := make(chan interface{})
	cs1 := make(chan interface{})
	cs2 := make(chan interface{})
	cs3 := make(chan interface{})
	
	// wg1.Add(5)
	
	go Split(&wg1, []string{"S"}, cs[0:4])
	go Gens(&wg1, []string{"Q", "3"}, cs0)
	go Print(&wg1, []string{"A2"}, cs1)
	go Print(&wg1, []string{"A1"}, cs2)
	go Print(&wg1, []string{"A3"}, cs3)

	wg1.Wait()

}

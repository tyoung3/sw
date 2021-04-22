package swbase

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

	// wg1.Add(1)
	go Launch(&wg1, []string{"S"}, Split, cs[0:4])
	Launch(&wg1, []string{"Q", "3"},  Gen, cs[0:1])
	Launch(&wg1, []string{"A2"},  Print, cs[1:2])
	Launch(&wg1, []string{"A1"},  Print, cs[2:3])
	Launch(&wg1, []string{"A3"},  Print, cs[3:4])

	wg1.Wait()

}

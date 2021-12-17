package sw

/*  	Network
		(G2 Gen "2")out -> in1(M Join) -> in(Sink Print)
        (G3 Gen "3")out -> in2(M)
        (G5 Gen "5")out -> in3(M)
*/

import "testing"
import "fmt"
import "sync"

func TestJoin(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	for i := 0; i < 4; i++ {
		cs = append(cs, make(chan interface{}))
	}

	fmt.Println("Testing Join-0.0.3")
	wg.Add(1)
	go Join(&wg, []string{"Join"}, cs[0:4])
	Launch(&wg, []string{"G2", "5", "0", "2"}, Gen, cs[1:2])
	Launch(&wg, []string{"G3", "3", "0", "3"}, Gen, cs[2:3])
	Launch(&wg, []string{"G5", "2", "0", "5"}, Gen, cs[3:4])
	Launch(&wg, []string{"Sink"}, Print, cs[0:1])

	fmt.Println("TestJoin waiting")
	wg.Wait()
	fmt.Println("TestJoin ended")
}

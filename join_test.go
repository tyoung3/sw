package github.com/tyoung3/sw

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

	fmt.Println("Testing Join-0.28.0")
	
	cs0 := make(chan interface{})
	cs1 := make(chan interface{})
	cs2 := make(chan interface{})
	cs3 := make(chan interface{})
	
	cs = append(cs,cs0)
	cs = append(cs,cs1)
	cs = append(cs,cs2)
	cs = append(cs,cs3)
		
	wg.Add(5)
	
	go Join(&wg,  []string{"Join"}, cs[0:4])
	go Gen(&wg,   []string{"G2", "5", "0", "2"}, cs1)
	go Gen(&wg,   []string{"G3", "3", "0", "3"}, cs2)
	go Gen(&wg,   []string{"G5", "2", "0", "5"}, cs3)
	go Print(&wg, []string{"Sink"}, cs0)

	fmt.Println("TestJoin waiting")
	wg.Wait()
	fmt.Println("TestJoin ended")
}

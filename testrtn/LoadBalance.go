package testrtn

/*  Generated StreamWork component, LoadBalance,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        1  input  ports
        3 output ports
*/

import (
	"sync"
)

// LoadBalance is @todo undocumented
func LoadBalance(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	
	var wg2 sync.WaitGroup
	wg2.Add(4)

	go Send(cs[3], &wg2, arg, 3)
	go Send(cs[2], &wg2, arg, 2)
	go Send(cs[1], &wg2, arg, 1)
	go Recv(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

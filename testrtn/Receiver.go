package testrtn

/*  Generated StreamWork component, Receiver,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        1  input  ports
        0 output ports
*/

import (
	"sync"
)

// Receiver is @todo undocumented
func Receiver(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	

	var wg2 sync.WaitGroup
	wg2.Add(1)

	Recv(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

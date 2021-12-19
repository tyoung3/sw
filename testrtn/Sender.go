package testrtn

/*  Generated StreamWork component, Sender,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        0  input  ports
        1 output ports
*/

import (
	"sync"
)

// Sender is @todo undocumented
func Sender(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	

	var wg2 sync.WaitGroup
	wg2.Add(1)

	Send(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

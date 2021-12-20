package testrtn

/*  Generated StreamWork component, Sender,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        0  input  ports
        1 output ports
*/

import (
	"sync"
        "strconv"
)

// testrtn/Sender StreamWork component mimics github.com/jpaulm/compontents/testrtn/Sender
func Sender(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	cfg := PkgConfig()
	//count, _ := cfg.IntOr("testrtn/github.com/tyoung3/sw/testrtn.count", 1)
	count, _ := cfg.IntOr("count", 1)
	
	var wg2 sync.WaitGroup
	l := len(arg)
	
	if l > 1 {
		count, _ = strconv.Atoi(arg[1])  // Override count with param 1
	}
		
	count=3  			// @todo Fix config later 
	for count > 0  {
		wg2.Add(1)
		Send(cs[0], &wg2, arg, 0)
		wg2.Wait()
		count = count  - 1
	}	
}

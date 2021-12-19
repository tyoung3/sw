package testrtn

/*  Generated StreamWork component, DelayedReceiver,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        1  input  ports
        0 output ports
*/

import (
	_ "fmt"
	"sync"
)

// DelayedReceiver is @todo undocumented
func DelayedReceiver(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	//cfg := PkgConfig()
	//bs, _ := cfg.IntOr("testrtn/github.com/tyoung3/sw/testrtn.buffersize", 1)
	//seqno, _ := cfg.IntOr("testrtn/github.com/tyoung3/sw/testrtn.seqno", 1)
	//title, _ := cfg.StringOr("testrtn/github.com/tyoung3/sw/testrtn.title", "n/a")
	// version := "v0.0.0"


	var wg2 sync.WaitGroup
	wg2.Add(1)

	Recv(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

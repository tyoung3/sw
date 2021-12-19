package testrtn

/*  Generated StreamWork component, LoadBalance,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        1  input  ports
        3 output ports
*/

import (
	"fmt"
	"github.com/tyoung3/sw/testrtn"
	"sync"
)

// LoadBalance is @todo undocumented
func LoadBalance(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	cfg := swbal.PkgConfig()
	bs, _ := cfg.IntOr("swbal/github.com/tyoung3/sw/testrtn.buffersize", 1)
	seqno, _ := cfg.IntOr("swbal/github.com/tyoung3/sw/testrtn.seqno", 1)
	title, _ := cfg.StringOr("swbal/github.com/tyoung3/sw/testrtn.title", "n/a")
	version := "v0.0.0"

	fmt.Print(title,
		" \u001b[36mRunning ",
		arg[0], "\t",
		"LoadBalance-",
		version,
		" bs=", bs,
		" seqno: ", seqno)

	fmt.Println(
		"\u001b[0m")

	if seqno != 1234 {
		fmt.Println(
			"\u001b[31mswbal/github.com/tyoung3/sw/gofbp/LoadBalance: Seqno is", seqno, "not = 1234.  Missing config file?\u001b[0m")
	}

	var wg2 sync.WaitGroup
	wg2.Add(4)

	go swbal.Send(cs[3], &wg2, arg, 3)
	go swbal.Send(cs[2], &wg2, arg, 2)
	go swbal.Send(cs[1], &wg2, arg, 1)
	go swbal.Recv(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

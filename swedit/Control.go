package swedit

/*  Generated StreamWork component, Control,
    by sw.sh on Fri Apr 23 02:13:51 PM EDT 2021
        1  input  ports
        2 output ports
*/

import (
	"fmt"
	// "github.com/tyoung3/sw/swedit"
	"sync"
)

func uSend(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()
	var ip update
	
	ip.name =   arg[0]
	ip.kind =  "update"
	ci <- ip
	// ci <- ip
}

func rSend(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()
	var ip update
	
	ip.name =   arg[0]
	ip.kind =  "request"
	ci <- ip
}

func Control(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	cfg := PkgConfig()
	bs, _ := cfg.IntOr("swedit.buffersize", 1)
	seqno, _ := cfg.IntOr("swedit.seqno", 1)
	title, _ := cfg.StringOr("swedit.title", "n/a")
	version := "v0.0.0"

	fmt.Print(title,
		" \u001b[36mRunning ",
		arg[0], "\t",
		"Control-",
		version,
		" bs=", bs,
		" seqno: ", seqno)

	fmt.Println(
		"\u001b[0m")

	if seqno != 1234 {
		fmt.Println(
			"\u001b[31mswedit/Control: Seqno is", seqno, "not = 1234.  Missing config file?\u001b[0m")
	}

	var wg2 sync.WaitGroup
	wg2.Add(3)

	go uSend(cs[2], &wg2, arg, 2)
	go rSend(cs[1], &wg2, arg, 1)
	go Recv(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

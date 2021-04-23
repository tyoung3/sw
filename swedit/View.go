package swedit

/*  Generated StreamWork component, View,
    by sw.sh on Fri Apr 23 02:13:52 PM EDT 2021
        1  input  ports
        1 output ports
*/

import (
	"fmt"
	"sync"
)

func View(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	cfg := PkgConfig()
	bs, _ := cfg.IntOr("swedit.buffersize", 1)
	seqno, _ := cfg.IntOr("swedit.seqno", 1)
	title, _ := cfg.StringOr("swedit.title", "n/a")
	version := "v0.0.0"

	fmt.Print(title,
		" \u001b[36mRunning ",
		arg[0], "\t",
		"View-",
		version,
		" bs=", bs,
		" seqno: ", seqno)

	fmt.Println(
		"\u001b[0m")

	if seqno != 1234 {
		fmt.Println(
			"\u001b[31mswedit/View: Seqno is", seqno, "not = 1234.  Missing config file?\u001b[0m")
	}

	var wg2 sync.WaitGroup
	wg2.Add(3)

	go Send(cs[2], &wg2, arg, 1)
	go Recv(cs[0], &wg2, arg, 0)
	go Recv(cs[1], &wg2, arg, 0)
	wg2.Wait()
}

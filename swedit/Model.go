package swedit

/*  Generated StreamWork component, Model,
    by sw.sh on Fri Apr 23 02:13:52 PM EDT 2021
        2  input  ports
        1 output ports
*/

import (
	"fmt"
	"sync"
)

func Model(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()
	cfg :=  PkgConfig()
	bs, _ := cfg.IntOr("swedit.buffersize", 1)
	seqno, _ := cfg.IntOr("swedit.seqno", 1)
	title, _ := cfg.StringOr("swedit.title", "n/a")
	version := "v0.0.0"

	fmt.Print(title,
		" \u001b[36mRunning ",
		arg[0], "\t",
		"Model-",
		version,
		" bs=", bs,
		" seqno: ", seqno)

	fmt.Println(
		"\u001b[0m")

	if seqno != 1234 {
		fmt.Println(
			"\u001b[31mswedit/Model: Seqno is", seqno, "not = 1234.  Missing config file?\u001b[0m")
	}

	var wg2 sync.WaitGroup
	wg2.Add(2)

	go Send(cs[1], &wg2, arg, 2)
	// go Recv(cs[1], &wg2, arg, 1)
	go Recv(cs[0], &wg2, arg, 0)
	wg2.Wait()
}

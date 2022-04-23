package fileio

/*  Generated StreamWork component, Getfile,
    by swgen.sh on Thu Dec 30 08:58:14 AM EST 2021
        0  input  ports
        1 output ports
*/

import (
	"sync"
)

type FileT struct { /* StreamWork Language  */
        S string /* Statement   */
        L int    /* Line Number -1=File name */
}

// Send SWL to Putfile
func sendSwl(ci chan interface{}, id string, line int) {
	var ip FileT
	ip.S = id
	ip.L = line
	ci <- ip
}

// Getfile is @todo undocumented
func Getfile(wg *sync.WaitGroup, arg []string, ch0 chan interface{}) {

	defer wg.Done()
	// cfg := swe.PkgConfig()
	//bs, _ := cfg.IntOr("swedit/swedit.buffersize", 1)
	//seqno, _ := cfg.IntOr("swedit/swedit.seqno", 1)
	//title, _ := cfg.StringOr("swedit/swedit.title", "n/a")
	// version := "v0.0.0"

	var wg2 sync.WaitGroup
	wg2.Add(0)

	sendSwl(ch0, "SWL from Getfile", 1)
	wg2.Wait()
}

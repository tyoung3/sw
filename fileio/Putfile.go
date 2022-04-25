package fileio

/*  Generated StreamWork component, Putfile,
    by swgen.sh on Thu Dec 30 08:58:14 AM EST 2021
        1  input  ports
        0 output ports
*/

import (
	"fmt"
	// swe "github.com/tyoung3/swedit"
	"log"
	"os"
	"sync"
)

const black = "\u001b[30m"
const red = "\u001b[31m"
const green = "\u001b[32m"
const yellow = "\u001b[33m"
const blue = "\u001b[34m"
const magenta = "\u001b[35m"
const cyan = "\u001b[36m"
const white = "\u001b[37m"
const brightRed = "\u001b[91m" // brightGreen=92, brightYellow ...
const resetColor = "\u001b[0m"

// RecvSwl receives SWL
func getSwl(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()

	var ofile *os.File
	var err error
	var fileName string
	// var len  int

	for {
		ip, ok := <-ci
		if ok != true {
			return
		}
		swl := ip.(FileT)
		if swl.L == -1 {
			// fmt.Println(arg[0], "\topen ",  fileName)
			fileName = swl.S
			ofile, err = os.Create(swl.S)
			if err != nil {
				log.Fatalf("%s%s failed creating file: %s", red, arg[0], err)
			}
			// fmt.Println(arg[0], "\tcreated ",  fileName)
		} else if swl.L == -2 {
			// fmt.Println(arg[0], "\tclose ")
			ofile.Close()
			return
		} else {
			_, err = ofile.WriteString(swl.S + "\n")
			if err != nil {
				fmt.Println(arg[0], "write failed", ofile)
				log.Fatalf("%s%s failed writing,%s, to file, %s; %s%s",
					red, arg[0], swl.S, fileName, err, resetColor)
			}
		}
	} // End for loop
}

// Putfile is @todo undocumented
func Putfile(wg *sync.WaitGroup, arg []string, ch0 chan interface{}) {

	defer wg.Done()
	//cfg := swe.PkgConfig()
	//bs, _ := cfg.IntOr("swedit/swedit.buffersize", 1)
	//seqno, _ := cfg.IntOr("swedit/swedit.seqno", 1)
	//title, _ := cfg.StringOr("swedit/swedit.title", "n/a")
	//version := "v0.0.1"

	var wg2 sync.WaitGroup
	wg2.Add(1)

	getSwl(ch0, &wg2, arg, 0)
	wg2.Wait()
}

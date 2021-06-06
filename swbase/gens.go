package swbase

import "fmt"
import "sync"
import "strconv"

// var Version string = "0.0.0"

/*Gens sends arg[1],  arg[2] long strings to channel cs[0] (out1)
    Strings consist of the process name
   and seq. no; i.e. G3-1, G3-2, etc.

   BUG cannot set length, yet.
*/
func Gens(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {
	var n0 = 7
	var n int
	//var nb int = 80

	defer wg.Done()

	l := len(arg)
	if l > 1 {
		n0, _ = strconv.Atoi(arg[1])
		/* if l > 2 {
		    _,_ := strconv.Atoi(arg[2])
		}
		*/
	}

	c := cs[0]

	for n = 1; n < n0+1; n++ {
		c <- fmt.Sprintf("%s-%d", arg[0], n)
	}

	close(c)
}

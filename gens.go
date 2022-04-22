package sw

import "fmt"
import "sync"
import "strconv"

/*Gens sends arg[1],  arg[2] long strings to channel cs[0] (out1)
   Strings consist of the process name
  and seq. no; i.e. G3-1, G3-2, etc.

  BUG cannot set length, yet.
*/
func Gens(wg *sync.WaitGroup, arg []string, ch chan interface{}) {
	var n0 = 7
	var n int

	defer close(ch)
	defer wg.Done()

	l := len(arg)
	if l > 1 {
		n0, _ = strconv.Atoi(arg[1])
	}

	for n = 1; n < n0+1; n++ {
		ch <- fmt.Sprintf("%s-%d", arg[0], n)
	}

}

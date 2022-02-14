package fileio

/*  Generated StreamWork component, Putfile,
    by swgen.sh on Thu Dec 30 08:58:14 AM EST 2021
        1  input  ports
        0 output ports
*/

import "testing"
import "fmt"
import "sync"
// import swe "github.com/tyoung3/swedit"

func TestSkel_Putfile(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"Test_Putfile"}

	fmt.Println("\u001b[32m", arg[0], "\u001b[0m")
	for i := 0; i < 0+1; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {
		defer wg.Done()
		var l FileT
		l.L = -1
		l.S = "/tmp/Putfile.txt"
		cs[0] <- l
		i := 1
		for i < 5 {
			l.L = i
			l.S = "PF_"
			cs[0] <- l
			i++
		}
		l.L = -2
		cs[0] <- l
		return
	}()

	go Putfile(&wg, arg, cs)
	wg.Wait()
	close(cs[0])
	fmt.Println("\u001b[32mTest_Putfile Ended\u001b[0m")
}

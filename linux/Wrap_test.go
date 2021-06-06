package linux

/*  Generated StreamWork component, Wrap,
    by sw.sh on Mon May 17 11:33:16 AM EDT 2021
        1  input  ports
        2 output ports
*/

import "testing"
import "fmt"
import "sync"
import "strings"

func msg(n int) string { // Serialize message output
	var bfr strings.Builder

	fmt.Fprintf(&bfr, "msg-%d\n", n)
	return bfr.String()
}

func TestSkel_Wrap(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"cat", "/usr/bin/cat", "internal/wrap.txt", "-"}

	for i := 0; i < 2+1; i++ {
		cs = append(cs, make(chan interface{}, 0))
	}

	wg.Add(4)
	// Send 4 lines of text to stdin
	go func() {
		defer wg.Done()
		var nbr int = 0
		for nbr < 4 {
			nbr = nbr + 1
			cs[0] <- msg(nbr)
		}
		close(cs[0])
		return
	}()
	// Display stdout
	go func() {
		defer wg.Done()
		for {
			ip, ok := <-cs[1]
			if ok != true {
				return
			}
			fmt.Print("TestWrap/stdout: ", ip)
		}
	}()
	// Display stderr
	go func() {
		defer wg.Done()
		for {
			ip, ok := <-cs[2]
			if ok != true {
				return
			}
			fmt.Print("TestWrap/stderr:", ip)
		}
	}()

	go Wrap(&wg, arg, cs)
	wg.Wait()
	fmt.Println("TestWrap Ended")
}

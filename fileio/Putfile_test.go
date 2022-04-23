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
	var wg sync.WaitGroup

	arg := []string{"Test_Putfile"}

	fmt.Println("\u001b[32m", arg[0], "\u001b[0m")
  ch0 := make(chan interface{})

	wg.Add(2)
	go func() {
		defer wg.Done()
		var l FileT
		l.L = -1
		l.S = "/tmp/Putfile.txt"
		ch0 <- l
		i := 1
		for i < 5 {
			l.L = i
			l.S = "PF_"
			ch0 <- l
			i++
		}
		l.L = -2
		ch0 <- l
		return
	}()

	go Putfile(&wg, arg, ch0)
	wg.Wait()
	close(ch0)
	fmt.Println("\u001b[32mTest_Putfile Ended\u001b[0m")
}

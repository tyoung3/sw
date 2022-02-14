package fileio

/*  Generated StreamWork component, Getfile,
    by swgen.sh on Thu Dec 30 08:58:14 AM EST 2021
        0  input  ports
        1 output ports
*/

import "testing"
import "fmt"
import "sync"

func Test_Getfile(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"Test_Getfile"}

	fmt.Println("\u001b[32m", arg[0], "\u001b[0m")
	for i := 0; i < 1+0; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {

		j := 0
		for j >= 0 {
			ip, ok := <-cs[j]
			if ok != true {
				break
			}
			fmt.Println("\u001b[32mTestGetfile chan:", j, "IP:", ip, "\u001b[0m")
			j--
		}

		wg.Done()
		return
	}()

	go Getfile(&wg, arg, cs)
	wg.Wait()
	fmt.Println("\u001b[32mTest_Getfile Ended\u001b[0m")
}

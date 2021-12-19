package testrtn

/*  Generated StreamWork component, Sender,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        0  input  ports
        1 output ports
*/

import "testing"
import "fmt"
import "sync"

func TestSkel_Sender(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestSkel_Sender"}

	fmt.Println(arg[0])
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
			fmt.Println("chan:", j, "IP:", ip)
			j--
		}

		fmt.Println("TestSkel_Sender Ended")
		wg.Done()
		return
	}()

	go Sender(&wg, arg, cs)
	wg.Wait()

}

package testrtn

/*  Generated StreamWork component, DelayedReceiver,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        1  input  ports
        0 output ports
*/

import "testing"
import "fmt"
import "sync"

func TestSkel_DelayedReceiver(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestSkel_DelayedReceiver"}

	fmt.Println(arg[0])
	for i := 0; i < 0+1; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {

		i := 0
		for i >= 0 {
			cs[i] <- i
			close(cs[i])
			i--
		}
		fmt.Println("TestSkel_DelayedReceiver Ended")
		wg.Done()
		return
	}()

	go DelayedReceiver(&wg, arg, cs)
	wg.Wait()

}

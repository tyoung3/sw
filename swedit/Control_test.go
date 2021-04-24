package swedit

/*  Generated StreamWork component, Control,
    by sw.sh on Fri Apr 23 02:13:51 PM EDT 2021
        1  input  ports
        2 output ports
*/

import "testing"
import "fmt"
import "sync"

func TestSkel_Control(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestSkel_Control"}

	fmt.Println(arg[0])
	for i := 0; i < 2+1; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {

		j := 2
		for j >= 1 {
			ip, ok := <-cs[j]
			if ok != true {
				break
			}
			fmt.Println("chan:", j, "IP:", ip)
			j--
		}

		i := 0
		for i >= 0 {
			cs[i] <- i
			close(cs[i])
			i--
		}
		fmt.Println("TestSkel_Control Ended")
		wg.Done()
		return
	}()

	go Control(&wg, arg, cs)
	wg.Wait()

}

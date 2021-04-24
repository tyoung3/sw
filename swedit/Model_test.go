package swedit

/*  Generated StreamWork component, Model,
    by sw.sh on Fri Apr 23 02:13:52 PM EDT 2021
        2  input  ports
        1 output ports
*/

import "testing"
import "fmt"
import "sync"

func TestSkel_Model(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestSkel_Model"}

	fmt.Println(arg[0])
	for i := 0; i < 1+2; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {

		j := 2
		for j >= 2 {
			ip, ok := <-cs[j]
			if ok != true {
				break
			}
			fmt.Println("chan:", j, "IP:", ip)
			j--
		}

		i := 1
		for i >= 0 {
			cs[i] <- i
			close(cs[i])
			i--
		}
		fmt.Println("TestSkel_Model Ended")
		wg.Done()
		return
	}()

	go Model(&wg, arg, cs)
	wg.Wait()

}

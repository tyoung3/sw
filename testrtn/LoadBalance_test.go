package testrtn

/*  Generated StreamWork component, LoadBalance,
    by swgen.sh on Sun Dec 19 12:02:38 PM EST 2021
        1  input  ports
        3 output ports
*/

import "testing"
import "fmt"
import "sync"

func TestSkel_LoadBalance(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestSkel_LoadBalance"}

	fmt.Println(arg[0])
	for i := 0; i < 3+1; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {

		j := 3
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
		fmt.Println("TestSkel_LoadBalance Ended")
		wg.Done()
		return
	}()

	go LoadBalance(&wg, arg, cs)
	wg.Wait()

}

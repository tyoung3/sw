package github.com/tyoung3/sw

/*  Generated StreamWork component, Pass,
    by sw.sh on Wed May  5 12:44:47 PM EDT 2021
        1  input  ports
        1 output ports
*/

import "testing"
import "fmt"
import "sync"

func TestSkel_Pass(t *testing.T) {
	var cs []chan interface{}
	var wg sync.WaitGroup

	arg := []string{"TestSkel_Pass", "1000"}

	// fmt.Println(arg[0])
	for i := 0; i < 1+1; i++ {
		cs = append(cs, make(chan interface{}))
	}

	wg.Add(2)
	go func() {
		defer close(cs[0])
		defer wg.Done()
		cs[0] <- 1
		ip, _ := <-cs[1]
		fmt.Println("TestSkel_Pass/IP:", ip)
		cs[0] <- 2
		//fmt.Println("TestSkel: Done sending");
		ip, _  = <-cs[1]
		fmt.Println("TestSkel_Pass Ended")
		return
	}()

	go Pass(&wg, arg, cs)
	wg.Wait()

}

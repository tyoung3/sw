package github.com/tyoung3/sw

/*  Generated StreamWork component, Pass,
 by sw.sh on Wed May  5 12:44:47 PM EDT 2021
     1  input  port
     1 output port

Purpose delay dataflow by a Poison distributed, average configurable interval of time in milliseconds.  Forward all input in arrival sequence to output.
*/

import (
	"math"
	"math/rand"
	str "strconv"
	"sync"
	"time"
	_ "fmt"
)

/** Send all IPs received.  Delay time Poison distributed. */
func loop(cs []chan interface{}, delay int) {

	r := rand.New(rand.NewSource(99)) /* Seed random number generator */
	//fmt.Println("Log ", delay, "=", math.Log( r.Float64()) )

	for {
		ip, ok := <-cs[0]
		if ok == true && ip != nil {
		    period := time.Duration(-float64(delay)*math.Log(r.Float64())) * time.Millisecond
		    // fmt.Println("period=",period);
			time.Sleep(period)
			cs[1] <- ip
		} else {
			close(cs[1])
			return
		}
	}
}

/*Pass delays input from chanell 0 for arg[1] milliseconds, then sends it out on channel 1.  */
func Pass(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {
	var delay int=1;  // Delay for one second.

	defer wg.Done()
	// cfg := pkgConfig()
	// delay, _ := cfg.IntOr("delay", 1000) /* Mean milliseconds delay; Poison distributed */
	if len(arg) > 1 {
		delay, _ = str.Atoi(arg[1])
	}

	// version := "v0.0.0"
	loop(cs, delay)
}

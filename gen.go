package sw

// import "fmt"
import "sync"
import "strconv"

var version = "v0.28.0"

/*
Gen sends 'nbr' integers, beginning with 'start', incremented
by 'inc';  argcuments 1, 2, and 3 respectively over port 0.

#####Examples
		(Gen will send:
		1 2 3 4 5 6 7

	 	(Gen "-i" "9" "2" "3") will send:
	2 5 8 11 14 17 20 23 26

	    (Gen "-i" "3" "17") will send:
	17 18 19

		(Gen "-i" "4" "-2" "-1") will send:
	-2 -3 -4 -5
*/
func Gen(wg *sync.WaitGroup, arg []string, c chan interface{}) {

	defer wg.Done()
	defer close(c)

	//fmt.Println(arg[0], " swbase.Gen", arg[1], arg[2], arg[3])
	nbr, _ := strconv.Atoi(arg[1])
	start, _ := strconv.Atoi(arg[2])
	inc, _ := strconv.Atoi(arg[3])

	ip := start

	for n := 0; n < nbr; n++ {
		c <- ip
		ip += inc
	}
}

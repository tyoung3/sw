package swutility


import "sync"
import "fmt"

/* StreamWork component MergeInt sends all input from channels cs[1:n] to channel cs[0] in order of arrival.

*/
func MergeInt(wg1 *sync.WaitGroup, cs ...chan interface{}) {
	var wg sync.WaitGroup

	defer wg1.Done()
	wg.Add(len(cs) - 1)

	for _, c := range cs[1:] {
		go func(c <-chan interface{}) {
			defer wg.Done()
			for v := range c {
				fmt.Println("Merge:", v)
				cs[0] <- v
			}
		}(c)
	}

	go func() {
		wg.Wait()
		close(cs[0])
	}()

}

package swutility


import "sync"
import "fmt"

/*MergeInt sends all input from channels cs[1:n] to channel cs[0] in order of arrival.
*/
func MergeInt(wg *sync.WaitGroup, cs ...chan interface{}) {
	var wg1 sync.WaitGroup

	defer wg.Done()
	wg1.Add(len(cs) - 1)

	for _, c := range cs[1:] {
		go func(c <-chan interface{}) {
			defer wg1.Done()
			for v := range c {
				fmt.Println("Merge:", v)
				cs[0] <- v
			}
		}(c)
	}

	go func() {
		wg1.Wait()
		close(cs[0])
	}()

}

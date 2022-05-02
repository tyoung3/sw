package os

/*	
	black="\u001b[30m"
        red="\u001b[31m"
        green="\u001b[32m"      
        lightgreen="\u001b[32;1m"        
        yellow="\u001b[33m"
        blue="\u001b[34m"
        magenta="\u001b[35m"
        cyan="\u001b[36m"
        white="\u001b[37m"
        reset="\u001b[0m"
*/


import "testing"
import "fmt"

func TestDebug(t *testing.T) {


	Debug("Debug is On")
	// wg.Wait()
	fmt.Println("TestDebug Ended")
}

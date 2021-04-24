package swedit

import config "github.com/zpatrick/go-config"
import "sync"
import "fmt"

type ip_t struct { /* Information Packet type */
	P string /* Process Name  */
	S string /* modulepath/component */
	I int    /* Port number */
}

/* PkgConfig initializes the go-config package.
See: https://github.com/zpatrick/go-config for details*/
func PkgConfig() *config.Config {
	mappings := map[string]string{
		"BUFFERSIZE": "buffersize",
		"SEQNO":      "seqno=7",
	}

	return config.NewConfig([]config.Provider{
		config.NewYAMLFile("/home/tyoung3/go/src/github.com/tyoung3/sw/swedit/swedit.yaml"),
		config.NewEnvironment(mappings)})
}

func Send(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()
	var ip ip_t
	ip.I = nport
	ip.P = arg[0]
	ci <- ip
}

func Recv(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()
	
	//for {		
		ip, ok := <-ci
		if ok!=true {
			return
		}
		fmt.Println(arg[0], nport, "Received:", ip)	
	//}	
}

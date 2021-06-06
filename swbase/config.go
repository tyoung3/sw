package swbase

import config "github.com/zpatrick/go-config"
import "sync"
import "fmt"

type ipT struct { /* Information Packet type */
	P string /* Process Name  */
	S string /* modulepath/component */
	I int    /* Port number */
}

/* PkgConfig initializes the go-config package.
See: https://github.com/zpatrick/go-config for details*/
func pkgConfig() *config.Config {
	mappings := map[string]string{
		"BUFFERSIZE": "buffersize",
		"SEQNO":      "seqno=7",
	}

	return config.NewConfig([]config.Provider{
		config.NewYAMLFile("/home/tyoung3/go/src/github.com/tyoung3/sw/swbase/html/swbase.yaml"),
		config.NewEnvironment(mappings)})
}

func send(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()
	var ip ipT
	ip.I = nport
	ip.P = arg[0]
	ci <- ip
}

func recv(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {
	defer wg2.Done()
	ip, _ := <-ci
	fmt.Println(arg[0], nport, "received:", ip)
}

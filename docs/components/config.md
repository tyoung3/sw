package cfg // import "github.com/tyoung3/sw/config"


FUNCTIONS

func pkgConfig() *config.Config

        PkgConfig initializes the go-config package.
    See: https://github.com/zpatrick/go-config for details

func recv(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int)
func send(ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int)

TYPES

type IpT struct {
	P string /* Process Name  */
	S string /* modulepath/component */
	I int    /* Port number */
}
    IpT is a common IP default type


package fileio // import "github.com/tyoung3/sw/fileio"


FUNCTIONS

func Getfile(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Getfile is @todo undocumented

func Putfile(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Putfile is @todo undocumented


TYPES

type FileT struct {
	S string /* Statement   */
	L int    /* Line Number -1=File name */
}


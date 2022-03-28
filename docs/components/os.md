package os // import "github.com/tyoung3/sw/os"

Package sw/os provides Operating System specific functionality for
StreamWork Golang components.

FUNCTIONS

func Debug(s string)
    Debug prints string, s, in yellow, if debugging mode is set ( DEBUG="Y").

func Wrap(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Wrap launches the specified linux executable and separate goroutines to a)
    forward all text lines from channel 0(cs[0]) to the executable's stdin pipe;
    b) forward text lines from the stdout pipe to channel 1; and c) forward text
    lines from stderr to channel 2.


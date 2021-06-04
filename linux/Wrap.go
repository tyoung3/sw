/** Pkg linux provides *Nix specific functionality for StreamWork Golang components. */
package linux

/*  Generated StreamWork component, Wrap,
    by sw.sh on Mon May 17 11:33:16 AM EDT 2021
        1  input port
        2 output ports
*/

import (
	"bufio"
	"io"
	"log"
	"os/exec"
	"sync"
)

/**  send: Write data from stdout or stderr to channel 1 or 2, respectively, one line at a time.*/
func send(stdoutStderr *io.ReadCloser, ci *chan interface{}, wg2 *sync.WaitGroup) {

	defer wg2.Done()
	defer close(*ci)
	buf := bufio.NewReader(*stdoutStderr)
	
	for {
		line, _, err := buf.ReadLine()
		if err != nil { return }
		msg := string(line)
		*ci <- msg
	}
}

/** recv:  Write data from channel 0 to stdin(pipe). */
func recv(stdin *io.WriteCloser, ci *chan interface{}, wg2 *sync.WaitGroup) {

	defer (*stdin).Close()
	defer wg2.Done()

	for {
		ip, ok := <-*ci
		if ok != true { return }
		ipt := ip.(string)
		_, err := io.WriteString(*stdin, ipt)
		if err != nil { log.Fatal(err)}
	}
}

/* Wrap  launches the specified linux executable and
separate goroutines to a) forward all text lines from channel 0(cs[0]) to the 
executable's stdin pipe; b) forward text lines from the stdout pipe to channel 1;
and c) forward text lines from stderr to channel 2.*/
func Wrap(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()

	cmd := exec.Command(arg[1],arg[2],arg[3])  /** ?? Allow for variable number of arguments. */
	// cmd.Args = arg  // causes arg[1]: 'no such file...' error.
	
	stdin, err := cmd.StdinPipe()
	if err != nil { log.Fatal(err) }
	
	stdout, err := cmd.StdoutPipe()
	if err != nil { log.Fatal(err) }

	stderr, err := cmd.StderrPipe()
	if err != nil { log.Fatal(err) }

	var wg2 sync.WaitGroup
	wg2.Add(3)

	go recv(&stdin,  &cs[0], &wg2)
	go send(&stdout, &cs[1], &wg2)
	go send(&stderr, &cs[2], &wg2)
		 
	if err := cmd.Start(); err != nil { log.Fatal(err)}
	if err := cmd.Wait();  err != nil { log.Fatal(err)}
	wg2.Wait()
}

/****************   End of WRAP.GO   ***************/

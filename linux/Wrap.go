/** Pkg linux provides *Nix specific functionality for StreamWork Golang components. */
package linux

/*  Generated StreamWork component, Wrap,
    by sw.sh on Mon May 17 11:33:16 AM EDT 2021
        1  input  ports
        2 output ports
*/

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"sync"
	"time"
)

/**  send: Write data from stdout or stderr to ci* one line at a time.*/
func send(stdoutStderr io.ReadCloser, ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {

	defer wg2.Done()
	defer close(ci)
	buf := bufio.NewReader(stdoutStderr)
	for {
		line, _, err := buf.ReadLine()
		if err != nil {
			if err != nil {
				return
			}
			if err == io.EOF {
				return 
			} else {
				fmt.Println("WRAP/send: ReadLine error on port ", nport)
				log.Fatal(err)
			}
		}
		msg := string(line)
		ci <- msg
		
	}
}

/** recv:  Write data from ci to stdin(pipe). */
func recv(stdin io.WriteCloser, ci chan interface{}, wg2 *sync.WaitGroup, arg []string, nport int) {

	defer stdin.Close()
	defer wg2.Done()

	for {
		ip, ok := <-ci
		if ok != true {
			time.Sleep(50 * time.Millisecond)
			return
		}
		ipt := ip.(string)
		_, err := io.WriteString(stdin, ipt)

		if err != nil {
			fmt.Println("WRAP/recv	: Fprintf error.")
			fmt.Fprintf(os.Stderr, "WRAP/recv: Fprintf: %v\n", err)
			log.Fatal(err)
		}
	}
}

/* Wrap:  Wrap  launches the specified linux executable then
     	   forwards all text lines from channel 0 to the stdin pipe;
           forwards text lines from the stdout pipe to channel 1;
           and finally forwards text lines from stderr to channel 2.*/
func Wrap(wg *sync.WaitGroup, arg []string, cs []chan interface{}) {

	defer wg.Done()

	cmd := exec.Command(arg[1], arg[2], arg[3]) 
	
	stdin, err := cmd.StdinPipe()
	if err != nil {
		log.Fatal(err)
	}
	
	stdout, err2 := cmd.StdoutPipe()
	if err2 != nil {
		log.Fatal(err2)
	}

	stderr, err3 := cmd.StderrPipe()
	if err3 != nil {
		log.Fatal(err3)
	}

	var wg2 sync.WaitGroup
	wg2.Add(3)

	go recv(stdin,  cs[0], &wg2, arg, 0)
	go send(stdout, cs[1], &wg2, arg, 1)
	go send(stderr, cs[2], &wg2, arg, 2)
	 
	if err4 := cmd.Start(); err4 != nil {
		fmt.Println("WRAP: command start error")
		log.Fatal(err4)
	}

	err5 := cmd.Wait()
	if err5 != nil {
		fmt.Println("WRAP: command wait error")
		log.Fatal(err)
	}
	wg2.Wait()
}

/****************   End of WRAP.GO   ***************/

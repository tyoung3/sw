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
func send(stdoutStderr io.ReadCloser, ci chan interface{}, wg2 *sync.WaitGroup) {

	defer wg2.Done()
	defer close(ci)
	buf := bufio.NewReader(stdoutStderr)
	for {
		line, _, err := buf.ReadLine()
		if err != nil {
			return
		}
		msg := string(line)
		ci <- msg
	}
}

/** recv:  Write data from ci to stdin(pipe). */
func recv(stdin io.WriteCloser, ci chan interface{}, wg2 *sync.WaitGroup) {

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
	
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		log.Fatal(err)
	}

	stderr, err := cmd.StderrPipe()
	if err != nil {
		log.Fatal(err)
	}

	var wg2 sync.WaitGroup
	wg2.Add(3)

	go recv(stdin,  cs[0], &wg2)
	go send(stdout, cs[1], &wg2)
	go send(stderr, cs[2], &wg2)
		 
	if err := cmd.Start(); err != nil {
		fmt.Println("WRAP: command start error")
		log.Fatal(err)
	}

	errc := cmd.Wait()
	if errc != nil {
		fmt.Println("WRAP: command wait error")
		log.Fatal(errc)
	}
	//close(cs[0])
	//stdin.Close()
	wg2.Wait()
}

/****************   End of WRAP.GO   ***************/

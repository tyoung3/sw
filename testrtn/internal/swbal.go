





package main

/*StreamWork Go code. 
 Generated by sw/swgo.c-0.18.5 Sun Dec 19 13:52:29 2021
 Configuration file: /home/tyoung3/go/sw/sw.cfg
*/

/***********   Expanded swbal.sw Network Definition   **********   
(Receiver2 github.com/tyoung3/sw/testrtn.Receiver ) 		<load-	3(LoadBalance github.com/tyoung3/sw/testrtn.LoadBalance);	
(Receiver1 github.com/tyoung3/sw/testrtn.Receiver ) 		<load-	2(LoadBalance github.com/tyoung3/sw/testrtn.LoadBalance);	
(Receiver0 github.com/tyoung3/sw/testrtn.DelayedReceiver ) 		<load-	1(LoadBalance github.com/tyoung3/sw/testrtn.LoadBalance);	
(LoadBalance github.com/tyoung3/sw/testrtn.LoadBalance ) 		<load-	0(Sender github.com/tyoung3/sw/testrtn.Sender "COUNT=10");	
# 4 streams, 5 processes, 4 components, 1 partition, 0 cycles.
*********************************************/

import "sync"
import sw "github.com/tyoung3/sw"
import "github.com/tyoung3/sw/testrtn"


func main() {
	var cs []chan interface{}
	var wg sync.WaitGroup

cs = append(cs,make(chan interface{}))
cs = append(cs,make(chan interface{}))
cs = append(cs,make(chan interface{}))
cs = append(cs,make(chan interface{}))

sw.Launch(&wg,[]string{"Receiver2"},	  testrtn.Receiver, cs[3:4])
sw.Launch(&wg,[]string{"Receiver1"},	  testrtn.Receiver, cs[2:3])
sw.Launch(&wg,[]string{"Receiver0"},	  testrtn.DelayedReceiver, cs[1:2])
sw.Launch(&wg,[]string{"LoadBalance"},	  testrtn.LoadBalance, cs[0:4])
sw.Launch(&wg,[]string{"Sender","COUNT=10"},	  testrtn.Sender, cs[0:1])

wg.Wait()
}
Copyright (C) 2019 Thomas W. Young, streamwork@twyoung.com 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file or its derivitaves except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SW-0.6.1 - STREAMWORK/FrontEnd
==============================

Name
----

         StreamWork - a flow based program(FBP) Go language framework.
         

Description
-----------

StreamWork is the prototype for a Go language,
flow-based-programming(FBP) system.  

StreamWork reads and executes a StreamWork network definition(ND) file.
Employing StreamWork, an ND becomes, in effect, an executable
script. Sw launches collects go components(defined in go packages)  
into one main.go program, launches them as goroutines, 
and connects them via Go interface channels.  

The ND consists of a list of streams(or dataflows). 
Each stream definition consists of a sink process, 
a sink port number, "<-", a source portnumber, and a source process followed by the statement terminator, ';'.   

Port numbers default to 0.

Ex.  
```
    (Hello)0 <- 0(World); 
```
produces:
```
Hello World
```

A process is defined by its process name, its component identifier,
and component arguments surrounded by parens. 

A stream definition consists of a sink component,
the channel pointer, and a source component, ended by a ```;```. 
 
Channel pointers consist of ```<```, an optional
buffersize integer, and ```-```. Example: ```<100-```
 
Because the Hello World example employs 
standard, default components, without 
arguments; the network definition can be simplified to 
 ```Hello <- World;```
 
IPs are designed as nil(empty) interfaces.   The interface
data type is determined by the sending component.  IPs
may or may not cause a type mis-match, depending 
on the sink component coding.  Components can be coded to
handle any type(including user-defined types), 
a few types(Print1 can process strings and integers), 
or just one type; on each receiving port.    
 
The ND language is defined in less than 50 statements. 
Progams developed using this simple system, 
however, are highly capable.  
 
Sw versions are backward compatible within the same major 
version(currently v0).  

Sw builds a network model in memory, then optionally generates
either an abstract syntax tree, 
a linearized tree(an ND recronstruction), 
a GraphViz .dot file, or Go source code from this model.
C and other languages could also be generated.  
JavaFBP is possible.   

Comments and critiques are welcome.    Contributors are encouraged.  

Please do not submit code before contacting the project by 
e-mailing streamwork@twyoung.com or  posting a request on Github.     

QuickStart (on Linux) 
----------
	* To run the generated Go code, install the 
	  tyoung3/StreamWork backend 
	  from github.  (Requires Go installation.).  
	  The backend should run 
	  in any Golang compatible environment.  Sw(written in C) 
	  will run without installing github/tyoung3/StreamWork; 
	  the generated Go code just won't work.
	* Download the 'sw' executable from github to any 
	  convenient location.
	* Run 'chmod a+x sw' if necessary. 
	* Run ```.../sw -v``` to check that the version is at least v0.6.1  
	* Change directory to $GOPATH/mod (create the directory
	  if necessary).
	  This is usually ~/go/mod.  Go modules will fail in ~/go/src.
	* Run go mod init fb/fb, unless go.mod already exists.  
	  
```	
echo "Foo <- Bar;" | sw > /tmp/fb.go 
```
	* Run 'go run /tmp/fb.go'

OUTPUT: 
Foo Bar
```

```go: finding github.com/tyoung3/streamwork/def latest```
 may appear the first time the program is run.
 
	* Examine /tmp/fb.go  

Release Notes
=============

V0.4.0
------

Enabled buffer size specification. 
Ex. (A a)0 <NNN- 0(B b); will allocate NNN buffers to this stream.

v0.5.0
------

Port numbers default to zero.  
Ex. (A a) <- (B b); expands to (A a)0 <- 0(B b);

v0.5.1
------ 

Introduces variables into the language, but are ignored for now.

v0.5.2
------

Enabled default components. 
Ex.  ```A<-B;``` expands to 
```(a def.Print1 )0  <- 0(b def.Gen1);
```

v0.5.3
------

	* Reorganized development tree and fixed scripts 

	* Cleaned up graphic.  
		* Moved component info to tooltips.  
		* Fixed up title.  
		* Cleaned up URLs. Works with .SVG 
		
v0.6.0
------
	* Introduced stream chaining. 
	  (A) <- (B) <- (C);  expands to: 
	  (A) <- (B);
	  (B) <- (C);		
		
v0.6.1
------
	* Fixed dataflow chaining problems

Named Ports
-----------

Ex.  (A a)FOO <- FOO(B b);  expands to (A a)0 <- 0(B b);
	 (A a)FOO <- BAR(B b);  fails with a name mismatch, but 
	 (A a)IN  <- OUT(B b);  succeeds, as do
	 (X1 a)0.SOCKET  <- PLUG.0(Y1 b); and
	 (X2 a)0.SLOT    <- TAB.0(Y2 b);
	 
	 
	 
SW.cf Language Notes
--------------------
Statements in the network definition language, SW.cf, are 
terminated with a semi-colon.  Semi-colons in code are like 
periods at the end of English statements -- 
they tell the reader (and the interpreter) when
you have reached the end; making reading the statements easier. 
Imagine trying to read a book without any periods (or initial capitals). 
Without semi-colons, line breaks become
necessary  and awkward syntax rules evolve.  

In the future, there may be some, very few exceptions to the 
semi-colon rule for special pre-interpreter commands, like INCLUDE.

The, ```<-```,  token is used to be consistent with its 
usage in the Go language.     

Comments in the SW.cf file provide 
clues to possible future language additions.  
We strive for backward compatibility.

Collate/Merge Example
---------------------

Given the input file: /tmp/collate.sw  

```   
#/TMP/COLLATE.SW
(C std.Collate)  <-  (G0  std.Gen1 "12" "1" "2" );
(C)1             <-  (M);         
(M std.Merge)1   <-  (G1  std.Gen1 "5"  "5" "1" );
(M)2             <-  (G2  std.Gen1 "8"  "2" "3" );
(Match0  Print1) <- 2(C std.Collate  );
(Match1  Print1) <- 3(C);
(Miss0   Print1) <- 4(C);
(Miss1   Print1) <- 5(C);
```
running the following (in Linux):
```
	sw < /tmp/collate.sw      > /tmp/collate/main.go
	cd /tmp/collate; go mod init
	go run *go   ; # Try go run main.go |sort | grep ...
```	
will produce:
```
go: finding github.com/tyoung3/streamwork/std latest
go: finding github.com/tyoung3/streamwork/strings latest
StreamWork Proof of Concept Example.
M std.Merge: starting 
G2  std.Gen1 8 2 3
M std.Merge:  2 3
G1  std.Gen1 5 5 1
M std.Merge:  5 3
G0  std.Gen1 12 1 2
M std.Merge:  6 3
    ... 
M std.Merge: exit 
M std.Merge: ending
Miss0 Int: 19
Miss0 Int: 21
Match0 Int: 23
Match1 Int: 17
Match1 Int: 23
```
but not necessarily in that order.
This will also produce /tmp/sw/main.go:
```
package main

/* DO NOT EDIT!!!
*
    generated by sw/swgo.c-...  */

import "fmt"
import "sync"
import "github.com/tyoung3/streamwork"
import "github.com/tyoung3/streamwork/strings"
import "github.com/tyoung3/streamwork/std"


func main() {
var cs []chan interface{}
var wg sync.WaitGroup

	fmt.Println("StreamWork Proof of Concept Example.")

	for i:=0; i<8; i++ {
		cs = append(cs, make(chan interface{}))
	}

/*       Network Definition  */
/* (Miss1 strings.Print1 )0  <- 5(C std.Collate)	*/
/* (Miss0 strings.Print1 )0  <- 4(C std.Collate)	*/
/* (Match1 strings.Print1 )0  <- 3(C std.Collate)	*/
/* (Match0 strings.Print1 )0  <- 2(C std.Collate)	*/
/* (M std.Merge )2  <- 0(G2 std.Gen1 "8" "2" "3")	*/
/* (M std.Merge )1  <- 0(G1 std.Gen1 "5" "5" "1")	*/
/* (C std.Collate )1  <- 0(M std.Merge)	*/
/* (C std.Collate )0  <- 0(G0 std.Gen1 "12" "1" "2")	*/

fbp.Launch(&wg,[]string{"Miss1"},	  strings.Print1, cs[7:8])
fbp.Launch(&wg,[]string{"Miss0"},	  strings.Print1, cs[6:7])
fbp.Launch(&wg,[]string{"Match1"},	  strings.Print1, cs[5:6])
fbp.Launch(&wg,[]string{"Match0"},	  strings.Print1, cs[4:5])
fbp.Launch(&wg,[]string{"G2","8","2","3"},	      std.Gen1, cs[3:4])
fbp.Launch(&wg,[]string{"G1","5","5"},	      std.Gen1, cs[2:3])
fbp.Launch(&wg,[]string{"M"},	      std.Merge, cs[1:4])
fbp.Launch(&wg,[]string{"G0","12","1","2"},	      std.Gen1, cs[0:1])

	for i:=0; i<6; i++ {
		cs_C:=append(cs_C, make(chan interface{}))
	}
	cs_C[0] = cs[0]
	cs_C[1] = cs[1]
	cs_C[2] = cs[4]
	cs_C[3] = cs[5]
	cs_C[4] = cs[6]
	cs_C[5] = cs[7]
fbp.Launch(&wg,[]string{"C"},	      std.Collate, cs_C[0:6])

wg.Wait()
}

```

Running:
```	 
	sw -m 4 < /tmp/collate.sw > /tmp/collate.dot
	dot -Tjpg  /tmp/collate.dot > /tmp/collate.jpg
```
produces /tmp/collate.jpg  [copy may be in this directory]

WARNING:
--------

	 std.Gen1 generates integer IPs. 
	 Note that std.Gen1 is not the same as
	 strings.Gen1, or def.Gen1.  
  
BUGS:
-----
	 std.Gen1 fails unless all three arguments are present.
	 
	 Re-ordering streams in the ND, sometimes causes sw to
	 fail for multi-port components. 

Author
------

    Tom Young, streamwork@twyoung.com
    
    with thanks to J.P.Morrison, Phillip W. Young, Sam Watkins, 
    all the other contributors to 
    flow-based-programming@googlegroups.com, 
    and to the developers of Linux/Ubuntu, gcc, 
    BNFC, Go, git, and Github. 

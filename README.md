Copyright (C) 2019,2020 Thomas W. Young, streamwork@twyoung.com 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file or its derivitaves except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SW-0.11.4 - STREAMWORK/FrontEnd
==============================

Name
----

         StreamWork - a flow based program(FBP) Go language framework.
         

Description
-----------

StreamWork is the prototype for a Go language,
flow-based-programming(FBP) system.  

StreamWork reads, analyzes, and executes a StreamWork network 
definition(ND) file.
Employing StreamWork, an ND becomes, in effect, an executable
script. 

By default, sw generates 
and builds a single main.go program which imports the StreamWork backend
to launch a goroutine 
for each process,  connect these processes via Go interface channels,
and wait for all processes to finish.  

On option, sw will create a GraphViz .dot file, an abstract syntax tree, or a linearized tree.

The network definition consists of a list of 
streams(or dataflows) and subnet definitions.  Each stream definition consists 
of a sink process, a sink port number, "<-", a source
portnumber, and a source process followed by the 
statement terminator, ';'; or a source process, a source portnumber, 
"->", a sink portnumber, and a sink process followed by the terminator. 
The arrows ("<-" and "->")
may include a stream buffer size: e.g. "<10-" and "-2>".  If not included,
buffer size defaults to zero.
  
Port numbers default to 0.

Ex.  
```
    (Hello) <- (World); 
```
produces:
```
Hello World
```

A process is defined by its process name, its component identifier,
and component arguments; all surrounded by parens. 
The component identifier and arguments may be omitted.  

A component identifier consists of its import path identifier, 
a period, '.', and the component name.  If  the path is omitted, 
'def' is assumed.  If the component name is also ommited, Print1 
is assumed for sink processes and Gen1 is assumed 
for source processes.   These defaults can be overridden by 
arguments to sw. 
 
Channel arrows consist of ```<```, an optional
buffersize integer, and ```-```. Example: ```<100-```
 
IPs are designed as nil(empty) interfaces whose
data type is determined by the sending component. A type 
mis-match will be reported by incompatible receiving 
components.  Components can be coded to handle any
type(including user-defined types); 
a few types(Print1 can process strings and integers); 
or just a single type; on each receiving port.   
 
Sw versions are backward compatible within the same major 
version(currently v0).    

Sw builds a network model in memory, then optionally generates
either an abstract syntax tree, 
a linearized tree(an ND recronstruction), 
a GraphViz .dot file, 
or Go source code from this model.

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
	  the generated Go code just won't work properly without it.
	* Download the 'sw' executable from github to any 
	  convenient bin path location, like /usr/local/bin or $GOPATH/bin.
	* Run 'chmod a+x sw' if necessary. 
	* Run ```sw -v``` to check that the version is at least v0.8.0 
	 
```	
echo "(Foo) <- (Bar);" | sw > /tmp/fb.go 
```
	* Run 'go run /tmp/fb.go'

OUTPUT: 

```
Foo Bar


"go: finding github.com/tyoung3/streamwork/def latest"```
 may appear the first time the program is run.

Release Notes
=============

0.4
--- 

Enabled buffer size specification. 
Ex. (A a)0 <NNN- 0(B b); will allocate NNN buffers to this stream.

0.5
--- 

Port numbers default to zero.  
Ex. (A a) <- (B b); expands to (A a)0 <- 0(B b);

Introduces variables into the language, but are ignored for now.

Enabled default components. 
Ex.  ```A<-B;``` expands to 
```(a def.Print1 )0  <- 0(b def.Gen1);
```

	* Reorganized development tree and fixed scripts 

	* Cleaned up graphic.  
		* Moved component info to tooltips.  
		* Fixed up title.  
		* Cleaned up URLs. Works with .SVG 
		
0.6
---

	* Introduced stream chaining. 
	  (A) <- (B) <- (C);  expands to: 
	  (A) <- (B);
	  (B) <- (C);		
		
	* Fixed dataflow chaining problems
	
0.7.0
------
	* Added subneting to NDs; BUGGY
-----------

0.7.1
------
	* Fixed collate example
	
0.7.3
------
	* Default path from first component.	
	
0.7.4	
-----
    * 

0.7.5
-----
	* Fixed some subnet port id problems. 
	* Worked on options to display comp name and arguments in graphs  
	
0.7.7
-----
	* Fixed subnet extra stream problem	
	* Introduced anonymous processes. 
	  Ex.  ```...(_  path.comp)...```
	  
	  
0.8.0
-----
	* Introduced subnet tabs.  In subnet definitions,
	  tags may be used to refer to external ports.  
	  Ex. ```'sn { (A) <- IN; }; (B 'sn)IN <- (C);```  
	  IN is an external reference tag.  The expanded 
	  network will be: ```(B-A def.Print1 )0 <- 0(C def.Gen1);  ``` 	
	 
	
0.8.2
-----
	* Updated for StreamWork-0.4.0 
	* Updated collate.sw	 
	
0.9.0
-----
	* Introduced the AutoJoin feature.  If two processes 
	  are sending 
	  to the same sink port, sw will create an anonymous 
	  poc.Join process to combine the two streams first.	
	  
0.9.1
-----
	* Introduced the AutoSplit feature.  If a process is 
	  sending to two sinks from the same port, sw will 
	  create an anonymous poc.Split process to send the 
	  data to both sink processes. 	  
	  
0.9.3
-----
	* Standardized FAIL messages. 
	* Show number processes, etc. statistics in 
	  network definition. 
	  Number of partitions equals number of disconnected 
	  process groups. 	 

0.10.0
------
	* Implemented right arrow in network definition language

0.10.1
------
	* Refactored and fixed expansion logic

0.10.2
------
	* Fixed some hermit logic

0.10.3
------
	* Fixed hermit logic.  Initial autoconnect logic. 

0.10.4
------
	* Implemented more hermit logic.   

0.11.0
------
	* Implemented port name matching.

0.11.1
------
	* Fixed External port errors
	* Commented heading of linearized tree output

0.11.3
------
	* Implemented configuration file, /home/tyoung3/.sw/sw.cfg

0.11.4
------
	* Added TODOs. 
	* Implemented string variables.
	
	
SW.cf Language Notes
--------------------
Statements in the network definition language, SW.cf, are 
terminated with a semi-colon.  Semi-colons in code are like 
periods at the end of English statements -- 
they tell the reader (and the interpreter) when
you have reached the end of a statement; making reading the statements easier. 
Imagine trying to read a book without any periods (or initial capitals). 

Without semi-colons, line breaks become part of the language 
definition leading to awkward syntax rules.  

In the future, there may be some, very few exceptions to the 
semi-colon rule for special pre-interpreter commands, like INCLUDE.

The, ```<-```,  token is used to be consistent with its 
usage in the Go language.  The ```->``` token is also available:
"(A)->(B)1<-(C);"  is valid.   

Comments in the SW.cf file provide 
clues to possible future language additions.  
We strive for backward compatibility.

Collate/Merge Example
---------------------

Run the following (in Linux):
```
	mkdir /tmp/collate
	sw <  sw/nds/collate.sw   > /tmp/collate/main.go
	cd /tmp/collate; go mod init collate/collate
	go run main.go |grep Match0  
```	
to produce:
``` 
Match0 Int: 7
Match0 Int: 9
Match0 Int: 11
Match0 Int: 17
Match0 Int: 23
```

Running:(HELLO)->(WORLD)
```	 (HELLO)->(WORLD)
	sw -m 3 <  sw/nds/collate.sw | dot -Tsvg > /tmp/collate.svg
```
produces /tmp/collate.svg, an image of the collate 
network definition.   
  
BUGS:
-----
	 poc.Gen1 fails unless all three arguments are present.

Author
------

    Tom Young, streamwork@twyoung.com
    
    with thanks to J.P.Morrison, Phillip W. Young, Sam Watkins, 
    the contributors to flow-based-programming@googlegroups.com, 
    and to the developers of Linux/Ubuntu, gcc, 
    BNFC, Go, git, and Github. 

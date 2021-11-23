Copyright (C) 2019,2020,2021 Thomas W. Young, streamwork@twyoung.com 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file or its derivitaves except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SW-0.14.9999 - STREAMWORK
======================

StreamWork
==========
         
   Flow based program(FBP) Go language framework and code generator.
         
[![CodeQL](https://github.com/tyoung3/sw/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/tyoung3/sw/actions/workflows/codeql-analysis.yml)
[![Go Report Card](https://goreportcard.com/badge/github.com/tyoung3/sw)](https://goreportcard.com/report/github.com/tyoung3/sw)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Description
-----------

StreamWork is a Go language(Golang), flow-based-programming(FBP) system.  	

By default, StreamWork reads, parses and analyzes,  a StreamWork network 
definition(ND) file (suffix: .sw),  then generates a main Go program. 

A network definition is, in effect, an executable
script.  While StreamWork is concerned with 
Go language FBP programs,  the ND described here is language agnostic.  It should be possible 
to generate corresponding code in other languages.         

By default, sw generates 
and builds a single main Go program which:  

  * imports sw compatible component package(s),  
  * launches a goroutine for each component instance (process),  
  * connects these processes via Golang interface channels, and 
  * waits for all processes to finish.  

On option, StreamWork will read, parse and interpret a network definition file then  create either a:
 
 * a Go main program,
 * a GraphViz .dot file,
 * a complete GO language project tree 
 
	After creating a project tree, StreamWork continues to test the generated components and 
	the final generated application.
 * an abstract syntax tree, or  
 * a linearized tree. 

swgo script
-----------

A bash script, swgo, will build and run the Generated GO program from a network definition.
```
echo "(Hello)->(World);" |sw
```
produces:
```
package main

/*StreamWork Go code. 
 Generated by sw/swgo.c-0.13.4 Fri Jun 18 11:23:37 2021
 Configuration file: ./sw.cfg
*/

/***********   Expanded stdin Network Definition   **********   
(World sw.Print ) 		<-	0(Hello sw.Gens);	
# 1 stream, 2 processes, 2 components, 1 partition, 0 cycles.
*********************************************/

import "sync"
import sw "github.com/tyoung3/sw/swbase"


func main() {
	var cs []chan interface{}
	var wg sync.WaitGroup

cs = append(cs,make(chan interface{}))

sw.Launch(&wg,[]string{"World"},	       sw.Print, cs[0:1])
sw.Launch(&wg,[]string{"Hello"},	       sw.Gens, cs[0:1])

wg.Wait()
}
```

swgraph script
--------------

Another bash script, swgraph, will display a graphic image of a network definition 
```
(m Model)1      -change>         (v View);
(c)2            -update>        1(v);
(v)2            -event>          (c Control); 
(c)1            -request>       (m);
```
produces: 

![Model/View/Control image](http://sw.twyoung.com/images/mvc.jpg)
for instance;

Processes are colored such that all components in the same package have the same color.
Not shown here, unfortunately, are the tooltips and html references.  Arrows are colored according
to stream buffersize: 0 - black; 1-green; 2 0r more - orange.   Coloring rules 
are not guaranteed to remain unchanged in future sw versions. 

The resulting image amounts to a Data Flow Diagram without datastores.  sw does not generate 
data storage access code.  Currently, data storage code must be contained within a StreamWork component.   

Network Definition
------------------

The network definition file consists of a list of 
streams(or dataflows); and may also contain subnet definitions, INCLUDE and PREFIX statements, and
comments.  

INCLUDEd files are also network definitions which may in turn contain
INCLUDE statements.  Exceeding 100 levels of includes will 
cause program termination.

A stream definition looks like:
```
(a C) -> (b D);
    or 
(E) <- (F); 
```
and consists of:

  * processname, component identifier, and optional arguments in parens 
  * portnumber (defaults to 0), 
  * a stream director:  right arrow("->") or left arrow("<-), 
  * portnumber, 
  * and another processname and component identifier, and optional arguments  in parens 
  * a statement terminator(';'). 

The stream director(director) points from the source process to the sink process.  A director may 
include a type identifier and/or a stream buffer size: e.g. "<type_A 10-"  or "-type_B>".  If not included, buffer size defaults to zero.
Example with anonymous processes:
```
  (_) -int 3> (_); [integer stream with buffersize of three] 
```

In this example, the default components send their process names to the channel or to stdout.  
```
    (Hello) <- (World); 
```
produces:
```
Hello World
```

A process is defined by its process name, its component identifier,
and component arguments; all surrounded by parens. 
The component identifier and arguments will default if omitted.  

A component identifier consists of its import module/package identifier, 
a slash, '/', and the component name.   All Go component names should be capitalized.
If  the path is omitted,  a configuration default path is assumed.  
If the component name is also omitted, configuration default component names
are assumed for sink, source, and filter(has both inputs and outputs) processes.
 
Channel arrows consist of ```<```, an optional type identifier,
an optional buffersize integer, and ```-```. Example: ```<100-```
The reverse (Ex: ```- myData_t 100>```) is also valid.
 
Information packets(IPs, streams, or dataflows) are designed as nil(empty) interfaces whose
data type is determined by the sending component. 
A type 
mis-match will be reported by incompatible receiving 
components.  Components can be coded to handle any
type(including user-defined types and structures); 
some components (Print, for instance) can process strings and integers; 
some just a single type; on each receiving port.   


It is possible, but due to extra complexity and code is not recommended, 
to send more than one type of data over a channel.  Multiple data types can better be handled 
within a struct or over multiple channels.
 
Sw versions are backward compatible within the same major 
version(currently v0).  (v0.12.2 is somewhat major, however. v0.13.4 introduced PREFIX and INCLUDE statements.)  

Sw builds a network model in memory, then optionally generates
either 
  
  * an abstract syntax tree, 
  * a linearized tree(a network definition recronstruction), 
  * a GraphViz .dot file, 
  * a complete working project tree, 
  * or Go source code from the network model.

C and other languages could also be generated, but this has not been implemented.
JavaFBP is also possible.   

Comments and critiques are welcome.    Contributors are encouraged.  

Please do not submit code before contacting the project.  Contact by 
e-mailing streamwork@twyoung.com  is preferred to posting a request on Github .     

QuickStart (on Linux) 
----------

	* The .../tyoung3/StreamWork backend is no longer required.  
	* Sw is written in C.  The bin directory contains bash scripts invoking sw.   
	* Download the 'sw' executable from github to any 
	  convenient bin path location, like /usr/local/bin or $GOPATH/bin.
	* Run 'chmod a+x sw' if necessary. 
	* Run ```sw -v``` to check the version.
	 
```	
echo "(Foo) <- (Bar);" | sw > /tmp/fb.go 
```
	* Run 'go run /tmp/fb.go'

OUTPUT: 

```
Foo Bar

## Building on Linux

    * Install ctags, libyaml-dev, bnfc, bison, and flex 
    * cd to go workkspace (like $GOPATH/src )
    * git clone https://github.com/tyoung3/sw.git
    * ./run sh c 
    


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
Ex.  ```(A)<-1(B)0<-(C);``` expands to: 
```(B sw.Pass ) 		<-	0(C sw.Gens);	
   (A sw.Print ) 		<-	1(B sw.Pass);
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

0.11.5
------
	* Fixed string variables

0.11.6
------
	* Fixed port autolinking
	* Changed subnet tag from quote(') to underscore(_).

0.11.7
------
	* Added missing name error messages.	
	
0.12.0
-------
	* Added ability to generate a complete project and run the Go code from a network definition file. 
	
	* Changed dot(.) in component identifier to a slash(/) to permit  module paths 
	  such as github.com/....   So (P def.Gen)  is now (P def/Gen).
	  
0.12.2
------
	* Consolidated the .../streamwork repo into the .../sw repo
	
	* Added type identifiers to stream definitions and .dot edge labels. 
	
	* Colored arrows in graph(.dot) output according to stream buffer sizes. 
	  0-black  1-green  >1-orange  	
	  
	* Created swbase package containing basic components Launch, Join, Split, 
	  Print, Gen, and Gens. 
	       
	* Created swutility package containing Merge and Collate components. 
	
0.13.0
------
	* Added Pass component to ...sw/swbase package
	
	* Fixes to dataflow type processing  	
	
	* Fix build process and installed build badge	 
	
0.13.1
------
	* Installed linux/Wrap function to encapsulate *Nix executables.	
	
0.13.2
------
	* Minor changes. Code cleaning.  Added license badge. 	
	
0.13.4
------
	* Include file implemented
	* Process string prefix implemented	
	
0.14.0
------
	* Correct versioning error (Previously added functionality)
	* Update home page links.
	
0.14.1
------
	* Update home page		
	
0.14.2
------
	* Fix default filter component  logic	
	
SW Language Notes
--------------------

The Streamwork network definition language, SW, is an unambiguous, context free grammar, making it 
directly interpretable, without preprocessing.  

SW has just two reserved words(INCLUDE and PREFIX) making it somewhat natural language
agnostic.  There is no guarantee this condition will continue, however, every effort 
will be made to ensure that all currently valid SW statements will remain valid.  Should 
this prove impossible,  the major version will be changed, i.e. to v1.0.0. 

Statements in SW, are terminated with a semi-colon.  Semi-colons in code are like 
periods at the end of English statements -- 
they tell the reader (and the interpreter) when
you have reached the end of a statement; making reading the statements easier. 
Imagine trying to read a book without any periods (or initial capitals). 

Additionally, without semi-colons line breaks become part of the language 
definition, leading to awkward and confusing syntax rules.  

The, ```<-```,  token is employed in order to be consistent with its 
usage in the Go language.  The ```->``` token is also available:
"(A) -> (B)1 <- (C);"  is valid SW.   

Collate/Merge Example
---------------------

Run the following (in Linux):
```
	mkdir /tmp/collate
	sw <  sw/nds/collate.sw   > /tmp/collate.go
	go run /tmp/collate.go |grep Match0  
```	
to produce:
``` 
Match0 Int: 5
Match0 Int: 7
Match0 Int: 9
Match0 Int: 11
Match0 Int: 17
Match0 Int: 23


Hello World
-----------

```
echo "(HELLO)->(WORLD);" |sw > /tmp/hello.go
go run  /tmp/hello.go 
Produces:
WORLD HELLO-1
WORLD HELLO-2
WORLD HELLO-3
WORLD HELLO-4
WORLD HELLO-5
WORLD HELLO-6
WORLD HELLO-7
```


```	  
	sw -m 3 <  sw/nds/collate.sw | dot -Tsvg > /tmp/collate.svg
```
produces /tmp/collate.svg, an image of the collate 
network definition.  
  
BUGS:
-----
	 Gen fails unless all three arguments are present.
	 
Home Page
---------

(https://sw.twyoung.com)

Author
------

    Tom Young, streamwork@twyoung.com
    
    with thanks to J. Paul Morrison, Phillip W. Young, Sam Watkins, 
    the contributors to flow-based-programming@googlegroups.com, 
    and to the developers of Linux/Ubuntu, gcc, 
    BNFC, Go, git, and Github. 

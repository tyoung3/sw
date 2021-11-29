$-- WARNING: Generated by ./configure.  DO NOT EDIT!
$--
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

SW-0.15.2 - STREAMWORK
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
 * a bash script file to help generate a complete GO language project tree. 
 
	After creating a project tree, StreamWork continues to test the generated components and 
	the final generated application.
 * an abstract syntax tree, or  
 * a linearized tree (a network definition reconstruction).   

## Synopsis
```
	sw [-m MODE] [-cfg CONFIGURATION_FILE] [-d DEFAULT_PATH] [ SW_FILE ]
	sw -v
	sw --help 
	
        If SW_FILE is omitted, sw will read from stdin. 
		MODE= 
			0-GOMODE		. Generate a main GO program[DEFAULT].
			1-ASTMODE		. Display the Abstract Syntax Tree 
			2-GENTREE		. Display the Linearized tree
			3-GRAPHMODE		. Generate Graphviz .dot file code
			4-JAVAFBP		. Incomplete and untested. Looking for help.
			5-PROJECT		. Generate bash script code for a project tree.
			7-CMODE			. Incomplete and untested. Looking for help.
```


swgo script
-----------

The bash script, swgo, will generate and run a GO program from a network definition:
```
  .../nds/hw.sw
(Hello) <string- (World);
```
swgo .../nds/hw
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

Which in turn produces:

Hello World-1
Hello World-2
Hello World-3
Hello World-4
Hello World-5
Hello World-6
Hello World-7
```

swgraph script
--------------

Another bash script, swgraph, will display a graphic image of a network definition:
   
```
#   .../nds/mvc.sw
(m Model)1      -change>         (v View);
(c)2            -update>        1(v);
(v)2            -event>          (c Control); 
(c)1            -request>       (m);
```
swgraph .../nds/mvc
produces: 

![Model/View/Control image](http://sw.twyoung.com/images/mvc.jpg)
for instance;

Processes are colored such that all components in the same package have the same color.
Not shown here, unfortunately, are the tooltips and html references.  Arrows are colored according
to stream buffersize: 0 - black; 1-green; 2 0r more - orange.   Coloring rules 
are not guaranteed to remain unchanged in future sw versions. 

The resulting image is an annotated Data Flow Diagram.

Network Definition
------------------

The network definition file consists of a list of 
streams(aka dataflows); and may also contain subnet definitions, 
INCLUDE and PREFIX statements, and comments.  

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
 
Information packets(IPs) are designed as nil(empty) interfaces.  The
data type is determined by the sending component. 
A type mis-match will be reported by incompatible receiving 
components.  Components can be coded to handle any
type(including user-defined types and structures). 
Some components (Print, for instance) can process strings and integers; 
some just a single type; on each receiving port.   


It is possible
to send more than one type of data over a channel.  
Multiple data types can also be handled 
within a struct or over multiple channels.
 
Sw versions are backward compatible within the same major 
version(currently v0).  (v0.12.2 is somewhat major, however. v0.13.4 introduced PREFIX and INCLUDE statements.)   

Sw builds a network model in memory, then optionally generates
either 
  
  * an abstract syntax tree, 
  * a linearized tree(a network definition reconstruction), 
  * a GraphViz .dot file, 
  * input to swproject.sh to build a complete working project tree, 
  * or Go source code from the network model.

C and other languages could also be generated, but this has not been implemented.
JavaFBP is also possible.   

Comments and critiques are welcome.    Contributors are encouraged.  

Please do not submit code before contacting the project.  Contact by 
e-mailing streamwork@twyoung.com  is preferred to posting a request on Github .     

QuickStart (on Linux) 
----------
  
### Comments  
  
  * Graphviz should be installed, but installation may proceed
    without it.
  * The ...github/tyoung3/StreamWork backend is no longer required.  
  * StreamWork is written in C. 
  
### Installation   
  * cd to any convenient workspace (/usr/src for example).
  * Download the latest sw-0.15.2.tar.gz file 
	  from https://github.com/tyoung3/sw
  * Run 'tar -xzf .../sw-...tar.gz' to extract source files
  * cd  sw-0.15.2
  * Run ./configure && make check
  * Run sudo make install.  
	  Sw and associated scripts will be installed in /usr/local/bin
	  
### Post Install 
   
#### Foo Bar test
	 
  * echo "(Foo) <- (Bar);" | sw > /tmp/fb.go 

  * Run: go run /tmp/fb.go

```
OUTPUT: 

Foo Bar-1
Foo Bar-2
Foo Bar-3
Foo Bar-4
Foo Bar-5
Foo Bar-6
Foo Bar-7
```

#### Generate a project
Try: swproject.sh g nds/postage

#### sw.sh Synopsis
```
sw.sh-1.0.1 USAGE: 
		b|build		. Build project with Autotools.
		c		. Make check
		cl       	. Show release check list. 
		d  [OPTs]	. Switch to docker container. 
		e		. Exit SW shell.
		d build [OPTs]	. Build SWdemo docker container. 
		doc		. Run and browse Doxygen 
		j		. Graph collate.sw with swgraph
		jl		. Generate and view locusts.png 
		p  [NAME..]	. Generate project(s) named NAME... 
		poc		. Build and run Proof of Concept 
		rm		. View README in /opt/google/chrome/chrome 
		rc		. Build and run Collate program 
		rl		. Run locusts program
		s		. Enter SW shell.  'e' to exit the shell. 
		v		. Display this script version
		x		. Edit this script
		--help	. Display this help
```		


## Building on Linux

  * Install ctags, libyaml-dev, bnfc, bison, and flex 
  * cd to go workspace (like $GOPATH/src )
  * git clone https://github.com/tyoung3/sw.git
  * ./sw.sh build;  # Runs autotools including ./configure. 
  * make check

Release Notes
=============

0.15.0
------
  * Implemented autotools
  
0.15.1
------
  * Fixed  Autotools(make distcheck) 
  * Created mktest.sh to build sw.test script  
  
0.15.2
------
  * Added exit(0) on '--help' option.
  * Updated  docs.
  * Fixed some script bugs
  
SW Language Notes
--------------------

The Streamwork network definition language, SW, is an unambiguous, context free grammar, making it 
directly interpretable, without preprocessing. 

You can find the StreamWork language description at .../docs/SW.pdf. 

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
	
to produce: 

Match0 Int: 5
Match0 Int: 7
Match0 Int: 9
Match0 Int: 11
Match0 Int: 17
Match0 Int: 23

``` 

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

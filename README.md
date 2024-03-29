# STREAMWORK -- SW-0.28.8 


Copyright (C) 2019,2020,2021,2022 Thomas W. Young, sw@twyoung.com 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file or its derivitaves except in compliance with the License.
You may obtain a copy of the License  at

[Apache License](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

All files in this repo are included in this license.

<!-- https://phrase.com/blog/posts/internationalization-i18n-go/ -->
 
![StreamWork Logo](http://sw.twyoung.com/images/StreamWork.svg)

## StreamWork
         
   Go language code generator.
         
[![CodeQL](https://github.com/tyoung3/sw/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/tyoung3/sw/actions/workflows/codeql-analysis.yml)
[![Go Report Card](https://goreportcard.com/badge/github.com/tyoung3/sw)](https://goreportcard.com/report/github.com/tyoung3/sw)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Contents
 * [Description](#description)
   * [Synopsis](#synopsis)
 * [Return code](#returncode)
 * [**_TestSWL_** program](#testswl) 
 * [Network Definition](#networkdefinition)
   * [Network Definition Files](#networkfiles)
 * [QuickStart on Linux](#quickstart) 
    * [Requirements](#requirements)  
    * [Installation](#installation)   
    * [Post Install](#postinstall) 
    * [Foo Bar test](#foobartest)
  * [Building on Linux](#buildingonlinux)
  * [StreamWork Language(SWL) Notes](#swlnotes)
      * [Stream types and component arguments](#streamtypes)
      * [Variables](#variables)
      * [Semi-colon commentary](#semicolons)
      * [Left Arrow comments](#leftarrow)
    * [Collate/Merge Example](#collatemerge)
  * [Bash Scripts](#bashscripts)
    * [Hello World](#helloworld)   
    * [**_swgo_** script](#swgo)
    * [**_swgraph_** Script](#swgraph)
    * [**_gofbp_ script**](#gofbpscript)
      * [gofbp Example](#gofbpexample)
        * [LOADBAL.SW](#loadbal)
    * [Generate a project](#generateaproject)
      * [**_sw.sh_** Synopsis](#synopsis)
  * [BUGS](#bugs)
  * [Home Page](#homepage)    
  * [Release Notes](#releasenotes)
  * [Author](#author)
  
## Description<a name="description"/>

StreamWork is a simple system for building complex programs. 

StreamWork can generate and test a complete Golang project from a simple
text file. It can also create a nice graph showing the components and 
their connections.

By default, StreamWork reads, parses, and analyzes; a simple 
SWL language StreamWork network definition(ND) file,  
then generates a main Go program.

Options allow you to produce an abstract syntax tree, a GraphViz dot file,  or a goFBP main prgram instead.


### Synopsis<a name="synopsis"/>

**_sw_** [-m MODE] [-cfg CONFIGURATION_FILE] [-d DEFAULT_PATH] [ SW_FILE ]

**_sw_** -v

**_sw_** --help 

If SW_FILE is omitted, **_sw_**  will read from stdin.

```	 
		MODE= 
			0-GOMODE		. Generate a main SW Go program[DEFAULT].
			1-ASTMODE		. Display the Abstract Syntax Tree 
			2-GENTREE		. Display the Linearized tree
			3-GRAPHMODE		. Generate Graphviz .dot file code
			4-JAVAFBP		. Incomplete and untested. Looking for help.
			5-PROJECT		. Generate **_swgen.sh_** code for a project tree.
			7-CMODE			. Incomplete and untested. Looking for help.
			8-GENGOFBP      . Generate main go code for J. P. Morrison's gofbp. 
```

## Return code<a name="returncode"/>
**_sw_** returns SUCCESS unless it encounters an error, in which case **_sw_** returns FAILURE.
See package documention for component return codes. 

## **_TestSWL_** program<a name="testswl"/> 
**_TestSWL_** syntax checks stdin or a SteamWork network definition file or a SteamWork configuration file.
### synopsis<a name="testswlsynopsis"/>

```
    usage: Call with one of the following argument combinations:
	--help		Display this help message.
	(no arguments)	Parse stdin verbosely.
	(files)		Parse content of files verbosely.
	-s (files)	Silent mode. Parse content of files silently.
```

## Network Definition <a name="networkdefinition"/>

A StreamWork network definition describes a program as a  list of data streams.
Each data stream consists of a source process, a director, and a sink process. 
The network definition is a compact text-based representation of a data flow diagram. 

StreamWork is concerned primarily with Go language FBP programs,
however, the network definition described here is language agnostic.  It is quite possible 
to generate corresponding code in other languages from a StreamWork ND.         

The script, **_swgo_**, reads and executes a network definition employing **_sw_** to properly launch and connect the processes.  By default, **_sw_** generates 
and builds a single main Go program which:  
  * imports sw compatible component package(s) as specified in the network definition,  
  * launches a goroutine for each process,  
  * connects these processes via Golang interface channels, and 
  * waits for all processes to finish.  
  * Once the processes launched, StreamWork has no subsequent
   interaction with them.

On option, **_sw_** will read, parse and interpret a network definition file then  create either a:
 
 * a StreamWork Go main program,
 * a gofbp      Go main program (see github.com/jpaulm/gofbp), 
 * a GraphViz   .dot file(script,( **_swgraph_** will create and display a graph(s) directly)
 * a bash script, (**_swproject_** generates a complete GO language project tree and 
 	 tests it)
 * an abstract syntax tree (a reverse polish notation rendition of the essential language components), 
    OR
 * a linearized tree (a network definition reconstruction).   

### Network Definition Files<a name="networkfiles"/>

A network definition file (in the SWL language[see below]) consists of a list of 
streams(aka dataflows); and may also contain subnet definitions, 
INCLUDE and PREFIX statements, and comments.  

INCLUDEd files are also network definitions which may in turn contain
INCLUDE statements.  Exceeding 100 levels of includes will 
cause program termination.

A stream definition looks something like:

```
(a C "ARG..." ) -ipType> (b D);
     or [reversing direction and using default component names]
(E)IN <- OUT.1(F)0 <- (G); 
```

![Figure 1](http://sw.twyoung.com/images/fig1.svg)
and consists of a list of streams.  Each stream consists of 
a source process, a stream director, a sink process and a terminating semicolon(;).   Each process consists of


  * a processname
  * optional component identifier 
  * optional string arguments, and 
  * optional process attributes [surrounded by brackets].  Attributes
    consist  of KEY=STRING|NUMBER statements, used mainly to enhance
    graphic images.
   
all surrounded by parens, and followed and/or preceded by optional 
port identifiers consisting of a port number preceded by an optional port name and period(.).  Omitted port identifiers default to zero(0).

The stream director points from the source process to the sink process.  A director may 
include a type identifier and/or a stream buffer size: e.g. "<type_A 10-"  or "-type_B 2>".  If not included, buffer size defaults to zero.

Example with anonymous process names and default components:

```
  (_) -int 3> (_); #[integer stream with buffersize of three]; 
```

![Figure 2](http://sw.twyoung.com/images/fig2.svg)
In this example, the default components [as specified in a config file, send their process names to the channel or to stdout: 

```
    (Hello) <- (World); 
```

produces:

```
Hello World
``` 

A process is defined by its process name, its component identifier, component arguments,
and process attributes; all surrounded by parens.   
The component identifier, arguments, and attributes will default if omitted. 
Process names are not apparent to Go and so need not follow Go naming 
rules, just the StreamWork conventions. 

A component identifier consists of its import module/package identifier, 
a slash, '/', and the component name.  Go component names need to be capitalized.
If  the path is omitted,  a configuration default path is assumed.  
If the component name is also omitted, configuration default component names
are assumed for sink, source, and filter(has both inputs and outputs) processes.
Subnet components are identified by ```'``` prefixing its identifier, as in
(A ^SubnetName) ...
 
Stream directors consist of ```<```, an optional, comma-separated list of type identifiers,
an optional buffersize integer, and ```-```. Example: ```<100-```
The reverse (Ex: `-myDataType,yourType 100>`) is also valid.
 
Information packets(IPs) are designed as nil(empty) interfaces.  The
data type is determined by the sending component.  It is possible for 
properly coded sink components to handle multiple data types.
A type mis-match will be reported by incompatible receiving 
components.  Components can be coded to handle any
type, including user-defined types and structures. 
Some components  can process strings and integers; 
other components just a single type; on each receiving port.   
 
**_sw_** versions beginning with v1.0.0 are backward compatible within the same major 
version(currently v0).  There is no such guarantee with v0.N.N versions, but we will
increase the minor version in such cases.  The master github branch may have many commits without creating a new version.  

**_sw_** builds a network model in memory, then optionally generates
either 
  
  * an abstract syntax tree, 
  * a linearized tree(a network definition reconstruction), 
  * a GraphViz .dot file, 
  * input to **_swproject_** to build a complete working project tree, 
  * or Go source code from the network model.
  * or Go main source code for JFM's gofbp. 

C and other languages could also be generated, but this has not been implemented.
JavaFBP is possible, for instance.   

Comments and critiques are welcome.    Contributors are encouraged.  

Please do not submit code before contacting the project.  Contact by 
e-mailing streamwork@twyoung.com or Discord/gofbp message is preferred to posting a request on Github.     

## QuickStart on Linux<a name="quickstart"/> 
  
### Requirements<a name="requirements"/>  
  * Gcc, etc.
  * Graphviz should be installed, but installation may proceed
    without it.
  * The ...github/tyoung3/StreamWork backend is no longer required.  
  * **_sw_** is written in C. 
  
### Installation<a name="installation"/>   
  * cd to any convenient workspace (/usr/local/src for example).
  * Download the latest sw-0.28.0.tar.gz file 
	  from https://github.com/tyoung3/sw/build
  * Run 'tar -xzf .../sw-0.28.0.tar.gz' to extract source files
  * cd  sw-0.28.0
  * Run ./configure && make check
  * Run sudo make install.  
	  **_sw_** and associated scripts will be installed in /usr/local/bin
	  
### Post Install<a name="postinstall"/>
   
#### Foo Bar test<a name="foobartest"/>

  mkdir /tmp/x/	 
  * **_echo_** "(Foo) <- (Bar);" | **_sw_** > /tmp/x/fb.go 
  
  **_cd_** /tmp/x/
  **_go_** mod tidy 

  * Run: **_go_** run /tmp/fb.go
  
  This is what the **_swgo_** script does: 
  try  **_swgo_** .../nds/fb.sw  
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


## Building on Linux<a name="buildingonlinux"/>

  * Install autotools, ctags, libyaml-dev, bnfc, bison, and flex 
  * cd to your project workspace (like /usr/local/src )
  * git clone https://github.com/tyoung3/sw.git
  * bin/sw.sh build;  # Runs autotools including .../sw/bin/configure. 
  * bin/sw.sh c;      # Runs make check in .../sw/src
  * bin/sw.sh bw;     # Builds Windows/sw.exe.  Requires mingw.  Run make distclean first.

## StreamWork Language(SWL) Notes<a name="swlnotes"/>

SWL is an unambiguous, context free grammar, making it directly interpretable, without preprocessing. 

See the bnfc StreamWork language description file, SWL.pdf. 

SWL has few reserved words,  making it somewhat natural language
agnostic.   

Every effort is made to ensure that all currently valid SWL
statements will remain valid.  Should 
this prove impractible,  the minor version will be incremented.
Once v1.0.0 is reached, the major version will be incremented instead.
Backward conpatibility is enforced for network definition files,
**_sw_**, and published Go modules only.  

Linux scripts and Go modules, are separately versioned.  

#### Stream types and component arguments<a name="streamtypes"/>
Stream channels can be any Go language type: int, string, struct, 
or interface.  '_' is shorthand for an interface channel type.   
Components with channels of varying types, should group 
types to simplify their entry points. 
 
Autojoin and autosplit work only with interface types.

While StreamWork packages a number of components, none of them
are required.  It is quite possible to define a network with no 
dependencies (other than Go packages) at all.  
The only requirement for a component is 
an entry point with two or more parameters: wait group, argument string 
slice, and a channel for each port. 

#### Variables<a name="varaibles"/>
SWL accepts string($NAME), environment string($_NAME), symbol(&NAME),  and numeric(%NAME) variables.  See SWL.pdf for acceptable usage.

StreamWork uses the following environment variables:
  * $BROWSER -- WWW browser 
  * $GOPATH  -- Go language path
  * $DEBUG   -- 'Y' will cause some messages to print.
    
#### Semi-colons<a name="semicolons"/>
Statements in SWL, are terminated with a semi-colon.  Semi-colons in code are like 
periods at the end of English statements -- 
they tell the reader (and the SWL interpreter) when
you have reached the end of a statement. This makes reading the statements easier. 
Imagine trying to read a book without any periods (or initial capitals). 
Additionally, without semi-colons line breaks become part of the language 
definition, leading to awkward, confusing syntax rules; difficult for the
reader to interpret.  

#### Left Arrow comments<a name="leftarrow"/>
The, ```<-```,  token is employed in order to be consistent with its 
usage in the Go language.  The ```->``` token is also available:
"(A) -> (B)1 <- (C);"  is valid SWL.   

### Collate/Merge Example<a name="collatemerge"/>

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

## Hello World<a name="helloworld"/>


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

produces 

![/tmp/collate.svg](http://sw.twyoung.com/images/collate.svg)
an image of the collate 
network.  

## Bash Scripts<a name="bashscripts"/>
### **_swgo_** script<a name="swgo"/>
The bash script, **_swgo_**, will generate and run a GO program from a network definition:

```
  .../nds/hw.sw
(Hello) <string- (World);
```

**_swgo_** .../nds/hw
produces:

```

package main

/*
                  StreamWork Go code. 
	Generated by sw/swgo.c-0.22.0 Wed Mar 16 14:48:30 2022
	from Network file: /usr/local/src/sw/src/nds/hw.sw
	Configuration file: /usr/local/src/sw/src/nds/sw.cfg
            ***  Expanded Network Definition  ***
(Hello sw.Print ) 		<_-	0(World sw.Gens);	
1 stream, 2 processes, 2 components, 1 partition, 0 cycles.
*/

import "sync"
import "github.com/tyoung3/sw"


func main() {
var wg sync.WaitGroup

cs0 := make(chan interface{},0)	//World.0->Hello.0

	wg.Add(1)

var cp1 []chan interface{}
cp1=append(cp1,cs0)
go	sw.Gens(&wg,[]string{"World"},cp1) // World

var cp2 []chan interface{}
cp2=append(cp2,cs0)
go	sw.Print(&wg,[]string{"Hello"},cp2) // Hello

wg.Wait()
}


Which in turn produces:

Hello World-1
Hello World-2
Hello World-3
Hello World-4
Hello World-5
Hello World-6
```

### **_swgraph_** Script<a name="swgraph"/>

Another bash script, **_swgraph_**, will display a graphic image of a network definition:
   
```
    .../nds/mvc.sw
(m Model)1      -change>         (v View);
(c)2            -update>        1(v);
(v)2            -event>          (c Control); 
(c)1            -request>       (m);
```

**_swgraph_** .../nds/mvc
produces: 

![Model/View/Control image](http://sw.twyoung.com/images/mvc.jpg)
for instance.
Processes are colored such that all components in the same package have the same color.
Not shown here, unfortunately, are the tooltips and html references.  Arrows are colored according to stream buffersize: 0 - black; 1-green; 2 or more - orange.   Coloring rules 
are not guaranteed to remain unchanged in future sw versions. 
**WARNING:** buffersize is related to deadlock potential in cyclic networks.

The resulting image is an annotated Data Flow Diagram.

### **_gofbp_ script**<a name="gofbpscript"/> 
**_gofbp_** produces and runs a gofbp program 
(see [github.com/jpaulm/gofbp](https://github.com/jpaulm/gofbp)  )
from a StreamWork net definition file.

#### gofbp Example (from sw/src/model/tests/gofbp/loadbal.sw)<a name="gofbpexample"/>

##### Given: LOADBAL.SW<a name="loadbal"/>

```
$core = "github.com/jpaulm/gofbp/core";
$trtn = "github.com/jpaulm/gofbp/components/testrtn";
(Sender $trtn/Sender "10 COUNT=10")OUT	-load> IN.0(LoadBalance $trtn/LoadBalance );
(LoadBalance)OUT.1 -load> IN(Receiver0 $trtn/DelayedReceiver);
(LoadBalance)OUT.2 -load> IN(Receiver1 $trtn/Receiver);
(LoadBalance)OUT.3 -load> IN(Receiver2 $trtn/Receiver);
```

`gofbp -b loadbal`
<p>produces </p>

![a graphic image of loadbal.sw](http://sw.twyoung.com/images/loadbal.svg)
and (on console)

```
Input to Receiver: Receiver1 > IP - # 1
Input to Receiver: Receiver1 > IP - # 4
Input to Receiver: Receiver1 > IP - # 6
Input to Receiver: Receiver1 > IP - # 8
Input to Receiver: Receiver2 > IP - # 0
Input to Receiver: Receiver2 > IP - # 3
Input to Receiver: Receiver2 > IP - # 7
Input to DelayedReceiver: Receiver0 > IP - # 2
Input to DelayedReceiver: Receiver0 > IP - # 5
Input to DelayedReceiver: Receiver0 > IP - # 9
```

### Generate a project<a name="generateaproject"/>
**_swproject_** -yaml YAML  -cfg ./src/nds/postage.cfg ./src/model/tests/postage.sw

produces the following source tree:

```
├── cmd
│   └── postage.go
├── ComputePostage.go
├── ComputePostage_test.go
├── config.go
├── GetLoc.go
├── GetLoc_test.go
├── GetWeight.go
├── GetWeight_test.go
├── go.mod
├── go.sum
├── internal
│   ├── gen.sh
│   ├── postage.sw
│   └── sw.cfg
├── ipT.go
├── PostageT.go
├── postage.yaml
├── PrintLabel.go
├── PrintLabel_test.go
├── Rates.go
├── Rates_test.go
├── RateT.go
├── testdata
│   └── README
└── WeighT.go

3 directories, 23 files

```

then produces this graph 
![postage.svg](http://sw.twyoung.com/images/postage.svg)
vets the code, and finally runs it.
The result is a running program ready for your enhancements.

#### **_sw.sh_** Synopsis<a name="sw.sh"/>

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

## BUGS:<a name="bugs"/>

**_sw.Gen_** fails unless all three arguments are present.

Stream directors like => and <= are accepted, but treated the same
as -> and <-, except for appearing differently in graphs.  
The meaning is reserved for future use, which could 
break existing networks.
	 
	 
### Fixed	 
[Fixed with v0.28.7] Subnet process names must be unique, 
but this is not guaranteed.  Using the same process name in different
subnet definitions will no longer cause 
unpredictable, negative consequences.

## Home Page<a name="homepage"/>

(https://sw.twyoung.com)
## Release Notes<a name="releasnotes"/>

### 0.18.0
  * Reorganized repo tree structure 
  * Renamed package swbase to sw and moved code to repo root
  * Changed package swutility to import package sw
  
### 0.18.4
  * Fixes for restructure problems
  * Fixes to bash scripts 
  * Fixes to githup builds   
  
### 0.18.5
  * More fixes
  * Moved .../sw/c to .../sw/src
  
### 0.18.6
  * Created gofbp script  
  * Added sw/testrtn package
  
### 0.18.7
  * Moved build process to project tree root
  
### 0.18.8
  * Fixed count in swbal.sw
  
### 0.18.9
  * Fix testrtn/Sender
  
### 0.19.0 
  * Many fixes to **_swproject_** script     
  
### 0.20.1
  * Fix swgraph file search    
  
### 0.20.6
  * Incorporate component attributes in SWL for future graphing enhancements.
  * Fix fan logic when connection is missing. 
    
### 0.20.7
  * Improve gofbp script
  * Update README

### 0.20.8 
  * Created fileio package with GetFile and PutFile and FileT 
    
### 0.20.10
  * Provide process attributes.  
  
### 0.21.0 
  * Can generate projects with or without YAML configurationswpro. 
  * Fixes to Wrap function.  
  
### 0.21.1
  * README updates  
  * Updated SWL.pdf
  
### 0.22.0
  * Go code generation revamped
  * Typed channels partly implemented, possibly breaking networks
    with types specified in a director. 
      
### 0.26.6
  * Fixed double arrow graph error      
  
### 0.26.7
  * Introduced mkdocs
  * Attempt to fix go.in yaml  Dependabot alert
  * Fix build error in swgraph.cswpro
  
### 0.26.8
  * Removed 'default:' error from swgraph.c 
  
## 0.26.9
  * Fixed bug with subnet attributes  
  
## 0.26.10
  * Fixed maximum subnet level checking
  * Introducted mkdocs web site docs
  
## 0.26.11
  * Changed type mismatches from FAILing to WARNING.   
  
## 0.27.0 
  * Changed package name from sw/linux to sw/os
  * Added sw/os/Debug function   
  
## 0.28.0 
  * Implemented typing of component channels. 
  * Defined underscore '_' as shorthand for 'interface{}' type.
  * Changed component argument from interface slice to interface in SW components with a single port. 
  * For components with multiple ports; adjacent channels of the same   
    type are combined into a channel slice.     
  * Fixed numerous problems with swproject. 
  
## 0.28.1
   * Fixed IP type bugs
   * Updated docs  
   
## 0.28.2
	* Fixed subnet expansion bugs   
	
## 0.28.3
    * Fix project generation i/o bug	
    
## 0.28.4
    * More project generation fixes	
    
## 0.28.6
    * Fix cfg initialization
    * Check Wextra warnings.
    * Remove some dead code    
    
## 0.28.7
    * Prefix subnet process names to make them unique.    
  
## 0.28.8 
    * Fix go.mod yaml.v3 dependency failure -- 'require stretch..v1.1
    * Point package names to github.com.../sw
    * Use src/model/sw not bin/sw(removed) in sw.sh/run script
      
## Author<a name="author"/>

    Tom Young, streamwork@twyoung.com
    
    with thanks to J. Paul Morrison, Phillip W. Young, Sam Watkins, 
    the contributors to flow-based-programming@googlegroups.com, 
    and to the developers/maintainers of Go, gcc, Linux/Ubuntu, 
    BNFC, git, GraphViz, Github and others. 

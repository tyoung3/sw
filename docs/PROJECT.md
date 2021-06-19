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



# Generate a Project

## Description

Generate project files from a network definition file.
Build and run the executable. 



## QuickStart (on Linux) 

Install go 

Install sw at $HOME/go/src/github.com/tyoung3/sw 

Change sw.cfg to fit your environment. 
Run sw.sh c go build and make sw (if necessary).



## Example

sw.sh p project/test/X Y Z


### OUTPUT: 

Generated module at $GOPATH/mod with packages and 
component stubs for all components referenced in the network definition file(X.SW file).
```
X
│   ├── sw.tmpl
│   ├── X
│   ├── X.go
│   └── X.sw
├── X.yaml
├── Y
│   ├── Comp1.go
│   ├── Comp1_test.go
│   ├── Comp2.go
│   ├── Comp2_test.go
│   ├── Comp3.go
│   └── Comp3_test.go
└── Z
    ├── Comp1.go
    ├── Comp1_test.go
    ├── Comp2.go
    ├── Comp2_test.go
    ├── Comp3.go
    └── Comp3_test.go

```
Executable program at X/X (package main) 


#### EXECUTABLE OUTPUT:
```
Module:X Pkg:Z Running C - Comp3 v0.0.0 bs = 1 seqno:  1234 
Module:X Pkg:Y Running A - Comp1 v0.0.0 bs = 1 seqno:  1234 
C chan: 1 IP: 38
Module:X Pkg:Z Running B - Comp2 v0.0.0 bs = 1 seqno:  1234 
B chan: 0 IP: 37
C chan: 0 IP: 1

```

## Environment Variables

DEBUG   y)issue yellow debug messages 
	n) No debug messages.
	

### Add a component/package to a module:

swgen.sh  gs MODULE PACKAGE CONFIG_TYPE INPORTS OUTPORTS COMPNAME [ARG VAL]...

Ex.
   swgen.sh gs X pkg_a YAML 2 3 a_Comp4 arg1 var1 

```
Output: 

X
├── config.go
├── go.mod
├── go.sum
├── internal
│   ├── sw.cfg
│   ├── sw.tmpl
│   ├── X
│   ├── X.go
│   └── X.sw
├── pkg_a
│   ├── a_Comp4.go
│   └── a_Comp4_test.go
├── X.yaml
├── Y
│   ├── Comp1.go
│   ├── Comp1_test.go
│   ├── Comp2.go
│   ├── Comp2_test.go
│   ├── Comp3.go
│   └── Comp3_test.go
└── Z
    ├── Comp1.go
    ├── Comp1_test.go
    ├── Comp2.go
    ├── Comp2_test.go
    ├── Comp3.go
    └── Comp3_test.go
```

4 directories, 23 files


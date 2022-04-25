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

Install sw: go get github.com/tyoung3/sw 

Change sw.cfg to fit your environment. 
Run sw.sh c go build and make sw (if necessary).

## Example

swproject -yaml YAML  -cfg ./src/nds/postage.cfg ./src/model/tests/postage.sw

### OUTPUT: 

Generated module at /usr/local/src/ with packages and 
component stubs for all components referenced in the network definition file(postage.sw file).
```
postage
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
│   ├── postage.go
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
└── WeighT.go

1 directory, 22 files

```
Executable program: .../postage/internal/postage.go (package main) 


#### EXECUTABLE OUTPUT:
```
BUGGY: Work in progress
```

## Environment Variables

DEBUG   y)issue yellow debug messages 
				n)No debug messages.
	

### Add a component/package to a module:

swgen.sh  gs MODULE PACKAGE CONFIG_TYPE  COMPNAME [ARG VAL]... [PORT..]
	PORT =  -i OR -O  TYPE
  TYPE = valid Golang type or underscore(_). 
  Underscore is short for interface{}

Ex.
   swgen.sh gs postage postage YAML ComputePostage -i _ -i _ -i WeighT -i RateT -o PostageT


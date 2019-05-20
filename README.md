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

STREAMWORK/FrontEnd
===================

Name
----

         StreamWork - a flow based program(FBP) Go language framework.
         

Description
-----------

StreamWork is a proof-of-concept for a Go language flow-based system 
which reads and executes a StreamWork network definition(NEMOD).

The current NEMOD is defined as a list of Flows.  Each Flow consists 
of a a sink process, a sink port number, "<->", a source portnumber, and   source process.  Ex.  

    (In strings.Print1)0 <- 0(Out strings.Gen1);

The IPs are designed as nil(empty) interfaces to be filled by the source components.    

This frontend has is extremely limited to just enough to provide the  
proof-of-concept.


Everything here(including the project name) is subject to change.  
Versions will be backward compatible within the same major version. 
Ex. your code depending on v0.0.1 will still work on v0.8.7, but may fail on v1.0.0.  
Streamwork is developed using the Go module facility, so that dependencies are clear.   

Contributors are encouraged.  Comments are particularly welcome.   
Please do not submit code before contacting the project by e-mailing streamwork@twyoung.com.     

QuickStart (on Linux) 
----------
	* Install StreamWork backend from github.  (Requires Go installation.)
	* Download 'sw' from github to any convenient location.
	* Run 'chmod a+x sw'
	* Run 'echo "(Sink strings.Print1)0 <- 0(Source strings.Gen1); " | ./sw ' 	> /tmp/main.go 
	* Run 'go run /tmp/main.go

OUTPUT: 
```	
	StreamWork Proof of Concept Example.
Sink Source-1
Sink Source-2
Sink Source-3
Sink Source-4
Sink Source-5
Sink Source-6
Sink Source-7
```

Author
------

    Tom Young, streamwork@twyoung.com

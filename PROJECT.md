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

Generate a Project
==============================

Description
-----------

Generate project files from .sw file 



QuickStart (on Linux) 
----------


Example
-------

sw.sh p X.sh Y X 

```	
PROJECT_NAME=ex1
mkdir ~/go/mod/$PROJECT_NAME || Die .
cd ~/go/mod/$PROJECT_NAME 
cat <<- EOF > ${PROJECT_NAME}.sw
sw -proj ${PROJECT_NAME}.sw
```

OUTPUT: 

```
Working program and graph
```



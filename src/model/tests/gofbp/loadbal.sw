#!/usr/local/src/sw/bin/gofbp

{#
Copyright (C) 2022 Thomas W. Young, sw@twyoung.com 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file or its derivitaves except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
#}

$core = "github.com/jpaulm/gofbp/core";
$trtn = "github.com/jpaulm/gofbp/components/testrtn";
(Sender $trtn/Sender "10 COUNT=10")OUT	-load> IN.0(LoadBalance $trtn/LoadBalance );
(LoadBalance)OUT.1 -load> IN(Receiver0 $trtn/DelayedReceiver);
(LoadBalance)OUT.2 -load> IN(Receiver1 $trtn/Receiver);
(LoadBalance)OUT.3 -load> IN(Receiver2 $trtn/Receiver);

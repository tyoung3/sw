#!/usr/local/bin/sw -8 $*   

$core = "github.com/jpaulm/core";
$trtn = "github.com/jpaulm/Components/testrtn";


(Sender $trtn/Sender "COUNT=40")OUT	-load> IN.0(LoadBalance $trtn/LoadBalance );
(LoadBalance)OUT.1 -load> IN(Receiver0 $trtn/DelayedReceiver);
(LoadBalance)OUT.2 -load> IN(Receiver1 $trtn/Receiver);
(LoadBalance)OUT.3 -load> IN(Receiver2 $trtn/Receiver);

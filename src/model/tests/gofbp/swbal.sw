#!/usr/src/sw/bin/swgo
$core = "github.com/tyoung3/sw";
$trtn = "github.com/tyoung3/sw/gofbp";
(Sender $trtn/Sender "COUNT=10")OUT	-load> IN.0(LoadBalance $trtn/LoadBalance );
(LoadBalance)OUT.1 -load> IN(Receiver0 $trtn/DelayedReceiver);
(LoadBalance)OUT.2 -load> IN(Receiver1 $trtn/Receiver);
(LoadBalance)OUT.3 -load> IN(Receiver2 $trtn/Receiver);
